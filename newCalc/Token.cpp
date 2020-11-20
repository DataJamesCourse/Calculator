#include "Token.h"

namespace NewCalc {
	
	Token::Token()
	:v(0),k(TokenType::None){}

	Token::Token(TokenType t)
		: v(0), k(t) {}

	Token::Token(TokenType t, double val)
		: v(val), k(t) {}
	double Token::Value() {
		return v;
	}

	TokenType Token::Kind() {
		return k;
	}
	ostream& operator<<(ostream& os, Token& t) {
		return os;
	}
}