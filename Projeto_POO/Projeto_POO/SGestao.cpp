#include "SGestao.h"
#include "ExportarDados.h"

SGestao::SGestao()
{
	
}

SGestao::~SGestao()
{
	apagar_lista(Lista_Modelos);
}


bool SGestao::Load(const string& fich)
{
	ifstream f(fich);
	if (f.is_open())
	{
		f.close();

		if (PesquisarModelo(fich))
		{
			cout << "Já foi carregado um ficheiro com o nome [" << fich << "] previamente!" << endl;
			return false;
		}

		Modelo* aux = new Modelo(fich);
		if (ERRO)
			delete aux;
		else
			Lista_Modelos.push_back(aux);  //criacao do modelo
	}
	else
		cout << "ERRO: O ficheiro [" << fich << "] não existe!" << endl;
	
	return not ERRO;  //retorna true se nao ocorrer erro e false se ocorrer
}

int SGestao::Contar(Tipo T)
{
	int contador = 0;
	switch (T)
	{
	case VERTICE:
		for (list<Modelo*>::iterator it = Lista_Modelos.begin(); it != Lista_Modelos.end(); ++it)
			contador += (*it)->get_numero_vertices();
		break;

	case ARESTA:
		for (list<Modelo*>::iterator it = Lista_Modelos.begin(); it != Lista_Modelos.end(); ++it)
			contador += (*it)->get_numero_arestas();
		break;

	case FACE:
		for (list<Modelo*>::iterator it = Lista_Modelos.begin(); it != Lista_Modelos.end(); ++it)
			contador += (*it)->get_numero_faces();
		break;
	}

	return contador;
}

Modelo* SGestao::PesquisarModelo(const string& fich) {
	if (Lista_Modelos.size() == 0) return NULL; // caso a lista de modelos nao tenha la nada
	for (list<Modelo*>::iterator it = Lista_Modelos.begin(); it != Lista_Modelos.end(); ++it)
	{
		if (fich.compare((*it)->getnome_ficheiro()) == 0)	// compara o nome do ficheiro com o nome dos fich. da Lista de modelos
			return (*it);
	}
	return NULL;
}

bool SGestao::Envolvente(const string& fich, Ponto& Pmin, Ponto& Pmax) {
	Modelo* m = PesquisarModelo(fich);
	if (m == NULL) // nao foi encontrado o modelo/a lista esta vazia
		return false;
	else
	{
		m->Ponto_minimo(Pmin);
		m->Ponto_maximo(Pmax);
		return true;
	}
}

bool SGestao::RemoverModelo(const string& fich)
{
	for (list<Modelo*>::iterator it = Lista_Modelos.begin(); it != Lista_Modelos.end(); ++it)
	{
		if (fich.compare((*it)->getnome_ficheiro()) == 0)	// compara o nome do ficheiro com o nome dos fich. da Lista de modelos
		{
			delete* it;  //eliminar o modelo
			Lista_Modelos.erase(it);  //eliminar o espaco alocado para o modelo na lista
			return true;
		}
	}
	return false;
}

double SGestao::AreaModelo(const string& fich)
{
	Modelo* m = PesquisarModelo(fich);
	if (m == NULL) // nao foi encontrado o modelo/a lista esta vazia
		return 0;
	else
		return m->get_area_total();
}

Face* SGestao::FaceMaiorArea(const string& fich)
{
	Modelo* m = PesquisarModelo(fich);
	if (m == NULL) // nao foi encontrado o modelo/a lista esta vazia
		return NULL;
	else
		return m->get_face_maior_area();
}

int SGestao::NumInterseccoes(Ponto A, Ponto B)
{
	int contador = 0;

	Reta R;
	R.A.x = A.x;
	R.A.y = A.y;
	R.A.z = A.z;

	R.v[0] = B.x - A.x;
	R.v[1] = B.y - A.y;
	R.v[2] = B.z - A.z;

	for (list<Modelo*>::iterator it = Lista_Modelos.begin(); it != Lista_Modelos.end(); ++it)
	{
		contador += (*it)->NumInterseccoes(R);
	}

	return contador;
}

void SGestao::MostrarModelo(const string& fich)
{
	Modelo* m = PesquisarModelo(fich);
	if (m == NULL) // nao foi encontrado o modelo/a lista esta vazia
		return;
	else
		m->mostrar();
}

Face* SGestao::FaceMaiorCurvatura(const string& fich)
{
	Modelo* m = PesquisarModelo(fich);
	if (m == NULL) // nao foi encontrado o modelo/a lista esta vazia
		return NULL;
	else
		return m->get_face_maior_curva();
}

int SGestao::Memoria()
{
	int memoria = 0;

	memoria += 1 * sizeof(list<Modelo*>);
	memoria += Lista_Modelos.size() * sizeof(Modelo*);
	for (list<Modelo*>::iterator it = Lista_Modelos.begin(); it != Lista_Modelos.end(); ++it)
	{
		memoria += (*it)->Memoria();
	}

	return memoria;
}

int SGestao::Memoria(const string& fich)
{
	Modelo* m = PesquisarModelo(fich);
	if (m == NULL) // nao foi encontrado o modelo/a lista esta vazia
		return -1;
	else
		return m->Memoria();
}

Modelo* SGestao::ModeloMaisMemoria()
{
	int mais_mem = -1;
	Modelo* mais_m = NULL;
	int aux;

	for (list<Modelo*>::iterator it = Lista_Modelos.begin(); it != Lista_Modelos.end(); ++it)
	{
		aux = (*it)->Memoria();
		if (mais_mem < aux)
		{
			mais_mem = aux;
			mais_m = *it;
		}
	}

	return mais_m;
}

void SGestao::EscreverXML(const string& fich, const string& fich_xml)
{
	PesquisarModelo(fich)->EscreverXML(fich_xml);
}

void SGestao::escrever_ficheiros_carregados_menu()
{
	for (list<Modelo*>::iterator it = Lista_Modelos.begin(); it != Lista_Modelos.end(); ++it)
	{
		ExportarDados::StringLeft("# -", (*it)->getnome_ficheiro().c_str(), Largura_menu - 3, " ", " #\n");
	}
}