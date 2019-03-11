#include "pch.h"
#include <iostream>
#include <fstream>
#if RELEASE
#include <Python.h>
//#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>
#endif
#include <chrono>
#include <iomanip>
#include <stdlib.h>
#include "math.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/types_c.h>
#include "opencvmex.hpp"

#include "rt_nonfinite.h"
#include "Threshold.h"
#include "Threshold_terminate.h"
#include "Threshold_emxAPI.h"
#include "Threshold_initialize.h"
using namespace cv;
using namespace std;
//Adaptive Integral threshold
//Code retrieved from https://github.com/phryniszak/AdaptiveIntegralThresholding/blob/master/main.cpp
void threshold_integral(Mat &input_mat, Mat &output_mat)
{
	// accept only char type matrices
	CV_Assert(!input_mat.empty());
	CV_Assert(input_mat.depth() == CV_8U);
	CV_Assert(input_mat.channels() == 1);
	CV_Assert(!output_mat.empty());
	CV_Assert(output_mat.depth() == CV_8U);
	CV_Assert(output_mat.channels() == 1);

	// rows -> height -> y
	auto nRows = input_mat.rows;
	// cols -> width -> x
	auto nCols = input_mat.cols;

	// create the integral image
	cv::Mat sum_mat;
	cv::integral(input_mat, sum_mat);

	CV_Assert(sum_mat.depth() == CV_32S);
	CV_Assert(sizeof(int) == 4);

	const auto s = MAX(nRows, nCols) / 8;
	const auto t = 0.15;

	// perform thresholding
	const auto s2 = s / 2;

	for (auto i = 0; i < nRows; ++i)
	{
		auto y1 = i - s2;
		auto y2 = i + s2;

		if (y1 < 0) {
			y1 = 0;
		}
		if (y2 >= nRows) {
			y2 = nRows - 1;
		}

		const auto p_y1 = sum_mat.ptr<int>(y1);
		const auto p_y2 = sum_mat.ptr<int>(y2);
		const auto p_input_mat = input_mat.ptr<uchar>(i);
		const auto p_output_mat = output_mat.ptr<uchar>(i);

		for (auto j = 0; j < nCols; ++j)
		{
			// set the SxS region
			auto x1 = j - s2;
			auto x2 = j + s2;

			if (x1 < 0) {
				x1 = 0;
			}
			if (x2 >= nCols) {
				x2 = nCols - 1;
			}

			const auto count = (x2 - x1) * (y2 - y1);

			// I(x,y)=s(x2,y2)-s(x1,y2)-s(x2,y1)+s(x1,x1)
			const auto sum = p_y2[x2] - p_y1[x2] - p_y2[x1] + p_y1[x1];

			if (static_cast<int>(p_input_mat[j] * count) < static_cast<int>(sum * (1.0 - t)))
				p_output_mat[j] = 255;
			else
				p_output_mat[j] = 0;
		}
	}
}
#if RELEASE
PyObject *pName, *pModule, *pFunc, *pArgs, *pValue, *img, *blockSize, *method, *param, *offSet, *thresholdedImg, *ArgsArray;
int pythonWrapper()
{
	Py_Initialize();

	//Importing python script
	const char * programName = "LocalThreshold";
	pName = PyUnicode_DecodeFSDefault(programName);
	pModule = PyImport_Import(pName);

	//const char *filename = "2mmBrinell250_31.400_-1.000.tif";
	const char *filename = "t19452-09_27.100_-87.700.tif";
	const char *methodName = "adaptThres";

	if (pModule != NULL)
	{
		//Defining the python function to use
		pFunc = PyObject_GetAttrString(pModule, methodName);
		//Defining the number of arguments of that function
		pArgs = PyTuple_New(5);

		//Reading the image 
		cv::Mat mat = cv::imread(filename, IMREAD_UNCHANGED);

		//...
		//Image processing before adaptive thresholding
		//...

		import_array();//this function call is important if we want to send a pyArray to the python function as a parameter


		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		//Converting Mat object to a regular 2d array (probably there is a simpler way to do this)
		int NumRows = mat.rows;
		int NumCols = mat.cols;

		std::vector<double> array;
		if (mat.isContinuous())
		{
			array.assign(mat.datastart, mat.dataend);
		}
		else
		{
			for (int i = 0; i < mat.rows; ++i)
			{
				array.insert(array.end(), mat.ptr<double>(i), mat.ptr<double>(i) + mat.cols);
			}
		}

		double** a = new double*[NumRows];
		for (int i = 0; i < NumRows; ++i)
			a[i] = new double[NumCols];

		int k = 0;
		for (size_t i = 0; i < NumRows; i++)
		{
			for (size_t j = 0; j < NumCols; j++)
			{
				a[i][j] = array[k++];
			}
		}

		//End of conversion from Mat to 2d array of int
		npy_intp mdim[] = { NumRows, NumCols };

		// PyArray_SimpleNew allocates the memory needed for the array.
		ArgsArray = PyArray_SimpleNew(2, mdim, NPY_DOUBLE);

		// The pointer to the array data is accessed using PyArray_DATA()
		double* p = (double*)PyArray_DATA(ArgsArray);

		// Copy the data from the "array of arrays" to the contiguous numpy array.
		for (int k = 0; k < NumRows; ++k)
		{
			memcpy(p, a[k], sizeof(double) * NumCols);
			p += NumCols;
		}

		//Defining all the arguments of the python function
		PyTuple_SetItem(pArgs, 0, ArgsArray);
		int block_size = 201;
		blockSize = PyLong_FromLong(block_size);
		PyTuple_SetItem(pArgs, 1, blockSize);
		const char *adptativeThresMethod = "gaussian";
		method = PyUnicode_FromString(adptativeThresMethod);
		PyTuple_SetItem(pArgs, 2, method);
		int param_val = 30;
		param = PyLong_FromLong(param_val);
		PyTuple_SetItem(pArgs, 3, param);
		int off_set = 0;
		offSet = PyLong_FromLong(off_set);
		PyTuple_SetItem(pArgs, 4, offSet);

		//Calling the python function
		pValue = PyObject_CallObject(pFunc, pArgs);
		npy_intp* dims = PyArray_DIMS(pValue);
		NumRows = dims[0];
		NumCols = dims[1];
		bool* ptr = (bool*)PyArray_DATA(pValue);
		//endResult is the 2d bool matrix resulted from calling the python threshold_local		
		bool** endResult = new bool*[NumRows];
		for (int i = 0; i < NumRows; ++i)
			endResult[i] = new bool[NumCols];
		k = 0;
		for (size_t i = 0; i < NumRows; i++)
		{
			for (size_t j = 0; j < NumCols; j++)
			{
				endResult[i][j] = ptr[k++];
			}
		}
	}
	Py_DECREF(pName);
	Py_DECREF(pArgs);
	Py_DECREF(pFunc);
	Py_DECREF(pModule);
	Py_Finalize();
	return 0;
}
#endif
double get_max(emxArray_real_T *matrix, const int num_rows, const int num_cols)
{
	auto max = DBL_MIN;
	auto k = 0;
	for (size_t i = 0; i < num_rows; i++)
	{
		for (size_t j = 0; j < num_cols; j++)
		{
			if (matrix->data[k] > max)
			{
				max = matrix->data[k];
			}
			k++;
		}
	}
	return max;
}
double get_min(emxArray_real_T *matrix, const int num_rows, const int num_cols)
{
	auto min = DBL_MAX;
	auto k = 0;
	for (size_t i = 0; i < num_rows; i++)
	{
		for (size_t j = 0; j < num_cols; j++)
		{
			if (matrix->data[k] < min)
			{
				min = matrix->data[k];
			}
			k++;
		}
	}
	return min;
}

