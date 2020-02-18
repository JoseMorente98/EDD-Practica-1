#include "TextEditor.h"
#include <windows.h>
#include <iostream>
#include "Validator.h"
#include <conio.h>

TextEditor::TextEditor()
{
}

TextEditor::~TextEditor()
{
}

int TextEditor::PositionX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X;
}
int TextEditor::PositionY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.Y;
}

void TextEditor::MoveXY(int x, int y) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hStdout, pos);
}

void TextEditor::PrintAndClean()
{
	system("cls");
	this->menu.MenuFile();
	this->listCharacter.Show();
}

void TextEditor::MainMenu()
{
	string inputText;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);

	this->menu.MainMenu();

	bool exit = false;
	do {
		std::cout << ">> ";
		std::cin >> inputText;

		Validator validator;
		if (validator.IsDigit(inputText)) {
			int inputText2 = stoi(inputText);
			switch (inputText2)
			{
			case 1:
				system("cls");
				FileMenu();
				break;
			case 2:
				system("cls");
				break;
			case 3:
				system("cls");
				break;
			case 4:
				system("cls");
				break;
			default:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cout << "Usted ha ingresado una opcion incorrecta.\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
				exit = true;
				inputText;
				break;
			}
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			cout << "Solamente puede ingresar digitos.\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			exit = true;
			inputText;
		}
	} while (exit);
}

void TextEditor::FileMenu()
{
	bool state = true;
	char character;
	int entry = 4;
	this->menu.MenuFile();

	//cout << ">> ";

	while (state) {
		character = _getch();
		int ascii = character;


		if (ascii == 75 && character == 'K')
		{
			MoveXY(PositionX() - 1, PositionY());
		}
		else if (ascii == 72 && character == 'H')
		{
			MoveXY(PositionX(), PositionY() - 1);
		}
		else if (ascii == 80 && character == 'P')
		{
			MoveXY(PositionX(), PositionY() + 1);
		}
		else if (ascii == 77 && character == 'M')
		{
			MoveXY(PositionX() + 1, PositionY());
		}
		/*
			REPORTES CTRL + C
		*/
		if (ascii == 3)
		{
			
		}
		/*
			BACKSPACE
		*/
		else if (ascii == 8) {
			listCharacter.Delete(PositionX() - 1, PositionY());
			MoveXY(PositionX() - 1, PositionY());
			PrintAndClean();
		}
		/*
			ENTER
		*/
		else if (ascii == 13)
		{
			listCharacter.Add('\n', PositionX(), PositionY());
			PrintAndClean();
			entry++;
		}
		/*
			GUARDAR CTRL + S
		*/
		else if (ascii == 19)
		{
			
		}
		/*
			TECLA DE ESCAPE CTRL + X
		*/
		else if (ascii == 24)
		{
			state = false;
			break;
		}
		/*
			TECLA REHACER CTRL + Y
		*/
		else if (ascii == 25) {
			if (!stackRedo.IsEmpty()) {
				LogChange* c = stackRedo.Pop();
				c->setState(true);
				stackUndo.Push(c);
				string search = c->getSearch() + ";" + c->getReplace();
				/*if(lista.Buscar(buscar)) {
					Limpiar();
				}*/
			}
		}
		/*
			TECLA DESHACER CTRL + Z
		*/
		else if (ascii == 26) { //Presiono CONTROL Z DESHACER
			if (!stackUndo.IsEmpty()) {
				LogChange* c = stackUndo.Pop();
				c->setState(true);
				stackRedo.Push(c);
				string search = c->getReplace() + ";" + c->getSearch();
				/*if (lista.Buscar(buscar)) {
					Limpiar();
				}*/
			}
		}
		else {
			listCharacter.Add(character, PositionX(), PositionY());
			PrintAndClean();
		}
	}
}

