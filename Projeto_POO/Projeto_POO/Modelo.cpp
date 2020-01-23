#include "Modelo.h"

bool ERRO = false;
extern void shellSort(Aresta** V, int tam);

Modelo::Modelo(const string& fich)
{
	vetor_vertices = NULL;
	AreaTotal = 0;
	PerimetroTotal = 0;
	nome_ficheiro = fich;
	Maior_face = NULL;
	vetor_arestas = NULL;
	Maior_curvatura = NULL;
	Maior_curvatura_media = NULL;

	Load();  //carregar dados do ficheiro para a memoria
}

Modelo::~Modelo()  //eliminar dados do modelo
{
	apagar_lista(lista_vertices);
	apagar_lista(lista_faces);
	apagar_lista(lista_arestas);
	if(vetor_vertices)
		delete vetor_vertices;
	if(vetor_arestas)
		delete vetor_arestas;
}

void Modelo::Load()
{
	ifstream ficheiro(nome_ficheiro);
	string linha;
	clock_t tempo_inicio;
	ERRO = false;

	if (!ficheiro.is_open())
	{
		cout << "ERRO: Ocorreu um problema na hora de abrir o ficheiro " << nome_ficheiro << " para analisar!" << endl;
		ERRO = true;
		return;
	}
	cout << "A carregar o ficheiro " << nome_ficheiro << " ..." << endl;
	tempo_inicio = clock();
	while (!ficheiro.eof())  //enquanto nao acabar de ler o ficheiro
	{
		getline(ficheiro, linha);  //obtem 1 linha do ficheiro
		if (!Adicionar_objeto(linha))  //se ocorreu um erro ao adicionar 1 elemento
		{
			ficheiro.close();
			ERRO = true;
			return;
		}
	}
	ficheiro.close();
	tempo_carregamento = (clock() - tempo_inicio) * 1.0 / CLOCKS_PER_SEC;

	cout << "A eliminar as arestas repetidas ..." << endl;
	tempo_inicio = clock();
	//eliminar_arestas_repetidas_v1();
	eliminar_arestas_repetidas_v2();
	tempo_eliminar_arestas = (clock() - tempo_inicio) * 1.0 / CLOCKS_PER_SEC;

	cout << "A determinar as Faces que contem maior curvatura com as vizinhas ..." << endl;
	determinar_curvatura_faces();

	tempo_total = tempo_carregamento + tempo_eliminar_arestas;

	cout << "Ficheiro carregado com sucesso!" << endl;
}

bool Modelo::Adicionar_vertice(string linha)
{
	lista_vertices.push_back(new Vertice(linha));  //adicionar o vertice a lista
	
	if (ERRO)
		return false;

	if (lista_vertices.size() == 1)  //se for o primeiro vertice a ser adicionado, inicializar o ponto maximo e o ponto minimo
	{
		**lista_vertices.begin() = PontoMinimo;
		**lista_vertices.begin() = PontoMaximo;
	}
	else
	{
		list<Vertice*>::iterator it = lista_vertices.end();
		it--;
		**it < PontoMinimo;
		**it > PontoMaximo;
	}

	return true;
}

bool Modelo::Adicionar_face(string linha)
{
	//so se converte a lista para vetor aqui porque primeiro estao os vertices do objeto e so depois as faces a carregar pelo mesmo
	if (vetor_vertices == NULL)  //se a lista de vertices ainda nao foi convertida para vetor
	{
		vetor_vertices = new Vertice*[lista_vertices.size()];  //criar vetor de vertices
		int i = 0;
		
		for (list<Vertice*>::iterator it = lista_vertices.begin(); it != lista_vertices.end(); ++it, ++i)  //copiar dados da lista para o vetor
		{
			vetor_vertices[i] = *it;
		}
	}

	Face* f = new Face(linha, vetor_vertices, lista_vertices.size(), &lista_arestas);

	if (ERRO)
	{
		delete f;
		return false;
	}

	AreaTotal += f->get_area();  //calcular a area do objeto
	if (Maior_face == NULL)
		Maior_face = f;
	else if (*Maior_face < *f)
		Maior_face = f;

	lista_faces.push_back(f);  //adicionar a face na lista

	return true;
}

