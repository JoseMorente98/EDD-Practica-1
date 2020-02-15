#pragma once
#include "Character.h"
#include <string>

class ListCharacter
{
public:
	Character* first;
	Character* last;
	bool IsEmpty();
	void Add(char c, int x, int y);
	void AddReplace(char c, int x, int y);
	bool IsBetween(int x, int y);
	void Delete(int x, int y);
	bool Search(std::string search);
	void Clean();
	void Order();
	void Show();
};

