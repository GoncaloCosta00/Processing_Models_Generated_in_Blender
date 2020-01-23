#include "Vertice.h"

extern bool Verificar_string_numero(string str);

Vertice::Vertice(string dados)
{
	x = 0;
	y = 0; 
	z = 0;

	guardar_dados(dados);
}

Vertice::~Vertice()
{

}

void Vertice::guardar_dados(string dados)
{
	enum coordenadas { X = 0, Y, Z };
	string aux;
	int coordenada = X;
	
	//podia ser feito com sscanf_s mas nao se sabe quantos vertices tem a face
	for (int i = 0; i < dados.size(); ++i)  //percorrer a string
	{
		if (dados[i] == ' ' || i == dados.size() - 1)  //se encontrar um espaco
		{
			if (i == dados.size() - 1 && dados[i] != ' ')
				aux += dados[i];  //adicionar o ultimo digito/caracter se chegar ao final da string

			if (aux == " ");
			else if (Verificar_string_numero(aux))  //verificar se a string e um numero
			{
				switch (coordenada)
				{
				case X:
					x = atof(aux.c_str());
					break;

				case Y:
					y = atof(aux.c_str());
					break;

				case Z:
					z = atof(aux.c_str());
					break;

				default:
					cout << "ERRO: Um dos vértices tem mais de 3 coordenadas!" << endl;
					ERRO = true;
					return;
					break;
				}
				coordenada++;
			}
			else if (aux.size() != 0)  //se a variavel auxiliar nao for um numero valido mas contem caracteres...
			{
				cout << "ERRO: Foram encontrados caracteres não dígitos nas coordenadas dos vertices!" << endl;
				ERRO = true;
				return;
			}
			aux = "";  //reiniciar varivel auxiliar
		}
		else
			aux += dados[i];  //acrescentar proximo caracter da linha
	}

	if (coordenada != Z + 1)
	{
		cout << "ERRO: Um dos vértices tem menos de 3 coordenadas!" << endl;
		ERRO = true;
		return;
	}
}

void Vertice::operator < (Ponto& Pmin) {
	if (Pmin.x > x)
		Pmin.x = x;
	if (Pmin.y > y)
		Pmin.y = y;
	if (Pmin.z > z)
		Pmin.z = z;
}

void Vertice::operator > (Ponto& Pmax) {
	if (Pmax.x < x)
		Pmax.x = x;
	if (Pmax.y < y)
		Pmax.y = y;
	if (Pmax.z < z)
		Pmax.z = z;
}

void Vertice::operator = (Ponto& P) {
	P.x = x;
	P.y = y;
	P.z = z;
}

void Vertice::EscreverXML(XMLWriter& writer)
{
	writer.WriteElementString("X", to_string(x));
	writer.WriteElementString("Y", to_string(y));
	writer.WriteElementString("Z", to_string(z));
}