bool Modelo::Adicionar_objeto(string linha)
{
	if (linha.size() == 0) return true;  //se a linha estiver vazia...

	int i_aux = 0;
	while (i_aux < linha.size() &&  (linha[i_aux] == ' ' || linha[i_aux] == '\n'))
		i_aux++;
	if (i_aux == linha.size())
		return true;

	linha = linha.substr(i_aux);  //remover os caracteres encontrados no ciclo
	
	string tipo = "";
	for (int i = 0; i < linha.size() && linha[i] != ' '; ++i)
	{
		tipo += linha[i];
	}
	
	//adicionar elemento com base no seu tipo
	//.substr(2) isto cria uma string que tem inicio no indice 2 e tem termino no fim da string
	if (tipo[0] == '#')  //se for um comentario...
		return true;
	else if (tipo == "v")  //se for um vertice...
		return Adicionar_vertice(linha.substr(2));
	else if (tipo == "f")  //se for uma face...
		return Adicionar_face(linha.substr(2));
	else  //se for algo que o programa nao esta concebido para
	{
		cout << "ERRO: O programa não se encontra preparado para analisar a variável do tipo [" << tipo << "]" << endl;
		return false;
	}

	return true;
}

void Modelo::eliminar_arestas_repetidas_v1()
{
	numero_arestas_antes = lista_arestas.size();
	int numero_arestas = numero_arestas_antes;
	vetor_arestas = new Aresta* [numero_arestas];
	int i;

	//converter lista num vetor
	i = 0;
	for (list<Aresta*>::iterator it = lista_arestas.begin(); it != lista_arestas.end() && i < numero_arestas; ++i, ++it)
		vetor_arestas[i] = (*it);

	for (int i = 0; i < numero_arestas; ++i)
	{
		for (int k = i + 1; k < numero_arestas; ++k)
		{
			if (vetor_arestas[i] && vetor_arestas[k] && *vetor_arestas[i] == *vetor_arestas[k])  //se as arestas ainda nao foram anuladas e sao iguais
			{
				//atualizar as faces que contem esta aresta
				vetor_arestas[i]->adicionar_face(vetor_arestas[k]->get_face());
				//atualizar a aresta da face
				vetor_arestas[k]->get_face()->mudar_aresta_x(vetor_arestas[k], vetor_arestas[i]);
				vetor_arestas[k] = NULL;
			}
		}
	}

	lista_arestas.clear();
	//copiar apenas as arestas que restaram para uma nova lista de arestas
	for (i = 0; i < numero_arestas; ++i)
	{
		if (vetor_arestas[i] != NULL)
			lista_arestas.push_back(vetor_arestas[i]);
	}

	delete vetor_arestas;
	numero_arestas_depois = lista_arestas.size();
	vetor_arestas = new Aresta * [numero_arestas_depois];
	//converter lista num vetor
	i = 0;
	for (list<Aresta*>::iterator it = lista_arestas.begin(); it != lista_arestas.end() && i < numero_arestas; ++i, ++it)
	{
		vetor_arestas[i] = (*it);
		PerimetroTotal += vetor_arestas[i]->get_perimetro();
	}
}

void Modelo::eliminar_arestas_repetidas_v2()
{
	numero_arestas_antes = lista_arestas.size();
	int numero_arestas = numero_arestas_antes;
	vetor_arestas = new Aresta * [numero_arestas];
	int i;

	//converter lista num vetor
	i = 0;
	for (list<Aresta*>::iterator it = lista_arestas.begin(); it != lista_arestas.end() && i < numero_arestas; ++i, ++it)
		vetor_arestas[i] = (*it);

	//ordenar as arestas por tamanho
	shellSort(vetor_arestas, numero_arestas);
	
	for (int i = 0; i < numero_arestas; ++i)
	{
		for (int k = i + 1; k < numero_arestas; ++k)
		{
			if (vetor_arestas[i] && vetor_arestas[k])  //se as arestas ainda nao foram anuladas
			{
				if (*vetor_arestas[i] < *vetor_arestas[k])
				{
					break;
				}
				else if (*vetor_arestas[i] == *vetor_arestas[k])  //se as aresats sao iguais
				{
					//atualizar as faces que contem esta aresta
					vetor_arestas[i]->adicionar_face(vetor_arestas[k]->get_face());
					//atualizar a aresta da face
					vetor_arestas[k]->get_face()->mudar_aresta_x(vetor_arestas[k], vetor_arestas[i]);
					vetor_arestas[k] = NULL;
				}
			}
		}
	}

	lista_arestas.clear();
	//copiar apenas as arestas que restaram para uma nova lista de arestas
	for (i = 0; i < numero_arestas; ++i)
	{
		if (vetor_arestas[i] != NULL)
			lista_arestas.push_back(vetor_arestas[i]);
	}

	delete vetor_arestas;
	numero_arestas_depois = lista_arestas.size();
	vetor_arestas = new Aresta * [numero_arestas_depois];
	//converter lista num vetor
	i = 0;
	for (list<Aresta*>::iterator it = lista_arestas.begin(); it != lista_arestas.end() && i < numero_arestas; ++i, ++it)
	{
		vetor_arestas[i] = (*it);
		PerimetroTotal += vetor_arestas[i]->get_perimetro();
	}
}

