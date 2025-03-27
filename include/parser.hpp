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
  int parseFunctionBody(Function &fn);
  [[noreturn]] void Error(const char* msg, Token* tk = nullptr);
  Token expect(TokenType expected, const char* msg) {
    Token tk = lexer->Next();
    if (tk.getType() != expected) 
      Error(msg, &tk); 
    return tk;
  }

  void expect(Token tk, TokenType expect, const char* msg) {
    if (tk.getType() != expect) 
      Error(msg, &tk); 
  }
};

#endif
