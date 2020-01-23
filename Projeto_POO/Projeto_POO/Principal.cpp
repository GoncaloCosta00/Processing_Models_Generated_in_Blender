#include "Lib.h"
#include "SGestao.h"
#include "ExportarDados.h"
extern bool Verificar_string_numero(string str);

SGestao* programa;
string comando = "dir \*.obj /b /o:n >";

int menu_contar()
{
	string aux;
	int opcao;
	ifstream f;

	system("cls");
	ExportarDados::PreencherChar("#", Largura_menu, "#", "#\n");
	ExportarDados::StringCenter("# ", "Contar", Largura_menu - 2, " ", " #\n");
	ExportarDados::PreencherChar("#", Largura_menu, "-", "#\n");
	ExportarDados::StringLeft("# ", "1) Contar Vertices", Largura_menu - 2, " ", " #\n");
	ExportarDados::StringLeft("# ", "2) Contar Arestas", Largura_menu - 2, " ", " #\n");
	ExportarDados::StringLeft("# ", "3) Contar Faces", Largura_menu - 2, " ", " #\n");
	ExportarDados::PreencherChar("#", Largura_menu, " ", "#\n");
	ExportarDados::StringLeft("# ", "0) Voltar", Largura_menu - 2, " ", " #\n");
	ExportarDados::PreencherChar("#", Largura_menu, "#", "#\n");
	cout << "Opção: ";
	cin >> aux;

	if (!Verificar_string_numero(aux))
		opcao = -1;
	else
		opcao = stoi(aux);

	cout << endl;

	switch (opcao)
	{
	case 1:
		cout << "Número total de vertices em memória: " << programa->Contar(VERTICE) << endl;
		break;

	case 2:
		cout << "Número total de arestas em memória: " << programa->Contar(ARESTA) << endl;
		break;

	case 3:
		cout << "Número total de faces em memória: " << programa->Contar(FACE) << endl;
		break;

	case 0:
		return 0;
		break;

	default:
		cout << "Opção inválida!" << endl << endl;
		system("pause");
		return 2;
		break;
	}
	cout << endl;
	system("pause");
	return 1;
}

int menu_memoria()
{
	string aux;
	int opcao;
	ifstream f;

	system("cls");
	ExportarDados::PreencherChar("#", Largura_menu, "#", "#\n");
	ExportarDados::StringCenter("# ", "Memória", Largura_menu - 2, " ", " #\n");
	ExportarDados::PreencherChar("#", Largura_menu, "-", "#\n");
	ExportarDados::StringLeft("# ", "1) Quanta memória está a ser ocupada", Largura_menu - 2, " ", " #\n");
	ExportarDados::StringLeft("# ", "2) Quanto de memória ocupa o modelo...", Largura_menu - 2, " ", " #\n");
	ExportarDados::StringLeft("# ", "3) Qual modelo ocupa mais memória?", Largura_menu - 2, " ", " #\n");
	ExportarDados::PreencherChar("#", Largura_menu, " ", "#\n");
	ExportarDados::StringLeft("# ", "0) Voltar", Largura_menu - 2, " ", " #\n");
	ExportarDados::PreencherChar("#", Largura_menu, "#", "#\n");
	cout << "Opção: ";
	cin >> aux;

	if (!Verificar_string_numero(aux))
		opcao = -1;
	else
		opcao = stoi(aux);

	cout << endl;

	switch (opcao)
	{
	case 1:
		cout << "O programa está a ocupar um total de " << programa->Memoria() << " bytes" << endl;
		break;

	case 2:
		if (programa->Numero_modelos_carregados() == 0)
		{
			cout << "Não existem modelos carregados, logo não poderá saber a memória ocupada pelos mesmos!" << endl;
			break;
		}
		cout << "Qual o ficheiro que deseja saber a memória ocupada por ele?" << endl;
		cin >> aux;
		cout << endl;
		if(programa->PesquisarModelo(aux))
			cout << "O modelo " << aux << " está a ocupar um total de " << programa->Memoria(aux) << " bytes" << endl;
		else
			cout << "O Modelo [" << aux << "] não foi carregado ainda!" << endl;
		break;

	case 3:
		if (programa->Numero_modelos_carregados() == 0)
		{
			cout << "Não existem modelos carregados, logo não existe o que mais memória consome!" << endl;
			break;
		}
		cout << "O modelo que ocupa mais memória é o [" << programa->ModeloMaisMemoria()->getnome_ficheiro() << "]" << endl;
		break;

	case 0:
		return 0;
		break;

	default:
		cout << "Opção inválida!" << endl << endl;
		system("pause");
		return 2;
		break;
	}
	cout << endl;
	system("pause");
	return 1;
}