void Modelo::Ponto_minimo(Ponto& Pmin)
{
	Pmin.x = PontoMinimo.x;
	Pmin.y = PontoMinimo.y;
	Pmin.z = PontoMinimo.z;
}

void Modelo::Ponto_maximo(Ponto& Pmax)
{
	Pmax.x = PontoMaximo.x;
	Pmax.y = PontoMaximo.y;
	Pmax.z = PontoMaximo.z;
}

int Modelo::NumInterseccoes(Reta R)
{
	int contador = 0;

	for (list<Face*>::iterator it = lista_faces.begin(); it != lista_faces.end(); ++it)
	{
		contador += (*it)->intersecao(R);
	}

	return contador;
}

void Modelo::mostrar()
{
	cout << "Nome Modelo: " << nome_ficheiro << endl;
	cout << "Envolvente: Pmin(" << PontoMinimo.x << ", " << PontoMinimo.y << ", " << PontoMinimo.z << ") || Pmax(" << PontoMaximo.x << ", " << PontoMaximo.y << ", " << PontoMaximo.z << ")" << endl;
	cout << "Foi reduzido o número de arestas de " << numero_arestas_antes << " para " << numero_arestas_depois << endl;
	cout << "Área do modelo: " << AreaTotal << " unidades de área" << endl;
	cout << "Perimetro do modelo: " << PerimetroTotal << " unidades" << endl;
	cout << "Tempo de load " << tempo_carregamento << " segundos" << endl;
	cout << "Tempo a eliminar arestas repetidas " << tempo_eliminar_arestas << " segundos" << endl;
	cout << "Tempo total " << tempo_total << " segundos" << endl;
	cout << "Área da maior face: " << Maior_face->get_area() << " unidades de área" << endl;
	cout << "Maior curvatura da face com maior curvatura: " << Maior_curvatura->get_maior_curva() << " graus" << endl;
	cout << "Curvatura média da face com maior curvatura média " << Maior_curvatura_media->get_curvatura_media() << " graus" << endl;
}

void Modelo::determinar_curvatura_faces()
{
	for (list<Aresta*>::iterator it = lista_arestas.begin(); it != lista_arestas.end(); ++it)  //percorrer as arestas
	{
		(*it)->determinar_curvatura_faces();
	}

	for (list<Face*>::iterator it = lista_faces.begin(); it != lista_faces.end(); ++it)
	{
		if (!Maior_curvatura)
		{
			Maior_curvatura = *it;
			(*it)->determinar_curvatura_media();
			Maior_curvatura_media = *it;
		}
		else
		{
			if (Maior_curvatura->get_maior_curva() < (*it)->get_maior_curva())
				Maior_curvatura = *it;

			(*it)->determinar_curvatura_media();
			if (Maior_curvatura_media->get_curvatura_media() < (*it)->get_curvatura_media())
				Maior_curvatura_media = *it;
		}
	}
}

int Modelo::Memoria()
{
	int memoria = 0;

	memoria += 5 * sizeof(double);
	memoria += 2 * sizeof(int);
	memoria += 3 * sizeof(Face*);
	memoria += 2 * sizeof(Ponto);
	memoria += 1 * sizeof(Aresta**);
	memoria += 1 * sizeof(list<Aresta*>);
	memoria += 1 * sizeof(Vertice**);
	memoria += 1 * sizeof(list<Vertice*>);
	memoria += 1 * sizeof(list<Face*>);
	memoria += 1 * sizeof(string);
	memoria += 2 * lista_vertices.size() * sizeof(Vertice*);
	memoria += lista_vertices.size() * (*lista_vertices.begin())->Memoria();  //os vertices tem todos a mesma memoria
	memoria += 2 * lista_arestas.size() * sizeof(Aresta*);
	for (int i = 0; i < lista_arestas.size(); ++i)
	{
		memoria += vetor_arestas[i]->Memoria();
	}
	memoria += 1 * lista_faces.size() * sizeof(Face*);
	for (list<Face*>::iterator it = lista_faces.begin(); it != lista_faces.end(); ++it)
	{
		memoria += (*it)->Memoria();
	}

	return memoria;
}

