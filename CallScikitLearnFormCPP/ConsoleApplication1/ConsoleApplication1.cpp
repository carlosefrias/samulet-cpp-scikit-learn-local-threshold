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

double are_equal(ushort* array, string csvFilename) 
{
	//Parsing the csv
	ifstream data(csvFilename);
	string line;
	auto vals = new double*[1024];
	for (int i = 0; i < 1024; ++i)
		vals[i] = new double[1024];
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
			if (col > 1023)
				break;
		}
		row++;
		//Checking if height don't match
		if (row > 1023)
			break;
	}
	auto sum_diff = 0;
	//Checking all the values one by one
	for (size_t i = 0; i < 1024; i++)
	{
		for (size_t j = 0; j < 1024; j++)
		{
			if (array[1024 * i + j] != vals[i][j])
				sum_diff++;
		}
	}
	cout << "differences: " << sum_diff << endl;
	return 100 - 100.0 * sum_diff / (1024.0 * 1024.0);
}

emxArray_real_T* mat_to_emx_array_uint16_t(Mat mat)
{
	//Check this
	//https://www.mathworks.com/help/vision/opencv-interface-support-package.html
	//To convert types the propper way

	const auto num_rows = mat.rows;
	const auto num_cols = mat.cols;

	auto** array = new ushort*[mat.rows];
	for (auto i = 0; i < mat.rows; ++i)
		array[i] = new ushort[mat.cols];

	for (auto i = 0; i < mat.rows; ++i)
		array[i] = mat.ptr<ushort>(i);

	const auto x = emxCreate_real_T(num_rows, num_cols);
	for (auto i = 0; i < num_rows; i++)
	{
		for (auto j = 0; j < num_cols; j++)
		{
			x->data[num_cols * i + j] = array[i][j];
		}
	}
	return x;
}

emxArray_real_T* mat_to_emx_array_real_t(Mat mat)
{
	//Check this
	//https://www.mathworks.com/help/vision/opencv-interface-support-package.html
	//To convert types the propper way

	const auto num_rows = mat.rows;
	const auto num_cols = mat.cols;

	auto** array = new double*[mat.rows];
	for (auto i = 0; i < mat.rows; ++i)
		array[i] = new double[mat.cols];

	for (auto i = 0; i < mat.rows; ++i)
		array[i] = mat.ptr<double>(i);

	const auto x = emxCreate_real_T(num_rows, num_cols);
	for (auto i = 0; i < num_rows; i++)
	{
		for (auto j = 0; j < num_cols; j++)
		{
			x->data[num_cols * i + j] = array[i][j];
		}
	}
	return x;

	// matlab compatable
	//const auto matlab_input = emxCreate_real_T(mat.rows, mat.cols);
	//// copy
	//for (auto r = 0; r < mat.rows; r++)
	//{
	//	const float * row_ptr = mat.ptr<float>(r);

	//	const int bytes = sizeof(float) * mat.rows;
	//	const auto ptr_offset = mat.rows * r;

	//	const auto p = matlab_input->data + ptr_offset;
	//	memcpy(p, row_ptr, bytes);
	//}
	//return matlab_input;
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
	const auto filename = "Gaussian.tif";
	//Reading the image 
	const auto mat = cv::imread(filename, IMREAD_UNCHANGED);
	double min, max;
	cv::minMaxLoc(mat, &min, &max);
	std::cout << "Original Mat:" << endl;
	std::cout << "min: " << min << "\nmax: " << max << endl;
	cv::Mat normalized_source_image = cv::Mat::zeros(mat.rows, mat.cols, CV_64FC1);
	//Normalize sourceImage
	for(auto r = 0; r < mat.rows; r++)
	{
		for (auto c = 0; c < mat.cols; c++)
		{
			auto& normalized_value = normalized_source_image.at<double>(r, c);
			normalized_value = (mat.at<ushort>(r, c) - min) / (max - min);
		}
	}
	double norm_min, norm_max;
	cv::minMaxLoc(normalized_source_image, &norm_min, &norm_max);
	std::cout << "Normalized Mat:" << endl;
	std::cout << "norm_min: " << norm_min << "\nnorm_max: " << norm_max << endl;

	//Starting the chrono clock
	const auto begin = std::chrono::steady_clock::now();
	//Converting Mat object to a mxArray
	const auto x = mat_to_emx_array_real_t(normalized_source_image);
	//const auto x = mat_to_emx_array_uint16_t(mat); //(my way)
	std::cout << "Normalized emx_array before threshold:" << endl;
	std::cout << "min: " << get_min(x, mat.rows, mat.cols) << "\nmax: " << get_max(x, mat.rows, mat.cols) << endl;

	emxArray_real_T *result;
	//Initializing emxArray_real_T* array
	emxInitArray_real_T(&result, 2);
	//Calling the matlab Threshold function
	Threshold(x, 0.01, 0, result); //3rd parameter is the mode: 0-mean; 1-gaussian; 2-median
	//ocvMxArrayToMat_double((mxArray*) Result, &Res);
	const auto min_t = get_min(result, mat.rows, mat.cols);
	const auto max_t = get_max(result, mat.rows, mat.cols);
	std::cout << "Threshold emx_array:" << endl;
	std::cout << "min_t: " << min_t << "\nmax_t: " << max_t << endl;

	cv::Mat threshold_mat = emx_array_real_t_to_mat(result, mat.rows, mat.cols);
	double max_t_mat, min_t_mat;
	cv::minMaxLoc(threshold_mat, &min_t_mat, &max_t_mat);
	std::cout << "Threshold mat:" << endl;
	std::cout << "min_t_mat: " << min_t_mat << "\nmax_t_mat: " << max_t_mat << endl;
	threshold_mat.convertTo(threshold_mat, CV_64F);
	cv::minMaxLoc(threshold_mat, &min_t_mat, &max_t_mat);
	std::cout << "Threshold mat after conversion to 64 bit:" << endl;
	std::cout << "min_t_mat: " << min_t_mat << "\nmax_t_mat: " << max_t_mat << endl;

	cv::Mat output = cv::Mat::zeros(mat.rows, mat.cols, CV_16UC1);

	for (auto r = 0; r < mat.rows; ++r)
	{
		for (auto c = 0; c < mat.cols; ++c)
		{
			const auto pixel_val = normalized_source_image.at<double>(r, c);
			const auto threshold = threshold_mat.at<double>(r, c) * USHRT_MAX * 3;

			if (pixel_val > threshold)
			{
				auto& output_value = output.at<ushort>(r, c);
				output_value = 1;
			}
		}
	}

	cv::minMaxLoc(output, &min, &max);
	output.convertTo(output, CV_16UC1, USHRT_MAX);
	cv::minMaxLoc(output, &min, &max);
	
	cv::imwrite("output.tif", output);

	//Stop the chrono clock
	const auto end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
	//Displaying the results
	cv::minMaxLoc(mat, &min, &max);
	std::cout << "Final Mat:" << endl;
	std::cout << "min: " << min << "\nmax: " << max << endl;
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





