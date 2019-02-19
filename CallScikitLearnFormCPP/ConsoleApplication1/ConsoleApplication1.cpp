// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Python.h"

PyObject *pName, *pModule, *pDict, *pFunc, *pArgs, *pValue;
int main() 
{
	printf("Calling Python from c++\n");
	const char * programName = "Sample";

	Py_Initialize();

	pName = PyUnicode_DecodeFSDefault(programName);
	pModule = PyImport_Import(pName);
	const char *methodName = "add";
	Py_DECREF(pName); 
	if (pModule != NULL)
	{
		pFunc = PyObject_GetAttrString(pModule, methodName);

		pArgs = PyTuple_New(2);
		pValue = PyLong_FromLong(5);
		PyTuple_SetItem(pArgs, 0, pValue);
		pValue = PyLong_FromLong(3);
		PyTuple_SetItem(pArgs, 1, pValue);

		pValue = PyObject_CallObject(pFunc, pArgs);
		Py_DECREF(pArgs);
		Py_DECREF(pFunc);
		Py_DECREF(pModule);

		printf("Result of call: %ld\n", PyLong_AsLong(pValue));
	}
	return 0;
}
