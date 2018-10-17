#ifndef STOCK_H
#define STOCK_H

#include <iostream>
#include "quote.h"
#include <vector>
class Stock
{
public:
  std::string nome;                  // nome da acao
  std::vector<Quote*> data;          // dados associados a ela
  int size;
  int filled = 0;


  Stock();                          // constructor
  Stock(std::string nome);
  ~Stock();

// Set e get //////////////////////////////////////
  std::string getNome();
  int getFilled();

///////////////////////////////////////////////////

// Operadores sobre a acao ////////////////////////
  void addData(Quote *q);
  void popLeft();
  Stock sample(int inicio, int fim);
  double mean();

// Visualizacao ///////////////////////////////////

void movingAverage(int MA_TAM, std::string filename);
friend std::ostream& operator<<(std::ostream& ostream, Stock& s);


};

#endif // STOCK_H
