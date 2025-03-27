#include "lexer.hpp"
#include <cstdlib>

class Parser {
public:
  Parser(Lexer* lex) : lexer(lex), level(0) {}
  int Parse(); 
private: 
  Lexer* lexer;
  unsigned level;

  int parseFunction();
  void Error(const char* msg, Token* tk = nullptr); 
};
