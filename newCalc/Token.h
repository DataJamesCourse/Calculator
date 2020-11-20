#ifndef TOKEN_H
#define TOKEN_H

#include "basic.h"


namespace NewCalc {

	enum class TokenType : short {
		Number,
		Plus,
		Minus,
		Multiply,
		Divide,
		Left_parentheses,
		Right_parentheses,
		Variable,
		None
	};

	class Token
	{
	private:
		double v;
		TokenType k;
		Token();
	public:
		Token(TokenType t);
		Token(TokenType t, double val);
		double Value();
		TokenType Kind();
		friend ostream& operator<<(std::ostream& os, const Token& t);
	};


}
#endif /* TOKEN_H */

