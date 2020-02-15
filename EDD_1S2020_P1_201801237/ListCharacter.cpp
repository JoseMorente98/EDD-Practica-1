#include "ListCharacter.h"
#include <iostream>
Character* firstReplace = NULL;
Character* lastReplace = NULL;

bool ListCharacter::IsEmpty()
{
	return first == NULL;
}

void ListCharacter::Add(char c, int x, int y)
{
	Character* aux  = new Character(c, x, y);

	if (IsEmpty()) {
		first = aux;
		last = first;
	}
	else {
		if (IsBetween(x, y)) {
			Character* temp = new Character();
			temp = first;
			while (temp != NULL) {
				if (temp->getPositionX() == x && temp->getPositionY() == y) {
					temp->getPrevious()->setPrevious(aux);
					aux->setPrevious(temp->getPrevious());
					temp->setPrevious(aux);
					aux->setNext(temp);
					break;
				}
				temp = temp->getNext();
			}
		}
		else {
			last->setNext(aux);
			aux->setNext(NULL);
			aux->setPrevious(last);
			last = aux;
		}
	}
}

void ListCharacter::AddReplace(char c, int x, int y)
{
	Character* aux;
	aux = new Character(c, x, y);
	if (firstReplace == NULL) {
		firstReplace = aux;
		firstReplace->setNext(NULL);
		firstReplace->setPrevious(NULL);
		lastReplace = firstReplace;
	}
	else {
		lastReplace->setNext(aux);
		aux->setNext(NULL);
		aux->setNext(lastReplace);
		lastReplace = aux;
	}
}

bool ListCharacter::IsBetween(int x, int y)
{
	Character* temp = new Character();
	int counter = 0;
	temp = first;
	while (temp != NULL) {
		if (temp->getPositionX() == x && temp->getPositionY() == y) {
			counter++;
			break;
		}
		temp = temp->getNext();
	}
	if (counter != 0)
	{
		return true;
	}
	return false;
}

void ListCharacter::Delete(int x, int y)
{
	
}

bool ListCharacter::Search(std::string search)
{

	return false;
}

void ListCharacter::Clean()
{
	first = NULL;
	firstReplace = NULL;
}

void ListCharacter::Order()
{
	int x = 0;
	int y = 4;
	Character* aux = new Character();
	aux = first;
	bool encontrado = false;
	if (!IsEmpty()) {
		while (aux != NULL) {

			if (aux->getCharacter() == '\n') {
				y++;
				x = 0;
			}
			aux->setPositionX(x);
			aux->setPositionY(y);
			x++;
			aux = aux->getNext();
		}
	}
}

void ListCharacter::Show()
{
	if (!IsEmpty()) {
		Character* aux;
		aux = first;
		while (aux != NULL)
		{
			std::cout << aux->getCharacter();
			aux = aux->getNext();
		}
	}
}
