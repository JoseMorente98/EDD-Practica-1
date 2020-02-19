#include "ListCharacter.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

Character* firstReplace = NULL;
Character* lastReplace = NULL;

bool ListCharacter::IsEmpty()
{
	return first == NULL;
}

void ListCharacter::Add(char c, int x, int y) {
	Character* aux =  new Character(c, x, y);

	if (first == NULL) {
		first = aux;
		first->setNext(NULL);
		first->setPrevious(NULL);
		last = first;
	}
	else {
		if (IsBetween(x, y)) {
			Character* aux2 = new Character();
			aux2 = first;
			while (aux2 != NULL) {
				if (aux2->getPositionX() == x && aux2->getPositionY() == y) {
					aux2->getPrevious()->setNext(aux);
					aux->setPrevious(aux2->getPrevious());
					aux2->setPrevious(aux);
					aux->setNext(aux2);
					break;
				}
				aux2 = aux2->getNext();
			}
		}
		else {
			last->setNext(aux);
			aux->setNext(NULL);
			aux->setPrevious(last);
			last = aux;
		}
		this->Order();
	}
}

bool ListCharacter::IsBetween(int x, int y)
{
	Character* aux2 = new Character();
	int counter = 0;
	aux2 = first;
	while (aux2 != NULL) {
		if (aux2->getPositionX() == x && aux2->getPositionY() == y) {
			counter++;
			break;
		}
		aux2 = aux2->getNext();
	}
	if (counter != 0)
	{
		return true;
	}
	return false;
}

void ListCharacter::Delete(int x, int y)
{
	Character* aux = new Character();
	aux = first;
	Character* previous = new Character();
	previous = NULL;
	bool find = false;
	if (!IsEmpty()) {
		
		while (aux != NULL && find != true) {

			if (aux->getPositionX() == x && aux->getPositionY()== y) {

				if (aux == first) {
				}
				else if (aux == last) {
					previous->setNext(NULL);
					last = previous;
				}
				else {
					previous->setNext(aux->getNext());
					aux->getNext()->setPrevious(previous);
				}
				find = true;
			}
			previous = aux;
			aux = aux->getNext();
		}
	}
	Order();
}

bool ListCharacter::Search(string search) {
	vector<string> similarText;
	string textSearch = search;
	string textSearch2 = ";";
	int quantity = 0;

	size_t findWord = textSearch.find(textSearch2);

	if (findWord != string::npos) {

		similarText.push_back(search.substr(0, findWord) + " ");

		similarText.push_back(search.substr(findWord + 1, search.size()) + " ");

		Character* aux = first;
		for (size_t i = 0; i < similarText[0].size(); i++)
		{
			while (aux != NULL)
			{
				if (aux->getCharacter() == similarText[0][i])
				{
					quantity++;
					aux = aux->getNext();
					break;
				}
				else
				{
					aux = aux->getNext();
				}
			}
		}
		if (quantity == similarText[0].size())
		{
			Replace(this->DeleteSpace(similarText[0]), this->DeleteSpace(similarText[1]));
			counter++;
			this->Search(this->DeleteSpace(search));
			return true;
		}
	}
	return false;
}

