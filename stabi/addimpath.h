/* stabi: a little c++ exception manager for python3
 *        completely compatible with python3 stable ABI
 *        Copyright (C) Nobun,  2016
 *        license:  MIT
 ******************************************************/

#ifndef STABI_PYTHON3_ADD_IMPORT_PATH_H
#define STABI_PYTHON3_ADD_IMPORT_PATH_H

#include <string>

namespace stabi {
  namespace python3 {
     int add_import_path(std::string path);
  }
}

#endif

