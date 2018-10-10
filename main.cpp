#include "../../include/exception.h"
#include "../../include/quote.h"
#include "../../include/stock.h"
#include "../../include/indivual.h"
#include "../../include/population.h"


#include <iostream>
#include <cmath>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <string>

using namespace std;

// Assinatura de funcoes uteis //////////////
void loadData(Stock& S, std::string file);
Population randomPopulation(Stock S, const int max_population, const int max_ma);
Population geneticAlgorithm(Stock S, const int max_population, const int max_ma, const int number_generations, const int TAM_INTERVAL, const double MUTATION_PROBABILITY);
/////////////////////////////////////////////

// Declaracao de funcoes ////////////////////
Population randomPopulation(Stock S, const int max_population, const int max_ma)
{
  Population pop = Population(S, max_population, max_ma);

  for (int i = 0; i < max_population; i++)
    pop.addIndividual( Organism(1 + rand()%(max_ma + 1), 1 + rand()%(max_ma + 1)));

  return pop;
}

void loadData(Stock& S, std::string file)
{

  std::ifstream input0(file.c_str());

  assert(file.is_open());

  int lines = 0;
  std::string date;
  double price;

  while (!input0.eof())
    lines ++;

  input0.close();

  S = Stock("S&P 500", lines);

  std::ifstream input(file.c_str());

  assert(input.is_open());

  while (!input.eof())
  {
    input >> date >> price;
    S.addData(Quote(S.getNome(), price, date));
  }

  input.close();
}

Population geneticAlgorithm (Stock stock, const int max_population, const int max_ma, const int number_generations, const int TAM_INTERVAL, const double MUTATION_PROBABILITY)
{

  std::cout << "Criando uma populacao aleatoria de " << max_population << " individuos";
  Population pop = randomPopulation(stock, max_population, max_ma);
  std::cout << " Pronto" << '\n';

  // Simulacao das geracoes

  std::cout << "Comecando a simulacao" << '\n';

  for ( int i = 1; i <= number_generations; i++)
  {
    pop.crossover(TAM_INTERVAL);

    pop.mutation(MUTATION_PROBABILITY)

    std::cout << "\r" << "Geracao numero " << i << "/" <<number_generations << std::flush;
  }

  std::cout << "\nCalculando o retorno dos organismos";

  for (int j = 0; j < pop.filled; j++)
    pop.individuos[j].retorno =pop.retorno(j);

  std::cout << " Fim"<< std::endl;

  return pop;
}

/////////////////////////////////////////////


int main(int argc, char** argv)
{
  srand(time(NULL));

  int POPULATION_SIZE          = atoi(argv[1]);
  int MAX_MOVING_AVERAGE       = atoi(argv[2]);
  int NUMBER_OF_GENERATIONS    = atoi(argv[3]);
  int TAM_INTERVAL             = atoi(argv[4]);
  double MUTATION_PROBABILITY  = stod(argv[5]);

  Stock SP500;
  loadData(SP500, "SP500.dat");

  Population pop = geneticAlgorithm(SP500.sample(0, floor(0.6 * SP500.getFilled())), POPULATION_SIZE, MAX_MOVING_AVERAGE, NUMBER_OF_GENERATIONS, TAM_INTERVAL, MUTATION_PROBABILITY);

  return 0;
}
