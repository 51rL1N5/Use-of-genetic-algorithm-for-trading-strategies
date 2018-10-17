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
  if (!filled) return 0.0;

  double m = data[0]->adjclose;

  double alpha = 2 / (1 + filled);

  for (int i = 0; i < data.size() ; i++)
    m = alpha * (data[i]->adjclose) + (1 - alpha)*m;

  return m;
}

Stock Stock::sample(int inicio, int fim)
{
  if (inicio > fim || inicio < 0 || fim >= filled)
  {
    std::cout << inicio << " " << fim  <<'\n';
    throw Error(INDEX_ERROR, "Erro na definicao de inicio (" +std::to_string(inicio)+ ") e fim (" +std::to_string(fim)+ ")");
  }

  Stock S(this->nome);

  for (int i = inicio; i <= fim; i++)
  {
    S.addData(this->data[i]);
  }

  return S;
}

void Stock::movingAverage(int MA_TAM, std::string filename)
{
  double MA[filled] = { 0.00 };

  MA[0] = this->data[0]->adjclose;

  double alpha = 2 / (1 + MA_TAM);

  for (int i = 1; i < filled; i++)
    MA[i] = alpha * this->data[i]->adjclose + (1 - alpha) * MA[i-1];

  std::ofstream file(filename);

  assert(file.is_open());

  for (int i = 0; i < filled; i++)
    file << this->data[i]->getData() << ", " <<MA[i] << std::endl;

  file.close();
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
