#include "StackRedo.h"
#include <iostream>
#include <fstream>

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

void StackRedo::GenerateGraph(string nombre) {
	string fileHeader = "digraph G {"
		"node[shape = box];\n";

	string body;
	string bodyTwo;
	string rankLogChange;

	std::ofstream ofs(nombre + ".dot", std::ofstream::out);

	LogChange* aux;
	aux = top;
	int counter = 0;
	string textFile = "";

	while (aux != NULL)
	{
		if (aux->getState()) {
			body = body + "NodeLogChange" + to_string(counter) + " [label =  " + '"' + "Palabra Buscada:  " + aux->getSearch() + " \n" +
				"Reemplazada por: " + aux->getReplace() + "\n"
				"Estado: Revertido\n"
				"Palabra: " + aux->getWord() + "\n"
				"Posicion: (" + to_string(aux->getPositionX()) + "," + to_string(aux->getPositionY()) + ")\n"
				+ '"' + " style=dashed, fillcolor=navy]\n";
		}
		else {
			body = body + "NodeLogChange" + to_string(counter) + " [label =  " + '"' + "Palabra Buscada:  " + aux->getSearch() + " \n" +
				"Reemplazada por: " + aux->getReplace() + "\n"
				"Estado: No revertido\n"
				"Palabra: " + aux->getWord() + "\n"
				"Posicion: (" + to_string(aux->getPositionX()) + "," + to_string(aux->getPositionY()) + ")\n"
				+ '"' + " style=dashed, fillcolor=navy]\n";
		}
		aux = aux->getNext();
		rankLogChange = rankLogChange + "NodeLogChange" + to_string(counter) + ";";
		counter++;
	}

	for (size_t i = 0; i < counter - 1; i++)
	{
		bodyTwo = bodyTwo + "NodeLogChange" + to_string(i) + "->NodeLogChange" + to_string(i + 1);

	}

	textFile = fileHeader + body + bodyTwo + "\n"  + "{rank=same; " + rankLogChange + "}\n}";
	ofs << textFile;

	ofs.close();
	system("dot -Tjpg -o StackRedo.png StackRedo.dot");
	system("StackRedo.png");
}