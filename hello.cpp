#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <functional>

class StringSwitch {
public:
  StringSwitch(std::string &t, std::function<void()> def) 
          : target(t), actionDefault(def) {}

  StringSwitch Case(const char* str, std::function<void()>& action) {
    actions[str] = action;
    return *this;
  }

  void Execute() {
    for (auto it = actions.begin();  it != actions.end(); ++it) {
      if (it->first == target) {
        it->second();
        return;
      }
    }

    actionDefault();
  }

private:
  std::string target;
  std::map<std::string, std::function<void()>> actions;
  std::function<void()> actionDefault;
  
};

enum TokenType {
  TT_NONE      = 0,  // returned if the lexer doesn't understand what a toke is
  TT_AUTO      = 1,  // "auto"
  TT_INT       = 2,  // "int"
  TT_IDENT     = 3,  // any identifier in source code
  TT_LPAR      = 4,  // '('
  TT_RPAR      = 5,  // ')'
  TT_LBRACE    = 6,  // '{'
  TT_RBRACE    = 7,  // '}'
  TT_RETURN    = 8,  // "return"
  TT_RETURNS   = 9,  // "->"
  TT_FUNCTION  = 10,  // "function"
  TT_SEMICOLON = 11, // ';'
  TT_COMMA     = 12, // ','
  TT_NUMBER    = 13, // An integer literal
  TT_COLON     = 14, // ':'
  TT_EOF       = 15, // End of file
};

class Parser;
class Token {
public:
  Token() : line(0), col(0), type(TT_NONE) {}
  Token(unsigned line, unsigned col, TokenType type) :
      line(line), col(col), type(type) {}

  void setData(std::string data) {
    this->ident = data;
  }

  void setData(long num) {
    this->num = num;
  }

  const char* toString() {
    switch (type) {
      case TT_NONE: return "none";
      case TT_AUTO: return "auto";
      case TT_INT: return "int";
      case TT_FUNCTION: return "function";
      case TT_IDENT: return ident.c_str();
      case TT_LPAR: return "(";
      case TT_RPAR: return ")";
      case TT_COMMA: return ",";
      case TT_LBRACE: return "{";
      case TT_RBRACE: return "}";
      case TT_RETURN: return "return";
      case TT_SEMICOLON: return ";";
      case TT_NUMBER: return "number";
      case TT_COLON: return ":";
      case TT_RETURNS: return "->";
      case TT_EOF: return "<EOF>";
    }
  }

  TokenType getType () {
    return type;
  }

  long getNum() {
    return num;
  }

private:
  TokenType type;
  unsigned  line;
  unsigned  col;
  std::string ident;
  long        num;

  friend class Parser;
};

class Lexer {
public:
  Lexer(const char* name) : filename(name), line(1), col(0) {
    file.open(name, std::ifstream::in);
    if (!file.is_open()) 
      valid = false;
    else
      valid = true;
  }

  bool isOpen() { // Always call isOpen() before starting the lexer
    return valid;
  }

  Token Next() {
    if (isEOF())
      return Token(line, col, TT_EOF);

    while (1) {
      int c = readChar();
      if (c == 0)
        return Token(line, col, TT_EOF);

      switch (c) {
        case '(': return Token(line, col, TT_LPAR);
	case ':': return Token(line, col, TT_COLON);
        case ')': return Token(line, col, TT_RPAR);
        case ',': return Token(line, col, TT_COMMA);
        case ';': return Token(line, col, TT_SEMICOLON);
        case '{': return Token(line, col, TT_LBRACE);
        case '}': return Token(line, col, TT_RBRACE);
	case '-': {
	  char next = Peek();
	  if (next == '>') {
	    readChar(); // consume the '>'
	    return Token(line, col, TT_RETURNS);
	  }
	  
	  Error("'-' not expected here");
	}
      }

      if (isTerminator(c))
        continue;

      if (c == '_' || std::isalpha(c)) {
        putBack(c); // putback so that lexIdentifier() can see 'c'
        return lexIdentifier();
      }

      if (std::isdigit(c)) {
        putBack(c); // putback so that lexNum can see 'c'
        return lexNum();
      }
      
    }

    return Token(line, col, TT_NONE);
  }

