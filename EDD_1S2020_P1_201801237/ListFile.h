#pragma once
#include "File.h"
class ListFile
{
private:
	File* first;
	File* last;
public:
	ListFile();
	void Add(string name, string route);
	void Show();
	//string buscarArchivo(int dato);
	void Clean();
	bool IsEmpty();
	File* Search(int index);
	void GenerateGraph(std::string name);
};

