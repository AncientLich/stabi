/* stabi: a little c++ exception manager for python3
 *        completely compatible with python3 stable ABI
 *        Copyright (C) Nobun,  2016
 *        license:  MIT
 ******************************************************/

#ifndef STABI_PYTHON3_TRACERR
#define STABI_PYTHON3_TRACERR

#include <string>

namespace stabi {
  namespace python3 {
     std::string tracerr(std::string module_name);    
  }
}

#endif

