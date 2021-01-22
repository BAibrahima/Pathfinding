
#include <Rcpp.h>
using namespace Rcpp;


// [[Rcpp::export]]

void bellman_ford(NumericMatrix edges,int vertex_source)
{
  int n;
  n=edges.ncol();
  NumericVector dis(n);

  for (int i=0; i<n; i++){
    dis[i]= INT_MAX;
  }


  /* Initialisation des distances Ã  l'infini */
  for(int k=0;k<n;k++)
  {
    dis[k]=INT_MAX;

  }
  dis[vertex_source]=0;

  /* relaxation de l'algorithme en rÃ©pÃ©tant l'actualisation des distances n-1 fois */
  for(int k=0;k<n-1;k++){

    for(int i=0;i<n;i++)
    {
      for(int j=0;j<n;j++)
      {
        if(edges(i,j) !=0 && dis[i] != INT_MAX && dis[i]+edges(i,j) < dis[j] )
        {
          dis[j]=dis[i]+edges(i,j);
        }
      }
    }
  }



  /* vÃ©rification de l'existance d'un cycle nÃ©gatif */
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      if(edges(i,j) !=0 && dis[i]+edges(i,j) < dis[j])
      {
        Rcout<<"\n\nle graphe contient un cycle de poids nÃ©gatif, l'algo de Bellman n'est pas adaptÃ© Ã  votre problÃ¨me!!\n";
        return;
      }
    }
  }
  Rcout<<"\nVertex"<<"  Distance from source";
  for(int i=0;i<n;i++)
  {
    Rcout<<"\n"<<i<<"\t"<<dis[i];
  }

}

