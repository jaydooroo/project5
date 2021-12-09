#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "StringAutomaton.h"
#include "PeriodAutomaton.h"
#include "Q_MarkAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "CommaAutomaton.h"
#include "IDAutomaton.h"
#include "CommentAutomaton.h"
#include "UndefinedAutomaton.h"
#include "EOFAutomaton.h"
Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`

    for(unsigned int i = 0; i < automata.size(); i++) {
        delete automata.at(i);
    }

    for(unsigned int i = 0; i < tokens.size(); i++) {
        delete tokens.at(i);
    }

}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new Q_MarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new CommentAutomaton);
    automata.push_back(new CommaAutomaton());

    automata.push_back(new UndefinedAutomaton());

    automata.push_back(new EOFAutomaton());
    // TODO: Add the other needed automata here
}

void Lexer::Run(std::string& input) {


    int lineNumber = 1;

    while(input.size() > 0) {
        if (input.at(0) == ' ') {
            input.erase(0, 1);
            continue;
        }
        if (input.at(0) == '\n') {
            lineNumber++;
            input.erase(0, 1);
            continue;
        }
        if (input.at(0) == '\t') {
            input.erase(0, 1);
            continue;
        }


        int maxRead = 0;
        int maxAutomation;
        int currentRead;

        for (unsigned int i = 0; i < automata.size() - 2; i++) {

            currentRead = automata.at(i)->Start(input);
            if (currentRead > maxRead) {
                maxRead = currentRead;
                maxAutomation = i;
            } //else if (currentRead == maxRead) { //ID class 에서 신경쓰기

            /* if( schemes or Facts ..etc == automata.at(i).~~) {
             maxRead = currentRead;
             maxIndex = i;
             */
            //}
        }
        if (maxRead > 0){
            tokens.push_back(automata.at(maxAutomation)->CreateToken(input.substr(0,maxRead),lineNumber));
            lineNumber = automata.at(maxAutomation)->NewLinesRead() + lineNumber;
        }
        else {
            maxRead = 1;
            currentRead = automata.at(automata.size() - 2) ->Start(input);

            if(currentRead > maxRead) {
                maxRead = currentRead;
            }

            tokens.push_back(automata.at(automata.size() - 2)->CreateToken(input.substr(0,maxRead),lineNumber));

            lineNumber = automata.at(automata.size() - 2)->NewLinesRead() + lineNumber;
            //add undefined token
        }

         // 맞는 경우가 정말로 한번도 없는지 파악해야함.
        input.erase(0, maxRead);
    }
    tokens.push_back(automata.at(automata.size() - 1)->CreateToken(input.substr(0,0),lineNumber));

    // add end of file token
    }

    // TODO: convert this pseudo-code with the algorithm into actual C++ code
    /*

    set lineNumber to 1
    // While there are more characters to tokenize
    loop while input.size() > 0 {
        set maxRead to 0
        set maxAutomaton to the first automaton in automata

        // TODO: you need to handle whitespace inbetween tokens

        // Here is the "Parallel" part of the algorithm
        // a  Each automaton runs with the same input
        foreach automaton in auto2mat {
            inputRead = automaton.Start(input)
            if (inputRead > maxRead) {
                set maxRead to inputRead
                set maxAutomaton to automaton
            }
        }
        // Here is the "Max" part of the algorithm
        if maxRead > 0 {
            set newToken to maxAutomaton.CreateToken(...)
                increment lineNumber by maxAutomaton.NewLinesRead()
                add newToken to collection of all tokens
        }
        // No automaton accepted input
        // Create single character undefined token
        else {
            set maxRead to 1
                set newToken to a  new undefined Token
                (with first character of input)
                add newToken to collection of all tokens
        }
        // Update `input` by removing characters read to create Token
        remove maxRead characters from input
    }
    add end of file token to all tokens
    */


    int Lexer::totalToken() {
        return tokens.size();

    }


    std::string Lexer::toString() {
        std::ostringstream oss;

        for(unsigned int i = 0; i < tokens.size() ; i++){
            oss << tokens.at(i)->toString() << std::endl;
        }

        return oss.str();
    }