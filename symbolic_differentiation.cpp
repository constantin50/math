/*

constantin werner
20.10.2021

*/

#include <iostream>
#include <string>
#include <exception>
#include <fstream>

using namespace std;

// BEFOREHAND DECLARATION OF SOME FUNCTIONS
class Array;
class Expression;
class Token;
Array tokenize(string& str);
Expression* create_expression(Array tokens , int start, int stop);
Expression* create_expression(Array tokens);
double get_value(string str, string var, string delimiter="; ");

// DEFINITION OF CLASSES

// CLASS FOR CUSTOM EXCEPTION
class Exception : public exception
{
    string s;

public:
    explicit Exception(string ss) : s(std::move(ss)) {}
    ~Exception() noexcept override = default;

    const char *what() const noexcept override 
    {
        return s.c_str();
    }
};

enum TokenType 
{
    NUMBER,
    VARIABLE,
    ADD,
    SUB,
    MUL,
    DIV,
    L_BRACKET,
    R_BRACKET
};

struct Token 
{
    TokenType type;
    double number;
    string variable;
    string str;
};


// CLASS FOR TOKENS' STORAGE, TO BE USED IN PARSING
class Array
{
  Token *tokens;
  int size;
  int top;

  void clean()
  {
    delete[] this->tokens;
  }

	void copy(const Array& that) 
	{
		this->size = that.size; 
		this->tokens = new Token[this->size];
	}
  public:
  
  Array()
  {
    size = 100;
    tokens = new Token[size];
    top = 0;
  }

	~Array()
	{ 
	    this->clean();
	}
	Array(const Array& that) 
	{
		this->size = that.size;
		this->tokens = new Token[this->size];
		for (int i = 0; i < this->size; i++)
		{
			this->tokens[i] = that.tokens[i];
		}
	}

  void push(Token x)
  {
      // EXPAND AN ARRAY IF NECESSARY
      if (top >= (size - 1)) 
      {
          Token* new_array = new Token[size + 100];
          for (int i = 0; i < size; i++)
          {
            new_array[i] = this->tokens[i];
          }
          this->tokens = new_array;
          delete[] new_array;
      }
      else 
      {
          tokens[top] = x;
          top += 1;
      }
  }

  size_t get_size()
  {
    return top;
  }

	Token& operator[](int index) 
	{ 
		if (index >= size || index < 0)
		{
			throw out_of_range("index out of range");
		}
		return tokens[index]; 
	}

	Token operator[](int index) const 
	{ 
		if (index >= size || index < 0)
		{
			throw out_of_range("index out of range");
		}
		return tokens[index]; 
	}
};


// BASE CLASS FOR AN EXPRESSION
class Expression
{
public:
    virtual Expression *derivative(string) = 0;
    virtual void print() = 0;
    virtual void print(ofstream&) = 0;
    virtual double eval(string str) = 0;
    virtual ~Expression() {};
};


// SUBCLASS FOR A NUMBER
class Number : public Expression 
{
private:
    double number;

public:
    Number() : number(0.0) { }

    Number(const double& n)
    {
        number = n;
    }
    
    ~Number() override = default;

    Expression* derivative(string var) override 
    {
        return new Number(0.0);
    }

    double eval(string str) override 
    {
        return number;
    }

    void print() override 
    {
        cout << number;
    }

    void print(ofstream& out) override 
    {
        out << number;
    }
};


// SUBCLASS FOR A VARIABLE
class Variable : public Expression 
{
private:

    string var;

public:

    Variable(string var) : var(var) {}

    ~Variable() override {}

    double eval(string str) override 
    {
        return get_value(str, var);
    }

    void print() override 
    {
        cout << var;
    }

    void print(ofstream &ofstream) override 
    {
        ofstream << var;
    }

    Expression* derivative(string chr) override
    {
        return new Number((chr == var) ? 1. : 0.);
    }
};


// SUBCLASS FOR ADDING EXPRESSION
class Add : public Expression
{
    Expression* left;
    Expression* right;

public:
    Add(Expression *left, Expression* right) : left(left) , right(right) {}

    ~Add() override 
    {
        delete left;
        delete right;
    }

    Expression* derivative(string chr) override
    {
        return new Add(left->derivative(chr), right->derivative(chr));
    }

    double eval(string str) override 
    {
        double value = left->eval(str) + right->eval(str);
        return value;
    }

    void print() override
    {
        cout << "(";
        left->print();
        cout << "+";
        right->print();
        cout << ")";
    }

    void print(ofstream& ofstream) override 
    {
        ofstream << "(";
        left->print(ofstream);
        ofstream << "+";
        right->print(ofstream);
        ofstream << ")";
    }
};


// SUBCLASS FOR SUBSTRACTION EXPRESSION
class Sub : public Expression
{
private:
    Expression* left;
    Expression* right;

public:
    Sub(Expression* left, Expression* right) : left(left) , right(right) {}

