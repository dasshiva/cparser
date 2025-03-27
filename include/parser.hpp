#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "lexer.hpp"
#include "ast.hpp"
#include <cstdlib>

class Parser {
public:
  Parser(Lexer* lex) : lexer(lex), level(0) {}
  int Parse(); 
private: 
  Lexer* lexer;
  unsigned level;
  Program root;

  int parseFunction();
  void Error(const char* msg, Token* tk = nullptr); 
};

#endif
