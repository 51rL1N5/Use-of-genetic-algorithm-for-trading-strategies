#include <population.h>
#include <stock.h>
#include <individual.h>
#include <exception.h>
#include <quote.h>
#include <omp.h>

#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>

// Define utils /////////////////////
#define INDEX_ERROR "Erro em indice"
/////////////////////////////////////

// Construtores /////////////////////
Population::Population() {}

Population::Population(Stock & S, int s, int ma)
{
  this->size   =  s;
  this->acao  =  S;
  this->filled =  0;
  this->max_ma = ma;

  this->individuos = new Individual[this->size];

  for (int i = 0; i < this->size; i++)
    individuos[i] = Individual(0,0);

}
/////////////////////////////////////

Population::~Population()
{
  delete[] individuos;
}

int Population::getFilled() { return this->filled; }

// Operadores sobre a populacao /////

void Population::addIndividual(Individual ind)
{ this->individuos[filled] = ind; filled++;}

void Population::assassinar()
{ delete this; }

double Population::fitness(Stock& s, int ind, int inicio)
{

  if (ind < 0 || ind >= filled)
    throw Error(INDEX_ERROR, "Erro no segundo parametro: " +
                             std::to_string(ind)             +
                             "-- Linha 35 da funcao fitness --"
               );

  double retorno = 1;
  // No lugar de calcularmos o retorno ao longo de todo o intervalo
  // de data disponivel, selecionaremos um intervalo especifico
  // dente os dados. Tal intervalo sera aleatorio.
  // O motivo disso sera ter organismos preparados para
  // Diversas situacoes diferentes, e nao apenas para o periodo
  // Completo.

  for (int i = inicio; i < s.getFilled() - 1; i++)
  {
    int inicio1 = i - individuos[ind].MA1 + 1;
    int inicio2 = i - individuos[ind].MA2 + 1;

    // atualizar retorno da estrategia
    if (s.sample(std::min(inicio1, i), i).mean() > s.sample(std::min(inicio2, i), i).mean())
    {
      retorno *= s.getData(i + 1).getPreco() /  s.getData(i).getPreco();
    }
    else
    {
      retorno *= s.getData(i).getPreco() /  s.getData(i+1).getPreco();
    }
  }

  return retorno;
}

double Population::retorno(int ind)
{
  // Retorna o retorno medio do individuo ind

  if (ind < 0 || ind >= filled)
    throw Error(INDEX_ERROR, "Tentando acessar um individuo que nao existe na posicao -> " + std::to_string(ind));

  double retorno = 1;

  for (int i = max_ma; i < acao.getFilled() - 1; i++)
  {

    if (acao.sample(i - individuos[ind].MA1 + 1 , i).mean() > acao.sample(i - individuos[ind].MA2 + 1, i).mean() )
    {
      retorno *= acao.getData(i+1).getPreco()/acao.getData(i).getPreco();
    }
    else
    {
      retorno *= acao.getData(i).getPreco()/acao.getData(i+1).getPreco();
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



  for (int i=0; i<top20; i++)
  {
  	for (int j=i+1; j<filled; j++)
    {
  		if (individuos[j].retorno>individuos[i].retorno)
      {
  			// Switch values between organisms[i] and organisms[j]
  			Individual temp=individuos[i];
  			individuos[i]=individuos[j];
  			individuos[j]=temp;
  		}
  	}
  	pop.addIndividual(individuos[i]);
  }
/*
  std::sort(individuos, individuos + filled - 1, [](Individual a, Individual b){
    return a.retorno >= b.retorno;
  });

  for(int i = 0; i < top20; i++)
  {
    pop.addIndividual(individuos[i]);
  }
*/
  return pop;
}

void Population::crossover(int TAM_INTERVAL)
{

  Population melhores = top20(TAM_INTERVAL);
  filled = 0;

  // Perpertuar a especie com os 20 melhores
  for(int i = 0; i < melhores.size; i++)
    addIndividual(melhores.individuos[i]);

  while ( filled != size)
  {
    // gerar os reprodutores
    int r1 = rand()%melhores.size;
    int r2 = rand()%melhores.size;

    // impedir que os dois reprodutores sejam iguais
    if (r1 == r2) continue;

    if (rand()%2 == 0)
      addIndividual(Individual(melhores.individuos[r1].MA1, melhores.individuos[r2].MA2));
    else
      addIndividual(Individual(melhores.individuos[r2].MA1, melhores.individuos[r1].MA2));
  }

//  melhores.assassinar();
}

void Population::mutation(double MUTATION_PROBABILITY)
{
  int top20 = floor(0.2 * filled);

  // Assim como na selecao natural, apenas as criancas sofrerao
  // mutacao, pois a mutacao é um aspecto intrisseco a reproducao
#pragma omp parallel
{
#pragma omp for
  for (int i = top20; i < filled; i++)
  {
    // Vamos fazer que as medias moveis tenham chance
    // de sofrer alteracao para algum valor aleatorio entre
    // 1 e max_ma

    if( (double) rand()/(RAND_MAX) <= MUTATION_PROBABILITY )
      individuos[i].MA1 = 1 + rand()%(max_ma);
    if( (double) rand()/ (RAND_MAX) <= MUTATION_PROBABILITY )
      individuos[i].MA2 = 1 + rand()%(max_ma);


    // Impedir que hajam duas crianças iguais
    // Para que nao tenhamos duas estrategias iguais
    for(int j = 0; j < i; j++)
    {
      if ( individuos[i].MA1 == individuos[j].MA1 && individuos[i].MA2 == individuos[j].MA2 )
       { i--; break; }
    }
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
      continue;
    ostream << "Individuo no. " << (i + 1) << ":\n" << pop.individuos[i] << std::endl;
  }

  return ostream;
}
/////////////////////////////////////
