#include "Face.h"

extern double* produto_externo(Vertice* v1, Vertice* v2, Vertice* v3);
extern double area_triangulo(Ponto I, Vertice* v1, Vertice* v2);

Face::Face(string dados, Vertice** Vertices, int num_vertices, list<Aresta*>* Arestas)
{
	perimetro = 0;
	area = 0;
	curvatura_media = 0;
	normal_ao_plano = NULL;
	maior_curvatura = 0;

	guardar_dados(dados, Vertices, num_vertices);
	if (ERRO)
		return;
	criar_arestas(Arestas);
	calcular_area();
}

Face::~Face()
{
	lista_curvaturas.clear();
	lista_arestas.clear();
	if(vetor_vertices)
		delete vetor_vertices;
	if(normal_ao_plano)
		delete normal_ao_plano;
}

list<int>* obter_lista_posicoes_vertices(string dados, int num_vertices)
{
	list<int>* vertices = new list<int>;
	string aux = "";
	int aux_i;

	//podia ser feito com sscanf_s mas nao se sabe quantos vertices tem a face
	for (int i = 0; i < dados.size(); ++i)  //percorrer a string
	{
		if (dados[i] == ' ' || i == dados.size() - 1)  //se encontrar um espaco
		{
			if(i == dados.size() - 1 && dados[i] != ' ')
				aux += dados[i];  //adicionar o ultimo digito/caracter se chegar ao final da string

			if (Verificar_string_numero(aux))  //verificar se a string e um numero
			{
				aux_i = atoi(aux.c_str());
				if (aux_i > num_vertices)  //se for indicado um vertice que nao existe (posicao superior ao numero de vertices carregados)
				{
					cout << "ERRO: Foi mencionado um vertice que não existe numa das faces!" << endl;
					vertices->clear();
					delete vertices;
					return NULL;
				}
				vertices->push_back(aux_i - 1);  //o vertice ja e adicionado em formato de indice para facilitar nos calculos posteriormente
			}
			else if (aux.size() != 0)  //se a variavel auxiliar nao for um numero valido mas contem caracteres...
			{
				cout << "ERRO: Foram encontrados caracteres não dígitos nos vertices de uma das faces!" << endl;
				vertices->clear();
				delete vertices;
				return NULL;
			}
			aux = "";  //reiniciar varivel auxiliar
		}
		else
			aux += dados[i];  //acrescentar proximo caracter da linha
	}

	return vertices;
}

void Face::guardar_dados(string dados, Vertice** Vertices, int num_vertices)
{
	list<int>* vertices;

	vertices = obter_lista_posicoes_vertices(dados, num_vertices);
	if (!vertices)  //se nao foi possivel criar uma lista com as posicoes dos vertices...
	{
		ERRO = true;
		return;
	}

	if (vertices->size() > LimiteVerticesPorFace)
	{
		cout << "ERRO: O programa não foi concebido para analisar faces com " << vertices->size() << " vertices!" << endl;
		delete vertices;
		ERRO = true;
		return;
	}

	if (vertices->size() < 3)
	{
		cout << "ERRO: Foi introduzida uma suposta face com " << vertices->size() << " vertices!" << endl;
		delete vertices;
		ERRO = true;
		return;
	}

	numero_vertices = vertices->size();
	vetor_vertices = new Vertice*[vertices->size()];
	int i = 0;
	for (list<int>::iterator indices = (*vertices).begin(); indices != (*vertices).end(); ++indices, ++i)
	{
		vetor_vertices[i] = Vertices[*indices];
	}

	delete vertices;
}

void Face::criar_arestas(list<Aresta*>* Arestas)
{
	Aresta* aux = new Aresta(vetor_vertices[0], vetor_vertices[numero_vertices-1], this);
	perimetro += aux->get_perimetro();
	lista_arestas.push_back(aux);
	(*Arestas).push_back(aux);

	for (int i = 0; i < numero_vertices - 1; ++i)
	{
		aux = new Aresta(vetor_vertices[i], vetor_vertices[i + 1], this);
		perimetro += aux->get_perimetro();
		lista_arestas.push_back(aux);
		(*Arestas).push_back(aux);
	}
}

void Face::calcular_area_triangulo()
{
	double a, b, c;
	double d, e, f;

	if (!normal_ao_plano)
	{
		Vertice* v1 = vetor_vertices[0];  //primeiro vertice
		Vertice* v2 = vetor_vertices[1];  //segundo vertice
		Vertice* v3 = vetor_vertices[2];  //terceiro vertice
		normal_ao_plano = produto_externo(v1, v2, v3);
	}

	area = (sqrt(pow(normal_ao_plano[0], 2) + pow(normal_ao_plano[1], 2) + pow(normal_ao_plano[2], 2))) / 2.0;
}

void Face::calcular_area()
{
	switch (numero_vertices)
	{
	case 3:
		calcular_area_triangulo();
		break;

	default:
		ERRO = 1;
		break;
	}
}

bool Face::operator > (Face& face)
{
	if (area > face.get_area())
		return true;
	else
		return false;
}

bool Face::operator < (Face & face)
{
	if (area < face.get_area())
		return true;
	else
		return false;
}

