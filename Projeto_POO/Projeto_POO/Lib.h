#pragma once

#include <iostream>
#include <fstream>
#include <clocale>
#include <string>
#include <list>
#include <map>
#include <math.h>
#include <time.h>
#include <Windows.h>

#define NomeArquivosOBJ "ficheiros_obj.txt"

#define PI    3.14159265358979323846  /* pi */
#define Largura_menu 60

using namespace std;

#define LimiteVerticesPorFace 3

struct ponto
{
	double x, y, z;
};

#define Ponto struct ponto

struct reta
{
	Ponto A;
	double v[3];
};

#define Reta struct reta

enum Tipo { VERTICE, ARESTA, FACE };

extern bool Verificar_string_numero(string str);

template<class T>
void apagar_lista(list<T>& Lista) {
	if (Lista.size() == 0)
		return;

	for (class list<T>::iterator it = Lista.begin(); it != Lista.end(); ++it)
	{
		delete* it;
	}
	Lista.clear();
}