#include <quote.h>
#include <iostream>


Quote::Quote(std::string _nome){
    this->nome = _nome;
    this->open = 0;
    this->close = 0;
    this->high = 0;
    this->low = 0;
    this->adjclose = 0;
    this->volume = 0;
    this->data = "0000/00/00";
}

Quote::Quote(std::string nome,std::string data,double open,double close,double high,double low,double adjclose,long long volume){
    this->nome  = nome;
    this->open = open;
    this->close = close;
    this->high = high;
    this->low = low;
    this->adjclose = adjclose;
    this->volume = volume;
    this->data = data;
}

Quote::Quote(std::string nome,std::string data,double open,double close,double adjclose){
    this->nome  = nome;
    this->open = open;
    this->close = close;
    this->high = 0;
    this->low = 0;
    this->adjclose = adjclose;
    this->volume = 0;
    this->data = data;
}

///////////////////////////////////////////////////

/// Get e set dos atributos ///////////////////////

std::string Quote::getNome() { return this->nome; }
void Quote::setNome(std::string nome) { this->nome = nome; }

std::string Quote::getData() { return this->data; }
void Quote::setData( std::string data ) { this->data = data; }

///////////////////////////////////////////////////


/// operadores sobre dados ////////////////////////

bool Quote::isNull() { return this->data == "0000/00/00"; }

///////////////////////////////////////////////////


/// visualizaçao //////////////////////////////////

std::ostream& operator<<(std::ostream& ostream, Quote& q)
{
  ostream << "Nome: " << q.nome << "   Open: " << q.open <<"   Close: " << q.close <<  "  Data: " << q.getData()
  << "volume: " << q.volume<< std::endl;
  return ostream;
}

std::istream& operator>>(std::istream& is, Quote& q){
  std::istream::sentry s(is);
  if (s){
    is >> q.data >> q.open >> q.close >> q.high >> q.low >> q.adjclose >> q.volume;

  }
  return is;
}

///////////////////////////////////////////////////
