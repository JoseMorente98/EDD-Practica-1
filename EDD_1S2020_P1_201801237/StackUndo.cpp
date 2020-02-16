#include "StackUndo.h"
#include <iostream>

StackUndo::StackUndo()
{
}

StackUndo::~StackUndo()
{
}

void StackUndo::Push(LogChange* p)
{
	LogChange* n;
	n = p;
	n->setNext(top);
	top = n;
}

bool StackUndo::IsEmpty()
{
	return top == NULL;
}

LogChange* StackUndo::Pop()
{
	if (IsEmpty())
		throw "La pila se encuentra vacía.";
	LogChange* aux = top;
	top = top->getNext();
	return aux;
}

void StackUndo::Show()
{
	if (!IsEmpty()) {
		LogChange* aux;
		aux = top;

		while (aux != NULL)
		{
			cout << "\t" << aux->getSearch() << endl;
			aux = aux->getNext();
		}
	}
}

void StackUndo::Clear()
{
	if (!IsEmpty()) {
		LogChange* aux;

		while (top != NULL)
		{
			aux = top;
			top = aux->getNext();
			delete(aux);
		}
	}
}
