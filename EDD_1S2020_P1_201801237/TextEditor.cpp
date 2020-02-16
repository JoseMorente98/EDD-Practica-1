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
				//MenuArchivo();
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
	bool estado = true;
	char foo;
	cout << ">> ";

	while (estado) {

		foo = _getch();
		int ascii = foo;
		if (ascii == 121) {
			estado = false;

			system("cls");
			this->listCharacter.Show();
		}
		else {
			this->listCharacter.Add(foo, 0, 0);
			std::cout << foo;
		}
	}
}

