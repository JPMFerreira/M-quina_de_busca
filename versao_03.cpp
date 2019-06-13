#include <iostream>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cmath>

using namespace std;


void imprimir(map<string, int> i){
    for(auto h : i){
        cout << h.first <<"," <<h.second << endl;
}

}
void imprimir(map<string,vector<string>> i){
    for(auto h : i){
        cout << h.first << " ( ";
        for(unsigned j=0;j<h.second.size();j++)
            cout << h.second[j] << " ";
        cout <<  ")" << endl;
    }
}
void imprimir(map<string,map<string, int>> i){
     for(auto h : i){
        cout << h.first << "( ";
        for(auto k:h.second){
            cout <<k.first << "," <<  k.second<< " ";
        }
        cout << ")" << endl;;
    }
}

//******************************** class Arquivo *****************************
class Arquivo{
    public:
        Arquivo(string pasta);
        void PegarNomeDosArquivos();
        vector<string> NomesDoc();
    private:
        vector<string> nome_documentos;
        string pasta_;
    


    friend class Teste;
};
//************************************implementação ******************************
Arquivo::Arquivo(string pasta):pasta_(pasta){}

void Arquivo::PegarNomeDosArquivos(){
    nome_documentos.push_back(pasta_+"Tp.txt");
    nome_documentos.push_back(pasta_+"Jp.txt");
    nome_documentos.push_back(pasta_+"ab.txt");
}
vector<string> Arquivo::NomesDoc(){
    return nome_documentos;
}
//******************************** class DocCoordenadas ************************

class MaquinaDeBusca{
    public:
    MaquinaDeBusca(const vector<string> nome_documentos);
    void PreencherPalavras();
    string Tratar(string palavra);
    int tf(const string palavra, const string documento);
    void IndiceInvertido();
    void idf();
    
    void Coordenadas();

    void Buscador();
    double Similaridade(string documento, string palavra);
    void Ranking(map<double,vector<string>> SimilaridadeDocumentos);

   

    set<string> get_Palavras();
    map<string,vector<string>> get_DocPalavras();
    map<string,vector<double>> get_Coord();
    map<string,map<string,int>> get_IndiceInvertido();
    double get_idf(string palavra);
    map<string,int> get_Fmax();

    private:
    set<string> palavras_;
    vector<string> nome_documentos_;
    map<string,vector<string>> m_DocPalavras;
    map<string, int> max_frequencia;
    map<string, double> idf_;
    map<string,map<string,double>> coord_;
    map<string,map<string,int>> indiceInvertido_;



    friend class Teste;
};
//************************************implementação ******************************
MaquinaDeBusca::MaquinaDeBusca(const vector<string> nome_documentos):nome_documentos_(nome_documentos){ }

string MaquinaDeBusca::Tratar(string palavra){
    int x = 0;
    while( x < palavra.length()){
        if(palavra[x]>='A' && palavra[x]<='Z'){
            palavra[x]+=32;
            x++;
        }
        else if(!(palavra[x]>='a' && palavra[x]<='z')){
            palavra.erase(palavra.begin()+x);               
        }
        else x++;
    }
    return palavra;
}

void MaquinaDeBusca::PreencherPalavras(){
        string palavra;
        vector<string> vec_aux;
        unsigned x=0,linha=0,coluna=0;
        for(auto doc:nome_documentos_){
            ifstream in(doc);
            while(!in.eof()){
                in>>palavra;
                palavra = Tratar(palavra);
            if( palavra.length()!=0){
                vec_aux.push_back(palavra);
                palavras_.insert(palavra);
            }
        }
        m_DocPalavras[doc]=vec_aux;
        vec_aux.clear();
    }
}


map<string,vector<string>> MaquinaDeBusca::get_DocPalavras(){
    return m_DocPalavras;
}

int MaquinaDeBusca::tf(const string palavra, const string documento){
    int f=0;
    vector<string> i= m_DocPalavras[documento];
        //i.second é o vetor de palavras contidas num documento
    for(int j =0; j<i.size();j++){
        if(palavra == i[j]){
            //i.first é o nome do documento;
            f++;
        }
    }
    return f;
}
void MaquinaDeBusca::IndiceInvertido(){
    int fMax=0,aux=0;
    for(auto i:palavras_){
        fMax=0;
        for(auto j:nome_documentos_){
            if(tf(i,j)!=0){
                indiceInvertido_[i][j]=tf(i,j);
                aux=tf(i,j);
                if(fMax<aux){
                    fMax=aux;
                }
            }
        }
        max_frequencia[i] = fMax;
    }
}
map<string,map<string,int>> MaquinaDeBusca::get_IndiceInvertido(){
    return indiceInvertido_;
}

