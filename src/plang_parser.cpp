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

        } else {
            return error("missing ')' in argument list");
        }
    } else {
        return error("missing '(' from function argument list");
    }
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
                } else {
                    return error("missing opening block '{'");
                }

            } else {
                return error("error parsing argument list");
            }
     
        } else {
            return error("expected function name after '@'");
        }
    } else {
        return error("can't find function '@' prefix!");
    }

    // Success
    return 0;
}

// '{' <statements> '}'
int PlangParser::parse_block() {
   
    // If next token is closing block we assume
    // this is an empty block
    get_token();    // Load m_token with token type
    
    if (m_token == '}') {
        // Immidiate end of block
        return 0;
    } else if (m_token == Token::IF) {
        // IF statement
        return parse_stmt_if();
    } else {
        error("unrecognized expression");
    }

    return 0;
}


// Standard IF statements
// IF ()
// IF () ELSE <BLOCK>
// With extra AS 
// IF () AS ID <BLOCK>
int PlangParser::parse_stmt_if() {
    // Already loaded IF from tokenizer
    
    if (get_token() == '(') {
   
        if (get_token() == Token::ID) {
        
            if (get_token() == ')') {

                // Check what is next token
                get_token();

                if (m_token == '{') {
                    // IF () { <BLOCK>  }
                    return parse_block();
                } else if (m_token == Token::AS) {
                    
                    if (get_token() == Token::ID) {
                        // IF () AS id
                        std::string id = get_token_value().s;

                        if (get_token() == '{') {
                            return parse_block();
                        } else {
                            return error("missing block in IF AS statement");
                        }

                    } else {
                        return error("missing identifier after keyword 'as' in IF AS statement");
                    }
                }

            } else {
                return error ("missing if statement closing expression ')'");
            }

        } else {
            return error("if statement expression missing");
        }

    } else {
        return error("missing opening if statement expression '('");
    }
    
    return 0;    
}
