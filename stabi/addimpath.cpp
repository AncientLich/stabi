/* stabi: a little c++ exception manager for python3
 *        completely compatible with python3 stable ABI
 *        Copyright (C) Nobun,  2016
 *        license:  MIT
 ******************************************************/

#include <Python.h>
#include <stabi/addimpath.h>
#include <stabi/pyexception.h>



int stabi::python3::add_import_path(std::string path) {
    PyObject *pName, *pModule, *pPath, *pFunc, *callback, *arguments, *as;
    //import sys
    pName = PyUnicode_FromString("sys");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if(pModule == NULL) throw stabi::python3::error_happened();
    //sys.path
    pPath = PyObject_GetAttrString(pModule,"path");
    if(pPath) {
       pFunc = PyObject_GetAttrString(pPath,"append");
    }
    else {
       Py_DECREF(pModule);
       throw stabi::python3::error_happened();
    }
    //sys.path.append
    if(pFunc && PyCallable_Check(pFunc)) {
       as = PyUnicode_FromString(path.c_str());
       arguments = PyTuple_New(1);
       PyTuple_SetItem(arguments, 0, as);
       callback = PyObject_CallObject(pFunc, arguments);
       //DECREF: we don't decref "as" becouse decrefing "arguments" takes care of it 
       //        (if you try to decref "as" you will have segmentation fault)
       Py_XDECREF(arguments);
       Py_DECREF(callback);
       Py_DECREF(pFunc);
       Py_DECREF(pPath);
       Py_DECREF(pModule);
       if(PyErr_Occurred())   throw stabi::python3::error_happened();
       return 1;
    }
    else {
       if(pFunc) Py_XDECREF(pFunc);
       Py_DECREF(pPath);
       Py_DECREF(pModule);
       throw stabi::python3::error_happened();
    }
    return 0;
}

