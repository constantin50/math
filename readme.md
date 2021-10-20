# Symbolic Differentiation

A symbolic differentiation program finds the derivative of a given formula with respect to a specified variable, producing a new formula as its output. 
In general, symbolic mathematics programs manipulate formulas to produce new formulas, rather than performing numeric calculations based on formulas.

The program ```symbolic_differentiation.cpp``` can read expression and differentiate it with respect to the given variable.

Example

input:
```
((2*x)*(2*y*y))
```

output:
```
((((0*x)+(2*0))*((2*y)*y))+((2*x)*((((0*y)+(2*1))*y)+((2*y)*1))))
```

i.e. 8*x*y

Besides, the program is able to evaluate an expression with given signifying.

```
exp->eval('x <- 5; y <- 3'); # get 8*5*3 = 120
```
