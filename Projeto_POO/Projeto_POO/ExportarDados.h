#pragma once
#include "Lib.h"

class ExportarDados
{
public:
	ExportarDados();
	~ExportarDados();

public:
	//Left
	static bool StringLeft(const char *Pre, const char *String, int EmptySpace_Qt, const char *EmptySpace_Char, const char *Pos);
	static bool StringLeft(const char *Pre, const char *String, int EmptySpace_Qt, const char *EmptySpace_Char);
	static bool StringLeft(const char *String, int EmptySpace_Qt, const char *EmptySpace_Char, const char *Pos);
	static bool StringLeft(const char *String, int EmptySpace_Qt, const char *EmptySpace_Char);

	//                                                  Center
	static bool StringCenter(const char *Pre, const char *String, int EmptySpace_Qt, const char *EmptySpace_Char, const char *Pos);
	static bool StringCenter(const char *Pre, const char *String, int EmptySpace_Qt, const char *EmptySpace_Char);
	static bool StringCenter(const char *String, int EmptySpace_Qt, const char *EmptySpace_Char, const char *Pos);
	static bool StringCenter(const char *String, int EmptySpace_Qt, const char *EmptySpace_Char);

	//                                                                                                        Right
	static bool StringRight(const char *Pre, const char *String, int EmptySpace_Qt, const char *EmptySpace_Char, const char *Pos);
	static bool StringRight(const char *Pre, const char *String, int EmptySpace_Qt, const char *EmptySpace_Char);
	static bool StringRight(const char *String, int EmptySpace_Qt, const char *EmptySpace_Char, const char *Pos);
	static bool StringRight(const char *String, int EmptySpace_Qt, const char *EmptySpace_Char);

	//Preencher um certo espaco com caracteres   ---------------------------------------------------
	static void PreencherChar(const char *Pre, int EmptySpace_Qt, const char *EmptySpace_Char, const char *Pos);
	static void PreencherChar(const char *Pre, int EmptySpace_Qt, const char *EmptySpace_Char);
	static void PreencherChar(int EmptySpace_Qt, const char *EmptySpace_Char, const char *Pos);
	static void PreencherChar(int EmptySpace_Qt, const char *EmptySpace_Char);
};

