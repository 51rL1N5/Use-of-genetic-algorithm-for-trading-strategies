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
#include <utility>

// Define utils /////////////////////
#define INDEX_ERROR "Erro em indice"
/////////////////////////////////////

// Construtores /////////////////////
Population::Population() {}

Population::Population(Stock S, int s, int ma)
{
std::cout << "construtor pop" <<std::endl;
  this->size   =  s;
  std::cout << "construtor pop" <<std::endl;
  this->acao  =  S;
  std::cout << "construtor pop" <<std::endl;
  this->filled =  0;
  std::cout << "construtor pop" <<std::endl;
  this->max_ma = ma;

  // for (int i = 0; i < this->size; i++)
  //   individuos.push_back(new Individual(0,0));
  //
  // individuos.shrink_to_fit();
}
/////////////////////////////////////

Population& Population::operator=(const Population &pop)
{
    std::cout << "construtor ===== Populacao\n";
    this->size   =  pop.size;
    this->acao  =  pop.acao;
    this->filled =  pop.filled;
    this->max_ma = pop.max_ma;
    this->individuos.clear();
    for(auto it:pop.individuos){
        Individual* Indaux = new Individual(*it);
        this->addIndividual(Indaux);
    }
    return *this;
}

Population::~Population()
{
  for (int i = 0; i < filled; i++){
    delete individuos[i];
    }
    individuos.clear();

}

int Population::getFilled() { return this->filled; }

// Operadores sobre a populacao /////

void Population::addIndividual(Individual *ind)
{
    if(ind == NULL) return;
    individuos.push_back(ind);
    size++;
    filled++;
}

void Population::assassinar()
{ delete this; }

double Population::fitness(Stock &s, int ind, int inicio)
{

  if (ind < 0 || ind >= filled)
    throw Error(INDEX_ERROR, "Erro no segundo parametro: " +
                             std::to_string(ind)             +
                             "-- Linha 35 da funcao fitness --"
               );

  double retorno = 0;
  // No lugar de calcularmos o retorno ao Mlongo de todo o intervalo
  // de dados disponivel, selecionaremos um intervalo especifico
  // dente os dados. Tal intervalo sera aleatorio.
  // O motivo disso sera ter organismos preparados para
  // Diversas situacoes diferentes, e nao apenas para o periodo
  // Completo.



  for (int i = inicio; i < s.getFilled() - 1; i++)
  {
    int inicio1 = i - individuos[ind]->Mlong + 1;
    int inicio2 = i - individuos[ind]->Mshort + 1;

    // atualizar retorno da estrategia
    if (s.sample(std::max(inicio1, 0), i ).mean() > s.sample(std::max(inicio2,0), i).mean())
      retorno += s.data[i + 1]->open - s.data[i + 1]->close;
    else
      retorno += s.data[i + 1]->close - s.data[i + 1]->open;

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

    int inicio1 = i - individuos[ind]->Mlong + 1;
    int inicio2 = i - individuos[ind]->Mshort + 1;

    // atualizar retorno da estrategia
    if (acao.sample(std::max(inicio1, 0), i).mean() > acao.sample(std::max(inicio2, 0), i).mean())
      retorno += acao.data[i + 1]->open - acao.data[i + 1]->close;
    else
      retorno += acao.data[i + 1]->close - acao.data[i + 1]->open;

  }
  return retorno;
}

Population Population::top20(int TAM_INTERVAL)
{

  // Gerar a populacao com os 20% melhores
  std::cout << "top20 filled = "<<this->size <<std::endl;
  int top20 = floor(0.2 * filled);

  Population pop;
  std::cout << "top20 depois de POP "<<std::endl;
  /////////////////////////////////////////////////

  // Selecionar um intervalo aletorio de tamanho TAM_INTERVAL
  // E amostra TAM_INTRVAL amostras do S&P 500
  // O objetivo disto é obter individuos que
  // possuam um bom rendimento em qualquer periodo de tempo
  // aleatorio

  int r = rand()%(acao.getFilled() - TAM_INTERVAL);

  // Calcular o fitness dos individuos

  Stock S = acao.sample(std::max(0, r - max_ma), r + TAM_INTERVAL);

  for (int i = 0; i < filled; i++){
    individuos[i]->retorno = fitness(S, i, max_ma);
    std::cout << "fit = "<< individuos[i]->retorno <<std::endl;
}


  for (int i=0; i<top20; i++)
  {
  	for (int j=i+1; j<filled; j++)
    {
  		if (individuos[j]->retorno > individuos[i]->retorno)
      {
  			// Switch values between organisms[i] and organisms[j]
  			Individual* temp=individuos[i];
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
    std::cout << "crossover 1" <<std::endl;
  Population melhores = top20(TAM_INTERVAL);
  filled = 0;
  std::cout << "crossover 2" <<std::endl;
  // Perpertuar a especie com os 20 melhores
  for(int i = 0; i < melhores.size; i++)
    addIndividual((melhores.individuos[i]));
std::cout << "crossover 3" <<std::endl;
  while ( filled != size)
  {
    // gerar os reprodutores
    int r1 = rand()%melhores.size;
    int r2 = rand()%melhores.size;

    // impedir que os dois reprodutores sejam iguais
    if (r1 == r2) continue;

    if (rand()%2 == 0){
        Individual *temp =  new Individual(melhores.individuos[r1]->Mlong, melhores.individuos[r2]->Mshort);
        addIndividual(temp);

    }

    else{
        Individual *temp =  new Individual(melhores.individuos[r2]->Mlong, melhores.individuos[r1]->Mshort);
        addIndividual(temp);

    }
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
      individuos[i]->Mlong = 1 + rand()%(max_ma);
    if( (double) rand()/ (RAND_MAX) <= MUTATION_PROBABILITY )
      individuos[i]->Mshort = 1 + rand()%(max_ma);

    if (individuos[i]->Mlong < individuos[i]->Mshort) std::swap(individuos[i]->Mlong , individuos[i]->Mshort);

    // Impedir que hajam duas crianças iguais
    // Para que nao tenhamos duas estrategias iguais
    for(int j = 0; j < i; j++)
    {
      if ( individuos[i]->Mlong == individuos[j]->Mlong && individuos[i]->Mshort == individuos[j]->Mshort )
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
    if (pop.individuos[i]->isNull())
      continue;
    ostream << "Individuo no. " << (i + 1) << ":\n" << *(pop.individuos[i]) << std::endl;
  }

  return ostream;
}
/////////////////////////////////////
