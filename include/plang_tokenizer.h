#ifndef PLANG_TOKENIZER
#define PLANG_TOKENIZER

#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <algorithm>


class PlangTokenizer {

    // Input buffer
    std::string m_input;

    // Current possition in input buffer
    std::size_t m_input_pos;

    // Currently read element from input
    int m_ch;

    // Counterss
    int m_input_line;   // Which line it is in the source code (0, 1,2,3...)
    int m_input_column; // Which column it is in the source code (0, 1,2,3...)

    // Simple input + counters initializer
    void input_init() {
        m_input.clear();
        m_input_pos = 0;

        // Counters
        m_input_line = 0;
        m_input_column = 0;
    }

    public:

    // Return counter with current line
    int get_line() {
        return m_input_line;
    }

    // Return counter with current column
    int get_column() {
        return m_input_column;
    }

    // Returns nth line of input
    std::string get_line_str(const int line) {
    
        std::string::iterator b = m_input.begin();
        std::string::iterator e = m_input.end();

        for (int i = 0 ; i < line ; ++i) {
            b = std::find(b, e, '\n');
        }

        return std::string(b, std::find(b, e, '\n'));
    }

    // Token values
    struct TokenValue {
        std::string s;
        int i;
        float f;
    } m_token_value;

    // Token types outputed by tokenizer
    struct Token {
        enum {
            // Language values
            END = -1,   // EOF!
            ID  = -2,
            INT = -3,
            FLT = -4,
            STR = -5,

            // Language keywords
            RETURN = -100,
            IF     = -200,
            ELSE   = -201,
            AS     = -202,
        };
    };  // Last read token

    // Mapping between keyword and token
    std::map<std::string, int> m_keyword_token_map = {
        {"return",  Token::RETURN},
        {"if",      Token::IF},
        {"else",    Token::ELSE},
        {"as",      Token::AS},
    };

    // Load all characters from input
    void load_input(const char *input, int size) {
        input_init();
        m_input = std::string(input, input + size);
    }

    // Load from string input
    void load_input(const char *input) {
        input_init();
        m_input = std::string(input);
    }

    // Return next element of input buffer
    int get_next_consume() {
        if (m_input_pos == m_input.size())
            return Token::END;
        return m_input[m_input_pos++];
    }

    // Get next element from the input and store it
    // in m_ch temporary value buffer to use after call
    int get_next() {
        m_ch = get_next_consume();

        // Collect some counter statistics
        m_input_column++;
        if (m_ch == '\n') {
            m_input_column = 0;
            m_input_line++;
        }
        return m_ch;
    }

    // Sneak-peak next token
    int get_next_preview() {
        if (m_input_pos == m_input.size())
            return Token::END;
        return m_input[m_input_pos];
    }

    // like isalpha checks if c is in set of allowed
    // identifier charset
    int isidchar(int c) {
        return std::isalpha(c) || std::isdigit(c) || c == '_';
    }

    // Parse input and get next token
    int get_token_val() {
        while (std::isspace(get_next())) {
            // Skipping all whitespaces
        }

        if (m_ch == Token::END)
            return Token::END;

        if (std::isalpha(m_ch)) {
            // ID: alphanumeric
            // KEYWORD: alphanumeric
            m_token_value.s = m_ch;

            while (isidchar(get_next_preview())) {
                m_token_value.s += get_next();
            }

            // If identifier is a keyword return keyword token
            if (m_keyword_token_map.find(m_token_value.s) != m_keyword_token_map.end()) {
                return m_keyword_token_map.at(m_token_value.s);
            }

            // Generic identifier
            return Token::ID;
        } else if (std::isdigit(m_ch)) {
            // INT: plain integer
            
            m_token_value.s = m_ch;
            
            while (std::isdigit(get_next_preview())) {
                m_token_value.s += get_next();
            }

            m_token_value.i = std::atoi(m_token_value.s.c_str());
            return Token::INT;
        }

        // Return read character
        m_token_value.s = m_ch;
        return m_ch;
    }

    // Get next token and saves int vaue in the buffer
    int get_token() {
        return get_token_val();
    }

    const TokenValue& get_token_value() {
        return m_token_value;
    }

};

#endif

