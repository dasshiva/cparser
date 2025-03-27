#ifndef __AST_HPP__
#define __AST_HPP__

#include <string>
#include <vector>

#define STT_RETURN 0
enum Type {
  TY_VOID,
  TY_INT
};

class Expr {
public:
  Expr() { void_expr = true; }
  Expr(long literal) : literal(literal), void_expr(false) {}
private:
  bool void_expr;
  long literal;
};

// Represents the parameter to a function
class Parameter {
public:
  Parameter(std::string &name, Type type) : name(name), type(type) {}
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
public:
  ReturnStatement(Expr value, bool isRet) : value(value), returnValue(isRet),
      CompoundStatement(STT_RETURN, "return") {}
private:
  bool   returnValue;
  Expr   value;
};

// A class that represents a single function declaration
class Function {
public:
  Function(std::string &name) : name(name) {}
  void setName(std::string& name) { this->name = name; }
  void addParam(Parameter& p) { params.push_back(p); }
  void addStatement(CompoundStatement& st) { stats.push_back(st); }
  void setReturnType(Type ty) {
    returnType = ty;
    if (ty == TY_VOID) 
      hasReturn = false;
    else
      hasReturn = true;
  }

  bool canReturn() { return hasReturn; }
  Type getReturnType() { return returnType; }
  std::string getName() { return name; }

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
