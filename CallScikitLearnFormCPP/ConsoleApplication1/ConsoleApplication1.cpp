// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Python.h>
//#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

PyObject *pName, *pModule, *pDict, *pFunc, *pArgs, *pValue;
PyObject *img, *blockSize, *method, *param, *offSet, *thresholdedImg;
int main() 
{
	printf("Calling Python from c++\n");
	const char * programName = "LocalThreshold";

	Py_Initialize();

	pName = PyUnicode_DecodeFSDefault(programName);
	pModule = PyImport_Import(pName);
	//const char *methodName = "add";
	//if (pModule != NULL)
	//{
	//	pFunc = PyObject_GetAttrString(pModule, methodName);

	//	pArgs = PyTuple_New(2);
	//	pValue = PyLong_FromLong(5);
	//	PyTuple_SetItem(pArgs, 0, pValue);
	//	pValue = PyLong_FromLong(3);
	//	PyTuple_SetItem(pArgs, 1, pValue);

	//	pValue = PyObject_CallObject(pFunc, pArgs);

	//	printf("Result of call: %ld\n", PyLong_AsLong(pValue));
	//}
	const char *methodName = "adaptThres";
	if (pModule != NULL) 
	{
		pFunc = PyObject_GetAttrString(pModule, methodName); 
		pArgs = PyTuple_New(5);
		
		//Define the 2d array (image)
		npy_intp Dims[2];
		Dims[0] = 50;
		Dims[1] = 50;

		import_array();
		
		// PyArray_SimpleNew allocates the memory needed for the array.
		img = PyArray_SimpleNew(2, Dims, NPY_DOUBLE);

		// The pointer to the array data is accessed using PyArray_DATA()
		double *p = (double *)PyArray_DATA(img);
		double **X_test2 = new double*[1024];
		
		//TODO: populate the X_Test2 array with random data...(or with the actual image values)

		// Copy the data from the "array of arrays" to the contiguous numpy array.
		for (int k = 0; k < 1024; ++k) 
		{
			memcpy(p, X_test2[k], sizeof(double) * 50);
			p += 50;
		}

		PyTuple_SetItem(pArgs, 0, img);
		blockSize = PyLong_FromLong(201);
		PyTuple_SetItem(pArgs, 1, blockSize);
		method = PyUnicode_FromString("gaussian");
		PyTuple_SetItem(pArgs, 2, method);
		param = PyLong_FromLong(30);
		PyTuple_SetItem(pArgs, 3, param);
		offSet = PyLong_FromLong(0);
		PyTuple_SetItem(pArgs, 4, offSet);

		
		pValue = PyObject_CallObject(pFunc, pArgs);
	}	
	Py_DECREF(pName);
	Py_DECREF(pArgs);
	Py_DECREF(pFunc);
	Py_DECREF(pModule);
	Py_Finalize();
	return 0;
}
