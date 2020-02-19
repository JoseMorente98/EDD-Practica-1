#include "StackUndo.h"
#include <iostream>
#include <fstream>

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

void StackUndo::GenerateGraph(string nombre) {
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
				"Estado:  Revertido\n"
				"Palabra: " + aux->getWord() + "\n"
				"Posicion: (" + to_string(aux->getPositionX()) + "," + to_string(aux->getPositionY()) + ")\n"
				+ '"' + " style=dashed, fillcolor=red]\n";
		}
		else {
			body = body + "NodeLogChange" + to_string(counter) + " [label =  " + '"' + "Palabra Buscada:  " + aux->getSearch() + " \n" +
				"Reemplazada por: " + aux->getReplace() + "\n"
				"Estado:  No revertido\n"
				"Palabra: " + aux->getWord() + "\n"
				"Posicion: (" + to_string(aux->getPositionX()) + "," + to_string(aux->getPositionY()) + ")\n"
				+ '"' + " style=dashed, fillcolor=red]\n";
		}		
		aux = aux->getNext();
		rankLogChange = rankLogChange + "NodeLogChange" + to_string(counter) + ";";
		counter++;
	}

	for (size_t i = 0; i < counter - 1; i++)
	{
		bodyTwo = bodyTwo + "NodeLogChange" + to_string(i) + "->NodeLogChange" + to_string(i + 1);

	}

	textFile = fileHeader + body + bodyTwo + "\n" + "{rank=same; " + rankLogChange + "}\n}";
	ofs << textFile;

	ofs.close();
	system("dot -Tjpg -o StackUndo.png StackUndo.dot");
	system("StackUndo.png");
}