int menu()
{
	string aux, aux1;
	int opcao;
	ifstream f;
	double auxb;
	Modelo* auxm;
	Ponto paux1;
	Ponto paux2;
	int auxi;
	Face* auxf;

	system("cls");
	ExportarDados::PreencherChar("#", Largura_menu, "#", "#\n");
	ExportarDados::StringCenter("# ", "Ficheiros carregados", Largura_menu-2, " ", " #\n");
	ExportarDados::PreencherChar("#", Largura_menu, "-", "#\n");
	programa->escrever_ficheiros_carregados_menu();
	ExportarDados::PreencherChar("#", Largura_menu, "#", "#\n");
	ExportarDados::StringCenter("# ", "Menu", Largura_menu-2, " ", " #\n");
	ExportarDados::PreencherChar("#", Largura_menu, "-", "#\n");
	ExportarDados::StringLeft("# ", "1) Carregar 1 Modelo", Largura_menu - 2, " ", " #\n");
	ExportarDados::StringLeft("# ", "2) Carregar todos os ficheiros [.obj]", Largura_menu - 2, " ", " #\n");
	ExportarDados::StringLeft("# ", "3) Remover 1 Modelo", Largura_menu - 2, " ", " #\n");
	ExportarDados::StringLeft("# ", "4) Contar...", Largura_menu - 2, " ", " #\n");
	ExportarDados::StringLeft("# ", "5) Área do modelo", Largura_menu - 2, " ", " #\n");
	ExportarDados::StringLeft("# ", "6) Procurar modelo...", Largura_menu - 2, " ", " #\n");
	ExportarDados::StringLeft("# ", "7) Quais os pontos envolventes?", Largura_menu - 2, " ", " #\n");
	ExportarDados::StringLeft("# ", "8) Memória", Largura_menu - 2, " ", " #\n");
	ExportarDados::StringLeft("# ", "9) Número de interseções com a reta...", Largura_menu - 2, " ", " #\n");
	ExportarDados::StringLeft("# ", "10) Qual é a maior face?", Largura_menu - 2, " ", " #\n");
	ExportarDados::StringLeft("# ", "11) Qual a face com maior curvatura?", Largura_menu - 2, " ", " #\n");
	ExportarDados::StringLeft("# ", "12) Escrever modelo num ficheiro [.xml]", Largura_menu - 2, " ", " #\n");
	
	ExportarDados::PreencherChar("#", Largura_menu, " ", "#\n");
	ExportarDados::StringLeft("# ", "0) Terminar", Largura_menu - 2, " ", " #\n");
	ExportarDados::PreencherChar("#", Largura_menu, "#", "#\n");
	cout << "Opção: ";
	cin >> aux;

	if (!Verificar_string_numero(aux))
		opcao = -1;
	else
		opcao = stoi(aux);

	cout << endl;

	switch (opcao)
	{
	case 1:
		cout << "Qual o ficheiro que quer carregar?" << endl;
		cin >> aux;
		cout << endl;
		programa->Load(aux);
		break;

	case 2:
		system(comando.c_str());
		f.open(NomeArquivosOBJ);
		if (!f.is_open())
		{
			cout << "ERRO: Não foi possível carregar a lista dos arquivos [.obj]" << endl;
			break;
		}
		while (!f.eof())  //enquanto nao acabar de ler o ficheiro
		{
			getline(f, aux);
			if(aux.size() != 0)
				programa->Load(aux);
			cout << endl;
		}
		f.close();
		break;

	case 3:
		if (programa->Numero_modelos_carregados() == 0)
		{
			cout << "Não existem modelos carregados, logo não pode remover nenhum!" << endl;
			break;
		}
		cout << "Qual o ficheiro que deseja remover?" << endl;
		cin >> aux;
		cout << endl;
		if (programa->RemoverModelo(aux))
			cout << "Modelo removido com sucesso!" << endl;
		else
			cout << "O Modelo [" << aux << "] não foi carregado ainda!" << endl;
		break;
		
	case 4:
		while (menu_contar());
		break;

	case 5:
		if (programa->Numero_modelos_carregados() == 0)
		{
			cout << "Não existem modelos carregados para se saber a área deles!" << endl;
			break;
		}
		cout << "Qual o ficheiro que deseja saber a área?" << endl;
		cin >> aux;
		cout << endl;
		auxb = programa->AreaModelo(aux);
		if (auxb)
			cout << "O modelo " << aux << " tem " << auxb << " unidades de área!" << endl;
		else
			cout << "O Modelo [" << aux << "] não foi carregado ainda!" << endl;
		break;

	case 6:
		if (programa->Numero_modelos_carregados() == 0)
		{
			cout << "Não existem modelos carregados, logo não vai encontrar nada!" << endl;
			break;
		}
		cout << "Qual o ficheiro que deseja encontrar?" << endl;
		cin >> aux;
		cout << endl;
		auxm = programa->PesquisarModelo(aux);
		if (auxm)
			auxm->mostrar();
		else
			cout << "O Modelo [" << aux << "] não foi carregado ainda!" << endl;
		break;

	case 7:
		if (programa->Numero_modelos_carregados() == 0)
		{
			cout << "Não existem modelos carregados para determinar os pontos envolventes!" << endl;
			break;
		}
		cout << "Qual o ficheiro que deseja saber os pontos envolventes?" << endl;
		cin >> aux;
		cout << endl;

		if (programa->Envolvente(aux, paux1, paux2))
		{
			cout << "Ponto mínimo: (" << paux1.x << ", " << paux1.y << ", " << paux1.z << ")" << endl;
			cout << "Ponto máximo: (" << paux2.x << ", " << paux2.y << ", " << paux2.z << ")" << endl;
		}
		else
			cout << "O Modelo [" << aux << "] não foi carregado ainda!" << endl;
		break;

	case 8:
		while (menu_memoria());
		break;

	case 9:
		if (programa->Numero_modelos_carregados() == 0)
		{
			cout << "Não existem modelos carregados para se intersetar com a reta!" << endl;
			break;
		}
		auxi = 1;
		do {
			system("cls");
			cout << "Qual a reta que deseja intersetar?" << endl;
			cout << "Ponto A" << endl;

			if (auxi == 1)
				cout << "x = ";
			else if(auxi > 1)
				cout << "x = " << paux1.x << endl;

			if (auxi == 2)
				cout << "y = ";
			else if (auxi > 2)
				cout << "y = " << paux1.y << endl;

			if (auxi == 3)
				cout << "z = ";
			else if (auxi > 3)
				cout << "z = " << paux1.z << endl;

			if (auxi > 3)
				cout << "Ponto B" << endl;

			if (auxi == 4)
				cout << "x = ";
			else if (auxi > 4)
				cout << "x = " << paux2.x << endl;

			if (auxi == 5)
				cout << "y = ";
			else if (auxi > 5)
				cout << "y = " << paux2.y << endl;

			if (auxi == 6)
				cout << "z = ";

			cin >> aux;

			if (Verificar_string_numero(aux))
			{
				switch (auxi)
				{
				case 1:
					paux1.x = stod(aux);
					break;

				case 2:
					paux1.y = stod(aux);
					break;

				case 3:
					paux1.z = stod(aux);
					break;

				case 4:
					paux2.x = stod(aux);
					break;

				case 5:
					paux2.y = stod(aux);
					break;

				case 6:
					paux2.z = stod(aux);
					break;
				}
				auxi++;
			}
		} while (auxi <= 6);  //6 = 6 coordenadas para introduzir
		
		cout << endl;
		
		cout << "A reta formada pelos pontos A(" << paux1.x << ", " << paux1.y << ", " << paux1.z << ") e B(" << paux2.x << ", " << paux2.y << ", " << paux2.z << "), interseta " << programa->NumInterseccoes(paux1, paux2) << " faces" << endl;
		break;

	case 10:
		if (programa->Numero_modelos_carregados() == 0)
		{
			cout << "Não existem modelos carregados, logo não existe a maior face de todas!" << endl;
			break;
		}
		cout << "Qual o ficheiro que deseja saber qual é a maior face?" << endl;
		cin >> aux;
		cout << endl;

		auxf = programa->FaceMaiorArea(aux);
		if (auxf)
			cout << "A maior face do modelo [" << aux << "] tem " << auxf->get_area() << " unidades de área" << endl;
		else
			cout << "O Modelo [" << aux << "] não foi carregado ainda!" << endl;
		break;

	case 11:
		if (programa->Numero_modelos_carregados() == 0)
		{
			cout << "Não existem modelos carregados, logo não existe curvatura entre nenhuma face!" << endl;
			break;
		}
		cout << "Qual o ficheiro que deseja saber qual a face que faz maios curva com as vizinhas?" << endl;
		cin >> aux;
		cout << endl;
		auxf = programa->FaceMaiorCurvatura(aux);
		if (auxf)
			cout << "A face com maior curvatura entre as faces vizinhas do modelo [" << aux << "] tem " << auxf->get_maior_curva() << " graus de curvatura" << endl;
		else
			cout << "O Modelo [" << aux << "] não foi carregado ainda!" << endl;
		break;

	case 12:
		if (programa->Numero_modelos_carregados() == 0)
		{
			cout << "Não existem modelos carregados, logo não pode guardar nenhum em formato [.xml]!" << endl;
			break;
		}
		cout << "Qual o ficheiro que deseja converter?" << endl;
		cin >> aux;
		cout << endl;
		
		if (programa->PesquisarModelo(aux))
		{
			cout << "Qual o nome que deseja? (coloque a extenção do ficheiro no nome)" << endl;
			cin >> aux1;
			cout << endl;
			programa->EscreverXML(aux, aux1);
		}
		else
			cout << "O Modelo [" << aux << "] não foi carregado ainda!" << endl;
		break;

	case 0:
		return 0;
		break;

	default:
		cout << "Opção inválida!" << endl << endl;
		system("pause");
		return 2;
		break;
	}
	
	switch (opcao)
	{
	case 4:
	case 8:
		break;

	default:
		cout << endl;
		system("pause");
		break;
	}
	
	return 1;
}


int main()
{
	setlocale(LC_CTYPE, "portuguese");
	comando += NomeArquivosOBJ;

	programa = new SGestao();

	while (menu());

	delete programa;
	
	return 0;
}