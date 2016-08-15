#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "plang_tokenizer.h"
#include <string>
#include <cstring>


TEST_CASE( "Tokenize empty string" , "[tokenizer]") {
    // Empty input parse
    const char * str_empty = "";
    
    PlangTokenizer tokenizer;

    tokenizer.load_input(str_empty);
    REQUIRE(tokenizer.get_token() == PlangTokenizer::Token::END);
}


TEST_CASE( "Tokenize single characters" , "[tokenizer]") {
    // Test if tokenizer can get all singe character 
    // tokens parsed from soruce code
    const char * str_empty = "@#={}()[]-+*/.,;\"";
    
    PlangTokenizer tokenizer;

    tokenizer.load_input(str_empty);

    const size_t empty_size = std::strlen(str_empty);
    for (size_t i=0 ; i < empty_size ; ++i) {
        REQUIRE(tokenizer.get_token() == str_empty[i]);
    }
    REQUIRE(tokenizer.get_token() == PlangTokenizer::Token::END);
}


TEST_CASE( "Tokenize ID" , "[tokenizer]") {
    // Single identifier parsing
    const char * str_id = "identifier";
    
    PlangTokenizer tokenizer;

    tokenizer.load_input(str_id);
    REQUIRE(tokenizer.get_token() == PlangTokenizer::Token::ID);
    REQUIRE(tokenizer.get_token_value().s == "identifier");
    REQUIRE(tokenizer.get_token() == PlangTokenizer::Token::END);
}


TEST_CASE( "Tokenize INT" , "[tokenizer]") {
    // Single identifier parsing
    const char * str_int = "1024";

    PlangTokenizer tokenizer;

    tokenizer.load_input(str_int);
    REQUIRE(tokenizer.get_token() == PlangTokenizer::Token::INT);
    REQUIRE(tokenizer.get_token_value().i == 1024);
    REQUIRE(tokenizer.get_token() == PlangTokenizer::Token::END);
}


TEST_CASE( "Tokenize basic string (main)" , "[tokenizer]") {
    // Empty MAIN function definition
    const char * str_main = "@main() {}";
    
    PlangTokenizer tokenizer;

    tokenizer.load_input(str_main);
    REQUIRE(tokenizer.get_token() == '@');
    REQUIRE(tokenizer.get_token() == PlangTokenizer::Token::ID);
    REQUIRE(tokenizer.get_token_value().s == "main");
    REQUIRE(tokenizer.get_token() == '(');
    REQUIRE(tokenizer.get_token() == ')');
    REQUIRE(tokenizer.get_token() == '{');
    REQUIRE(tokenizer.get_token() == '}');
    REQUIRE(tokenizer.get_token() == PlangTokenizer::Token::END);
}

