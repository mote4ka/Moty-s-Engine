#pragma once
#include "../RHI/OpenGL/Shaders/ShaderClass/getFileContent.cpp"
#include "string"
#include <ostream>

class Map {
public:
	//Map(const char* path);
	//std::string data;
	const char* data = Content::GetFileContent("C:/Users/moty/source/repos/Moty-s-Engine/Source/Engine/Core/Maps/level0.map").c_str();
private:

};