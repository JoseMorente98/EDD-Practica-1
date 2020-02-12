#include <iostream>
using namespace std;

class Menu
{
public:
	void mostrarMenu();
	void menuArchivo();

};

void Menu::mostrarMenu() {
	cout << "UNIVERSIDAD DE SAN CARLOS DE GUATEMALA\n";
	cout << "FACULTAD DE INGENIERIA\n";
	cout << "ESTRUCTURA DE DATOS\n";
	cout << "PRACTICA NO. 1\n";
	cout << "JOSE RAFAEL MORENTE GONZALEZ\n";
	cout << "201801237\n";
	cout << "MENU PRINCIPAL\n";
	cout << "1. Crear Archivo\n";
	cout << "2. Abrir Archivo\n";
	cout << "3. Archivo Reciente\n";
	cout << "4. Salir\n";
}

void Menu::menuArchivo() {
	cout << "CTRL + W (Buscar y Remplazar)\n";
	cout << "CTRL + C (Reportes)\n";
	cout << "CTRL + S (Guardar)\n";
}