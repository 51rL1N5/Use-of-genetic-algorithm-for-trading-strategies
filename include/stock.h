#ifndef STOCK_H
#define STOCK_H

#include <iostream>
#include "quote.h"

class Stock
{
private:
  std::string nome;                  // nome da acao
  Quote* data;                        // dados associados a ela

  int size;
  int filled = 0;
public:

  Stock();                          // constructor
  Stock(std::string nome, int size);

// Set e get //////////////////////////////////////
  std::string getNome();
  int getFilled();
  Quote getData(int i);
///////////////////////////////////////////////////

// Operadores sobre a acao ////////////////////////
  void addData(Quote q);
  void popLeft();
  double mean();
  Stock sample(int inicio, int fim);

// Visualizacao ///////////////////////////////////

void movingAverage(int MA_TAM, std::string filename);
friend std::ostream& operator<<(std::ostream& ostream, Stock& s);


};

#endif // STOCK_H
