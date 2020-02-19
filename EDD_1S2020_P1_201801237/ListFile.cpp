#include "ListFile.h"
#include <iostream>
#include <fstream>

ListFile::ListFile() {
	first = NULL;
	last = NULL;
}

int counter = 1;
void ListFile::Add(string name, string route)
{
	File* aux = new File(counter, name, route);
	if (first == NULL) {
		first = aux;
		first->setLink(first);
		last = first;
	}
	else {
		last->setLink(aux);
		aux->setLink(first);
		last = aux;
	}
	counter++;
}

void ListFile::Show()
{
	 File* aux;
	 if (last != NULL)
	 {
		 aux = last->getLink();
		 do {
			 std::cout << aux->getIndex() << ". " << aux->getName() << " : " << aux->getRoute() << "\n";
			 aux = aux->getLink();
		 } while (aux != first);
	 }
}

void ListFile::Clean()
{
	counter = 1;
	first = NULL;
	last = NULL;
}

bool ListFile::IsEmpty()
{
	return first == NULL;
}

File* ListFile::Search(int index)
{
	File* aux;
	aux = last->getLink();
	do {
		if (aux->getIndex() == index)
		{
			return aux;
		}
		aux = aux->getLink();
	} while (aux != first);
	return NULL;
}

void ListFile::GenerateGraph(std::string name)
{
	string fileHead = "digraph G {"
		"node[shape = circle, style=dashed, fillcolor=red];\n";
	string fileFooter = "}";
	string body;
	string bodyTwo;
	string bodyNode;

	ofstream ofs(name + ".dot", ofstream::out);

	int counterFile = 0;
	string textFile = "";

	File* aux;
	aux = last->getLink();
	do {
		body = body + "Node" + to_string(aux->getIndex()) + "[label = " + '"' + "Nombre: " + aux->getName() + " " +
			"\nRuta: \n\t-" + aux->getRoute() + '"' + "]\n";
		bodyNode = bodyNode + "Node" + to_string(aux->getIndex()) + ";";
		counterFile++;
		aux = aux->getLink();
	} while (aux != first);

	for (size_t i = 1; i < counterFile; i++)
	{
		bodyTwo = bodyTwo + "Node" + to_string(i) + "->Node" + to_string(i + 1) + "\n";
	}
	bodyTwo = bodyTwo + "Node" + to_string(counterFile) + "->Node1";


	textFile = fileHead + body + bodyTwo + "{rank=same; " + bodyNode + fileFooter + "}";
	ofs << textFile;
	ofs.close();
	system("dot -Tjpg -o ListaCircular.png ListaCircular.dot");
	system("ListaCircular.png");
}