    ~Sub() override
    {
        delete left;
        delete right;
    }

    Expression* derivative(string chr) override
    {
        return new Sub(left->derivative(chr), right->derivative(chr));
    }

    double eval(string str) override 
    {
        double value = left->eval(str) - right->eval(str);
        return value;
    }

    void print() override
    {
        cout << "(";
        left->print();
        cout << "-";
        right->print();
        cout<< ")";
    }

    void print(ofstream &output) override 
    {
        output << "(";
        left->print(output);
        output << "-";
        right->print(output);
        output << ")";
    }
};

Expression* create_expression(Array tokens) 
{
    return create_expression(tokens, 0, tokens.get_size());
}


Expression* parse_expression(string str)
{
    return create_expression(tokenize(str));
}


// SUBCLASS FOR MULTIPLICATION EXPRESSION
class Mul : public Expression
{
private:

    Expression* left;
    Expression* right;

public:
    Mul(Expression* left , Expression* right) : left(left) , right(right) {}

    ~Mul() override
    {
        delete left;
        delete right;
    }

    Expression* derivative(string chr) override
    {
        return new Add(new Mul(left->derivative(chr), right) , new Mul(left , right->derivative(chr)));
    }

    double eval(string str) override 
    {
        double value = left->eval(str) * right->eval(str);
        return value;
    }

    void print() override
    {
        cout << "(";
        left->print();
        cout << "*";
        right->print();
        cout << ")";
    }

    void print(ofstream &output) override 
    {
        output << "(";
        left->print(output);
        output << "*";
        right->print(output);
        output << ")";
    }
};


// // SUBCLASS FOR DIVISION EXPRESSION
class Div : public Expression
{
private:
    Expression* left;
    Expression* right;

public:
    Div(Expression* left , Expression* right) : left(left) , right(right) {}

    ~Div() override
    {
        delete left;
        delete right;
    }

    Expression* derivative(string chr) override
    {
        return new Div(
                new Sub(new Mul(left->derivative(chr) , right) , new Mul(left , right->derivative(chr))),
                new Mul(right, right)
                );
    }

    double eval(string str) override 
    {
        double value = left->eval(str) / right->eval(str);
        return value;
    }

    void print() override
    {
        cout << "(";
        left->print();
        cout << "/";
        right->print();
        cout << ")";
    }

    void print(ofstream &output) override 
    {
        output << "(";
        left->print(output);
        output << "/";
        right->print(output);
        output << ")";
    }
};

// SUBCLASS FOR MINUS EXPRESSION
class Minus : public Expression 
{
private:
    Expression* value;

public:
    explicit Minus(Expression* expression) : value(expression) {}

    ~Minus() override 
    {
        delete value;
    }

    Expression *derivative(string chr) override 
    {
        return new Minus(value->derivative(chr));
    }

    double eval(string str) override 
    {
        double result = -value->eval(str);
        return result;
    }

    void print() override 
    {
        cout << "-";
        value->print();
    }

    void print(ofstream &output) override 
    {
        output << "-";
        value->print(output);
    }

};


// UTILITY FUNCTION FOR PARSING
Array tokenize(string& str) 
{
    Array tokens;
    int pos = 0;
    int const length = str.length();
    while (pos < length) 
    {
        // SKIP SPACES
        while(isspace(str[pos]) && pos < str.length())
            ++pos;

        Token token;

        if (isalpha(str[pos])) 
        {
            char var = str[pos];

            if (pos + 1 == length || !isalpha(str[pos + 1])) {
                token.type = VARIABLE;
                token.variable = var;
                token.str = var;
                tokens.push(token);
                ++pos;
            }
        }

        else if (isdigit(str[pos]) || (str[pos] == '.' && pos + 1 < length && isdigit(str[pos + 1]))) 
        {
            string num;
            num += str[pos++];
            bool point_found = false;
            // IF A NUMBER IS A FRACTION
            while (isdigit(str[pos]) || str[pos] == '.') 
            {
                if (str[pos] == '.') 
                {
                    if (!point_found) 
                    {
                        point_found = true;
                    }
                    else 
                    {
                        throw Exception("too many points in number");
                    }
                }
                num += str[pos++];
            }
            token.type = NUMBER;
            token.number = stod(num);
            token.str = num;
            tokens.push(token);
        }
        else 
        {
            switch (str[pos]) 
            {
                case '+': 
                {
                    token.type = ADD;
                    token.str = "+";
                    break;
                }
                case '-': 
                {
                    token.type = SUB;
                    token.str = "-";
                    break;
                }
                case '*': 
                {
                    token.type = MUL;
                    token.str = "*";
                    break;
                }
                case '/': 
                {
                    token.type = DIV;
                    token.str = "/";
                    break;
                }
                case '(': 
                {
                    token.type = L_BRACKET;
                    token.str = "(";
                    break;
                }
                case ')': 
                {
                    token.type = R_BRACKET;
                    token.str = ")";
                    break;
                }
                default: 
                {
                    throw Exception("unexpected character");
                }
            }
            tokens.push(token);
            ++pos;
        }
    }
    return tokens;
}

