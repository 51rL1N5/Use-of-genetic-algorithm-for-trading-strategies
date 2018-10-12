#include <exception.h>
#include <iostream>
#include <cstdlib>

Error::Error(std::string problema, std::string descricao)
{
  std::cerr << "::::: Problema  -> " << problema << " :::::::" << std::endl;
  std::cerr << "::::: Descricao -> " << descricao << " :::::::" << std::endl;

  exit(EXIT_FAILURE);
}
