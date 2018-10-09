#ifndef STOCK_H
#define STOCK_H

#include <iostream>
#include "quote.h"

class Stock
{
private:
  std::string nome; // nome da acao
  Quote data;       // dados associados a ela

  int size;
  int filled;
public:

  Stock();

};

#endif // STOCK_H
