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
using namespace std;

PyObject *pName, *pModule, *pDict, *pFunc, *pArgs, *pValue, *imageArray, *resultPath;
PyObject *img, *blockSize, *method, *param, *offSet, *thresholdedImg;
PyArrayObject *np_arg;
int main() 
{
	
	printf("Calling Python from c++\n");

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
		
		std::cout <<"C++\t\tmat.data[0]:\t\t"<< (int) mat.data[0] << endl;
		//...
		//Image processing before adaptive thresholding
		//...

		//Converting Mat object to a regular 2d array (probably there is a simpler way to do this)
		int NumRows = mat.rows;
		int NumCols = mat.cols;

		std::vector<int> array;
		if (mat.isContinuous()) {
			array.assign(mat.datastart, mat.dataend);
		}
		else {
			for (int i = 0; i < mat.rows; ++i) {
				array.insert(array.end(), mat.ptr<int>(i), mat.ptr<int>(i) + mat.cols);
			}
		}

		int** a = new int*[NumRows];
		for (int i = 0; i < NumRows; ++i)
			a[i] = new int[NumCols];

		int k = 0;
		for (size_t i = 0; i < NumRows; i++)
		{
			for (size_t j = 0; j < NumCols; j++)
			{
				a[i][j] = array[k++];
			}
		}
		//End of conversion from Mat to 2d array of int
		std::cout << "C++\t\ta[0][0]:\t\t" << a[0][0] << std::endl;

		import_array();//this function call is important if we want to send a pyArray to the python function as a parameter

		npy_intp mdim[] = { NumRows, NumCols };
		//Converting 2d int array to PyArrayObject
		np_arg = reinterpret_cast<PyArrayObject*>(PyArray_SimpleNewFromData(2, mdim, PyArray_INT, reinterpret_cast<void*>(a)));

		//Converting PyArrayObject to PyObject
		imageArray = reinterpret_cast<PyObject*>(np_arg);

		//Defining all the arguments of the python function
		PyTuple_SetItem(pArgs, 0, imageArray);
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
		
		printf("end...");
	}	
	Py_DECREF(pName);
	Py_DECREF(pArgs);
	Py_DECREF(pFunc);
	Py_DECREF(pModule);
	Py_Finalize();
	return 0;
}