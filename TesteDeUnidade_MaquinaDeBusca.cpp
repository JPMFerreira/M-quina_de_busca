#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
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
  static map<string, double> idf(const vector<string> TESTE)
  {
    return TESTE.idf_;
  }
  static map<string,map<string,double>> coord(const vector<string> TESTE)
  {
    return TESTE.coord_;
  }
  static map<string,map<string,int>> indiceInvertido(const vector<string> TESTE)
  {
    return TESTE.indiceInvertido_;
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
    CHECK(Teste::indiceInvertido(TESTE) == TESTE.IndiceInvertido());
  }

  TEST_CASE("MaquinaDeBusca::idf()") {
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
    TESTE.idf();
    (CHECK Teste::idf(TESTE) != NULL);
  }

  TEST_CASE("MaquinaDeBusca::Coordenadas()") {
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
    TESTE.idf();
    TESTE.Coordenadas();
    (CHECK Teste::coord(TESTE) != NULL);
  }

  TEST_CASE("MaquinaDeBusca::Buscador())") {
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
    TESTE.idf();
    TESTE.Coordenadas();
    (CHECK Teste::coord(TESTE) != NULL);
  } 
 
}
