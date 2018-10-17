#include <stock.h>
#include <quote.h>
#include <exception.h>

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

// Define utils /////////////////////////////
#define MIN_SIZE_ERROR "Erro no tamanho"
#define MAX_SIZE_ERROR "Erro no tamanho"
#define INCOHERENT_ID "Erro na identificacao"
#define INDEX_ERROR "Error nos indices"
/////////////////////////////////////////////

// Construtores /////////////////////////////
Stock::Stock(){}

Stock::Stock(std::string nome)
{
  // tratar excessao possível
  //if (size < 1) throw Error(MIN_SIZE_ERROR, "O tamanho dos dados deve ser, pelo menos, igual a 1");

  this->nome = nome;
  this->size = 0;

}


Stock::~Stock(){
    for(int i=0;i<data.size();i++)
        delete data[i];
}

///////////////////////////////////////////////

// Get ////////////////////////////////////////
std::string Stock::getNome() { return this->nome; }

int Stock::getFilled() { return this->filled; }

///////////////////////////////////////////////

// Operadores sobre acao //////////////////////

void Stock::addData(Quote *q)
{
  if(q == NULL) return;//Lançar erro talvez
  data.push_back(q);
  size++;
}

double Stock::mean()
{
  // if (!filled) return 0.0;
  // double m = 0.0;
  //
  // for (int i = 0; i < filled; i++)
  //   m+= this->data[i].getPreco();
  //
  // return m/filled;
}

void Stock::movingAverage(int MA_TAM, std::string filename)
{
  // double MA[filled] = { 0.00 };
  //
  // for (int i = 0; i < filled; i++)
  // {
  //   for (int j = 0; j < MA_TAM; j++)
  //     MA[i] += (this->data[std::max(i - j, j)].getPreco())/(MA_TAM+1);
  // }
  //
  //
  // std::ofstream file(filename);
  //
  // assert(file.is_open());
  //
  // for (int i = 0; i < filled; i++)
  //   file << this->data[i].getData() << ", " <<MA[i] << std::endl;
  //
  // file.close();
}

///////////////////////////////////////////////

// Visualizacao ///////////////////////////////

std::ostream& operator<<(std::ostream& ostream, Stock& q)
{
  std::string nome = q.getNome();

  ostream << "Nome da acao: " << nome << std::endl;

  // if(!q.data[0].isNull())
  // {
  //   ostream << "Data inicial: "<< q.data[0].getData() << std::endl;
  //   ostream << "Data final: " << q.data[q.filled - 1].getData() << std::endl;
  // }
  //
  // ostream << "Quantidade de dados disponiveis: " << q.filled << std::endl << "-------------------------------------\n";
  //
  // ostream << "  Date\t\t Price\n ------\t\t------\n\n";
  //
  for (auto it : q.data)
  {
    if (it->isNull())
      continue;
    ostream << *it;
  }

  return ostream;
}

///////////////////////////////////////////////
