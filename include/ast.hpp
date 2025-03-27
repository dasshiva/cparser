#ifndef __AST_HPP__
#define __AST_HPP__

#include <vector>

enum Type {
  TY_VOID,
  TY_INT
};

class Expr {
  long literal;
};

class Parameter {
private:
  std::string name; // Name of the parameter
  Type type;        // The parameter's type
};

// Base class to represent all compound statements
class CompoundStatement {
public:
  CompoundStatement(unsigned type, const char* desc) :
	  type(type), desc(desc) {}
  const char* toString() { return desc; }
protected:
  unsigned type;
  const char* desc;
}; 

// Represents a "return" statement
class ReturnStatement : protected CompoundStatement {
private:
  bool   returnValue;
  Expr   value;
};

// A class that represents a single function declaration
class Function {
private:
  std::string name; // The function's name
  bool hasReturn;   // does this function return a value?
  Type returnType;  // Return Type of the function
  std::vector<Parameter> params; // represents the functions parameters
  std::vector<CompoundStatement> stats; // statements in the function body
};

// A class that represents the program as a whole
// It is actually used to represent the 'top-level' in the grammar
// Since the only things that can appear at the top level are
// function declarations now, Program is just a vector of them now
class Program {
public:
  Program() {}
  void addFunction(Function& Fn) { funcs.push_back(Fn); }
private:
  std::vector<Function> funcs;
};

#endif
