#pragma once
#include "Lib.h"

class XMLWriter
{
	char caracteravanco;
	string avanco;
	ofstream fich;
	list<string> LI;
	string nome_ficheiro;

public:
	XMLWriter();
	~XMLWriter();
	void WriteStartDocument(string ficheiro);
	void WriteEndDocument();
	void WriteElementString(string el, string valor);
	void WriteStartElement(string el);
	void WriteEndElement();
};

