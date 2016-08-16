#ifndef PLANG_PARSER
#define PLANG_PARSER

#include "plang_tokenizer.h"


class PlangParser {

    // Type used for token
    typedef PlangTokenizer::Token Token;
    typedef PlangTokenizer::TokenValue TokenValue;

    // Tokenizer used by language
    PlangTokenizer m_tokenizer;

    // Error message function
    int error(const char * msg) {
        return fprintf(stderr, "error: %s\n", msg);
    }

    int error(const std::string & msg) {
        return error(msg.c_str());
    }

    // Token read from tokenizer (buffer)
    int m_token;

    // Get token from tokenizer
    // Remember token in member variable
    int get_token() {
        return m_token = m_tokenizer.get_token();
    }

    const TokenValue& get_token_value() {
        return m_tokenizer.get_token_value();
    }

    // Main parser loop
    void parser_loop();

    // Parser loop supporting functions
    // Return:  0 - success
    //         !0 - error
    //
    int parse_function();  // @ <ID> ( <ARG_LIST> ) { <BLOCK>  }
    int parse_function_arg_list();  // <ARG_LIST>

    public:

    // Parse text input
    void parse_input(const char * input) {
    
        m_tokenizer.load_input(input);

        parser_loop();
    }

};

#endif

