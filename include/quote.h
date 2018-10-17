#ifndef QUOTE_H
#define QUOTE_H

#include <iostream>

class Quote{
public:
  double open, close, high, low, adjclose, volume;
  std::string nome;
  std::string data;

  Quote();
  Quote(std::string nome,std::string data,double open,double close,double high,double low,double adjclose,double volume);
  Quote(std::string nome,std::string data,double open,double close,double adjclose);
  Quote(std::string nome);

/// Get e set dos atributos ////////////////////////////////
  std::string getNome();
  void setNome(std::string nome);
  std::string getData();
  void setData(std::string data);

/// operadores sobre dados //////////////////////////////////
void aumentarPreco(double incremento); // Aumenta o preco da acao
void addRetorno(double incremento);    // Adiciona um retorno (em percentagem)
bool isNull();                         // Retorna true se a quote for nula (data == "0000/00/00")
//////////////////////////////////////////////////////////////

/// Visualizacao /////////////////////////////////////////////
friend std::ostream& operator<<(std::ostream& ostream, Quote&);
friend std::istream& operator>>(std::istream& is, Quote&);
//////////////////////////////////////////////////////////////
};



#endif // QUOTE_H
