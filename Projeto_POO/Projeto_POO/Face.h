#pragma once
#include "Objeto.h"
#include "Aresta.h"
#include "XMLWriter.h"

class Face : public Objeto
{
	Vertice** vetor_vertices;
	list<Aresta*> lista_arestas;
	double perimetro;
	double area;
	int numero_vertices;
	list<double> lista_curvaturas;
	double curvatura_media;
	double maior_curvatura;
	double* normal_ao_plano;

	//funcoes auxiliares-----------------------------------------------------------------------------------------------
	void guardar_dados(string dados, Vertice** Vertices, int num_vertices);
	void criar_arestas(list<Aresta*>* Arestas);
	void calcular_area();
	void calcular_area_triangulo();
	int intersecao_triangulo(Reta R);
	
public:
	Face(string dados, Vertice** Vertices, int num_vertices, list<Aresta*>* Arestas);
	~Face();
	string quem_sou() { return "Face"; }
	double get_area() { return area; }
	double get_perimetro() { return perimetro; }
	bool operator > (Face& face);
	bool operator < (Face& face);
	int intersecao(Reta R);
	void mudar_aresta_x(Aresta* de, Aresta* para);
	double* get_normal() { return normal_ao_plano; }
	void operator == (Face& face);
	double get_maior_curva() { return maior_curvatura; }
	double get_curvatura_media() { return curvatura_media; }
	void determinar_curvatura_media();
	void EscreverXML(XMLWriter& writer);
	int Memoria();
};

