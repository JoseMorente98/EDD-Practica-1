#pragma once
#include <string>
using namespace std;
class File
{
public:
	/*
	   PROPIEDADES
   */
	int index;
	string name;
	string route;
	File* link;
	File(int i, string name, string route);
	File();
	virtual ~File();

	/*
		GETTER'S
	 */
	File* getLink() const;
	int getIndex() const;
	string getName() const;
	string getRoute() const;

	/*
		SETTER'S
	 */
	void setIndex(int a);
	void setName(string a);
	void setRoute(string a);
	void setLink(File* a);
};

