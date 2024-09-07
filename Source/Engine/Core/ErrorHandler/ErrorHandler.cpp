#include <iostream>
#include "Error.h"
#include "../../../Dev/App.cpp"


int main() {
	std::cout << "ErrorHandler ready!\n";
	try {
		App app;
		app.Run();
	}
	catch (Error err) {
		std::cout << "#FATAL ERROR "<< err.code << ": " << err.msg << " " << err.object << "!\n";
		return -1;
	}
	return 0;
}