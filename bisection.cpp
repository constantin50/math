#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double eps1 = 0.0000001;
const double eps2 = 0.000000001;

double f(double x) 
{
    return exp(x) + 3*x - 20;
}

double bisection(double a, double b, double eps) 
{
   int counter = 0;
   double c = a;
   while ((b-a) >= eps) 
   {
      counter += 1;
      c = (a+b)/2;
      if (f(c) == 0.0)
         break;
      else if (f(c)*f(a) < 0)
         b = c;
      else
         a = c;
   }

   cout << "given that eps = " << eps << "\nnumber of iteration: " << counter << endl; 
   return c;
}

int main()
{
    int a, b;

    cin >> a;
    cin >> b;

    cout << "x = " << setprecision(9) << bisection(a, b, eps1) << endl;

    return 0;
}