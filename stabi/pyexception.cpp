/* stabi: a little c++ exception manager for python3
 *        completely compatible with python3 stable ABI
 *        Copyright (C) Nobun,  2016
 *        license:  MIT
 ******************************************************/

#include <stabi/pyexception.h>



const char* stabi::python3::error_happened::what() const throw() {
    return "A python exception was raised";
}



const char* stabi::python3::error_decref::what() const throw() {
    std::string errmsg = "Unfreed memory found at ";
    errmsg.append(_err_where);
    errmsg.append(" .\nYou forgot to decref it.");
    return errmsg.c_str();
}



stabi::python3::error_decref::error_decref(std::string err_where) {
    _err_where = err_where;
}



stabi::python3::error_happened::~error_happened() throw() {}

stabi::python3::error_decref::~error_decref() throw() {}

