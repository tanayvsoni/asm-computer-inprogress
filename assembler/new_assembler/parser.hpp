#ifndef PARSE_HPP
#define PARSE_HPP

#include "main.hpp"
#include "lexer.hpp"

class Parse {
private:
    std::vector<ParsedInstruction>& m_parsedList;
    Lexer m_lexer;

public:
    Parse(Lexer lexer);

};

#endif
