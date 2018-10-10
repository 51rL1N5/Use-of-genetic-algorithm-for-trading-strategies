#include "../../include/population.h"
#include "../../include/stock.h"
#include "../../include/individual.h"
#include "../../include/exception.h"
#include "../../include/quote.h"

#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>

// Define utils /////////////////////
#define INDEX_ERROR "Erro em indice"
/////////////////////////////////////

// Construtores /////////////////////
Population::Population() {}

Population::Population(Stock S, int s, int ma)
{
  this->size   =  s;
  this->stock  =  S;
  this->filled =  0;
  this->max_ma = ma;

  this->individuos = new Individual[this->size];
}
/////////////////////////////////////


// Operadores sobre a populacao /////

void Population::addIndividual(Individual ind)
{ this->individuos[filled] = ind; filled++;}

double Population::fitness(Stock& s, int fim, int inicio)
{

  if (fim < 0 || fim >= filled)
    throw Error(INDEX_ERROR, "Erro no segundo parametro: " +
                             std::to_string(fim)             +
                             "-- Linha 35 da funcao fitness --"
               );


  // No lugar de calcularmos o retorno ao longo de todo o intervalo
  // de data disponivel, selecionaremos um intervalo especifico
  // dente os dados. Tal intervalo sera aleatorio.
  // O motivo disso sera ter organismos preparados para
  // Diversas situacoes diferentes, e nao apenas para o periodo
  // Completo.

  for (int i = inicio; i < s.getFilled() - 1; i++)
  {
    // atualizar retorno da estrategia
    if (s.sample(i - individuos[n].MA1 + 1, i).mean() > s.sample(i - individuos[n].MA2 + 1, i).mean())
    {
      retorno *= s.getData(i + 1).getPrice() /  s.getData(i).getPrice();
    }
    else
    {
      retorno *= s.getData(i).getPrice() /  s.getData(i+1).getPrice();
    }
  }

  return retorno;
}

double Population::retorno(int ind)
{
  // Retorna o retorno medio do individuo ind

  if (ind < 0 || n >= filled)
    throw Error(INDEX_ERROR, "Tentando acessar um individuo que nao existe na posicao -> " + std::to_string(ind));

  double retorno = 1;

  for (int i = max_ma; i < acao.getFilled(); i++)
  {
    if (acao.sample(i - individuos[ind].MA1 + 1, i).mean() > acao.sample(i - individuos[ind].MA2 + 1, i).mean() )
    {
      retorno *= acao.getData(i+1).getPrice()/acao.getData(i).getPrice();
    }
    else
    {
      retorno *= acao.getData(i).getPrice()/acao.getData(i+1).getPrice();
    }
  }

  return retorno;
}

Population Population::top20(int TAM_INTERVAL)
{

  // Gerar a populacao com os 20% melhores
  int top20 = floor(0.2 * filled);

  Population pop = Population(acao, top20, max_ma);
  /////////////////////////////////////////////////

  // Selecionar um intervalo aletorio de tamanho TAM_INTERVAL
  // E amostra TAM_INTRVAL amostras do S&P 500
  // O objetivo disto é obter individuos que
  // possuam um bom rendimento em qualquer periodo de tempo
  // aleatorio

  int r = rand()%(acao.getFilled() - TAM_INTERVAL);

  Stock S = acao.sample(std::max(0, r - max_ma), r + TAM_INTERVAL);

  // Calcular o fitness dos individuos

  for (int i = 0; i < filled; i++)
    individuos[i].retorno = fitness(S, i, max_ma);

  std::sort(individuos, individuos + top20 - 1, [](Individual a, Individual b){
    return a.retorno < b.retorno;
  });

  for(int i = 0; i < top20; i++)
  {
    pop.addOrganism(individuos[i]);
  }

  return pop;
}

void Population::crossover(int TAM_INTERVAL)
{

  Population melhores = top20(TAM_INTERVAL);
  filled = 0;

  // matar a antiga populacao
  for(int i = 0; i < size; i++)
    individuos[i].killObject();

  // Perpertuar a especie com os 20 melhores
  for(int i = 0; i < melhores.size; i++)
    addIndividual(melhores.individuos[i]);


  while ( filled != size)
  {
    // gerar os reprodutores
    int r1 = rand()%top.size();
    int r2 = rand()%top.size();

    // impedir que os dois reprodutores sejam iguais
    if (r1 == r2) continue;

    if (rand()%2 == 0)
      addIndividual(Individual(melhores.individuos[r1].MA1, melhores.individuos[r2].MA2));
    else
      addIndividual(Individual(melhores.individuos[r2].MA1, melhores.individuos[r1].MA2));
  }


}

void Population::mutation(double MUTATION_PROBABILITY)
{
  int top20 = floor(0.2 * filled);

  // Assim como na selecao natural, apenas as criancas sofrerao
  // mutacao, pois a mutacao é um aspecto intrisseco a reproducao

  for (int i = top20; i < filled; i++)
  {
    // Vamos fazer que as medias moveis tenham chance
    // de sofrer alteracao para algum valor aleatorio entre
    // 1 e max_ma

    if( (double) rand()/(RAND_MAX) <= MUTATION_PROBABILITY )
      individuos[i].MA1 = 1 + rand()%(max_ma + 1);
    if( (double) rand()/ (RAND_MAX) <= MUTATION_PROBABILITY )
      individuos[i].MA2 = 1 + rand()%(max_ma + 1);


    // Impedir que hajam duas crianças iguais
    // Para que nao tenhamos duas estrategias iguais
    for(int j = 0; j < i; j++)
    {
      if ( individuos[i].MA1 == individuos[i].MA1 && individuos[i].MA2 == individuos[i].MA2 )
       { i--; break; }
    }
  }


}
/////////////////////////////////////

// Visualizacao /////////////////////
std::ostream& operator<<(std::ostream& ostream, Population& pop)
{

  ostream << "Tamanho da populacao: " << pop.filled << std::endl;
  ostream << "Acao: " << pop.acao.getNome() << "\n\n";

  for ( int i = 0; i < pop.size; i++)
  {
    if (pop.individuos[i].isNull())
      continue
    ostream << "Individuo no. " << (i + 1) << ":\n" << pop.individuos[i] << std::endl;
  }

  return osteam;
}
/////////////////////////////////////
