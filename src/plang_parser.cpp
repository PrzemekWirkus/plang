#include "plang_parser.h"
#include <string>


// Main parser loodp
void PlangParser::parser_loop() {

    while (m_tokenizer.get_token() != Token::END) {
        
        if (parse_function()) {
            error("unable to parse function!");
        }
    }

}

// '(' ... ')'
int PlangParser::parse_function_arg_list() {
    // Always success (empty argument list)
    if (get_token() == '(') {
        if (get_token() != ')') {
           
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

            if (parse_function_arg_list()) {

                // Parse block

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

