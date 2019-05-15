# stabi
A tiny and very minimal c++ library for embedding python

# usage
Simply add stabi files into your c++ project

    ```
    stabi/addimpath.cpp
    stabi/pyexception.cpp
    stabi/runfunct.cpp
    stabi/tracerr.cpp
    ```

then, when you need add this include as FIRST include

    ```c++
    #include stabi/python.hpp
    ```

wich will include <Python.h> by itself

# available functions

**stabi::python3::add_import_path(std::string path)**
   add path to python import path. This is really important in embedding python
   (current directory is not a valid python path when embedding python).
   It raises stabi::python3::error_happened() exception if it fails

**stabi::python3::run_function(std::string import, std::string funcname, PyObject* arguments = NULL)**
   run a function from python file. You must set the import string in order to import
   the python file, and then the function name to run.
   arguments must be builded with C Api. Here there is an example:
        
        ```c++
        // example for calling a function wich requires a string parameter
        void run_x(std::string &relpath) {
           std::string relpath = "value";
           const char *relpath_cstr = relpath_str.c_str();
           PyObject *obj;
           PyObject *param1 = PyUnicode_FromString(relpath_cstr);
           PyObject *params = PyTuple_New(1);
           PyTuple_SetItem(params, 0, param1);
           bool isok = true;
           try {
              obj = stabi::python3::run_function("myfile", "function", params);
           }
           catch (stabi::python3::error_happened) {
              std::string errmsg = stabi::python3::tracerr("myfile.py");
              isok=false;
              //manage error 
           }
           if(isok) {
              Py_DECREF(obj);
              stabi::python3::decref_run_function();
              Py_DECREF(params);
           }
           else { stabi::python3::decref_run_function(); Py_DECREF(params); }
        ```
    
   when the function is not more used, you should decref it with 
   stabi::python3::decref_run_function, as the example showed

**(exception) stabi::python3::error_happened**
   this exception is raised when a python raises an exception

**stabi::python3::tracerr(std::string origin_file)**
   this function returns the python traceback as std::string.