UINT16_T get_max(emxArray_uint16_T *matrix, const int num_rows, const int num_cols)
{
	UINT16_T max = 0;
	auto k = 0;
	for (size_t i = 0; i < num_rows; i++)
	{
		for (size_t j = 0; j < num_cols; j++)
		{
			if (matrix->data[k] > max)
			{
				max = matrix->data[k];
			}
			k++;
		}
	}
	return max;
}

UINT16_T get_min(emxArray_uint16_T *matrix, const int num_rows, const int num_cols)
{
	UINT16_T min = UINT16_MAX;
	auto k = 0;
	for (size_t i = 0; i < num_rows; i++)
	{
		for (size_t j = 0; j < num_cols; j++)
		{
			if (matrix->data[k] < min)
			{
				min = matrix->data[k];
			}
			k++;
		}
	}
	return min;
}

UINT16_T get_max(UINT16_T** a, const int num_rows, const int num_cols)
{
	UINT16_T max = 0;
	for (size_t i = 0; i < num_rows; i++)
	{
		for (size_t j = 0; j < num_cols; j++)
		{
			if (a[i][j] > max)
				max = a[i][j];
		}
	}
	return max;
}

bool are_equal(Mat mat, string csvFilename) 
{
	//Parsing the csv
	ifstream data(csvFilename);
	string line;
	auto vals = new double*[mat.rows];
	for (int i = 0; i < mat.rows; ++i)
		vals[i] = new double[mat.cols];
	auto row = 0;
	auto col = 0;
	while (getline(data, line))
	{
		stringstream line_stream(line);
		string cell;
		col = 0;
		while (getline(line_stream, cell, ','))
		{
			vals[row][col++] = atof(cell.c_str());
			//Checking if width don't match
			if (col > mat.cols)
				return false;
		}
		row++;
		//Checking if height don't match
		if (row > mat.rows)
			return false;
	}
	//Transforming mat to an array
	auto array = new double*[mat.rows];
	for (auto i = 0; i < mat.rows; ++i)
		array[i] = new double[mat.cols];

	for (auto i = 0; i < mat.rows; ++i)
		array[i] = mat.ptr<double>(i);
	//Checking all the values one by one
	for (size_t i = 0; i < mat.rows; i++)
	{
		for (size_t j = 0; j < mat.cols; j++)
		{
			if (abs(array[i][j] - vals[i][j]) > 0.0000001)
				return false;
		}
	}
	return true;
}

