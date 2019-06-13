// Copyright 2018 Universidade Federal de Minas Gerais (UFMG)
//
// Lista de exercícios sobre Tipos Abstratos de Dados.
// Aplicação: Números MaquinaDeBuscas - Coordenadas Euclidianas.

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#include "maquina_de_busca.h"
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
  static set<string> palavras(const vector<string> TESTE)
  {
    return TESTE.palavras_;
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

  TEST_CASE("MaquinaDeBusca::MaquinaDeBusca(vector<string> nome_documentos)") {
    ifstream arq_teste("arq_teste.txt");
    vector<string> parametro;
    string aux;
    while(!arq_teste.eof()){
        arq_teste >> aux;
        parametro.push_back(aux);
        aux.clear();
        i++;
    }
    MaquinaDeBusca TESTE(parametro);
    CHECK(TESTE.nome_documentos() != empty())
  }

  TEST_CASE("MaquinaDeBusca::Tratar(string Palavra)"){
    ifstream arq_teste("arq_teste.txt");
    vector<string> parametro;
    string aux;
    int i=0;
    while(!arq_teste.eof()){
        arq_teste >> aux;
        parametro.push_back(aux);
        aux.clear();
        parametro[i] = Tratar(parametro[i]);
        i++;
    }
    MaquinaDeBusca TESTE(parametro);
    i = 0;
    while (i < parametro.length()){
        CHECK(parametro[i] >= 'a' && parametro[i] <= 'z');
        i++;
    }
  }

  TEST_CASE("MaquinaDeBusca::PreencherPalavras()") {
    ifstream arq_teste("arq_teste.txt");
    vector<string> parametro;
    string aux;
    int i=0;
    while(!arq_teste.eof()){
        arq_teste >> aux;
        parametro.push_back(aux);
        aux.clear();
        parametro[i] = Tratar(parametro[i]);
        i++;
    }
    MaquinaDeBusca TESTE(parametro);
    TESTE.PreencherPalavras();
    set<string> comparacao;
    while (int g = 0;g<parametro.size();g++){
        comparacao.insert(parametro[g]); 
        i++;
    }    
    CHECK(TESTE.Palavras() == comparacao);
  }

  TEST_CASE("MaquinaDeBusca::tf(const string palavra, const string documento)") {
    ifstream arq_teste("arq_teste.txt");
    vector<string> parametro;
    string aux;
    int i=0;
    while(!arq_teste.eof()){
        arq_teste >> aux;
        parametro.push_back(aux);
        aux.clear();
        parametro[i] = Tratar(parametro[i]);
        i++;
    }
    MaquinaDeBusca TESTE(parametro);
    int T = tf("teste","arq_teste.txt");
    CHECK(T == 2);
  }

  TEST_CASE("MaquinaDeBusca::IndiceInvertido()") {
    ifstream arq_teste("arq_teste.txt");
    vector<string> parametro;
    string aux;
    int i=0;
    while(!arq_teste.eof()){
        arq_teste >> aux;
        parametro.push_back(aux);
        aux.clear();
        parametro[i] = Tratar(parametro[i]);
        i++;
    }
    MaquinaDeBusca TESTE(parametro);
    TESTE.IndiceInvertido();
    

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
