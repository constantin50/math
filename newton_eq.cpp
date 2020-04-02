#include<bits/stdc++.h> 

using namespace std; 

const double eps1 = 0.0000001;
const double eps2 = 0.000000001;
  
double f(double x) 
{ 
    return -2*x + x*x*x;
} 
  
double df(double x) 
{ 
    return 3*x*x - 2*x; 
} 
  
// ftion to find the root 
double newton(double x, double eps) 
{ 
    int counter = 0;
    double h = f(x) / df(x); 
    while (abs(h) >= eps) 
    { 
        counter += 1;
        h = f(x)/df(x); 
   
        // x(i+1) = x(i) - f(x) / f'(x)   
        x = x - h; 
    } 
    cout << "given that eps = " << eps << "\nnumber of iteration: " << counter << endl; 
    return x;
} 
  

int main() 
{ 
    double x0 = 2; // Initial values assumed 
    double x = newton(x0, eps1); 
    cout << setprecision(9) << x;
    return 0; 
} 