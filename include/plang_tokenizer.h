#ifndef PLANG_TOKENIZER
#define PLANG_TOKENIZER

#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cctype>

#define XXX 2

class PlangTokenizer {

    // Input buffer
    std::vector<char> m_input;

    // Current possition in input buffer
    std::size_t m_input_pos;

    // Currently read element from input
    int m_ch;

    public:

    // Token values
    struct TokenValue {
        std::string s;
        int i;
        float f;
    } m_token_value;

    // Token types outputed by tokenizer
    struct Token {
        enum {
            END = -1,   // EOF!
            ID = -2,
            INT = -3,
            FLT = -4,
            STR = -5,
        };
    };  // Last read token

    int m_token;    // Last token read

    // Load all characters from input
    void load_input(const char *input, int size) {
        m_input = std::vector<char>(input, input + size);
        m_input_pos = 0;
    }

    // Load from string input
    void load_input(const char *input) {
        m_input = std::vector<char>(input, input + std::strlen(input));
        m_input_pos = 0;
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
        return m_ch = get_next_consume();
    }

    // Sneak-peak next token
    int get_next_preview() {
        if (m_input_pos == m_input.size())
            return Token::END;
        return m_input[m_input_pos];
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
            m_token_value.s = m_ch;

            while (std::isalpha(get_next_preview())) {
                m_token_value.s += get_next();
            }
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
        return m_token = get_token_val();
    }

    const TokenValue& get_token_value() {
        return m_token_value;
    }

};

#endif

