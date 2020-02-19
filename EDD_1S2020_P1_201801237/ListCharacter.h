#pragma once
#include "Character.h"
#include <string>
using namespace std;

class ListCharacter
{
public:
	Character* first;
	Character* last;
	int counter = 0;
	bool IsEmpty();
	void Add(char c, int x, int y);
	bool IsBetween(int x, int y);
	void Delete(int x, int y);
	bool Search(string search);
	void Replace(string search, string replace);
	string DeleteSpace(string& str);
	void Clean();
	void Order();
	void Show();
	void GenerateGraph(string fileName);
	void SaveFile(string nombre);
	bool FirstEmpty();
};

