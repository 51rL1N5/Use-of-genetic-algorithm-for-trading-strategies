#ifndef QUOTE_H
#define QUOTE_H

#include <iostream>


class Quote{
private:

  double preco;
  std::string nome;
  std::string data;

public:

  Quote();
  Quote(std::string nome, double preco, std::string data);


/// Get e set dos atributos ////////////////////////////////
  std::string getNome();
  void setNome(std::string nome);
  double getPreco();
  void setPreco(double preco);
  std::string getData();
  void setData(std::string data);
/////////////////////////////////////////////////////////////

/// operadores sobre dados //////////////////////////////////
void aumentarPreco(double incremento); // Aumenta o preco da acao
void addRetorno(double incremento);    // Adiciona um retorno (em percentagem)
bool isNull();                         // Retorna true se a quote for nula (data == "0000/00/00")
//////////////////////////////////////////////////////////////

/// Visualizacao /////////////////////////////////////////////
friend std::ostream& operator<<(std::ostream& ostream, Quote&);
//////////////////////////////////////////////////////////////

};



#endif // QUOTE_H
