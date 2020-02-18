#pragma once
#include "File.h"
class ListFile
{
private:
	File* first;
	File* last;
public:
	void Add(string name, string route);
	void Show();
	//string buscarArchivo(int dato);
	void Clean();
	bool IsEmpty();
	string Search(int id);
	void GenerateGraph(std::string name);
};

