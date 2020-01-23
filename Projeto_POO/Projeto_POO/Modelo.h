#pragma once
#include "Lib.h"
#include "Aresta.h"
#include "Vertice.h"
#include "Face.h"
#include "XMLWriter.h"

extern bool Verificar_string_numero(string str);

class Modelo
{
	string nome_ficheiro;
	list<Face*> lista_faces;
	list<Vertice*> lista_vertices;
	Vertice** vetor_vertices;
	list<Aresta*> lista_arestas;
	Aresta** vetor_arestas;

	Ponto PontoMinimo;
	Ponto PontoMaximo;

	Face* Maior_face;
	Face* Maior_curvatura;
	Face* Maior_curvatura_media;

	int numero_arestas_antes;
	int numero_arestas_depois;

	double AreaTotal;
	double PerimetroTotal;

	//tempos
	double tempo_carregamento;
	double tempo_eliminar_arestas;
	double tempo_total;

	bool Adicionar_vertice(string linha);
	bool Adicionar_face(string linha);

	//funcoes auxiliares ----------------------------------------------------------------------------------------------
	void Load();
	bool Adicionar_objeto(string linha);
	void eliminar_arestas_repetidas_v1();
	void eliminar_arestas_repetidas_v2();
	void determinar_curvatura_faces();

public:
	Modelo(const string& fich);
	~Modelo();
	string quem_sou() { return "Modelo"; }

	void Ponto_minimo(Ponto& Pmin);
	void Ponto_maximo(Ponto& Pmax);
	string getnome_ficheiro() { return nome_ficheiro; }
	int get_numero_vertices() { return lista_vertices.size(); }
	int get_numero_arestas() { return lista_arestas.size(); }
	int get_numero_faces() { return lista_faces.size(); }
	double get_area_total() { return AreaTotal; }
	double get_perimetro_total() { return PerimetroTotal; }
	Face* get_face_maior_area() { return Maior_face; }
	double get_tempo_load() { return tempo_carregamento; }
	double get_tempo_eliminar_arestas() { return tempo_eliminar_arestas; }
	double get_tempo_total() { return tempo_total; }
	int get_numero_arestas_faces() { return numero_arestas_antes; }
	int get_numero_arestas_objeto() { return numero_arestas_depois; }
	int NumInterseccoes(Reta R);
	Face* get_face_maior_curva() { return Maior_curvatura; }
	Face* get_face_maior_curva_media() { return Maior_curvatura_media; }
	void EscreverXML(const string& fich_xml);
	int Memoria();

	void mostrar();
};

