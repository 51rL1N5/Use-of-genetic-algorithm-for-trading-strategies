#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

class Individual
{
private:
  int MA1;
  int MA2;

  double retorno;

public:

// Construtores //////////////////
  Individual();
  Individual(int i, int j);
//////////////////////////////////

// Operadoes sobre organismo//////
  void killObject();

  bool isNull();
//////////////////////////////////

// Visualizacao //////////////////
  friend std::ostream& operator<<(std::ostream& ostream, Individual& ind);
//////////////////////////////////
};

#endif // INDIVIDUAL_H
