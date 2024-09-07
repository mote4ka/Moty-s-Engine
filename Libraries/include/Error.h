#pragma once
#include <string>

struct Error {
	Error(int code,const char* msg,const char* object = "");
	int code = 0;
	std::string msg = "";
	std::string object = "";
};