void ListCharacter::Replace(string search, string replace) {
	Character* aux = first;
	Character* nodeFirst;
	Character* nodeLast;
	Character* nodeAux;
	string linkTogether;

	do
	{
		if (aux->getCharacter() == search[0] && (aux->getPrevious() == NULL || aux->getPrevious()->getCharacter() == ' ' || aux->getPrevious()->getCharacter() == '.' || aux->getPrevious()->getCharacter() == ',' || aux->getPrevious()->getCharacter() == '\n'))
		{
			while (aux->getCharacter() != ' ')
			{
				linkTogether += aux->getCharacter();
				if (aux->getCharacter() == NULL || aux->getNext()->getCharacter() == ' ')
				{
					break;
				}
				aux = aux->getNext();
			}

			if (search == linkTogether)
			{
				nodeLast = aux;
				while (aux->getCharacter() != search[0])
				{
					aux = aux->getPrevious();
				}

				nodeFirst = aux;
				if (nodeFirst != first)
				{
					nodeFirst = aux->getPrevious();
				}

				for (int i = 0; i < replace.size(); i++)
				{
					nodeAux = new Character(replace[i], 0, 0);

					nodeFirst->setNext(nodeAux);
					nodeAux->setPrevious(nodeFirst);

					if (i == replace.size() - 1)
					{
						if (nodeLast != last)
						{
							nodeAux->setNext(nodeLast->getNext());
							nodeLast->getNext()->setPrevious(nodeAux);
						}
						else
						{
							last = nodeAux;
						}
					}

					nodeFirst = nodeFirst->getNext();

					if (nodeFirst->getPrevious() != NULL && nodeFirst->getPrevious() == first && nodeFirst->getPrevious()->getCharacter() == search[0])
					{
						nodeFirst->getPrevious()->setNext(NULL);
						nodeFirst->setPrevious(NULL);
						first = nodeFirst;
					}
				}
				aux = nodeFirst;
			}
		}

		aux = aux->getNext();
	} while (aux != NULL);
	this->Order();
}

inline string ListCharacter::DeleteSpace(string& text)
{
	text.erase(0, text.find_first_not_of(' '));       //prefixing spaces
	text.erase(text.find_last_not_of(' ') + 1);         //surfixing spaces
	return text;
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
			//std::cout << aux->getCharacter() << "(" << aux->getPositionX()  << "," << aux->getPositionY() << ")";
			if (aux->getCharacter() == '\n') {
				std::cout << "\n ";
			}
			else {
				std::cout << aux->getCharacter();
			}			
			aux = aux->getNext();
		}
	}
}

void ListCharacter::GenerateGraph(std::string fileName)
{
	Character* aux = first->getNext();
	string fileHead = "digraph G {\n"
		"node[shape = box];\n";
	string fileFooter = "}";

	string body;
	string bodyTwo;

	std::ofstream ofs(fileName + ".dot", std::ofstream::out);

	string textFile = "";
	int counter = 0;

	while (aux != NULL)
	{
		if (aux->getCharacter() == ' ') {
			body = body + "Node" + to_string(counter) + " [label = " + '"' + " " + '"' + " shape=circle, style=dashed, fillcolor=darkgreen];\n";
		}
		else if (aux->getCharacter() == '\n')
		{
			body = body + "Node" + to_string(counter) + " [label = " + '"' + " " + '"' + " shape=circle, style=dashed, fillcolor=darkgreen];\n";
		}
		else {
			body = body + "Node" + to_string(counter) + " [label = " + '"' + aux->getCharacter() + '"' + " shape=circle, style=dashed, fillcolor=darkgreen];\n";
		}
		aux = aux->getNext();
		counter++;
	}

	for (size_t i = 0; i < counter - 1; i++)
	{
		bodyTwo = bodyTwo + "Node" + to_string(i) + "->Node" + to_string(i + 1) + ";\nNode" + to_string(i + 1) + "->Node" + to_string(i) + ";\n";
	}

	textFile = fileHead + body + bodyTwo + fileFooter;
	ofs << textFile;

	ofs.close();
	system("dot -Tjpg -o ListaDoble.png ListaDoble.dot");
	system("ListaDoble.png");
}

void ListCharacter::SaveFile(string nombre) {
	Character* aux = first->getNext();
	string texto = "";

	if (aux != NULL)
	{
		ofstream fout;
		string routeFile = "C:" + to_string('\\') + "EDD" + to_string('\\') + nombre + ".txt";
		fout.open(routeFile);
		while (aux != NULL)
		{
			fout << aux->getCharacter();
			aux = aux->getNext();
		}
		fout.close();
	}
}

bool ListCharacter::FirstEmpty()
{
	return first->getNext() == NULL;
}