void Modelo::EscreverXML(const string& fich_xml)
{
	XMLWriter writer;
	XMLWriter writer_aux;

	writer.WriteStartDocument(fich_xml);
		writer.WriteStartElement("Modelo");
		
			writer.WriteElementString("Nome", nome_ficheiro);
			writer.WriteElementString("Perimetro", to_string(PerimetroTotal));
			writer.WriteElementString("Area", to_string(AreaTotal));
			writer.WriteElementString("Número_de_arestas_carregadas", to_string(numero_arestas_antes));
			writer.WriteElementString("Número_de_arestas", to_string(numero_arestas_depois));
			
			writer.WriteStartElement("Tempos");
				writer.WriteElementString("Tempo_de_load", to_string(tempo_carregamento));
				writer.WriteElementString("Tempo_a_eliminar_arestas_repetidas", to_string(tempo_eliminar_arestas));
				writer.WriteElementString("Tempo_TOTAL", to_string(tempo_total));
			writer.WriteEndElement();

			writer.WriteStartElement("Face_com_maior_curvatura");
				Maior_curvatura->EscreverXML(writer);
			writer.WriteEndElement();

			writer.WriteStartElement("Face_com_maior_curvatura_média");
				Maior_curvatura_media->EscreverXML(writer);
			writer.WriteEndElement();

			writer.WriteStartElement("Face_com_maior_área");
				Maior_face->EscreverXML(writer);
			writer.WriteEndElement();

			writer.WriteStartElement("Envolvente");
				writer.WriteStartElement("Ponto_minimo");
					writer.WriteElementString("X", to_string(PontoMinimo.x));
					writer.WriteElementString("Y", to_string(PontoMinimo.y));
					writer.WriteElementString("Z", to_string(PontoMinimo.z));
				writer.WriteEndElement();
				writer.WriteStartElement("Ponto_máximo");
					writer.WriteElementString("X", to_string(PontoMaximo.x));
					writer.WriteElementString("Y", to_string(PontoMaximo.y));
					writer.WriteElementString("Z", to_string(PontoMaximo.z));
				writer.WriteEndElement();
			writer.WriteEndElement();
		writer.WriteEndElement();
	writer.WriteEndDocument();
	string file_name;
	string pre_name = "";
	string extencao = "";
	string aux = "";
	string nome_modelo;
	for (int i = fich_xml.size() - 1; i >= 0; --i)
	{
		aux += fich_xml[i];  //grava a extencao do fim para o inicio
		if (fich_xml[i] == '.')
		{
			aux += ']';
			for (int k = aux.size() - 1; k >= 0; --k)  //colloca a extenco na ordem correta de escrita
				extencao += aux[k];

			for (int k = 0; k < i; ++k)  //grava o nome do ficheiro a colocar
			{
				pre_name += fich_xml[k];
			}
			break;
		}
	}
	pre_name += '[';

	for (int i = 0; i < nome_ficheiro.size(); ++i)
	{
		if (nome_ficheiro[i] == '.')
			break;
		aux += nome_ficheiro[i];
	}

	file_name = pre_name + "VERTICES" + extencao;
	writer_aux.WriteStartDocument(file_name);
		writer_aux.WriteStartElement(nome_ficheiro);
			for (list<Vertice*>::iterator it = lista_vertices.begin(); it != lista_vertices.end(); ++it)
			{
				writer_aux.WriteStartElement("Vertice");
					(*it)->EscreverXML(writer_aux);
				writer_aux.WriteEndElement();
			}
		writer_aux.WriteEndElement();
	writer_aux.WriteEndDocument();

	file_name = pre_name + "FACES" + extencao;
	writer_aux.WriteStartDocument(file_name);
		writer_aux.WriteStartElement(nome_ficheiro);
			for (list<Face*>::iterator it = lista_faces.begin(); it != lista_faces.end(); ++it)
			{
				writer_aux.WriteStartElement("Face");
					(*it)->EscreverXML(writer_aux);
				writer_aux.WriteEndElement();
			}
		writer_aux.WriteEndElement();
	writer_aux.WriteEndDocument();

	file_name = pre_name + "ARESTAS" + extencao;
	writer_aux.WriteStartDocument(file_name);
		writer_aux.WriteStartElement(nome_ficheiro);
			for (list<Aresta*>::iterator it = lista_arestas.begin(); it != lista_arestas.end(); ++it)
			{
				writer_aux.WriteStartElement("Aresta");
					(*it)->EscreverXML(writer_aux);
				writer_aux.WriteEndElement();
			}
		writer_aux.WriteEndElement();
	writer_aux.WriteEndDocument();
	
}