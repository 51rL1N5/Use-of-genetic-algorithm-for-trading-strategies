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

Stock::Stock(std::string nome, int size)
{
  // tratar excessao possível
  if (size < 1) throw Error(MIN_SIZE_ERROR, "O tamanho dos dados deve ser, pelo menos, igual a 1");

  this->nome = nome;
  this->size = size;

  this->data = new Quote[size];


  // inicializando os dados como zero
  for(int i = 0; i < size; i++)
    this->data[i] = Quote(nome, 0.00, "0000/00/00");

}

///////////////////////////////////////////////

// Get ////////////////////////////////////////
std::string Stock::getNome() { return this->nome; }

int Stock::getFilled() { return this->filled; }

Quote Stock::getData(int i) { return this->data[i];}

///////////////////////////////////////////////

// Operadores sobre acao //////////////////////

void Stock::addData(Quote q)
{
  // tratar excessao
  if(filled >= size) throw Error(MAX_SIZE_ERROR, "tentativa de adicionar mais dados do que o declarado");

  if(q.getNome() != nome) throw Error(INCOHERENT_ID, "Nome da acao associada ao dado e incoerente");

  if (!filled)
    this->data[filled] = q;


  for (int i = 0; i < filled; i++)
  {
    if (this->data[i].getData() > q.getData())
    {
      this->data[filled] = this->data[i];
      this->data[i] = q;
      break;
    }

    if( i == filled - 1)
      this->data[filled] = q;

  }

  filled++;
}

void Stock::popLeft()
{
  // Deletar o elemento mais antigo

  if (size == 1)
  {
    this->data[0] = Quote(this->nome, 0.00, "0000/00/00");
    this->filled = 0;
    return;
  }
  else if (this->filled == 0)
  {
    return;
  }
  else
  {
    for (int i = 1; i < filled; i++)
      this->data[i-1] = this->data[i];

    this->data[filled-1] = Quote(nome, 0.00, "0000/00/00");
    filled--;
  }

}

double Stock::mean()
{
  if (!filled) return 0.0;

  double m = 0.0;

  for (int i = 0; i < filled; i++)
    m+= this->data[i].getPreco();

  return m/filled;

}

Stock Stock::sample(int inicio, int fim)
{

  if (inicio > fim || inicio < 0 || fim >= filled)
  {
    std::cout << inicio << " " << fim  <<'\n';
    throw Error(INDEX_ERROR, "Erro na definicao de inicio (" +std::to_string(inicio)+ ") e fim (" +std::to_string(fim)+ ")");
  }

  Stock S(this->nome, fim - inicio + 1);

  for (int i = inicio; i <= fim; i++)
  {
    S.addData(this->data[i]);
  }

  return S;
}


void Stock::movingAverage(int MA_TAM, std::string filename)
{
  double MA[filled] = { 0.00 };

  for (int i = 0; i < filled; i++)
  {
    for (int j = 0; j < MA_TAM; j++)
      MA[i] += (this->data[std::max(i - j, j)].getPreco())/(MA_TAM+1);
  }


  std::ofstream file(filename);

  assert(file.is_open());

  for (int i = 0; i < filled; i++)
    file << this->data[i].getData() << ", " <<MA[i] << std::endl;

  file.close();
}

///////////////////////////////////////////////

// Visualizacao ///////////////////////////////

std::ostream& operator<<(std::ostream& ostream, Stock& q)
{
  std::string nome = q.getNome();

  ostream << "Nome da acao: " << nome << std::endl;

  if(!q.data[0].isNull())
  {
    ostream << "Data inicial: "<< q.data[0].getData() << std::endl;
    ostream << "Data final: " << q.data[q.filled - 1].getData() << std::endl;
  }

  ostream << "Quantidade de dados disponiveis: " << q.filled << std::endl << "-------------------------------------\n";

  ostream << "  Date\t\t Price\n ------\t\t------\n\n";

  for (int i = 0; i < q.size; i++)
  {
    if (q.data[i].isNull())
      continue;
    ostream << q.data[i].getData() << "\t" << q.data[i].getPreco() << std::endl;
  }

  return ostream;
}

///////////////////////////////////////////////
