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
    void error_begin() {
        const int line = m_tokenizer.get_line();
        const int column = m_tokenizer.get_column();
        fprintf(stderr, "error in [%d, %d]: ", 
                line,
                column);
    }

    void error_description() {
        const int line = m_tokenizer.get_line();
        const int column = m_tokenizer.get_column();
        fprintf(stderr, "\t%s\n", 
                m_tokenizer.get_line_str(line).c_str());
        
        fprintf(stderr, "\t");
        for (int i = 0 ; i < column ; ++i) {
            fprintf(stderr, " ");
        }
        fprintf(stderr, "^\n");
    }
    
    int error(const std::string & msg) {
        error_begin();
        fprintf(stderr, "%s\n", msg.c_str());
        error_description();
        return m_token;
    }

    int error(const std::string & prefix, const std::string & msg) {
        error_begin();
        fprintf(stderr, "error: %s: %s\n", 
                prefix.c_str(), 
                msg.c_str());
        error_description();
        return m_token;
    }

    // Token type and value read from tokenizer (buffer)
    int m_token;
    TokenValue m_token_value;

    // Get token from tokenizer
    // Remember token in member variable
    int get_token() {
        m_token = m_tokenizer.get_token();
        m_token_value = m_tokenizer.get_token_value();
        return m_token;
    }

    // Get token payload (int, float, string etc.)
    const TokenValue& get_token_value() {
        return m_token_value;
    }

    // Main parser loop
    void parser_loop();

    public:

    // Parser loop supporting functions
    // Return:  0 - success
    //         !0 - error
    //
    int parse_function(); // @ <ID> ( <ARG_LIST> ) { <BLOCK>  }
    int parse_function_arg_list();  // <ARG_LIST>
    int parse_block();              // '{' <stmts> '}'
    int parse_stmt_if();            // IF () ELSE {}
    int parse_stmt_if_condition();  // ( expression )

    // Load input to tokenizer
    void load_input(const char * input) {
       m_tokenizer.load_input(input);
    }

    // Parse text input
    void parse_input(const char * input) {
    
        load_input(input);

        parser_loop();
    }

};

#endif

