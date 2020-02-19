#include "TextEditor.h"
#include "Validator.h"

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include <fstream>
#include <stdio.h>

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
				system("cls");
				this->menu.MainMenu();
				exit = true;
				break;
			case 2:
				system("cls");
				OpenFileMenu();
				system("cls");
				this->menu.MainMenu();
				exit = true;
				break;
			case 3:
				if (!listFile.IsEmpty())
				{
					system("cls");
					OpenRecent();
					system("cls");
					this->menu.MainMenu();
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					cout << " La lista se encuentra vacia D:\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
					exit = true;
					inputText;
				}
				break;
			case 4:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "__________________________________________________\n";
				cout << "Esperamos que regrese :D\n";
				cout << "__________________________________________________\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
				exit = false;
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
	stackRedo.Clear();
	stackUndo.Clear();
	listCharacter.Clean();
	listCharacter.Add(' ', 0, 4);
	this->PrintAndClean();
	bool state = true;
	char character;
	int entry = 4;
	bool arrowState = false;
	int ascii;

	do {
		character = _getch();
		ascii = character;

		if (ascii == -32) {
			arrowState = true;
		}
		else if (ascii == 75 && arrowState)
		{
			MoveXY(PositionX() - 1, PositionY());
			arrowState = false;
		}
		else if (ascii == 72 && arrowState) 
		{
			MoveXY(PositionX(), PositionY()-1);
			arrowState = false;
		}
		else if (ascii == 80 && arrowState) 
		{
			MoveXY(PositionX(), PositionY() + 1);
			arrowState = false;
		}
		else if (ascii == 77 && arrowState)
		{
			MoveXY(PositionX() + 1, PositionY());
			arrowState = false;
		}
		/*
		BACKSPACE
		*/
		else if (ascii == 8) 
		{
			listCharacter.Delete(PositionX() - 1, PositionY());
			MoveXY(PositionX() - 1, PositionY());
			PrintAndClean();
		}
		/*
		SALIR CTRL + X
		*/
		else if (character == 24)
		{
			break;
		}
		/*
		ENTER
		*/
		else if (character == 13)
		{
			listCharacter.Add('\n', PositionX(), PositionY());
			PrintAndClean();
			entry++;
		}
		/*
		BUSCAR CTRL + W
		*/
		else if (character == 23) 
		{
			this->Search();
		}
		/*
		REHACER CTRL + Y
		*/
		else if (character == 25) 
		{
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
		DESHACER CTRL + Z
		*/
		else if (character == 26) 
		{
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
		/*
		REPORTES CTRL + C
		*/
		else if (character == 3) 
		{ 
			this->Reports();
		}
		/*
		GUARDAR CTRL + S
		*/
		else if (character == 19) 
		{ 
			this->SaveFile();
		}
		else {
			listCharacter.Add(character, PositionX(), PositionY());
			PrintAndClean();
		}
		character = ' ';
	} while (-1);

}

void TextEditor::FileRead()
{
	stackRedo.Clear();
	stackUndo.Clear();
	this->PrintAndClean();
	bool state = true;
	char character;
	int entry = 4;
	bool arrowState = false;
	int ascii;

	do {
		character = _getch();
		ascii = character;

		if (ascii == -32) {
			arrowState = true;
		}
		else if (ascii == 75 && arrowState)
		{
			MoveXY(PositionX() - 1, PositionY());
			arrowState = false;
		}
		else if (ascii == 72 && arrowState)
		{
			MoveXY(PositionX(), PositionY() - 1);
			arrowState = false;
		}
		else if (ascii == 80 && arrowState)
		{
			MoveXY(PositionX(), PositionY() + 1);
			arrowState = false;
		}
		else if (ascii == 77 && arrowState)
		{
			MoveXY(PositionX() + 1, PositionY());
			arrowState = false;
		}
		/*
		BACKSPACE
		*/
		else if (ascii == 8)
		{
			listCharacter.Delete(PositionX() - 1, PositionY());
			MoveXY(PositionX() - 1, PositionY());
			PrintAndClean();
		}
		/*
		SALIR CTRL + X
		*/
		else if (character == 24)
		{
			break;
		}
		/*
		ENTER
		*/
		else if (character == 13)
		{
			listCharacter.Add('\n', PositionX(), PositionY());
			PrintAndClean();
			entry++;
		}
		/*
		BUSCAR CTRL + W
		*/
		else if (character == 23)
		{
			this->Search();
		}
		/*
		REHACER CTRL + Y
		*/
		else if (character == 25)
		{
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
		DESHACER CTRL + Z
		*/
		else if (character == 26)
		{
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
		/*
		REPORTES CTRL + C
		*/
		else if (character == 3)
		{
			this->Reports();
		}
		/*
		GUARDAR CTRL + S
		*/
		else if (character == 19)
		{
			this->SaveFile();
		}
		else {
			int x = PositionX();
			int y = PositionY();
			listCharacter.Add(character, x, y);
			PrintAndClean();
		}
		character = ' ';
	} while (-1);
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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << "\n__________________________________________________\n";
		cout << listCharacter.counter << " reemplazos.";
		listCharacter.counter = 0;
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
				if (!listCharacter.FirstEmpty()) {
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

string TextEditor::ReadRoute(string route) {
	string text = "";
	string line = "";
	ifstream fileRoute(route);
	if (fileRoute.is_open()) {
		while (getline(fileRoute, text))
		{
			line += text + "\n";
		}
		fileRoute.close();
	} else {
		return "0";
	}
	return line;
}

void TextEditor::OpenFileMenu() {
	this->menu.LoadFile();
	string route;
	cout << ">>";
	cin >> route;

	string cont = this->ReadRoute(route);
	if (cont != "0")
	{
		listCharacter.Clean();
		listCharacter.Add(' ', 0, 4);
		for (size_t i = 0; i < cont.size(); i++)
		{
			if (cont[i] == '\n') {
				listCharacter.Add('\n', i + 1, 4);
			}
			else {
				listCharacter.Add(cont[i], i + 1, 4);
			}			
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << "\nArchivo encontrado :D";
		cout << "\n__________________________________________________\n";

		string nameFile = "";
		for (size_t i = route.size() - 1; i > 0; i--)
		{
			if (route[i] == '\\')
			{
				nameFile = route.substr(i + 1, route.size());
				break;
			}
		}
		listFile.Add(nameFile, route);
		system("pause");
		this->FileRead();
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << " Archivo no disponible D:\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		system("pause");
	}
}

void TextEditor::OpenFileMenu(string route) {
	string cont = this->ReadRoute(route);
	if (cont != "0")
	{
		listCharacter.Clean();
		listCharacter.Add(' ', 0, 4);
		for (size_t i = 0; i < cont.size(); i++)
		{
			if (cont[i] == '\n') {
				listCharacter.Add('\n', i + 1, 4);
			}
			else {
				listCharacter.Add(cont[i], i + 1, 4);
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << "\nArchivo encontrado :D";
		cout << "\n__________________________________________________\n";

		string nameFile = "";
		for (size_t i = route.size() - 1; i > 0; i--)
		{
			if (route[i] == '\\')
			{
				nameFile = route.substr(i + 1, route.size());
				break;
			}
		}
		listFile.Add(nameFile, route);
		system("pause");
		this->FileRead();
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << " Archivo no disponible D:\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		system("pause");
	}
}

void TextEditor::OpenRecent() {
	listCharacter.Clean();
	this->menu.MenuOpenRecent();
	
	if (!listFile.IsEmpty())
	{
		listFile.Show();

		string inputText = "";
		bool exit = true;
		while(exit) {
			std::cout << "\n >> ";
			std::cin >> inputText;
			if (inputText== "X") 
			{
				listFile.GenerateGraph("ListaCircular");
				exit = false;
				break;
			}
			else {
				Validator validator;
				if (validator.IsDigit(inputText)) {
					int inputText2 = stoi(inputText);
					File* findFile = listFile.Search(inputText2);
					if (findFile != NULL) {						
						this->OpenFileMenu(findFile->getRoute());
						break;
					}
					else {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						cout << " Archivo no disponible D:\n";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
						system("pause");
					}
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					cout << "Solamente puede ingresar digitos o X.\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
					exit = true;
					inputText;
				}
			}
		}
	}
}

void TextEditor::SaveFile() {
	bool state = true;
	
	this->menu.MenuSave();
	while(state) {
		string search = "";
		cout << ">>";
		cin >> search;
		if (search.length() > 0)
		{
			listCharacter.SaveFile(search);
			listFile.Add(search, "C:\EDD");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			cout << " Guardado correctamente :D\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			state = false;
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			cout << " Ingrese un nombre. \n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			state = true;
		}
	}
}