#pragma once
#include "Lib.h"

extern bool ERRO;

class Objeto
{
public:
	virtual string quem_sou() { return "Objeto"; }
	virtual double get_area() { return -1; }
	virtual double get_perimetro() { return -1; }
};

