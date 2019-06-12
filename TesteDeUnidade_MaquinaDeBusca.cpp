// Copyright 2018 Universidade Federal de Minas Gerais (UFMG)
//
// Lista de exercícios sobre Tipos Abstratos de Dados.
// Aplicação: Números MaquinaDeBuscas - Coordenadas Euclidianas.

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "maquina_de_busca.h"
#include "doctest.h"
#include <iostream>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <map>



class Teste
{
public:
  static set<string> palavras()
  {
    return palavras_;
  }
  static vector<string> nome_documentos()
  {
    return nome_documentos_;
  }
  static map<string,vector<string>> m_DocPalavras()
  {
    return  m_DocPalavras;
  }
  static map<string, int> max_frequencia()
  {
    return max_frequencia;
  }
  static map<string, double> idf()
  {
    return idf_;
  }
  static map<string,vector<double>> hash()
  {
    return hash_;
  }
  static map<string,map<string,int>> indiceInvertido()
  {
    return indiceInvertido_;
  }
};


TEST_SUITE("MaquinaDeBusca") {
  TEST_CASE("MaquinaDeBusca::MaquinaDeBusca(vector<string> nome_)") {
    ifstream arq_teste("arq_teste.txt");
    string str;
    while(!arq_teste.eof()){
    arq_teste >> str;
    }
    MaquinaDeBusca test();
    CHECK(nome_documentos() != empty())
  }

  TEST_CASE("MaquinaDeBusca::PreencherPalavras()") {
    
  }

  TEST_CASE("MaquinaDeBusca::tf(const string palavra, const string documento)") {
    
  }

  TEST_CASE("MaquinaDeBusca::IndiceInvertido()") {
    
  }

  TEST_CASE("MaquinaDeBusca::idf()") {

  }

  TEST_CASE("MaquinaDeBusca::get_Palavras()"){
    
  }

  TEST_CASE("MaquinaDeBusca::get_DocPalavras()"){
    
  }

  TEST_CASE("MaquinaDeBusca::get_Hash()") {
    
  }

  TEST_CASE("MaquinaDeBusca::get_IndiceInvertido()") {
    
  }

  TEST_CASE("MaquinaDeBusca::get_idf(string palavra)") {
    
  }

 
}
