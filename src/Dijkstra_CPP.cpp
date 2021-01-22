#include <Rcpp.h>
// [[Rcpp::plugins("cpp11")]]
using namespace Rcpp;
using namespace std;


// [[Rcpp::export]]

int distMin(NumericVector distance ,LogicalVector visited, int n){

  int minVertex=-1;
  for (int i=0 ;i< n; i++){
    if (!visited[i] && (minVertex==-1 || distance[i]< distance[minVertex])){
      minVertex = i;
    }

  }
  return minVertex;
}



// Function to print shortest
// path from source to j
// using parent array
// [[Rcpp::export]]
void printPath(NumericVector parent, int j)
{

  // Base Case : If j is source
  if (parent[j] == - 1)
    return;

  printPath(parent, parent[j]);

  Rcout<< j;
}

// A utility function to print
// the constructed distance
// array
// [[Rcpp::export]]
void printSolution(NumericVector dist, int n,NumericVector parent)
{
  int src = 0;
  Rcout<<"V  | Dist | Path";
  for (int i = 1; i < n; i++)
  {
    Rcout<<endl<<src<<"->"<<i<<"| "<<dist[i]<<" | "<<src;
    printPath(parent, i);
  }
}



// [[Rcpp::export]]

void dijkstra_cpp(NumericMatrix edges){
  int n;
  n=edges.ncol();
  NumericVector distance(n);
  NumericVector parent(n);
  LogicalVector visited(n);

  for (int i=0; i<n; i++){
    parent[0]=-1;
    distance[i]= INT_MAX;
    visited[i]= false;
  }
  distance[0]=0;

  for (int i=0;i<n-1;i++){

    int minVertex=distMin(distance,visited,n);

    visited[minVertex]=true;

    for (int j=0;j<n;j++){

      if(edges(minVertex,j) !=0 && !visited[j]){
        int dist = distance[minVertex] + edges(minVertex,j);
        if (dist< distance[j]){
          parent[j]=minVertex;
          distance[j] = dist;
        }
      }
    }

  }


  Rcout<<endl<<"les chemins les plus courts partant du sommet d'origine "<<endl;
  printSolution(distance, n, parent);


}
