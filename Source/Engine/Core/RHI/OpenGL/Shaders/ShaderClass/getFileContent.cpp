#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include "Error.h"

static std::string getFileContent(const char* path) {
	std::ifstream in(path, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	std::cout << "Failed to open file: " << path << "\n";
	return "";
}