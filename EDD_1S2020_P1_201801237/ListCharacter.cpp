#include "ListCharacter.h"
#include <iostream>
#include <fstream>

using namespace std;

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

void ListCharacter::GenerateGraph(std::string fileName)
{
	string fileHead = "digraph G {\n"
		"node[shape = box];\n";

	string fileFooter = "}";

	string body;
	string bodyTwo;

	std::ofstream ofs(fileName + ".dot", std::ofstream::out);

	Character* aux = first;
	string textFile = "";
	int counter = 0;

	while (aux != NULL)
	{
		if (aux->getCharacter() == ' ') {
			body = body + "NodoCharacter" + to_string(counter) + " [label = " + '"' + " " + '"' + "];\n";
		}
		else if (aux->getCharacter() == '\n')
		{
			body = body + "NodoCharacter" + to_string(counter) + " [label = " + '"' + " " + '"' + "];\n";
		}
		else {
			body = body + "NodoCharacter" + to_string(counter) + " [label = " + '"' + aux->getCharacter() + '"' + "];\n";
		}
		aux = aux->getNext();
		counter++;
	}

	for (size_t i = 0; i < counter - 1; i++)
	{
		bodyTwo = bodyTwo + "NodoCharacter" + to_string(i) + "->NodoCharacter" + to_string(i + 1) + ";\nNodoCharacter" + to_string(i + 1) + "->NodoCharacter" + to_string(i) + ";\n";
	}

	textFile = fileHead + body + bodyTwo + fileFooter;
	ofs << textFile;

	ofs.close();
	system("dot -Tjpg -o ListaDoble.png ListaDoble.dot");
	system("ListaDoble.png");
}
