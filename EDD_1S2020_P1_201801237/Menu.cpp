#include "Menu.h"
#include <iostream>
#include <windows.h>

using namespace std;

void Menu::MainMenu()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	cout << "__________________________________________________\n";
	cout << "UNIVERSIDAD DE SAN CARLOS DE GUATEMALA\n";
	cout << "FACULTAD DE INGENIERIA\n";
	cout << "ESTRUCTURA DE DATOS A\n";
	cout << "PRACTICA NO. 1\n";
	cout << "JOSE RAFAEL MORENTE GONZALEZ\n";
	cout << "201801237\n";
	cout << "MENU PRINCIPAL\n";
	cout << "1. Crear Archivo\n";
	cout << "2. Abrir Archivo\n";
	cout << "3. Archivo Reciente\n";
	cout << "4. Salir\n";
	cout << "__________________________________________________\n";

}

void Menu::MenuFile()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	cout << " CTRL + W (Buscar y Remplazar)\n";
	cout << " CTRL + C (Reportes)\n";
	cout << " CTRL + S (Guardar)		CTRL + X (Escape)\n";
	cout << " __________________________________________________\n";
}

void Menu::MenuReports()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	cout << "\n __________________________________________________\n";
	cout << " REPORTES\n";
	cout << " __________________________________________________\n";
	cout << " 1. Lista de Caracteres\n";
	cout << " 2. Pila Deshacer\n";
	cout << " 3. Pila Rehacer\n";
	cout << " 4. Salir\n";
	cout << " __________________________________________________\n";
}