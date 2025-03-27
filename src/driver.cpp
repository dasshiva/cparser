#include "parser.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

int main(int argc, const char** argv) {
  if (argc != 2)
    return 1;

  Lexer lex(argv[1]);
  if (!lex.isOpen()) {
    std::cout << "Unable to open file " << argv[1] << "\n";
    return 1;
  }

  Parser parser(&lex);
  parser.Parse();
  /*
  while (1) {
    Token tk = lex.Next();
    if (tk.getType() == TT_EOF)
      break;
    std::cout << tk.toString();
    if (tk.getType() == TT_NUMBER)
      std::cout << '(' << tk.getNum() << ')';
    std::cout << '\n';
  } */
  return 0;
}
