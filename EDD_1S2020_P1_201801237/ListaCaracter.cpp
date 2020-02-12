#include "ListaCaracter.h"
Caracter* primero;
Caracter* ultimo;
ListaCaracter::ListaCaracter()
{
	primero = NULL;
	ultimo = NULL;
}

ListaCaracter::~ListaCaracter()
{
}

bool ListaCaracter::IsVacia()
{
	return primero == NULL;
}

void ListaCaracter::InsertarFinal(Caracter *anterior, char entrada)
{
	if (anterior == ultimo) {
		Caracter* aux;
		aux = new Caracter(entrada);
		aux->setAnterior(anterior);
		anterior->setSiguiente(aux);
		anterior = aux;
	}	
}

void ListaCaracter::InsertarInicio(char entrada)
{
	Caracter* aux = new Caracter(entrada);
	if (IsVacia())
	{
		primero = aux;
		ultimo = aux;
	}
	else {
		aux->setSiguiente(primero);
		primero->setAnterior(aux);

		primero = aux;
	}
}

void ListaCaracter::Insertar(char entrada)
{
	if (IsVacia()) {
		InsertarInicio(entrada);
	}
	else {
		InsertarFinal(ultimo, entrada);
	}
}

void ListaCaracter::Visualizar()
{
	Caracter* n;
	n = primero;
	while (n != NULL)
	{
		std::cout << n->getDato();
		n = n->getSiguiente();
	}
}
