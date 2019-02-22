#include "pch.h"
#include <iostream>
#include <Python.h>
#include <chrono>
#include <iomanip>
//#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "rt_nonfinite.h"
#include "Threshold.h"
#include "Threshold_terminate.h"
#include "Threshold_emxAPI.h"
#include "Threshold_initialize.h"
#include "adaptthresh.h"

using namespace cv;
using namespace std;
//Adaptive Integral threshold
//Code retrieved from https://github.com/phryniszak/AdaptiveIntegralThresholding/blob/master/main.cpp
void thresholdIntegral(cv::Mat &inputMat, cv::Mat &outputMat)
{
	// accept only char type matrices
	CV_Assert(!inputMat.empty());
	CV_Assert(inputMat.depth() == CV_8U);
	CV_Assert(inputMat.channels() == 1);
	CV_Assert(!outputMat.empty());
	CV_Assert(outputMat.depth() == CV_8U);
	CV_Assert(outputMat.channels() == 1);

	// rows -> height -> y
	int nRows = inputMat.rows;
	// cols -> width -> x
	int nCols = inputMat.cols;

	// create the integral image
	cv::Mat sumMat;
	cv::integral(inputMat, sumMat);

	CV_Assert(sumMat.depth() == CV_32S);
	CV_Assert(sizeof(int) == 4);

	int S = MAX(nRows, nCols) / 8;
	double T = 0.15;

	// perform thresholding
	int s2 = S / 2;
	int x1, y1, x2, y2, count, sum;

	// CV_Assert(sizeof(int) == 4);
	int *p_y1, *p_y2;
	uchar *p_inputMat, *p_outputMat;

	for (int i = 0; i < nRows; ++i)
	{
		y1 = i - s2;
		y2 = i + s2;

		if (y1 < 0) {
			y1 = 0;
		}
		if (y2 >= nRows) {
			y2 = nRows - 1;
		}

		p_y1 = sumMat.ptr<int>(y1);
		p_y2 = sumMat.ptr<int>(y2);
		p_inputMat = inputMat.ptr<uchar>(i);
		p_outputMat = outputMat.ptr<uchar>(i);

		for (int j = 0; j < nCols; ++j)
		{
			// set the SxS region
			x1 = j - s2;
			x2 = j + s2;

			if (x1 < 0) {
				x1 = 0;
			}
			if (x2 >= nCols) {
				x2 = nCols - 1;
			}

			count = (x2 - x1)*(y2 - y1);

			// I(x,y)=s(x2,y2)-s(x1,y2)-s(x2,y1)+s(x1,x1)
			sum = p_y2[x2] - p_y1[x2] - p_y2[x1] + p_y1[x1];

			if ((int)(p_inputMat[j] * count) < (int)(sum*(1.0 - T)))
				p_outputMat[j] = 255;
			else
				p_outputMat[j] = 0;
		}
	}
}

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
		//Defining the python funtion to use
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

		//Calling the python funtion
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
double getMax(emxArray_real_T *matrix, int numRows, int numCols)
{
	double max = DBL_MIN;
	int k = 0;
	for (size_t i = 0; i < numRows; i++)
	{
		for (size_t j = 0; j < numCols; j++)
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
double getMin(emxArray_real_T *matrix, int numRows, int numCols)
{
	double min = DBL_MAX;
	int k = 0;
	for (size_t i = 0; i < numRows; i++)
	{
		for (size_t j = 0; j < numCols; j++)
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

UINT16 getMax(emxArray_uint16_T *matrix, int numRows, int numCols)
{
	UINT16 max = 0;
	int k = 0;
	for (size_t i = 0; i < numRows; i++)
	{
		for (size_t j = 0; j < numCols; j++)
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

UINT16 getMin(emxArray_uint16_T *matrix, int numRows, int numCols)
{
	UINT16 min = UINT16_MAX;
	int k = 0;
	for (size_t i = 0; i < numRows; i++)
	{
		for (size_t j = 0; j < numCols; j++)
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

//Using the matlab to c++ generated code for the adaptive threshold
void usingMatlabGenCode()
{
	std::cout << std::fixed;
	std::cout << std::setprecision(10);

	//const char *filename = "2mmBrinell250_31.400_-1.000.tif";
	const char *filename = "t19452-09_27.100_-87.700.tif";
	//Reading the image 
	cv::Mat mat = cv::imread(filename, IMREAD_UNCHANGED);

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	//Converting Mat object to a regular 2d array (probably there is a simpler way to do this)
	int NumRows = mat.rows;
	int NumCols = mat.cols;
	
	/*std::vector<UINT16> array;
	if (mat.isContinuous())
	{
		array.assign(mat.datastart, mat.dataend);
	}
	else
	{
		for (int i = 0; i < mat.rows; ++i)
		{
			array.insert(array.end(), mat.ptr<UINT16>(i), mat.ptr<UINT16>(i) + mat.cols);
		}
	}

	UINT16** a = new UINT16*[NumRows];
	for (int i = 0; i < NumRows; ++i)
		a[i] = new UINT16[NumCols];

	int k = 0;
	for (size_t i = 0; i < NumRows; i++)
	{
		for (size_t j = 0; j < NumCols; j++)
		{
			a[i][j] = array[k];
			k++;
		}
	}*/

	//Converting the 2D long array (image) to a emxArray_uint16_T* (1st parameter of the Threshold function)
	emxArray_uint16_T *X;
	X = emxCreate_uint16_T(NumRows, NumCols);
	for (size_t i = 0; i < NumRows; i++)
	{
		for (size_t j = 0; j < NumCols; j++)
		{
			//X->data[NumRows * i + j] = a[i][j];
			//UINT16* val = new UINT16[1];
			//val = mat.ptr<UINT16>(NumRows * i + j);
			X->data[NumRows * i + j] = mat.ptr<UINT16>(NumRows * i + j);
		}
	}

	/*for (size_t i = 0; i < X->size; i++)
	{

	}*/
	//Result will contain the result of the matlab Threshold function
	emxArray_real_T *Result;
	emxInitArray_real_T(&Result, 2);

	//Calling the matlab Threshold function
	Threshold(X, 0.01, 0, Result);
	
	//In the Result is the output of the matlab Threshold function
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;


	//TODO: convert Result to a Mat again and show the comparasion
	cv::Mat outputMat = cv::Mat::zeros(mat.size(), CV_16U);
	long *p_outputMat;
	int k = 0;
	for (size_t i = 0; i < NumRows; i++)
	{
		p_outputMat = outputMat.ptr<long>(i);
		for (size_t j = 0; j < NumCols; j++)
		{
			//cout << Result->data[k] << endl;
			p_outputMat[j] = Result->data[k];
			k++;
		}
	}
	double min, max;
	cv::minMaxLoc(mat, &min, &max);
	cout << "Original Mat:" << endl;
	cout << "min: " << min << "\nmax: " << max << endl;
	cout << "After converting to a emxArray_uint16_T :" << endl;
	cout << "min: " << getMin(X, NumRows, NumCols) << "\nmax: " << getMax(X, NumRows, NumCols) << endl;
	cout << "After Thresholding in a emxArray_real_T format:" << endl;
	cout << "min: " << getMin(Result, NumRows, NumCols) << "\nmax: " << getMax(Result, NumRows, NumCols) << endl;
	cout << "Final Mat:" << endl;
	cv::minMaxLoc(outputMat, &min, &max);
	cout << "min: " << min << "\nmax: " << max << endl;

	printf("end");
	//// Show binary image
	//cv::imshow("output image", outputMat);
	////! [bin_2] 

	//cv::waitKey(0);

}

int main()
{
	//Doing the adaptive threshold using python scikit-learn threshold_local function
	//Wrapping python in c++
	//pythonWrapper();

	//Using the matlab to c++ generated code for the adaptive threshold
	usingMatlabGenCode();

	//const char *filename = "2mmBrinell250_31.400_-1.000.tif";
	//const char *filename = "t19452-09_27.100_-87.700.tif";
	////Reading the image 
	//cv::Mat mat = cv::imread(filename, IMREAD_UNCHANGED);
	//cv::Mat bw2 = cv::Mat::zeros(mat.size(), CV_8UC1);
	//thresholdIntegral(mat, bw2);

	//// Show binary image
	//cv::imshow("binary integral", bw2);
	////! [bin_2] 

	//cv::waitKey(0);
	return 0;
}





