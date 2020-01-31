#pragma once
#include <string>
#include <memory>
#include <fstream>
#include <vector>

#include "tree.h"
#include "token.h"

namespace FC { namespace FE {

class CodeParser
{
private:
    std::fstream fs;
    std::vector<Token *> tokenList;
    std::vector<Token *> parseStack;

    struct parsingTableEntry {
        enum Action {
            SHIFT,
            GOTO,
            REDUCE,
            ACCEPT
        } action;
        int num;

        parsingTableEntry(Action action) : action(action) {}
        parsingTableEntry(Action action, int num) : action(action), num(num) {}
    };

public:
    CodeParser(const std::string &path, std::shared_ptr<IR::Tree> tree);
    ~CodeParser();
    void scan();
    void printTokenList();
    void parse();
    parsingTableEntry lookupParsingTable(int cntState, Token::Kind tokenKind);
};
}}