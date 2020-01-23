#include "Aresta.h"
#include "Face.h"

Aresta::Aresta(Vertice* V1, Vertice* V2, Face* f)
{
	v1 = V1;
	v2 = V2;
	vetor_faces = NULL;
	comprimento = sqrt(pow(v1->getX() - v2->getX(), 2) + pow(v1->getY() - v2->getY(), 2) + pow(v1->getZ() - v2->getZ(), 2));

	lista_faces.push_back(f);
}

Aresta::~Aresta()
{
	lista_faces.clear();
	delete vetor_faces;
}

void Aresta::adicionar_face(Face* face)
{
	lista_faces.push_back(face);
}

bool Aresta::operator == (Aresta& aresta)  //verificado atraves do endereco de memoria dos vertices
{
	if (v1 != aresta.v1 && v1 != aresta.v2)
		return false;
	if (v2 != aresta.v2 && v2 != aresta.v1)
		return false;
	return true;
}

bool Aresta::operator > (Aresta& aresta)
{
	if (comprimento > aresta.get_perimetro())
		return true;
	else
		return false;
}

bool Aresta::operator < (Aresta& aresta)
{
	if (comprimento < aresta.get_perimetro())
		return true;
	else
		return false;
}

void Aresta::converter_lista_faces()
{
	if(vetor_faces)
		delete vetor_faces;
	vetor_faces = new Face * [lista_faces.size()];
	int i = 0;
	for (list<Face*>::iterator it = lista_faces.begin(); it != lista_faces.end(); ++it, ++i)
		vetor_faces[i] = *it;
}

void Aresta::determinar_curvatura_faces()
{
	converter_lista_faces();

	for (int i = 0; i < lista_faces.size(); ++i)
	{
		for (int k = i + 1; k < lista_faces.size(); ++k)
		{
			*vetor_faces[i] == *vetor_faces[k];
		}
	}
}

int Aresta::Memoria()
{
	int memoria = 0;

	memoria += 1 * sizeof(double);
	memoria += 2 * sizeof(Vertice*);
	memoria += 1 * sizeof(Face**);
	memoria += 1 * sizeof(list<Face*>);
	memoria += 2 * lista_faces.size() * sizeof(Face*);

	return memoria;
}

void Aresta::EscreverXML(XMLWriter& writer)
{
	writer.WriteElementString("Comprimento", to_string(comprimento));

	writer.WriteStartElement("Vertices");
		writer.WriteStartElement("Vertice");
			v1->EscreverXML(writer);
		writer.WriteEndElement();
		writer.WriteStartElement("Vertice");
		v2->EscreverXML(writer);
		writer.WriteEndElement();
	writer.WriteEndElement();

	writer.WriteStartElement("Faces");
	for (int i = 0; i < lista_faces.size(); ++i)
	{
		writer.WriteStartElement("Face");
			vetor_faces[i]->EscreverXML(writer);
		writer.WriteEndElement();
	}
	writer.WriteEndElement();
}