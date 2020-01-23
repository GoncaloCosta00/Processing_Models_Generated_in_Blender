#pragma once
#include "Lib.h"
#include "Modelo.h"
#include "XMLWriter.h"

class SGestao
{
	list<Modelo*> Lista_Modelos;

public:
	SGestao();
	
	void escrever_ficheiros_carregados_menu();
	bool Load(const string& fich);
	int Contar(Tipo T);
	double AreaModelo(const string& fich);
	Modelo* PesquisarModelo(const string& fich);
	bool Envolvente(const string& fich, Ponto& Pmin, Ponto& Pmax);
	int Memoria();
	int Memoria(const string& fich);
	Modelo* ModeloMaisMemoria();
	int NumInterseccoes(Ponto A, Ponto B);
	bool RemoverModelo(const string& fich);
	void EscreverXML(const string& fich, const string& fich_xml);
	Face* FaceMaiorArea(const string& fich);
	Face* FaceMaiorCurvatura(const string& fich);
	int Numero_modelos_carregados() { return Lista_Modelos.size(); }

	void MostrarModelo(const string& fich);

	~SGestao();
};

