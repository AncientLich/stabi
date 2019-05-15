/* stabi: a little c++ exception manager for python3
 *        completely compatible with python3 stable ABI
 *        Copyright (C) Nobun,  2016
 *        license:  MIT
 ******************************************************/

#ifndef STABI_PYTHON3_RUN_FUNCTION
#define STABI_PYTHON3_RUN_FUNCTION

#include <string>

namespace stabi {
  namespace python3 {
     PyObject* run_function(std::string import, std::string funcname, PyObject* arguments = NULL);
     void decref_run_function();
  }
}

#endif

