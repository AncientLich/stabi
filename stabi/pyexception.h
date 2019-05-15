/* stabi: a little c++ exception manager for python3
 *        completely compatible with python3 stable ABI
 *        Copyright (C) Nobun,  2016
 *        license:  MIT
 ******************************************************/

#ifndef STABI_PYTHON3_EXCEPTION
#define STABI_PYTHON3_EXCEPTION

#include <exception>
#include <string>

namespace stabi {
   namespace python3 {
       class error_happened: public std::exception
       {
           public:
               virtual const char* what() const throw();
               ~error_happened() throw();
       };
       
       class error_decref: public std::exception
       {
           public:
               error_decref(std::string err_where);
               virtual const char* what() const throw();
               ~error_decref() throw();
           
           private:
               std::string _err_where;
       };
   }
}

#endif

