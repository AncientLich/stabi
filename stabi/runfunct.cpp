#include <Python.h>
/* stabi: a little c++ exception manager for python3
 *        completely compatible with python3 stable ABI
 *        Copyright (C) Nobun,  2016
 *        license:  MIT
 ******************************************************/

#include <stabi/runfunct.h>
#include <stabi/pyexception.h>


namespace stabi {
   namespace python3 {
      namespace ns_runfun {
         static PyObject * pModule;
         static PyObject * pFunc;
         static PyObject * callback;
      }
   }
}



PyObject * stabi::python3::run_function(std::string import, std::string funcname, PyObject* arguments) {
    PyObject *pName;
    if(stabi::python3::ns_runfun::pModule != NULL) throw stabi::python3::error_decref("stabi::python3::run_function");
    pName = PyUnicode_FromString(import.c_str());
    //pModule is a class member
    stabi::python3::ns_runfun::pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if(stabi::python3::ns_runfun::pModule == NULL) {
       if(arguments) Py_DECREF(arguments);
       throw stabi::python3::error_happened();
    }
    stabi::python3::ns_runfun::pFunc = PyObject_GetAttrString(stabi::python3::ns_runfun::pModule, funcname.c_str());
    if(stabi::python3::ns_runfun::pFunc && PyCallable_Check(stabi::python3::ns_runfun::pFunc)) {
       stabi::python3::ns_runfun::callback = PyObject_CallObject(stabi::python3::ns_runfun::pFunc, arguments);
       if (PyErr_Occurred()) {
          if(arguments) Py_DECREF(arguments);
          throw stabi::python3::error_happened();
       }
    }
    else {
       if(arguments) Py_DECREF(arguments);
       throw stabi::python3::error_happened();
    }
    return stabi::python3::ns_runfun::callback;
}



void stabi::python3::decref_run_function() {
    if(stabi::python3::ns_runfun::callback) {
       Py_XDECREF(stabi::python3::ns_runfun::callback);
       stabi::python3::ns_runfun::callback = NULL;
    }
    if(stabi::python3::ns_runfun::pFunc) {
       Py_XDECREF(stabi::python3::ns_runfun::pFunc);
       stabi::python3::ns_runfun::pFunc = NULL;
    }
    if(stabi::python3::ns_runfun::pModule) {
       Py_XDECREF(stabi::python3::ns_runfun::pModule);
       stabi::python3::ns_runfun::pModule = NULL;
    }
}


