#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double p(double x)
{
  return -2/x;
}

double q(double x)
{
  return 2/(x*x);
}

double r(double x)
{
  return sin(log(x))/(x*x);
}

double *DiferencaFinita(double a, int N, double h, double alfa, double beta)
{
  double t;
  int i;
  double *D=calloc(N,sizeof(double));
  double *U=calloc(N,sizeof(double));
  double *L=calloc(N,sizeof(double));
  double *R=calloc(N,sizeof(double));
  double *l=calloc(N,sizeof(double));
  double *u=calloc(N,sizeof(double));
  double *z=calloc(N,sizeof(double));
  double *y=calloc(N+1,sizeof(double));

  //primeiro
  t = a+h;
  D[1] = 2 + h*h*q(t);
  U[1] = -1 + (h/2)*p(t);
  R[1] = -h*h*r(t) + (1 + h/2*p(t))*alfa;

  //meio
  for (i=2; i<N; i++) 
  {
    t += h;
    D[i] = 2 + h*h*q(t);
    U[i] = -1 + (h/2)*p(t);
    L[i] = -1 - (h/2)*p(t);
    R[i] = -h*h*r(t);
  }

  //último
  t += h;
  D[N] = 2 + h*h*q(t);
  L[N] = -1 - (h/2)*p(t);
  R[N] = -h*h*r(t) + (1 - h/2*p(t))*beta;

  //algoritmo de Crout
  l[1] = D[1];
  u[1] = U[1]/D[1];
  z[1] = R[1]/l[1];
  
  for(i=2; i<N; i++) 
  {
    l[i] = D[i] - L[i]*u[i-1];
    u[i] = U[i]/l[i];
    z[i] = (R[i] - L[i]*z[i-1])/l[i];
  }
  
  l[N] = D[N] - L[N]*u[N-1];
  z[N] = (R[N] - L[N]*z[N-1])/l[N];
  y[N] = z[N];
  y[0] = alfa;
  y[N+1] = beta;
  for (i=N-1; i>0; i--) y[i] = z[i] - u[i]*y[i+1];
  
  return y;
}

  
int main(int argc, char **argv)
{
  double a, b, alfa, beta, h, *x;
  int N,i;
  
  a=1;
  b=2;
  alfa=1;
  beta=2;
  N=9;
  h=(b-a)/(N+1);
  
  x=malloc(sizeof(double ) * (N+1));

  x=DiferencaFinita(a, N, h, alfa, beta);
  
  for (i=0; i<=N+1; i++) printf("%lf %lf\n", a+i*h, x[i]);
  return 0;
}