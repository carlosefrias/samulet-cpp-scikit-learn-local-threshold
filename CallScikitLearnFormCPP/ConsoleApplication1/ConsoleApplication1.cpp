// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Python.h>
//#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

PyObject *pName, *pModule, *pDict, *pFunc, *pArgs, *pValue, *path, *resultPath;
PyObject *img, *blockSize, *method, *param, *offSet, *thresholdedImg;
PyArrayObject *imagem;
int main() 
{
	printf("Calling Python from c++\n");
	const char * programName = "LocalThreshold";

	Py_Initialize();

	pName = PyUnicode_DecodeFSDefault(programName);
	pModule = PyImport_Import(pName);

	const char *filename = "2mmBrinell250_31.400_-1.000.tif";
	const char *methodName = "adaptThres";

	if (pModule != NULL) 
	{
		pFunc = PyObject_GetAttrString(pModule, methodName); 
		pArgs = PyTuple_New(6);
		
		cv::Mat image;

		image = cv::imread(filename, IMREAD_UNCHANGED);

		const char *pathOriginal = "image.tif";
		cv::imwrite(pathOriginal, image);

		path = PyUnicode_FromString(pathOriginal);
		PyTuple_SetItem(pArgs, 0, path);
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
		const char *pathResult = "ThreseholdedImg.tif";
		resultPath = PyUnicode_FromString(pathResult);
		PyTuple_SetItem(pArgs, 5, resultPath);
		
		PyObject_CallObject(pFunc, pArgs);

		cv::Mat resultImg = cv::imread(pathResult, IMREAD_UNCHANGED);

		namedWindow("Display window", WINDOW_AUTOSIZE);
		imshow("Display window", resultImg);

		waitKey(0);
	}	
	Py_DECREF(pName);
	Py_DECREF(pArgs);
	Py_DECREF(pFunc);
	Py_DECREF(pModule);
	Py_Finalize();
	return 0;
}



//Define the 2d array (image)
//npy_intp Dims[2];
//Dims[0] = 1024;
//Dims[1] = 1024;

//import_array();
//
//// PyArray_SimpleNew allocates the memory needed for the array.
//img = PyArray_SimpleNew(2, Dims, NPY_LONG);

//// The pointer to the array data is accessed using PyArray_DATA()
//long *p = (long *)PyArray_DATA(img);
//long **X_test = new long*[1024];
//
////TODO: populate the X_Test array with the actual image values
//for (int i = 0; i < image.rows; i++) 
//{
//	for (int j = 0; i < image.cols; j++) 
//	{
//		//std::cout << image.at<uchar>(i, j) << std::endl;
//		X_test[i][j] = image.at<uchar>(i, j);
//	}
//}

//// Copy the data from the "array of arrays" to the contiguous numpy array.
//for (int k = 0; k < 1024; ++k) 
//{
//	memcpy(p, X_test[k], sizeof(long) * 1024);
//	p += 1024;
//}