  ~Lexer() { // close file if this is a valid stream
    if (valid)
      file.close();
  }

private:
  std::ifstream file;
  unsigned line;
  unsigned col;
  const char* filename;
  bool valid;

  bool isEOF() {
    return file.eof();
  }

  char readChar() {
    // Only get new characters if we haven't reached EOF already
    if (isEOF())
	    return 0;
    char c = 0;
    while (1) {
      c = file.get();
      if (isEOF())
        return 0; // EOF
      else if (c == ' ' || c == '\t')
        col++;
      else if (c == '\n') {
        line++;
	col = 0;
      }
      else {
	col++;
	break;
      }
      
    }

    return c;
  }

  void putBack(char c) {
    if (!c) // do not allow EOF to be putback
      return;

    file.putback(c);
    if (c == '\n')
      line--;
    col--; // FIXME: What if col == 0? This wil cause undefined behaviour
  }

  char Peek() {
    char c = file.get();
    putBack(c);
    return (char) c;
  }

  bool isTerminator(char c) {
    return (c == '\n') || (c == '\t') || (c == ' ') ||
      (!c) || (c == ';');
  }

  // Determines if 'c' can occur in an identifier
  bool canOccurInIdent(char c) {
    return (std::isalpha(c) || c == '_' ||
        std::isdigit(c));
  }

  

  Token lexIdentifier() {
    // We are here because Next detected either '_' or an alphabet
    // identifiers follow this grammar: 
    // identifier  ::= ( letter | '_' ) { letter | digit | '_' }
    // letter    ::= upper-case | lower-case
    // lower-case  ::= 'a' | 'b' | 'c' | ... | 'x' | 'y' | 'z'
    // upper-case  ::= 'A' | 'B' | 'C' | ... | 'X' | 'Y' | 'Z'
    // digit   ::= oct-digit | '8' | '9'
    // oct-digit ::= bin-digit | '2' | '3' | '4' | '5' | '6' | '7'
    // bin-digit ::= '0' | '1'

    // The only way we know that an identifier has ended is by detecting
    // whitespace characters like space, newline, tabs or EOF or because
    // we encountered a character that can't be in an identifier

    // Once an identifier has been read, we need to compare the identifier
    // with the set of reserved keywords and if it matches, return 
    // the keyword instead of TT_IDENT

    // The exact maximum length of an identifier is not specified by the 
    // C standard, but C99 says that at least 63 characters must be supported
    // for the length of an identifier.
    // We play this safely and use 256 as the upper limit of the number of 
    // characters in an identifier. Practically, no one is using that many
    // letters in an identifier but machine generated C code might.

    std::string ident;
    bool terminated = false;
    unsigned len = 0;

    // Save where the identifier starts
    unsigned savedLine = col, savedCol = col;

    // No need to check if the first character is a letter or '_' as that 
    // was already done by Next() before calling us
    for (; len < 256; len++) {
      char c = readChar();
      
      if (isTerminator(c)) {
        putBack(c);
        terminated = true;
        break;
      }

      if (!canOccurInIdent(c)) {  // identifier has ended
        putBack(c);
        terminated = true;
        break;
      }

      ident += c;
    }

    if (!terminated) 
      Error("Identifier too long");

    Token ret;
    std::function<void()> f1 = [&ret, savedLine, savedCol] () mutable
          { ret = Token(savedLine, savedCol, TT_INT); };
    std::function<void()> f2= [&ret, savedLine, savedCol] () mutable
          { ret = Token(savedLine, savedCol, TT_FUNCTION); };
    std::function<void()> f3 = [&ret, savedLine, savedCol] () mutable 
          { ret = Token(savedLine, savedCol, TT_AUTO); };
    std::function<void()> f4 = [&ret, savedLine, savedCol] () mutable 
          { ret = Token(savedLine, savedCol, TT_RETURN); }; 
    std::function<void()> f5 = [&ret, savedLine, savedCol, ident] () mutable {
            ret = Token(savedLine, savedCol, TT_IDENT); 
            ret.setData(ident);
          }; 

    StringSwitch ss(ident, f5);
    ss.Case("int", f1);
    ss.Case("function", f2);
    ss.Case("auto", f3);
    ss.Case("return", f4);
    ss.Execute();

    return ret;
  }

