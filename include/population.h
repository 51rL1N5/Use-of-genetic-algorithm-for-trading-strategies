#ifndef POPULATION_H
#define POPULATION_H

#include "stock.h"
#include "individual.h"

#include <iostream>

class Population {
private:


public:
  std::vector<Individual*> individuos;
  Stock acao;

  int size;
  int filled;
  int max_ma;

// Construtores //////////////////
  Population();
  Population(Stock S, int s, int ma);
//////////////////////////////////

  ~Population();
  int getFilled();
// Operadores sobre a populacao///
  void addIndividual(Individual *ind);
  void assassinar();

  double fitness(Stock& s, int fim, int inicio);  // Calcula o fit dos individuos
  double retorno(int ind);                        // Retorna o fit dos individuos

  Population top20(int TAM_INTERVAL);             // Retorna os 20% melhores individuos
  void crossover(int TAM_INTERVAL);
  void mutation(double MUTATION_PROBABILITY);     // Faz mutacao em todos os filhos dos 20% melhores
//////////////////////////////////

// Visualizacao //////////////////
friend std::ostream& operator<<(std::ostream& ostream, Population& pop);
//////////////////////////////////
};

#endif // POPULATION_H
