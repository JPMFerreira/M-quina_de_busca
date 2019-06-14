#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include <map>
#include <cmath>
#include <dirent.h>

using namespace std;

//******************************** class MaquinaDeBusca ************************

class MaquinaDeBusca{
    public:
    void LerDiretorios();
    void PreencherPalavras();
    string Tratar(string palavra);
    int tf(const string palavra, const string documento);
    void IndiceInvertido();
    void idf();
    void Coordenadas();
    void Buscador();
    double Similaridade(string documento, string palavra);
    void Ranking(map<double,vector<string>> SimilaridadeDocumentos);

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

void MaquinaDeBusca:: LerDiretorios(){
DIR *dir;
 struct dirent *lsdir;
 auto caminho="Arquivos/20news-bydate-test/alt.atheism";
 string aux="Arquivos/20news-bydate-test/alt.atheism";
 string aux2;
 dir = opendir(caminho);
 int count=0;
 //print all the files and directories within directory */
 while ( ( lsdir = readdir(dir) ) != NULL )
 {  
     if(count >=2){
         aux2 = aux+'/'+lsdir->d_name;
         nome_documentos_.push_back(aux2);
     }
     count++;
     if(count == 100)
        break;
 }
    //nome_documentos_.push_back("Arquivos/20news-bydate-test/alt.atheism/53068");
    closedir(dir);

}

string MaquinaDeBusca::Tratar(string palavra){
    unsigned x =0;
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

int MaquinaDeBusca::tf(const string palavra, const string documento){
    int f=0;
    vector<string> i= m_DocPalavras[documento];
        //i.second é o vetor de palavras contidas num documento
    for(unsigned j =0; j<i.size();j++){
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

void MaquinaDeBusca::idf(){
    double aux;
    for(auto i:palavras_){
        aux = nome_documentos_.size();
        idf_[i] = log(aux/indiceInvertido_[i].size());
    }
}

void MaquinaDeBusca::Coordenadas(){
    int x =1;
    for(auto i:nome_documentos_){
        for(auto j:palavras_){
            coord_[i][j]= idf_[j] * tf(j,i)/max_frequencia[j];
        }
        x++;
    }
}

string retirarDiretorio(string nomeDoc){
    int a = nomeDoc.size();
    for(;a>=0;a--){
        if(nomeDoc[a]=='/'){
            nomeDoc.erase(0,a+1);
            break;
        }
    }
    return nomeDoc;
}

void MaquinaDeBusca::Ranking(map<double,vector<string>> SimilaridadeDocumentos){
    system("cls");
    int contador=1;
    cout << "                                    RANKING"<< endl;
    for(auto i=SimilaridadeDocumentos.rbegin();i!=SimilaridadeDocumentos.rend();++i){
        cout <<"       " << contador << "o  ";
        for(auto j:i->second){
            cout  << retirarDiretorio(j) << "  ";
        }
        contador++;
        cout << endl;
        if(contador>20)
            break;
    }
}

void MaquinaDeBusca::Buscador(){
    string busca, aux;
    vector<string> palavrasDaBusca;
    map<string,int> PalavraFreq;
    map<string, double> CoordenadasDaBusca;
    map<double,vector<string>> SimilaridadeDocumentos;
    cout << "\n\n\n                                    BUSCADOR\n\n\n"<< endl << "Pesquisar:    ";
    getline(cin,busca);

    // separar por palavra a string de busca
    for(unsigned i=0;i<busca.size();i++){
        if(busca[i]!=' ')
            aux.push_back(busca[i]);
        if(busca[i]==' '|| i == busca.size()-1){
            aux = Tratar(aux);
            palavrasDaBusca.push_back(aux);
            aux.clear();
        }
    }
    //preenchendo PalavraFrequencia
    for(unsigned j=0;j<palavrasDaBusca.size();j++){
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
        w++;
    }
    map<string,double> sim_;
    for(auto p:PalavraFreq){
        for( auto k:indiceInvertido_[p.first]){
            sim_[k.first] += CoordenadasDaBusca[p.first] * coord_[k.first][p.first];            
        }
    }
    for(auto l:nome_documentos_){
            SimilaridadeDocumentos[sim_[l]].push_back(l);
    }
    Ranking(SimilaridadeDocumentos);
}

int main(){
    MaquinaDeBusca b;
    b.LerDiretorios();
    b.PreencherPalavras();
    b.IndiceInvertido();
    b.idf();
    b.Coordenadas();
    b.Buscador();
    return 0;
}