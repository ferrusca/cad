/**
  * Calculo de PI (secuencial).
  * Se utiliza la integral de 1/(1+x²) dx [0,1] = pi/4
  *
  */

#include <stdio.h>

double f (double a) {
  return 4.0 / (1.0 + a * a);
}

int main(int argc, char** argv) {
  // n: numero de rectangulos. Se divide la gráfica en 1/n
  int n, i;
  double PI25DT = 3.141592653589793238462643;
  // h: altura de los rectángulos
  double pi, h, sum, x;
  n = 100;
  h = 1.0/(double)n;
  sum = 0.0;
  for (i = 1; i <= n; ++i)
  {
    x = h * ((double)i - 0.5);
    sum += f(x);
  }

  pi = h * sum;
  printf("PI es aproximadamente %.16f, el error cometido es %.16f\n", pi, fabs(pi - PI25DT));
}