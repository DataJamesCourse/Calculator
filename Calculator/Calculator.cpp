// Calculator.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

/*
THE RULE OF ARIMETHRIC CALCULATION

1. EXPRESSION := TERM | TERM + EXPRESSION
   TERM := FACTOR | FACTOR * TERM
   FACTOR := NUMBER | (EXPRESSION)



   */

enum class token_type {
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    RIGHT_PARENTHESES,
    LEFT_PARENTHESES,
    NONE
};



class token {
public:
    int value;
    token_type kind;
    token()
        :value(0), kind(token_type::NONE) {}

    token(token_type k)
        :value(0), kind(k) {}
    token(int v, token_type k)
        :value(v), kind(k) {}
    int Value() {
        return value;
    }
    token_type Kind() {
        return kind;
    }
    friend ostream& operator<<(ostream& os, const token& t);
};

ostream& operator<<(ostream& os, const token& t) {
    string k;
    switch (t.kind) {
    case token_type::DIVIDE :
        k = "/";
        break;
    case token_type::LEFT_PARENTHESES :
        k = "(";
        break;
    case token_type::MINUS:
        k = "-";
        break;
    case token_type::MULTIPLY:
        k = "*";
        break;
    case token_type::NONE:
        k = "nil";
        break;
    case token_type::NUMBER:
        k = "number";
        break;
    case token_type::PLUS:
        k = "+";
        break;
    case token_type::RIGHT_PARENTHESES:
        k = ")";
        break;
   }
    os << "KIND : " << k << " VALUE : " << t.value ;
    return os;
}

class tokenizer {
private:
    int parentheses;
    vector<token> tokens;
    istringstream is;
    vector<token>::iterator it;
    tokenizer()
        :tokens(), is(),parentheses(0)
    {
    }
public:
    tokenizer(string v)
        :tokens(), is(v + ";"),parentheses(0) 
    {
        //Why  the initializer adds a semicolon?
        //We need a one more character to parse an expression 
        //because the last character of the expression is discarded from while (isget()){}
        // ,which may cause the routine ignores the th last number token.

    }
    void run() {
        char c;
        while (is.get(c)) {

            if (isdigit(c)) {

                int value = c - '0';
                while (is.get(c)) {
                    if (isdigit(c)) {

                        value = value * 10;
                        value = value + c - '0';
                    }
                    else {

                        is.putback(c);
                        token vTok(value, token_type::NUMBER);
                        tokens.push_back(vTok);
                        break;
                    }
                }
            }
            else {

                token Tok;

                switch (c) {
                case '+':
                    Tok.kind = token_type::PLUS;
                    tokens.push_back(Tok);
                    break;
                case '*':
                    Tok.kind = token_type::MULTIPLY;
                    tokens.push_back(Tok);
                    break;
                case '/':
                    Tok.kind = token_type::DIVIDE;
                    tokens.push_back(Tok);
                    break;
                case '-':
                    Tok.kind = token_type::MINUS;
                    tokens.push_back(Tok);
                    break;
                case '(':
                    Tok.kind = token_type::LEFT_PARENTHESES;
                    tokens.push_back(Tok);
                    break;
                case ')':
                    Tok.kind = token_type::RIGHT_PARENTHESES;
                    tokens.push_back(Tok);
                    break;


                }

            }

        }
        Iterator_reset();
    }
    void print() {
        for (const token& element : tokens)
        {
            cout << element << "\n";
        }
    }
    void Iterator_reset() {
        it = tokens.begin();
    }
    token getToken() {
        token t = *it;
        if (it != tokens.end()) {
            it++;
       }
        return  t;

    }

    bool getToken(token& t) {
        if (it == tokens.end())
            return false;
        t = *it;
        it++;
        return true;
    }

    void backToken() {
        it--;
    }

    int expr() {
        int val = term();

        return val;
    }

    int term() {
        int val = prim();


    }

    int prim() {
        token t;
        getToken(t);
        switch (t.kind) {
        case token_type::NUMBER :
        {int val = t.value;
        return val; }
        case token_type::LEFT_PARENTHESES:
         {int val = expr();
         getToken(t);
         if (t.kind != token_type::RIGHT_PARENTHESES) {

         }
         return val;
         }
        }
    }
    void debug() {
        Iterator_reset();
        token t;
        while (getToken(t)) {

        }
      

    }
};

int main()
{
    string expression = "(54*32-12)+32";
    tokenizer calc(expression);
    calc.run();
    cout <<"\n"+ expression + "\n";
    calc.print();
  
  //  calc.debug();
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
