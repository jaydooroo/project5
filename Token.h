#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COLON,
    COLON_DASH,
    STRING,
    UNDEFINED,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    COMMA,
    COMMENT,
    _EOF
};

class Token
{
private:
    TokenType type;
    std::string description;
    int line;

public:
    Token(TokenType type, std::string description, int line);
    std::string toString();
    std::string dayToString (TokenType token);
    TokenType getTokenType();
    std::string getDescription ();
    int getLine ();
    // TODO: add other needed methods
};

#endif // TOKEN_H

