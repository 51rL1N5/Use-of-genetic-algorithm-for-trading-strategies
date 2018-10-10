#include "../../include/individual.h"

#include <iostream>

// Construtores ///////////////////////////
Individual::Individual() {}

Individual::Individual(int i, int j)
{
  this->MA1 = std::max(i,0);
  this->MA2 = std::max(j,0);
  retorno   = 0.00;
}
///////////////////////////////////////////


// Operadores sobre o individuo ///////////
void Individual::killObject()
{
  delete this;
}

bool Individual::isNull() { return MA1 == 0 && MA2 == 0; }
//////////////////////////////////////////

// Visualizacao //////////////////////////
std::ostream& operator<<(std::ostream& ostream, Individual& ind)
{
  if (ind.retorno != 0.0)
    ostream << "Retorno: " << ind.retorno << std::endl;

  return ostream;
}
//////////////////////////////////////////
