#include "plang_parser.h"
#include <string>


// Main parser lood
// <program> ...
void PlangParser::parser_loop() {
    // Parser loop, top level program is parsed here
    while (get_token() != Token::END) {
        if (parse_function() == 0) {
            // Function parsed correctly
        }
        else {
            error("unable to parse function!");
        }
    }
}

// '(' ... ')'
int PlangParser::parse_function_arg_list() {
    // Always success (empty argument list)
    if (get_token() == '(') {

        if (get_token() == ')') {

            // Read empty argument list 
            return 0;

        } else return error("missing ')' in argument list");

    } else return error("missing '(' from function argument list");

    return 0;
}

// @ <ID> ( <ARG_LIST> ) { <BLOCK>  }
int PlangParser::parse_function() {

    if (get_token() == '@') {

        if (get_token() == Token::ID) {

            // Function name
            std::string name = get_token_value().s;

            if (parse_function_arg_list() == 0) {

                if (get_token() == '{') {

                    // Parse whole block with code
                    return parse_block();

                } else return error("missing opening block '{'");

            } else return error("error parsing argument list");

        } else return error("expected function name after '@'");

    } else return error("can't find function '@' prefix!");

    // Success
    return 0;
}

// '{' <statements> '}'
int PlangParser::parse_block() {

    // If next token is closing block we assume
    // this is an empty block
    //
    // m_token - should contain opening block
    get_token();    // Load m_token

    while (m_token != '}') {

        if (m_token == Token::IF) {
            // IF statement
            return parse_stmt_if();
        } else return error("unrecognized expression");

    }

    // m_token == '}' end of block
    return 0;
}


int PlangParser::parse_stmt_if_condition() {

    // IF (val) 
    //    ^^^^^
    // IF (val) as id
    //    ^^^^^^^^^^^
    // Result: in m_token next token after condition

    const char * if_msg = "in if stmt condition";
    
    if (get_token() == '(') {
        if (get_token() == Token::ID) {
            if (get_token() == ')') {
                if (get_token() == Token::AS) {
                    if (get_token() == Token::ID) {
                        // IF () AS id
                        std::string id = get_token_value().s;

                        // Load next token to m_token
                        get_token();

                    } else return error(if_msg, "missing identifier after keyword 'as'");
                } else return 0;    // m_token contains next token
            } else return error (if_msg, "missing closing ')'");
        } else return error(if_msg, "condition missing");
    } else return error(if_msg, "missing opening '('");
    
    return 0;
}

// Standard IF statements
// [done] IF ()
// IF () ELSE <BLOCK>
// With extra AS 
// [done] IF () AS ID <BLOCK>
int PlangParser::parse_stmt_if() {
    // Must return in m_token next token after correctly read IF statment
    // Already loaded IF from tokenize

    const char * if_msg = "in if stmt";
    
    if (parse_stmt_if_condition() == 0) {
        // m_token holds token after IF condition

        if (m_token == '{') {
            if (parse_block() == 0) {
                if (get_token() == Token::ELSE) {
                    if (get_token() == '{') {
                        return parse_block();
                    } else error(if_msg, "missing block opening '{' after else");
                } else return 0; // No ELSE continues
            }

        } else return error(if_msg, "missing block opening '{'");
    
    }

    return 0;    
}

// Variable assignment
// ID = ID ';'
//    = INT ';'

int PlangParser::parse_assignment() {
    // TODO
    return 0;
}

