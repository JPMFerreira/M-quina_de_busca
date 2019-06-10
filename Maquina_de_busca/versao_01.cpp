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
};
//************************************implementação ******************************
Arquivo::Arquivo(string pasta):pasta_(pasta){}

void Arquivo::PegarNomeDosArquivos(){
    nome_documentos.push_back(pasta_+"Tp.txt");
    nome_documentos.push_back(pasta_+"Jp.txt");
}
vector<string> Arquivo::NomesDoc(){
    return nome_documentos;
}
//******************************** class DocCoordenadas ************************

class DocCoordenadas{
    public:
    DocCoordenadas(const vector<string> nome_documentos);
    void PreencherPalavras();
    int tf(const string palavra, const string documento);
    void IndiceInvertido();
    void idf();
    
    void Hash();
    
   


    set<string> get_Palavras();
    map<string,vector<string>> get_DocPalavras();
    map<string,vector<double>> get_Hash();
    map<string,map<string,int>> get_IndiceInvertido();
    double get_idf(string palavra);

    private:
    set<string> palavras_;
    vector<string> nome_documentos_;
    map<string,vector<string>> m_DocPalavras;
    map<string, int> max_frequencia;
    map<string, double> idf_;
    map<string,vector<double>> hash_;
    map<string,map<string,int>> indiceInvertido_;
};
//************************************implementação ******************************
DocCoordenadas::DocCoordenadas(const vector<string> nome_documentos):nome_documentos_(nome_documentos){ }

    
void DocCoordenadas::PreencherPalavras(){
    string palavra;
    vector<string> vec_aux;
    unsigned x=0,linha=0,coluna=0;
    for(auto doc:nome_documentos_){
        ifstream in(doc);
        while(!in.eof()){
            in>>palavra;
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
            x=0;
            if( palavra.length()!=0){
                vec_aux.push_back(palavra);
                palavras_.insert(palavra);
            }
        }
        m_DocPalavras[doc]=vec_aux;
        vec_aux.clear();
    }
}


map<string,vector<string>> DocCoordenadas::get_DocPalavras(){
    return m_DocPalavras;
}

int DocCoordenadas::tf(const string palavra, const string documento){
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
void DocCoordenadas::IndiceInvertido(){
    int fMax=0,aux=0;
    for(auto i:palavras_){
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
map<string,map<string,int>> DocCoordenadas::get_IndiceInvertido(){
    return indiceInvertido_;
}

void DocCoordenadas::idf(){

    for(auto i:palavras_){
        idf_[i] = log(nome_documentos_.size()/indiceInvertido_[i].size());
        //cout << "log(" << nome_documentos_.size()<< "/" << indiceInvertido_[i].size() <<") = "<<idf_[i] << endl;
    }
}
double DocCoordenadas::get_idf(string palavra){
    return idf_[palavra];
}
void DocCoordenadas::Hash(){
    for(auto i:nome_documentos_){
        
    }
}







int main(){
    Arquivo arq("dia/");
    arq.PegarNomeDosArquivos();

    DocCoordenadas b(arq.NomesDoc());
    b.PreencherPalavras();
    imprimir(b.get_DocPalavras());
    cout<<endl<<endl<<endl;
    b.IndiceInvertido();
    imprimir(b.get_IndiceInvertido());
    
    b.idf();
    
   



   // b.IndiceInvertido();
    //b.Hash();
    return 0;
}