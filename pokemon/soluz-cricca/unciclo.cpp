#include <fstream>
#include <vector>
using namespace std;
/*
Usiamo una semplice visita in profondità, per trovare la
dimensione del ciclo guardiamo la differenza di profondita fra i nodi
collegati dall'arco che chiude il ciclo
 */

struct nodo{
  vector<int> vic;
  int depth = -1;
};

vector<nodo> G;
int ciclo = 0;

void dfs(int nodo, int padre){
  for(int vic:G[nodo].vic){
    if(vic!=padre){
      if(G[vic].depth==-1){
        // Se il nodo non era stato scoperto, continua la visita
        G[vic].depth = G[nodo].depth+1;
        dfs(vic,nodo);
      }else if(G[vic].depth<G[nodo].depth){
        // Se si tratta di un nodo al di sopra di me, abbiamo trovato un ciclo
        ciclo = G[nodo].depth-G[vic].depth+1;
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
  out<<ciclo<<endl;
  return 0;
}
