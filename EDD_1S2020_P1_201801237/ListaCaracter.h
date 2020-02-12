#pragma once
#include "Caracter.h"
class ListaCaracter
{
public:
	ListaCaracter();
	~ListaCaracter();
	bool IsVacia();
	void InsertarFinal(Caracter* anterior, char entrada);
	void InsertarInicio(char entrada);
	void Insertar(char entrada);
	void Visualizar();
};

