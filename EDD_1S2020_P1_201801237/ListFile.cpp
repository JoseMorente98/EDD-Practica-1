#include "ListFile.h"
#include <iostream>
int counter = 1;
void ListFile::Add(string name, string route)
{
	File* aux = new File(counter, name, route);
	if (IsEmpty()) {
		first = aux;
		first->setLink(first);
		last = first;
	}
	else {
		last->setLink(aux);
		aux->setLink(first);
		last = first;
	}
	counter++;
}

void ListFile::Show()
{
	File* aux;
	aux = last->getLink();
	do {
			std::cout << aux->getIndex() << ". " << aux->getName() << " : " << aux->getRoute() ;
			aux = aux->getLink();
	 } while (aux != first);
}

void ListFile::Clean()
{
	first = NULL;
	last = NULL;
}

bool ListFile::IsEmpty()
{
	return first == NULL;
}

string ListFile::Search(int index)
{
	File* aux;
	aux = last->getLink();
	do {
		if (aux->getIndex() == index)
		{
			return aux->getRoute();
		}
		aux = aux->getLink();
	} while (aux != first);
	return "NULL";
}

void ListFile::GenerateGraph(std::string name)
{
	File* aux;
	aux = last->getLink();
	do {
		std::cout << aux->getIndex() << ". " << aux->getName() << " : " << aux->getRoute();
		aux = aux->getLink();
	} while (aux != first);
}
