#include <individual.h>
#include <exception.h>
#include <iostream>

// Construtores ///////////////////////////
Individual::Individual() {}

Individual::Individual(int i, int j)
{
  if (i < 0 || j < 0) throw Error("Parametros invalidos","Tentativa de colocar media a longo prazo negativa");

  this->Mlong = std::min(i,j);
  this->Mshort = std::max(i,j);
  retorno   = 0.00;
}
///////////////////////////////////////////

// Operadores sobre o individuo ///////////
void Individual::killObject()
{
  delete this;
}

bool Individual::isNull() { return Mshort == 0 && Mlong == 0; }
//////////////////////////////////////////

// Visualizacao //////////////////////////
std::ostream& operator<<(std::ostream& ostream, Individual& ind)
{
  if (ind.retorno != 0.0)
    ostream << "Retorno: " << ind.retorno << std::endl;

  return ostream;
}
//////////////////////////////////////////
