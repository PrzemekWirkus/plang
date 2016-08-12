#ifndef PLANG_TOKENUZER
#define PLANG_TOKENUZER

#include <vector>
#include <string>
#include <cctype>

template <class T>
class PlangTokenizer {

    // Input buffer
    std::vector<T> m_input;

    // Current possition in input buffer
    int m_input_pos;

    // Currently read element from input
    int m_ch;

    public:

    // Token values
    union {
        std::string s;
        int i;
        float f;
    } m_token_value;

    // Token types outputed by tokenizer
    struct Token {
        enum {
            EOF = -1,
            STR = -2,
            INT = -3,
            FLT = -4,
        };
    };

    // Load all characters from input
    void load_input(const T *input, int size) {
        m_input = std::vector<T>(input, input + size);
        m_input_pos = 0;
    }

    // Return next element of input buffer
    int get_next_ch() {
        if (m_input_pos == m_input.size())
            return Token::EOF;
        return m_input[m_input_pos++];
    }

    int get_next() {
        return m_ch = get_next_ch();
    }

    // Parse input and get next token
    int get_token() {
        while (std::isspace(get_next())) {
            // Skipping all whitespaces
        }

        if (m_ch == Token::EOF)
            return Token::EOF;

        if (std::isalpha(m_ch)) {
            // STRING: alphanumeric
            m_token_value.s = (char)m_ch;

            while (std::isalpha(get_next())) {
                m_token_value.s += (char)m_ch;
            }
            return Token::STR;
        } else if (std::isdigit(m_ch)) {
            // INT: plain integer
            
            m_token_value.s = (char)m_ch;
            
            while (std::isdigit(get_next())) {
                m_token_value.s += (char)m_ch;
            }

            m_token_value.i = atoi(m_token_value.s.c_str());
            return Token::INT;
        }

        // Return read character
        return m_ch;
    }

};

#endif

