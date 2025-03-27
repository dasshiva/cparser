#include "parser.hpp"
#include "ast.hpp"
#include "lexer.hpp"

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

int Parser::parseFunctionBody(Function& fn) {
  // fun-body := '{' compound-stmt '}'
  // The first '{' has already been consumed by parseFunction
  return 0;
}

int Parser::parseFunction() {
  // fun-signature := identifer '(' params ')' [ "->" type]
  // params := param { ',' param }
  // params := identifier ':' type
  // type   := "int"
  
  Token fname = expect(TT_IDENT, "Expected name of function");
  Function fn(fname.ident);

  expect(TT_LPAR, "Expected '(' (start of the function parameter list)");
  while (1) {
    Token id = lexer->Next();
    if (id.getType() == TT_RPAR) break;

    // If we are here, it means we are parsing the beginning of a parameter 
    expect(id, TT_IDENT, "Expected parameter name");
    expect(TT_COLON, "Expected ':' (between parameter type and name)");
    Token ty = lexer->Next();
    expect(ty, TT_INT, "Expected keyword 'int' (Type of parameter)");
    Parameter p(id.ident, TY_INT);
    fn.addParam(p);
  }

  Token maybeReturn = lexer->Next();
  if (maybeReturn.getType() == TT_RETURNS) {
    expect(TT_INT, "Expected keyword 'int' (Return type)");
    fn.setReturnType(TY_INT);
    expect(TT_LBRACE, "Expected '{' (to start function body)");
  }
  else if (maybeReturn.getType() == TT_LBRACE) { // Beginning of function body
    fn.setReturnType(TY_VOID);
  }
  else 
    Error("Expected '{' (to start function body)", &maybeReturn);

  return parseFunctionBody(fn); 
}
