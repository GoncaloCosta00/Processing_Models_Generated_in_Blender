#include "Lib.h"
#include "Aresta.h"

bool Verificar_string_numero(string str)
{
	int aux1, aux2;
	if (str.size() == 0) return false;

	string str_validar = "0123456789.eE-+";  //string com os caracteres aceitaveis

	if (str[0] == '-' || str[0] == '+')  //se o primeiro caractere for o + ou o -....
		str = str.substr(1);

	if (str[0] == '.' && str.size() == 1) return false;  //se a string apenas for "." ...

	if (count(str.begin(), str.end(), '.') <= 1 && str.find_first_not_of(str_validar) > str.size())  //se so existir 1 . e nao for encontrado nenhum caractere nao valido...
		return true;

	//verificar se a string contem algo acerca de exponenciais  e-5   E+2   etc
	aux1 = count(str.begin(), str.end(), 'e');
	aux2 = count(str.begin(), str.end(), 'E');
	if (aux1 > 1 || aux2 > 1) return false;
	if (aux1 == 1 && aux2 == 1) return false;

	int menos = count(str.begin(), str.end(), '-');
	int mais = count(str.begin(), str.end(), '+');
	if (aux1 || aux2)
	{
		if (menos > 1 || mais > 1) return false;
		if (menos == 1 && mais == 1) return false;
		return true;
	}

	return false;
}

void shellSort(Aresta** V, int n)
{
	int h = 1;
	int i, j;
	Aresta* pivo; // Para insertion 
	do
		h = (3 * h) + 1;
	while (h < n);

	do {
		h /= 3;
		// insertion 
		for (i = h;i < n;i++) {
			pivo = V[i];
			j = i - h;
			while ((j >= 0) && (*pivo < *V[j])) {
				V[j + h] = V[j];
				j = j - h;
			}
			V[j + h] = pivo;
		}
		// insertion 

	} while (h > 1);
}

double* produto_externo(Vertice *v1, Vertice* v2, Vertice* v3)
{
	double a, b, c;
	double d, e, f;
	double* u = new double[3];
	//v2 -> v1
	a = v1->getX() - v2->getX();
	b = v1->getY() - v2->getY();
	c = v1->getZ() - v2->getZ();

	//v2 -> v3
	d = v3->getX() - v2->getX();
	e = v3->getY() - v2->getY();
	f = v3->getZ() - v2->getZ();

	//resultado do produto externo
	u[0] = (b * f) - (c * e);
	u[1] = (c * d) - (a * f);
	u[2] = (a * e) - (b * d);

	return u;
}

double area_triangulo(Ponto I, Vertice* v1, Vertice* v2)
{
	double a, b, c;
	double d, e, f;
	double u[3];
	//v2 -> v1
	a = v1->getX() - v2->getX();
	b = v1->getY() - v2->getY();
	c = v1->getZ() - v2->getZ();

	//v2 -> v3
	d = I.x - v2->getX();
	e = I.y - v2->getY();
	f = I.z - v2->getZ();

	//resultado do produto externo
	u[0] = (b * f) - (c * e);
	u[1] = (c * d) - (a * f);
	u[2] = (a * e) - (b * d);

	return (sqrt(pow(u[0], 2) + pow(u[1], 2) + pow(u[2], 2))) / 2.0;
}