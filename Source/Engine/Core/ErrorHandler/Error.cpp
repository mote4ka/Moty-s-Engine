#include "Error.h"

Error::Error(int code,const char* msg, const char* object)
{
	Error::code = code;
	Error::msg = msg;
	Error::object = object;
}
