/* stabi: a little c++ exception manager for python3
 *        completely compatible with python3 stable ABI
 *        Copyright (C) Nobun,  2016
 *        license:  MIT
 ******************************************************/


#include <stabi/python.hpp>
#include <iostream>


std::string stabi::python3::tracerr(std::string module_name) {
   std::string value;
   //if(PyErr_Occurred()) {
     
     PyObject *exc, *val, *tb, *except_msglist, *item, *myargs;
     Py_ssize_t msglist_size;
     PyErr_Fetch(&exc, &val, &tb);
     PyErr_NormalizeException(&exc, &val, &tb);
     try {
        stabi::python3::decref_run_function();
        myargs = PyTuple_New(3);
        if(exc == NULL) exc = Py_None;
        if(val == NULL) val = Py_None;
        if(tb == NULL) tb = Py_None;
        PyTuple_SetItem(myargs, 0, exc);
        PyTuple_SetItem(myargs, 1, val);
        PyTuple_SetItem(myargs, 2, tb);
        except_msglist = stabi::python3::run_function("traceback", "format_exception", myargs);
     }
     catch(stabi::python3::error_happened) {
        if(myargs)   Py_XDECREF(myargs);
        if(exc != Py_None)  Py_XDECREF(exc);
        if(val != Py_None)  Py_XDECREF(val);
        if(tb  != Py_None)  Py_XDECREF(tb);
        stabi::python3::decref_run_function();
        return "Impossible to write down the traceback error message.\nCannot run traceback.format_exception() from python library.";
     }
     //msglist_size = PyList_GET_SIZE(except_msglist);
     msglist_size = PyList_Size(except_msglist);
     value = "An error occurred while calling python module: ";
     value.append(module_name);
     value.append("\n------------------------------------------------------\n\n");
     for(Py_ssize_t a=0; a < msglist_size; ++a) {
           char *item_value; Py_ssize_t sz;
           item = PyList_GetItem(except_msglist, a);
           // item_value = PyUnicode_AsUTF8AndSize(item, &sz);
           PyObject * ditem = PyUnicode_AsUTF8String(item);
           item_value = PyBytes_AsString(ditem);
           Py_DECREF(ditem);
           std::string tmp(item_value);
           //this will avoid to print messages like:
           //    File "<frozen importlib._bootstrap>", line 2237, in _find_and_load
           //on traceback, wich are useless and confusing
           if (tmp.find("._bootstrap>\", line ") == std::string::npos) {
              value.append(tmp);
           }
     }
     //decrefing traceback arguments and myargs
     if(myargs)   Py_XDECREF(myargs);
     if(exc != Py_None)  Py_XDECREF(exc);
     if(val != Py_None)  Py_XDECREF(val);
     if(tb  != Py_None)  Py_XDECREF(tb);
     stabi::python3::decref_run_function(); //decrefing except_msglist;
   /* }
   else {
     stabi::python3::decref_run_function(); //added for convenience
     value = "An unhandled exception occurred while calling python module \"";
     value.append(module_name);
     value.append("\",\n[C++ stabi::python::tracerr() ) cannot handle it in any way]");
   } */
   return value;
}

