#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
/*
Come cicli.cpp, ma stampiamo il posizionamento.
Sia K il numero di tipi di pokemon: per ogni nodo di profondita P,
assegniamo ai suoi archi uscenti il pokemon  P%K.
Per decidere l'orientamento degli archi,
usiamo la profondita restituita dalla visita in profondita.
 */

struct nodo{
  vector<int> vic;
  int depth = -1;
};

vector<nodo> G;
int K = 0;

int mcd(int a, int b){
  if(b==0)
    return a;
  return mcd(b, a%b);
}

void dfs(int nodo, int padre){
  for(int vic:G[nodo].vic){
    if(vic!=padre){
      if(G[vic].depth==-1){
        // Se il nodo non era stato scoperto, continua la visita
        G[vic].depth = G[nodo].depth+1;
        dfs(vic,nodo);
      }else if(G[vic].depth<G[nodo].depth){
        // Se si tratta di un nodo al di sopra di me, abbiamo trovato un ciclo
        int cur_ciclo = G[nodo].depth-G[vic].depth+1;
        if(K==0)
          K=cur_ciclo;
        else
          K=mcd(K,cur_ciclo);
      }
    }
  }
}

int main(){
  ifstream in("input.txt");
  ofstream out("output.txt");
  // Lettura del grafo
  int N,E;
  in>>N>>E;
  G.resize(N);
  for(int i=0;i<E;i++){
    int f,t;
    in>>f>>t;
    G[f].vic.push_back(t);
    G[t].vic.push_back(f);
  }
  // Eseguo la dfs a partire da tutti i nodi non scoperti
  for(int i=0;i<N;i++){
    if(G[i].depth==-1){
      G[i].depth=0;
      dfs(i,-1);
    }
  }
  // Stampo la dimensione del ciclo
  out<<K<<endl;

  // disposizione
  for(int i=0;i<N;i++){
    for(int vic:G[i].vic){
      if(vic>i){
        cout << "(nodo (n.d), vic (v.d)): (" \
          << i << "(" << G[i].depth << ")" \
          << ", " \
          << vic << "(" << G[vic].depth << ")" \
          << ") - ";
        int type = 1;
        if(K!=0){
          // Stampo il tipo di pokemon in base alla profondità
          // Se è un arco dell'albero DFS, prendo la profondita del nodo
          // piu alto
          // Altrimenti del nodo piu profondo
          if(abs(G[vic].depth-G[i].depth)==1){
            type = (min(G[vic].depth,G[i].depth)) % K;
          }else{
            type = (max(G[vic].depth,G[i].depth)) % K;
          }
        }
        cout << "(" << i << ", " << vic << ") ";
        cout<<"type: " << type << endl;
        out<<type<<endl;
      }
    }
  }
  return 0;
}
