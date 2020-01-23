#pragma once
#include "Objeto.h"
#include "Vertice.h"
#include "XMLWriter.h"

class Face;

class Aresta : public Objeto
{
	double comprimento;
	Vertice* v1;
	Vertice* v2;
	list<Face*> lista_faces;
	Face** vetor_faces;
	void converter_lista_faces();

public:
	Aresta(Vertice* V1, Vertice* V2, Face* f);
	~Aresta();
	string quem_sou() { return "Aresta"; }
	double get_area() { return 0; }
	double get_perimetro() { return comprimento; }
	Face* get_face() { return *lista_faces.begin(); }
	void adicionar_face(Face* face);
	bool operator == (Aresta& aresta);
	bool operator > (Aresta& aresta);
	bool operator < (Aresta& aresta);
	void determinar_curvatura_faces();
	void EscreverXML(XMLWriter& writer);
	int Memoria();
};
