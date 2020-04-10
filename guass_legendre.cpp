/*
Gauss–Legendre quadrature is a form of Gaussian quadrature 
for approximating the definite integral of a function.

The given implementation supports 2, 3 and 5 nodes. 
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x) {
    return sqrt(1-x*x*x);
}

double GaussLegendre(double a, double b, int n)
{
   double result = 0;
   vector<double> w, x;
   switch(n)
   {
      case 2: 
      {
         w.resize(2);
         w = {1,1};
         x = {0.57735, -0.57735};
         break;
      }
      case 3:
      {
         w.resize(3);
         w = {0.888889,0.555556,0.555556};
         x = {0, 0.774597, -0.774597};
         break;
      }
      case 5:
      {
         w.resize(5);
         w = {0.568888, 0.478629,0.478629,0.236927,0.236927};
         x = {0, 0.53846,-0.53846,0.90618,-0.90618};
         break;
      }
   }

   for (int i=0;i<n;i++)
   {
      result += w[i]*f(x[i]);
   }


   return result;
}

int main()
{
   int n; 
   double a;
   double b; 

   cout << "Enter the left and right border [a,b]: ";
   cin >> a >> b;

   cout << "2 nodes: " << setprecision(10) << GaussLegendre(a,b,2) << endl; 
   cout << "3 nodes: " << setprecision(10) << GaussLegendre(a,b,3) << endl;
   cout << "5 nodes: " << setprecision(10) << GaussLegendre(a,b,5) << endl;



   return 0;
}
