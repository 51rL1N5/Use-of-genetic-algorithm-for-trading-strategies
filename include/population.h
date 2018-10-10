#ifndef POPULATION_H
#define POPULATION_H

#include "../../include/stock.h"
#include "../../include/individual.h"

#include <iostream>

class Population {
private:
  Individual * individuos;
  Stock        acao;

  int size;
  int filled;
  int max_ma;

public:
// Construtores //////////////////
  Population();
  Population(Stock S, int s, int ma);
//////////////////////////////////

// Operadores sobre a populacao///
  void addIndividual(Individual ind);

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