emxArray_uint16_T* mat_to_emx_array_uint16_t(Mat mat)
{
	//Check this
	//https://www.mathworks.com/help/vision/opencv-interface-support-package.html
	//To convert types the propper way

	const auto num_rows = mat.rows;
	const auto num_cols = mat.cols;

	auto** array = new UINT16_T*[mat.rows];
	for (auto i = 0; i < mat.rows; ++i)
		array[i] = new UINT16_T[mat.cols];

	for (auto i = 0; i < mat.rows; ++i)
		array[i] = mat.ptr<UINT16_T>(i);

	const auto x = emxCreate_uint16_T(num_rows, num_cols);
	for (size_t i = 0; i < num_rows; i++)
	{
		for (size_t j = 0; j < num_cols; j++)
		{
			x->data[num_cols * i + j] = array[i][j];
		}
	}
	return x;
}

auto emx_array_real_t_to_mat(emxArray_real_T* result, const int num_rows, const int num_cols) -> Mat
{
	//Check this
	//https://www.mathworks.com/help/vision/opencv-interface-support-package.html
	//To convert types the propper way

	const auto res_array = new double[num_rows * num_cols];
	for (size_t i = 0; i < num_rows * num_cols; i++)
	{
		res_array[i] = result->data[i];
	}
	Mat res(num_rows, num_cols, CV_64F, res_array);
	std::memcpy(res.data, res_array, num_rows * num_cols * sizeof(double));
	return res;
}

