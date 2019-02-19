// CallScikitLearnFormCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Python.h>

PyObject *pName, *pModule, *pDict, *pArgs, *pFunc, *pValue;

int main()
{
	printf("Calling Python from c++");
	Py_Initialize();
	pName = PyBytes_FromString("Sample");
	// Import the file as a Python module.
	pModule = PyImport_Import(pName);
	// Create a dictionary for the contents of the module.
	pDict = PyModule_GetDict(pModule);
	// Get the add method from the dictionary.
	pFunc = PyDict_GetItemString(pDict, "add");
	// Create a Python tuple to hold the arguments to the method.
	pArgs = PyTuple_New(2);
	// Convert 2 to a Python integer.
	pValue = PyLong_FromLong(2);
	// Set the Python int as the first and second arguments to the method.
	PyTuple_SetItem(pArgs, 0, pValue);
	PyTuple_SetItem(pArgs, 1, pValue);
	// Call the function with the arguments.
	PyObject* pResult = PyObject_CallObject(pFunc, pArgs);
	// Print a message if calling the method failed.
	if (pResult == NULL)
		printf("Calling the add method failed.\n");
	// Convert the result to a long from a Python object.
	long result = PyLong_AsLong(pResult);
	// Destroy the Python interpreter.
	Py_Finalize();
	// Print the result.
	printf("The result is %d.\n", result); std::cin.ignore();
	return 0;
}