void MaquinaDeBusca::idf(){
    double aux;
    for(auto i:palavras_){
        aux = nome_documentos_.size();
        idf_[i] = log(aux/indiceInvertido_[i].size());
        cout << "log(" << nome_documentos_.size()<< "/" << indiceInvertido_[i].size() <<") = "<<idf_[i] << endl;
    }
}
double MaquinaDeBusca::get_idf(string palavra){
    return idf_[palavra];
}
void MaquinaDeBusca::Coordenadas(){
    int x =1;
    for(auto i:nome_documentos_){
        cout << "doc"<< x << "( ";
        for(auto j:palavras_){
            coord_[i][j]= idf_[j] * tf(j,i)/max_frequencia[j];
              cout <<coord_[i][j]<< " ";
        }
        cout << ")"<< endl;
        x++;
    }
}
map<string,int> MaquinaDeBusca::get_Fmax(){
    return max_frequencia;
}
// QUEBRAR BUSCA EM PALAVRAS_UNITARIAS
    // TEM Q USAR O idf JÁ EXISTENTE DA PALAVRA DIGITADA E MULTIPLICAR 
    // PELA FREQUENCIA DELA NA STRING DIGITADA (ex: "Thiago th14iago ribeiro")
    // OBTENDO ASSIM O W(BUSCA,PALAVRA_UNITARIA). O CONJUNTO DE Ws FORMA UMA COORDENADA
    // DE BUSCA (ex: 0 0 0 0,489 0,234 0 0 0 0 0 0...);
    // TEM QUE FAZER A SOMATORIA DAS SIMILARIDADES DE CADA PALAVRA_UNITARIA EM CADA DOCUMENTO 
    // (ex: SIM(D1,thiago)+SIM(D1,thiago)+SIM(D1,ribeiro))
    // O QUE DEMONSTRAR MAIOR SIMILARIDADE ESTARÁ NO TOPO DO RANKING
    // CRIAR UM MAP<DOUBLE,STRING> (MAP<SOMATORIA_SIMILARIDADE,NOME_DOCUMENTO)
    // E IMPRIMIR EM ORDEM DECRESCENTE (ISSO SERÁ A RESPOSTA DO NOSSO PROGRAMA)

void MaquinaDeBusca::Ranking(map<double,vector<string>> SimilaridadeDocumentos){
    int contador=1;
    for(auto i=--SimilaridadeDocumentos.end();i!=--SimilaridadeDocumentos.begin();--i){
        for(auto j:i->second){
            cout << contador << "o  " << j << "  ";
            contador++;
        }
        cout << endl;
    }
}
void MaquinaDeBusca::Buscador(){
    string busca, aux;
    vector<string> palavrasDaBusca;
    map<string,int> PalavraFreq;
    map<string, double> CoordenadasDaBusca;
    map<double,vector<string>> SimilaridadeDocumentos;
    getline(cin,busca);
    // separar por palavra a string de busca
    for(int i=0;i<busca.size();i++){
        if(busca[i]!=' ')
            aux.push_back(busca[i]);
        if(busca[i]==' '|| i == busca.size()-1){
            aux = Tratar(aux);
            palavrasDaBusca.push_back(aux);
            cout << aux << endl;
            aux.clear();
        }
    }

    //preenchendo PalavraFrequencia
    for(int j=0;j<palavrasDaBusca.size();j++){
        if(PalavraFreq.find(palavrasDaBusca[j])!=PalavraFreq.end()){
            PalavraFreq[palavrasDaBusca[j]]++;
        }else{
            PalavraFreq[palavrasDaBusca[j]] = 1;
        }
    }

    double aux1;
    int w=1;
    for(auto z:PalavraFreq){
        aux1 = z.second  ;
        CoordenadasDaBusca[z.first] = aux1*idf_[z.first]/ max_frequencia[z.first];
        cout << "Posicao " << w  << " = " <<CoordenadasDaBusca[z.first] << "  tf  "<< aux1 << " idf  " << idf_[z.first] << "  frequencia max  "<< max_frequencia[z.first] << endl;
        w++;
    }

    map<string,double> sim_;
    map<string,int> aux2;
    double xx;
    cout << coord_.size();
    for(auto p:PalavraFreq){
        for( auto k:indiceInvertido_[p.first]){
            sim_[k.first] += CoordenadasDaBusca[p.first] * coord_[k.first][p.first];
            cout << "Similaridade do doc na palavra " << p.first<< "= "<<  "P.first " << p.first << "  K.first  " << k.first << "  sim_  " <<sim_[k.first] << " Coordenada  " <<CoordenadasDaBusca[p.first] <<" coord_[k.first][p.first] " << coord_[k.first][p.first] << "    idf   " << idf_[p.first]<< endl;
            
        }
        
        cout << endl;
    }
    for(auto l:nome_documentos_){
            SimilaridadeDocumentos[sim_[l]].push_back(l);
    }
    Ranking(SimilaridadeDocumentos);
}






int main(){
    Arquivo arq("dia/");
    arq.PegarNomeDosArquivos();

    MaquinaDeBusca b(arq.NomesDoc());
    b.PreencherPalavras();
    imprimir(b.get_DocPalavras());
    cout<<endl<<endl<<endl;
    b.IndiceInvertido();
    imprimir(b.get_IndiceInvertido());
    
    b.idf();
    b.Coordenadas();
    imprimir(b.get_Fmax());
    b.Buscador();
   



   // b.IndiceInvertido();
    //b.Coordenadass();
    return 0;
}