// извлекает из строки означивания s в виде "x <- 11; y <- 4" значение переменной var
double get_value(string s, string var, string delimiter)
{
  if (s.find(var) == string::npos)
  {
    throw Exception("The given variable has NOT been found");
  }
  s += "; "; // add delimiter in the end for correct work of a cycle below
  size_t pos = 0;
  string ss; // current substring
  while ((pos = s.find(delimiter)) != string::npos) 
  {
      ss = s.substr(0, pos);
      if (ss.find(" <- ") != string::npos)
      {
        // check that variables match
        if (s.substr(0, s.find(" <- ")) == var)
        {
          return stod(s.substr(s.find(" <- ")+4, -1));
        }
      }
      else
      {
        break;
      }
      s.erase(0, pos + delimiter.length());
  }
  throw Exception("The given string is not correct; the string must have the form: 'var1 <- value1; var2 <- value2; ...'");
}

// look-up table for tokens' priority
inline int get_priority(Token token) 
{
    if (token.type == NUMBER || token.type == VARIABLE) return 0;
    if (token.type == L_BRACKET || token.type == R_BRACKET) return 1;
    if (token.type == ADD || token.type == SUB || token.type == MUL) return 3;
    return 2;
}

// get token with the highest priority
int get_highest_priority_token(Array tokens, int start, int stop) 
{
    int curr_priority = -1;
    int idx = 0;
    int brackets = 0;
    for (int i = start; i < stop; i++) 
    {
        int p = get_priority(tokens[i]);
        if (p > curr_priority || (p == curr_priority && p > 1)) 
        {
            curr_priority = p;
            idx = i;
        }
        if (tokens[i].type == L_BRACKET) 
        {
            brackets = 1;
            ++i;
            while (brackets > 0 && i < stop) 
            {
                if (tokens[i].type == L_BRACKET) 
                {
                    ++brackets;
                }
                if (tokens[i].type == R_BRACKET) 
                {
                    --brackets;
                }
                i++;
            }
            if (brackets > 0)
            {
                throw Exception("unbalanced brackets");
            }
            i--;
        }
    }
    return idx;
}

// поиск индекса близжайшей от индекса start закрывающийся скобочки в массиве tokens
int find_closest_bracket(Array tokens, int start, int stop) 
{
    int idx = start + 1;
    int brackets = 1;
    while (brackets && idx < stop) 
    {
        if (tokens[idx].type == L_BRACKET) 
        {
            brackets++;
        }
        if (tokens[idx].type == R_BRACKET) 
        {
            brackets--;
        }
        idx++;
    }
    if (brackets > 0) 
    {
        throw Exception("unbalanced brackets");
    }
    idx--;
    return idx;
}


// BUILD AN EXPRESSION FROM TOKENS
Expression* create_expression(Array tokens, int start, int stop)
{
    if (stop - start == 1)
    {
        Token &token = tokens[start];
        if (token.type == VARIABLE)
        {
            return new Variable(token.variable);
        }
        if (token.type == NUMBER)
        {
            return new Number(token.number);
        }
        throw Exception("unexpected single token");
    }
    
    int index = get_highest_priority_token(tokens, start, stop);
    Token &token = tokens[index];
    if (index == start) 
    {
        if (token.type == SUB) 
        {
            return new Minus(create_expression(tokens, start + 1, stop));
        }
        else if (token.type == L_BRACKET) 
        {
            int close_bracket = find_closest_bracket(tokens, index, stop);
            if (close_bracket != stop - 1) 
            {
                throw Exception("brackets are not balanced");
            }
            return create_expression(tokens, index + 1, close_bracket);
        }
        throw Exception("unexpected token with start index");
    }
    Expression* left = create_expression(tokens, start, index);
    Expression* right = create_expression(tokens, index + 1, stop);

    if (token.type == ADD) 
    {
        return new Add(left, right);
    }
    if (token.type == SUB) 
    {
        return new Sub(left, right);
    }
    if (token.type == MUL) 
    {
        return new Mul(left, right);
    }
    if (token.type == DIV) 
    {
        return new Div(left, right);
    }
    throw Exception("unexpected token");

}


Expression * read_expression(istream &input) 
{ 
    string str;
    getline(input, str);
    Expression * expression = create_expression(tokenize(str));    
    return expression;    
}


int main()
{
    ifstream fin("input.txt"); // example: ((2*x)*(3*y))
	  ofstream fout("output.txt");

    Expression * expression = read_expression(fin);
    Expression * result = expression->derivative("y");
    result->print(fout);

    return 0;
}
