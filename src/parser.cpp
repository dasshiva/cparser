#include "parser.hpp"

int Parser::Parse() {
  while (1) {
    // We are here only at top-level 'program'
    // program ::= declarations | EOF
    // declaeations := fun-decl
    // fun-decl := "function" fun-signature fun-body
    Token tk = lexer->Next();
    if (tk.getType() == TT_EOF)
      break;
    else if (tk.getType() == TT_FUNCTION) {
      if (parseFunction() > 0)
        return 1;
    } else
      Error("Unexpected token", &tk);
  }

  return 0;
}

void Parser::Error(const char *msg, Token *tk) {
  std::cout << "ERROR: ";
  if (tk != nullptr) {
    std::cout << "At line " << tk->line << " column " << tk->col << '\n';
    ;
    std::cout << "'" << tk->toString();
    std::cout << "' -> ";
  }
  std::cout << msg << "\n";
  std::exit(1);
}

int Parser::parseFunction() {
  // fun-signature := identifer '(' params ')' [ "->" type]
  // params := param { ',' param }
  // params := identifier ':' type
  // type   := "int"
  // fun-body := '{' compound-stmt '}'
  return 0; 
}
