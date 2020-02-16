#include "StackRedo.h"
#include <iostream>

StackRedo::StackRedo()
{
}

StackRedo::~StackRedo()
{
}

void StackRedo::Push(LogChange* p)
{
	LogChange* n;
	n = p;
	n->setNext(top);
	top = n;
}

bool StackRedo::IsEmpty()
{
	return top == NULL;
}

LogChange* StackRedo::Pop()
{
	if (IsEmpty())
		throw "La pila se encuentra vacía.";
	LogChange* aux = top;
	top = top->getNext();
	return aux;
}

void StackRedo::Show()
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

void StackRedo::Clear()
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
