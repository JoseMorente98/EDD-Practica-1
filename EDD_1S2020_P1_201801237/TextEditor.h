#pragma once
#include "ListCharacter.h"
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
	StackUndo stackUndo;
	StackRedo stackRedo;
	Menu menu;

public:
	TextEditor();
	virtual ~TextEditor();
	void MainMenu();
	void FileMenu();
};

