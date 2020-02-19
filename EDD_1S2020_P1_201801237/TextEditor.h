#pragma once
#include "ListCharacter.h"
#include "ListFile.h"
#include "StackUndo.h"
#include "StackRedo.h"
#include "Menu.h"
class TextEditor
{
/*
	VARIABLES GLOBALES
*/
public:
	ListCharacter listCharacter;
	ListFile listFile;
	StackUndo stackUndo;
	StackRedo stackRedo;
	Menu menu;

public:
	TextEditor();
	virtual ~TextEditor();
	int PositionX();
	int PositionY();
	void MoveXY(int x, int y);
	void MainMenu();
	void FileMenu();
	void FileRead();
	void Search();
	void Reports();
	void OpenFileMenu();
	void OpenFileMenu(string route);
	void OpenRecent();
	void SaveFile();
	string ReadRoute(string route);
	void PrintAndClean();
};

