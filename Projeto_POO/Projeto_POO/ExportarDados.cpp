#include "ExportarDados.h"



ExportarDados::ExportarDados()
{
}


ExportarDados::~ExportarDados()
{
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

bool ExportarDados::StringLeft(const char *Pre, const char *String, int EmptySpace_Qt, const char *EmptySpace_Char, const char *Pos)
{
	int TamanhoString = 0, Indice = 0;

	//Calcular o tamanho da String
	while (String[Indice] != 0)
	{
		Indice++;
	}
	TamanhoString = Indice;

	if (TamanhoString > EmptySpace_Qt)
		return false;

	cout << Pre;
	for (int i = 0; i < EmptySpace_Qt; i++)
	{
		if (String[i] != 0)  //escreve as letras da string
			cout << String[i];
		else  //escreve o caracter do EmptySpace
		{
			for (int k = i; k < EmptySpace_Qt; k++)
			{
				cout << EmptySpace_Char;
			}
			break;
		}
	}
	cout << Pos;
	return true;
}

bool ExportarDados::StringLeft(const char *Pre, const char *String, int EmptySpace_Qt, const char *EmptySpace_Char)
{
	int TamanhoString = 0, Indice = 0;

	//Calcular o tamanho da String
	while (String[Indice] != 0)
	{
		Indice++;
	}
	TamanhoString = Indice;

	if (TamanhoString > EmptySpace_Qt)
		return false;

	cout << Pre;
	for (int i = 0; i < EmptySpace_Qt; i++)
	{
		if (String[i] != 0)  //escreve as letras da string
			cout << String[i];
		else  //escreve o caracter do EmptySpace
		{
			for (int k = i; k < EmptySpace_Qt; k++)
			{
				cout << EmptySpace_Char;
			}
			break;
		}
	}
	return true;
}

bool ExportarDados::StringLeft(const char *String, int EmptySpace_Qt, const char *EmptySpace_Char, const char *Pos)
{
	int TamanhoString = 0, Indice = 0;

	//Calcular o tamanho da String
	while (String[Indice] != 0)
	{
		Indice++;
	}
	TamanhoString = Indice;

	if (TamanhoString > EmptySpace_Qt)
		return false;

	for (int i = 0; i < EmptySpace_Qt; i++)
	{
		if (String[i] != 0)  //escreve as letras da string
			cout << String[i];
		else  //escreve o caracter do EmptySpace
		{
			for (int k = i; k < EmptySpace_Qt; k++)
			{
				cout << EmptySpace_Char;
			}
			break;
		}
	}
	cout << Pos;
	return true;
}

bool ExportarDados::StringLeft(const char *String, int EmptySpace_Qt, const char *EmptySpace_Char)
{
	int TamanhoString = 0, Indice = 0;

	//Calcular o tamanho da String
	while (String[Indice] != 0)
	{
		Indice++;
	}
	TamanhoString = Indice;

	if (TamanhoString > EmptySpace_Qt)
		return false;

	for (int i = 0; i < EmptySpace_Qt; i++)
	{
		if (String[i] != 0)  //escreve as letras da string
			cout << String[i];
		else  //escreve o caracter do EmptySpace
		{
			for (int k = i; k < EmptySpace_Qt; k++)
			{
				cout << EmptySpace_Char;
			}
			break;
		}
	}
	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

bool ExportarDados::StringCenter(const char *Pre, const char *String, int EmptySpace_Qt, const char *EmptySpace_Char, const char *Pos)
{
	int TamanhoString = 0, Indice = 0, Limite = 0;

	//Calcular o tamanho da String
	while (String[Indice] != 0)
	{
		Indice++;
	}
	TamanhoString = Indice;

	if (TamanhoString > EmptySpace_Qt)
		return false;

	cout << Pre;

	//Calcular a quantidade de espacos antes da String
	if (EmptySpace_Qt % 2 == 0)  //espaco vazio par
	{
		if (TamanhoString % 2 == 0) //espaco vazio par e string par
			Limite = EmptySpace_Qt / 2 - TamanhoString / 2;
		else  //espaco vazio par e string impar
			Limite = EmptySpace_Qt / 2 - TamanhoString / 2 - 1;
	}
	else  //espaco vazio impar
	{
		Limite = EmptySpace_Qt / 2 - TamanhoString / 2;
	}

	for (int i = 0; i < Limite; i++)  //Escrever o carater do EmptySpace
	{
		cout << EmptySpace_Char;
	}
	for (int i = 0; i < TamanhoString; i++) // Escrever a String
	{
		cout << String[i];
	}

	//Calcular a quantidade de espacos depois da String
	if (EmptySpace_Qt % 2 == 0)  //espaco vazio par
	{
		Limite += TamanhoString;
	}
	else  //espaco vazio impar
	{
		Limite += TamanhoString;
	}

	for (int i = Limite; i < EmptySpace_Qt; i++)  //Escrever o carater do EmptySpace
	{
		cout << EmptySpace_Char;
	}
	cout << Pos;
	return true;
}

bool ExportarDados::StringCenter(const char *Pre, const char *String, int EmptySpace_Qt, const char *EmptySpace_Char)
{
	int TamanhoString = 0, Indice = 0, Limite = 0;

	//Calcular o tamanho da String
	while (String[Indice] != 0)
	{
		Indice++;
	}
	TamanhoString = Indice;

	if (TamanhoString > EmptySpace_Qt)
		return false;

	cout << Pre;

	//Calcular a quantidade de espacos antes da String
	if (EmptySpace_Qt % 2 == 0)  //espaco vazio par
	{
		if (TamanhoString % 2 == 0) //espaco vazio par e string par
			Limite = EmptySpace_Qt / 2 - TamanhoString / 2;
		else  //espaco vazio par e string impar
			Limite = EmptySpace_Qt / 2 - TamanhoString / 2 - 1;
	}
	else  //espaco vazio impar
	{
		Limite = EmptySpace_Qt / 2 - TamanhoString / 2;
	}

	for (int i = 0; i < Limite; i++)  //Escrever o carater do EmptySpace
	{
		cout << EmptySpace_Char;
	}
	for (int i = 0; i < TamanhoString; i++) // Escrever a String
	{
		cout << String[i];
	}

	//Calcular a quantidade de espacos depois da String
	if (EmptySpace_Qt % 2 == 0)  //espaco vazio par
	{
		Limite += TamanhoString;
	}
	else  //espaco vazio impar
	{
		Limite += TamanhoString;
	}

	for (int i = Limite; i < EmptySpace_Qt; i++)  //Escrever o carater do EmptySpace
	{
		cout << EmptySpace_Char;
	}
	return true;

}

bool ExportarDados::StringCenter(const char *String, int EmptySpace_Qt, const char *EmptySpace_Char, const char *Pos)
{
	int TamanhoString = 0, Indice = 0, Limite = 0;

	//Calcular o tamanho da String
	while (String[Indice] != 0)
	{
		Indice++;
	}
	TamanhoString = Indice;

	if (TamanhoString > EmptySpace_Qt)
		return false;

	//Calcular a quantidade de espacos antes da String
	if (EmptySpace_Qt % 2 == 0)  //espaco vazio par
	{
		if (TamanhoString % 2 == 0) //espaco vazio par e string par
			Limite = EmptySpace_Qt / 2 - TamanhoString / 2;
		else  //espaco vazio par e string impar
			Limite = EmptySpace_Qt / 2 - TamanhoString / 2 - 1;
	}
	else  //espaco vazio impar
	{
		Limite = EmptySpace_Qt / 2 - TamanhoString / 2;
	}

	for (int i = 0; i < Limite; i++)  //Escrever o carater do EmptySpace
	{
		cout << EmptySpace_Char;
	}
	for (int i = 0; i < TamanhoString; i++) // Escrever a String
	{
		cout << String[i];
	}

	//Calcular a quantidade de espacos depois da String
	if (EmptySpace_Qt % 2 == 0)  //espaco vazio par
	{
		Limite += TamanhoString;
	}
	else  //espaco vazio impar
	{
		Limite += TamanhoString;
	}

	for (int i = Limite; i < EmptySpace_Qt; i++)  //Escrever o carater do EmptySpace
	{
		cout << EmptySpace_Char;
	}
	cout << Pos;
	return true;
}

bool ExportarDados::StringCenter(const char *String, int EmptySpace_Qt, const char *EmptySpace_Char)
{
	int TamanhoString = 0, Indice = 0, Limite = 0;

	//Calcular o tamanho da String
	while (String[Indice] != 0)
	{
		Indice++;
	}
	TamanhoString = Indice;

	if (TamanhoString > EmptySpace_Qt)
		return false;

	//Calcular a quantidade de espacos antes da String
	if (EmptySpace_Qt % 2 == 0)  //espaco vazio par
	{
		if (TamanhoString % 2 == 0) //espaco vazio par e string par
			Limite = EmptySpace_Qt / 2 - TamanhoString / 2;
		else  //espaco vazio par e string impar
			Limite = EmptySpace_Qt / 2 - TamanhoString / 2 - 1;
	}
	else  //espaco vazio impar
	{
		Limite = EmptySpace_Qt / 2 - TamanhoString / 2;
	}

	for (int i = 0; i < Limite; i++)  //Escrever o carater do EmptySpace
	{
		cout << EmptySpace_Char;
	}
	for (int i = 0; i < TamanhoString; i++) // Escrever a String
	{
		cout << String[i];
	}

	//Calcular a quantidade de espacos depois da String
	if (EmptySpace_Qt % 2 == 0)  //espaco vazio par
	{
		Limite += TamanhoString;
	}
	else  //espaco vazio impar
	{
		Limite += TamanhoString;
	}

	for (int i = Limite; i < EmptySpace_Qt; i++)  //Escrever o carater do EmptySpace
	{
		cout << EmptySpace_Char;
	}
	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

bool ExportarDados::StringRight(const char *Pre, const char *String, int EmptySpace_Qt, const char *EmptySpace_Char, const char *Pos)
{
	int TamanhoString = 0, Indice = 0, Limite = 0;

	//Calcular o tamanho da String
	while (String[Indice] != 0)
	{
		Indice++;
	}
	TamanhoString = Indice;

	Limite = EmptySpace_Qt - TamanhoString; //determinar a quantidade de caracteres do EmptySpace

	if (Limite < 0)
		return false;

	cout << Pre;

	for (int i = 0; i < Limite; i++)  //escrever caracteres  do EmptySpace
	{
		cout << EmptySpace_Char;
	}
	for (int i = 0; i < TamanhoString; i++)  //escrever String
	{
		cout << String[i];
	}
	cout << Pos;
	return true;
}

bool ExportarDados::StringRight(const char *Pre, const char *String, int EmptySpace_Qt, const char *EmptySpace_Char)
{
	int TamanhoString = 0, Indice = 0, Limite = 0;

	//Calcular o tamanho da String
	while (String[Indice] != 0)
	{
		Indice++;
	}
	TamanhoString = Indice;

	Limite = EmptySpace_Qt - TamanhoString; //determinar a quantidade de caracteres do EmptySpace

	if (Limite < 0)
		return false;

	cout << Pre;

	for (int i = 0; i < Limite; i++)  //escrever caracteres  do EmptySpace
	{
		cout << EmptySpace_Char;
	}
	for (int i = 0; i < TamanhoString; i++)  //escrever String
	{
		cout << String[i];
	}
	return true;
}

bool ExportarDados::StringRight(const char *String, int EmptySpace_Qt, const char *EmptySpace_Char, const char *Pos)
{
	int TamanhoString = 0, Indice = 0, Limite = 0;

	//Calcular o tamanho da String
	while (String[Indice] != 0)
	{
		Indice++;
	}
	TamanhoString = Indice;

	Limite = EmptySpace_Qt - TamanhoString; //determinar a quantidade de caracteres do EmptySpace

	if (Limite < 0)
		return false;

	for (int i = 0; i < Limite; i++)  //escrever caracteres  do EmptySpace
	{
		cout << EmptySpace_Char;
	}
	for (int i = 0; i < TamanhoString; i++)  //escrever String
	{
		cout << String[i];
	}
	cout << Pos;
	return true;
}

bool ExportarDados::StringRight(const char *String, int EmptySpace_Qt, const char *EmptySpace_Char)
{
	int TamanhoString = 0, Indice = 0, Limite = 0;

	//Calcular o tamanho da String
	while (String[Indice] != 0)
	{
		Indice++;
	}
	TamanhoString = Indice;

	Limite = EmptySpace_Qt - TamanhoString; //determinar a quantidade de caracteres do EmptySpace

	if (Limite < 0)
		return false;

	for (int i = 0; i < Limite; i++)  //escrever caracteres  do EmptySpace
	{
		cout << EmptySpace_Char;
	}
	for (int i = 0; i < TamanhoString; i++)  //escrever String
	{
		cout << String[i];
	}
	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

void ExportarDados::PreencherChar(const char *Pre, int EmptySpace_Qt, const char *EmptySpace_Char, const char *Pos)
{
	cout << Pre;
	for (int i = 0; i < EmptySpace_Qt; i++)  //escrever os caracteres do EmptySpace
	{
		cout << EmptySpace_Char;
	}
	cout << Pos;
}

void ExportarDados::PreencherChar(const char *Pre, int EmptySpace_Qt, const char *EmptySpace_Char)
{
	cout << Pre;
	for (int i = 0; i < EmptySpace_Qt; i++)  //escrever os caracteres do EmptySpace
	{
		cout << EmptySpace_Char;
	}
}

void ExportarDados::PreencherChar(int EmptySpace_Qt, const char *EmptySpace_Char, const char *Pos)
{
	for (int i = 0; i < EmptySpace_Qt; i++)  //escrever os caracteres do EmptySpace
	{
		cout << EmptySpace_Char;
	}
	cout << Pos;
}

void ExportarDados::PreencherChar(int EmptySpace_Qt, const char *EmptySpace_Char)
{
	for (int i = 0; i < EmptySpace_Qt; i++)  //escrever os caracteres do EmptySpace
	{
		cout << EmptySpace_Char;
	}
}