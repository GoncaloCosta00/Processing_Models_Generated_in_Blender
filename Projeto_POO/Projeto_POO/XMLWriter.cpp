#include "XMLWriter.h"

XMLWriter::XMLWriter()
{
	caracteravanco = '	';
	avanco = "";
}

XMLWriter::~XMLWriter()
{
	if (fich.is_open())
		WriteEndDocument();
}


void XMLWriter::WriteStartDocument(string ficheiro)
{
	if (fich.is_open())
	{
		cout << "Está atualmente aberto um ficheiro!" << endl;
		return;
	}
	avanco = "";
	fich.open(ficheiro);
	nome_ficheiro = ficheiro;
	if (!fich.is_open())
		cout << "Não foi possivel criar o ficheiro " << nome_ficheiro << endl;
	else
		cout << "A criar o ficheiro [" << nome_ficheiro << "]" << endl;
}

void XMLWriter::WriteEndDocument()
{
	if (!fich.is_open())
	{
		//cout << "Nenhum ficheiro aberto para fechar!" << endl;
		return;
	}
	if (LI.size() != 0)
		//cout << "A terminar os elementos que ficaram por encerrar! ..." << endl;
	while (LI.size() != 0)
	{
		WriteEndElement();
	}
	fich.close();
	cout << "Ficheiro [" << nome_ficheiro << "] criado com sucesso!" << endl;
}

void XMLWriter::WriteElementString(string el, string valor)
{
	//cout << "A criar o elemento..." << endl;
	fich << avanco << "<" << el << ">";
	//cout << "A criar a string..." << endl;
	fich << valor;
	//cout << "A encerrar o elemento..." << endl;
	fich << "</" << el << ">" << endl;
	//cout << "String adicionada com sucesso!" << endl;
}

void XMLWriter::WriteStartElement(string el)
{
	fich << avanco << "<" << el << ">" << endl;
	avanco += caracteravanco;
	LI.push_front(el);
	//cout << "Elemento criado com sucesso!" << endl;
}

void XMLWriter::WriteEndElement()
{
	string aux;
	if (LI.size() == 0)
	{
		//cout << "Sem elementos por terminar!" << endl;
		return;
	}
	avanco.erase(strlen((char*)&avanco) - 1);
	fich << avanco << "</" << *(LI.begin()) << ">" << endl;
	LI.pop_front();
	//cout << "Elemento encerrado com sucesso!" << endl;
}