  static bool isHexDigit(char c) {
    if (std::isdigit(c) || 
        (c >= 'A' && c <= 'F') ||
        (c >= 'a' && c <= 'f'))
      return true;

    return false;
  }

  static bool isOctalDigit(char c) {
    return (c >= '0' && c <= '7') ? true : false; 
  }

  static bool isBinaryDigit(char c) {
    return (c == '0' || c == '1') ? true : false;
  }

  static bool isDecimalDigit(char c) {
    return std::isdigit(c);
  }

  Token lexNum() {
    //  Grammar rules for parsing integers
    //  integer   ::= dec-integer | hex-integer | oct-integer | bin-integer
    //  bin-integer ::= ( "0b" | "0B" ) bin-digit { bin-digit }
    //  oct-integer ::= ( "0o" | "0O" ) oct-digt { oct-digit }
    //  hex-integer ::= ( "0x" | "0X" ) hex-digit { hex-digit }
    //  dec-integer ::= digit { digit }
    //  hex-digit ::= digit | 'a' | 'b' | 'c' | 'd' | 'e' | 'f'
    //  | 'A' | 'B' | 'C' | 'D' | 'E' | 'F'
    //  digit   ::= oct-digit | '8' | '9'
    //  oct-digit ::= bin-digit | '2' | '3' | '4' | '5' | '6' | '7'
    //  bin-digit ::= '0' | '1'

    // Here, we enforce some constraints on integer lengths
    // Hexadecimal = upto 16 digits
    // Decimal = upto 19 digits
    // Binary = upto 64 digits
    // Octal = upto 21 digits
    unsigned base = 10;
    bool (*validator) (char) = isDecimalDigit;
    unsigned limit = 19;
    unsigned saveCol = col, saveLine = line;

    // the first digit tells us if we are expecting some kind of base specifier
    // or not. If it is 0, expect a base specifier or the literal '0'
    char c = readChar();
    if (c == '0') {
      char maybeBase = Peek();
      if (isTerminator(maybeBase)) { // this is the literal '0'
          Token ret = Token(saveLine, saveCol, TT_NUMBER);
          ret.setData(0);
          return ret;
      }

      switch (maybeBase) {
        case 'b': case 'B' : limit = 64; base = 2; 
                             validator = isBinaryDigit; break;
        case 'o': case 'O' : limit = 21; base = 8; 
                             validator = isOctalDigit; break;
        case 'x': case 'X' : limit = 16; base = 16; 
                             validator = isHexDigit; break;
        default:
                Error("Invalid base specifier for integer literal");
      }

      readChar(); // skip the base specifier
    }
    else
      putBack(c);

    std::string number;
    bool terminated = false;
    for (unsigned i = 0; i < limit; i++) {
      char c = readChar();
      if (validator(c)) 
        number += c;
      else {
        putBack(c); // this is not ours put it back
        terminated = true;
        break;
      }
    }

    if (!terminated) 
      Error("Integer literal too large");
    
    Token ret = Token(saveLine, saveCol, TT_NUMBER);
    ret.setData(std::stol(number, nullptr, base));
    return ret;
  }

  void Error(const char* s) {
    std::cout << "In file " << filename << " " << line << ":" << col
      << " ERROR : " << s;
    std::exit(1);
  }
};

class Parser {
public:
  Parser(Lexer* lex) : lexer(lex), level(0) {}
  int Parse() {
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
      }
      else 
	Error("Unexpected token", &tk);
      
    }

    return 0;
  }

private: 
  Lexer* lexer;
  unsigned level;
  int parseFunction() {
    return 0;
  }

  void Error(const char* msg, Token* tk = nullptr) {
    std::cout << "ERROR: ";
    if (tk != nullptr) {
      std::cout << "At line " << tk->line << " column " << tk->col << '\n';;
      std::cout << "'" << tk->toString();
      std::cout << "' -> ";
    }
    std::cout << msg << "\n";
    std::exit(1);
  }
};


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
