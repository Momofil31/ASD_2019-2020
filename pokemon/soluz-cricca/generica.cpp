#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
Questo algoritmo usa l'algoritmo di Tarjan per trovare "bridges", archi la cui rimozione rende disconnesso il grafo:
https://en.wikipedia.org/wiki/Bridge_(graph_theory)#Tarjan.27s_Bridge-finding_algorithm
L'algoritmo segue questi passi:
1. Leggo il grafo
2. Eseguo Tarjan per trovare i bridges, che verranno ignorati nel resto dell'algoritmo
3. Per ogni arco non-bridge a, segno a come da ignorare ed uso Tarjan sul grafo rimanente
   per trovare archi che devono comparire nel ciclo insieme ad a
4. Calcolo l'output come MCD fra i vari gruppi trovati nel punto 3
5. Assegno i pokemon stando attento a mantenere l'equilibrio
 */

ifstream in("input.txt");
ofstream out("output.txt");

struct nodo{
  vector<int> vic;
  vector<int> archi;
  int pre;
  int low;
};

struct arco{
  int f,t;
  bool bridge=false;
  int group = -1;
  arco(int ff, int tt): f(ff), t(tt) {}
};

vector<nodo> G;
vector<arco> A;

int N,E;

void leggiGrafo(){
  in>>N>>E;
  G.resize(N);
  for(int i=0;i<E;i++){
    int f,t;
    in>>f>>t;
    G[f].vic.push_back(t);
    G[t].vic.push_back(f);
    G[f].archi.push_back(i);
    G[t].archi.push_back(i);
    A.push_back(arco(f,t));
  }
}


void dfsBridges(int id, int padre, int& count, vector<int>& found){
  nodo& n=G[id];
  n.pre = count;
  n.low = count;
  count++;
  for(int i=0;i<n.vic.size();i++){
    if(!A[n.archi[i]].bridge){
      int vic = n.vic[i];
      if(G[vic].pre == -1){
        dfsBridges(vic,id,count,found);
        n.low = min(n.low,G[vic].low);
        if(G[vic].low==G[vic].pre){
          found.push_back(n.archi[i]);
        }
      }else if(vic!=padre){
        n.low = min(n.low,G[vic].low);  
      }
    }
  }
}


//Eseguo algoritmo di Tarjan per trovare bridges
void findBridges(){
  for(auto& nodo:G){
    nodo.pre = -1;
    nodo.low = -1;
  }
  int count = 1;
  vector<int> bridges;
  for(int i=0;i<N;i++){
    if(G[i].pre==-1){
      dfsBridges(i, -1, count, bridges);
    }
  }
  for(int i:bridges){
    A[i].bridge = true;
  }
}


//Dato un arco, lo rimuovo e cerco bridges nell'arco rimanente
int findGroup(arco& a,int groupId){
  a.group = groupId;
  int size = 1;
  for(auto& nodo:G){
    nodo.pre = -1;
    nodo.low = -1;
  }
  vector<int> group;
  int count = 0;
  a.bridge = true;
  dfsBridges(a.f,a.f,count,group);
  a.bridge = false;
  for(int i:group){
    A[i].group = groupId;
    size++;
  }
  return size;
}



int mcd(int a, int b){
  if(b==0)
    return a;
  else
    return mcd(b,a%b);
}

int main(){
  leggiGrafo();
  // Trovo gli archi che non possono essere in cicli
  findBridges();

  // Per ogni arco, trovo quelli che devono stare nello stesso ciclo
  vector<int> sizes;
  for(auto& a:A){
    if(!a.bridge && a.group==-1){
      sizes.push_back(findGroup(a,sizes.size()));
    }
  }
  int K;
  if(sizes.size()==0)
    K = 1;
  else{
    K = sizes[0];
    for(int i:sizes)
      K = mcd(K,i);
  }

  // dichiaro un vector di lunghezza size e inizializzato a 0
  // per mettere i pokemon
  vector<int> C(sizes.size(),0);

  out<<K<<endl;
  for(auto& a:A)
    if(a.bridge)
      out<<0<<endl;
    else{
      out<<C[a.group]%K<<endl;
      C[a.group]++;
    }
  return 0;
}
