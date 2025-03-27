#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#include "utility.hpp"
#include <cstdlib>
#include <fstream>
#include <string>
#include <cctype>
#include <iostream>

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

  const char* toString(); 

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

  Token Next();

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

  char readChar();   
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

  Token lexIdentifier(); 
  
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

  Token lexNum();

  void Error(const char* s) {
    std::cout << "In file " << filename << " " << line << ":" << col
      << " ERROR : " << s;
    std::exit(1);
  }
};

#endif