int Face::intersecao_triangulo(Reta R)
{
	double denominador, t;
	Ponto I;

	Vertice* v1 = vetor_vertices[0];  //primeiro vertice
	Vertice* v2 = vetor_vertices[1];  //segundo vertice
	Vertice* v3 = vetor_vertices[2];  //terceiro vertice

	if (!normal_ao_plano)
	{
		normal_ao_plano = produto_externo(v1, v2, v3);
	}

	denominador = (normal_ao_plano[0] * R.v[0]) + (normal_ao_plano[1] * R.v[1]) + (normal_ao_plano[2] * R.v[2]);
	if (denominador == 0) //reta paralela
		return 0;

	double d = -((normal_ao_plano[0] * v2->getX()) + (normal_ao_plano[1] * v2->getY()) + (normal_ao_plano[2] * v2->getZ()));

	t = -(d + ((normal_ao_plano[0] * R.A.x) + (normal_ao_plano[1] * R.A.y) + (normal_ao_plano[2] * R.A.z))) / denominador;

	I.x = R.A.x + t * R.v[0];
	I.y = R.A.y + t * R.v[1];
	I.z = R.A.z + t * R.v[2];

	double Atriangulo_Iv1v2;
	double Atriangulo_Iv2v3;
	double Atriangulo_Iv1v3;

	Atriangulo_Iv1v2 = area_triangulo(I, v1, v2);
	Atriangulo_Iv2v3 = area_triangulo(I, v2, v3);
	Atriangulo_Iv1v3 = area_triangulo(I, v1, v3);
	
	double area_3_triangulos = Atriangulo_Iv1v2 + Atriangulo_Iv2v3 + Atriangulo_Iv1v3;
	double per_erro = 0.000000000001;
	if (area_3_triangulos < area + per_erro && area_3_triangulos > area - per_erro)  //se a soma da area dos 3 triangulos for igual a area da face
		return 1;   //a reta interseta a face

	return 0;  //nao interseta
}

int Face::intersecao(Reta R)
{
	switch (numero_vertices)
	{
	case 3:
		return intersecao_triangulo(R);
		break;

	default:
		ERRO = 1;
		return 0;
		break;
	}
}

void Face::mudar_aresta_x(Aresta* de, Aresta* para)
{
	for (list<Aresta*>::iterator it = lista_arestas.begin(); it != lista_arestas.end(); ++it)
	{
		if (*it == de)
		{
			delete* it;
			*it = para;
			return;
		}
	}
}

void Face::operator == (Face& face)
{
	double cos_angulo;
	
	cos_angulo = (normal_ao_plano[0] * face.normal_ao_plano[0]) + (normal_ao_plano[1] * face.normal_ao_plano[1]) + (normal_ao_plano[2] * face.normal_ao_plano[2]);
	cos_angulo = cos_angulo / (sqrt(pow(normal_ao_plano[0], 2) + pow(normal_ao_plano[1], 2) + pow(normal_ao_plano[2], 2)) + sqrt(pow(face.normal_ao_plano[0], 2) + pow(face.normal_ao_plano[1], 2) + pow(face.normal_ao_plano[2], 2)));

	//acos apenas calcula os valores entre -1 e 1 logo...
	while (cos_angulo < -1 || cos_angulo > 1)
	{
		if (cos_angulo < -1)
			cos_angulo += 2;

		if (cos_angulo > 1)
			cos_angulo -= 2;
	}

	double angulo = acos(cos_angulo);

	//converter de radianos para graus
	//   180   ------------   pi
	//   x   ------------   angulo
	angulo = angulo * 180 / PI;
	
	curvatura_media += angulo;
	if (maior_curvatura < angulo)
		maior_curvatura = angulo;
	lista_curvaturas.push_back(angulo);

	face.curvatura_media += angulo;
	if (face.maior_curvatura < angulo)
		face.maior_curvatura = angulo;
	face.lista_curvaturas.push_back(angulo);
}

void Face::determinar_curvatura_media()
{
	if(lista_curvaturas.size())
		curvatura_media = curvatura_media / lista_curvaturas.size();
}

int Face::Memoria()
{
	int memoria = 0;

	memoria += 4 * sizeof(double);
	memoria += lista_curvaturas.size() * sizeof(double);
	memoria += numero_vertices * sizeof(Vertice*);
	memoria += 1 * sizeof(Vertice**);
	memoria += 1 * sizeof(list<Aresta*>);
	memoria += lista_arestas.size() * sizeof(Aresta*);
	memoria += 1 * sizeof(int);
	memoria += 1 * sizeof(list<double>);
	memoria += 1 * sizeof(double*);

	return memoria;
}

void Face::EscreverXML(XMLWriter& writer)
{
	writer.WriteElementString("Perimetro", to_string(perimetro));
	writer.WriteElementString("Area", to_string(area));
	writer.WriteElementString("Curvatura_média_entre_faces_vizinhas", to_string(curvatura_media));
	writer.WriteElementString("Maior_curvatura_entre_faces_vizinhas", to_string(maior_curvatura));

	writer.WriteStartElement("Vertices");
	for (int i = 0; i < numero_vertices; ++i)
	{
		writer.WriteStartElement("Vertice");
			vetor_vertices[i]->EscreverXML(writer);
		writer.WriteEndElement();
	}
	writer.WriteEndElement();
}
