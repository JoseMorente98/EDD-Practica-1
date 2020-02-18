#include "TextEditor.h"
#include "Validator.h"

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <vector>

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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	this->listCharacter.Show();
}

void TextEditor::MainMenu()
{
	string inputText;

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
				cout << "Usted ha ingresado una optionText incorrecta.\n";
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
			this->Reports();
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
			TECLA DE ESCAPE CTRL + W
		*/
		else if (ascii == 23)
		{
			this->Search();
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
				if (listCharacter.Search(search)) {
					PrintAndClean();
				}
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
				if (listCharacter.Search(search)) {
					PrintAndClean();
				}
			}
		}
		else {
			listCharacter.Add(character, PositionX(), PositionY());
			PrintAndClean();
		}
	}
}

void TextEditor::Search() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "\n__________________________________________________\n";
	cout << "\nBUSCAR Y REEMPLAZAR: ";
	cout << "\n__________________________________________________\n";
	string search = "";
	cin >> search;
	size_t found = search.find(";");
	vector<string> wordSearch;
	wordSearch.push_back(search.substr(0, found));
	wordSearch.push_back(search.substr(found + 1, search.size()));

	if (listCharacter.Search(search)) {
		PrintAndClean();
		cout << "\n__________________________________________________\n";
		//cout << listCharacter.getContador() << " Se afectaron 10(s)\n";
		cout << "\n__________________________________________________\n";
		system("pause");
		PrintAndClean();
		/*
			ALMACENAR PALABRA BUSCADA EN PILA
		*/
		stackUndo.Push(new LogChange(wordSearch[0], wordSearch[1], false, "", 0, 0));
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << "Palabra no encontrada D:";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	}
}

void TextEditor::Reports() {
	this->menu.MenuReports();
	string inputText = "";
	bool exit = false;
	do {
		std::cout << " >> ";
		std::cin >> inputText;

		Validator validator;
		if (validator.IsDigit(inputText)) {
			int inputText2 = stoi(inputText);
			switch (inputText2)
			{
			case 1:
				if (!listCharacter.IsEmpty()) {
					listCharacter.GenerateGraph("ListaDoble");
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					cout << " La lista se encuentra vacia D:\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
				}
				exit = true;
				break;
			case 2:
				if (!stackUndo.IsEmpty()) {
					stackUndo.GenerateGraph("StackUndo");
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					cout << " La pila se encuentra vacia D:\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
				}
				exit = true;
				break;
			case 3:
				if (!stackRedo.IsEmpty()) {
					stackRedo.GenerateGraph("StackRedo");
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					cout << " La pila se encuentra vacia D:\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
				}
				exit = true;
				break;
			case 4:
				this->PrintAndClean();
				exit = false;
				break;
			default:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cout << "Usted ha ingresado una opción incorrecta.\n";
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