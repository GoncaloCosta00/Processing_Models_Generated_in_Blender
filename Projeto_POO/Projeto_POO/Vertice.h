#pragma once
#include "Objeto.h"
#include "XMLWriter.h"

class Vertice : public Objeto
{
	double x, y, z;

	//funcoes auxiliares--------------------------------------------------------------------------------------------
	void guardar_dados(string dados);

public:
	Vertice(string dados);
	~Vertice();
	string quem_sou() { return "Vertice"; }
	double get_area() { return 0; }
	double get_prerimetro() { return 0; }
	int Memoria() { return 3 * sizeof(double); }
	void EscreverXML(XMLWriter& writer);

	double getX() { return x; }
	double getY() { return y; }
	double getZ() { return z; }

	void operator < (Ponto& Pmin);
	void operator > (Ponto& Pmax);
	void operator = (Ponto& P);
};

