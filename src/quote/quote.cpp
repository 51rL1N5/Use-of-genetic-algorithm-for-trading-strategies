#include "../../include/quote.h"

#include <iostream>


/// Construtor ////////////////////////////////////

Quote::Quote(){};

Quote::Quote(std::string nome, double preco, std::string data)
{
  this->nome  = nome;
  this->preco = preco;
  this->data = data;
}

///////////////////////////////////////////////////



/// Get e set dos atributos ///////////////////////

std::string Quote::getNome() { return this->nome; }
void Quote::setNome(std::string nome) { this->nome = nome; }

double Quote::getPreco() { return preco; }
void Quote::setPreco(double preco) { this->preco = preco; }

std::string Quote::getData() { return this->data; }
void Quote::setData( std::string data ) { this->data = data; }

///////////////////////////////////////////////////


/// operadores sobre dados ////////////////////////
void Quote::aumentarPreco(double incremento) { this->preco += incremento; }
void Quote::addRetorno(double incremento) { this->preco *= 1 + incremento; }

bool Quote::isNull() { return this->data == "0000/00/00"; }

///////////////////////////////////////////////////


/// visualizaçao //////////////////////////////////

std::ostream& operator<<(std::ostream& ostream, Quote& q)
{
  ostream << "Nome: " << q.getNome() << "\nPreco: " << q.getPreco() << "\nData: " << q.getData() << std::endl;
  return ostream;
}

///////////////////////////////////////////////////