//Using the Matlab to c++ generated code for the adaptive threshold
auto using_matlab_gen_code() -> void
{
	//Seting 10 decimal places to be presented when printing floating numbers
	std::cout << std::fixed;
	std::cout << std::setprecision(10);
	//const char *filename = "2mmBrinell250_31.400_-1.000.tif";
	const auto filename = "t19452-09_27.100_-87.700.tif";
	//Reading the image 
	const auto mat = cv::imread(filename, IMREAD_UNCHANGED);
	//Starting the chrono clock
	const auto begin = std::chrono::steady_clock::now();
	//Converting Mat object to a mxArray
	//mxArray *X = ocvMxArrayFromImage_int16(mat); //(Proper way)
	const auto x = mat_to_emx_array_uint16_t(mat); //(my way)
	//Result will contain the result of the matlab Threshold function
	emxArray_real_T *result;
	//Initializing emxArray_real_T* array
	emxInitArray_real_T(&result, 2);
	//Calling the matlab Threshold function
	Threshold(x, 0.01, 0, result); //3rd parameter is the mode: 0-mean; 1-gaussian; 2-median
	//ocvMxArrayToMat_double((mxArray*) Result, &Res);
	const auto res = emx_array_real_t_to_mat(result, mat.rows, mat.cols);
	double min, max;
	cv::minMaxLoc(mat, &min, &max);
	const auto output_array = new double[mat.rows * mat.cols];
	for (auto i = 0; i < mat.rows; ++i)
	{
		for (auto j = 0; j < mat.cols; ++j) {
			const auto k = mat.cols * i + j;
			//const auto normalized_pixel_val = (mat.at<UINT16_T>(i,j) - min) / (max - min);
			const auto pixel_val = mat.at<UINT16_T>(i, j);
			if (pixel_val >= (result->data[k]) * UINT16_MAX)
			{
				output_array[k] = 1.0;
			}
			else
				output_array[k] = 0.0;
		}
	}
	Mat output_mat(mat.rows, mat.cols, CV_64F, output_array);
	std::memcpy(output_mat.data, output_array, mat.rows * mat.cols * sizeof(double));

	minMaxLoc(output_mat, &min, &max);
	output_mat.convertTo(output_mat, CV_8UC1, 255);
	minMaxLoc(output_mat, &min, &max);
	
	imwrite("output.tif", output_mat);
	//
	//minMaxLoc(mat, &min, &max);
	//Mat normalized_image;
	//divide((max - min), mat - min, normalized_image);
	//Mat binary_image = normalized_image > res;
	//binary_image.convertTo(binary_image, CV_16UC1, USHRT_MAX);
	//imwrite("output2.tif", binary_image);

	//Stop the chrono clock
	const auto end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
	//Displaying the results
	minMaxLoc(mat, &min, &max);
	cout << "Original Mat:" << endl;
	cout << "min: " << min << "\nmax: " << max << endl;
	cout << "After converting to a emxArray_uint16_T :" << endl;
	cout << "min: " << get_min(x, mat.rows, mat.cols) << "\nmax: " << get_max(x, mat.rows, mat.cols) << endl;
	cout << "After Thresholding in a emxArray_real_T format:" << endl;
	cout << "min: " << get_min(result, mat.rows, mat.cols) << "\nmax: " << get_max(result, mat.rows, mat.cols) << endl;
	cout << "Final Mat:" << endl;
	minMaxLoc(res, &min, &max);
	cout << "min: " << min << "\nmax: " << max << endl;
	//Checking if the result is equal to the matlab one
	//file.csv contains the obtained results with matlab with the same image and parameters
	cout << "results are equal: " << are_equal(res, "file.csv") << endl;
}

int main()
{
	//Doing the adaptive threshold using python scikit-learn threshold_local function
	//Wrapping python in c++
	//pythonWrapper();

	//Using the matlab to c++ generated code for the adaptive threshold
	using_matlab_gen_code();

	return 0;
}





