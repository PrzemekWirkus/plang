#include "catch.hpp"

#include "plang_parser.h"
#include <string>

TEST_CASE( "Parse @main function definition (empty body)", "[parser]" ) {

    // Simple @main funtcion with empty block

    PlangParser parser;
    parser.load_input("@main() {}");

    REQUIRE(parser.parse_function() == 0);
}

TEST_CASE( "Parse functions definitions (broken)", "[parser][.]" ) {

    {
        PlangParser parser;
        parser.load_input("@main() }");
        REQUIRE(parser.parse_function() != 0);
    }

    {
        PlangParser parser;
        parser.load_input("@main( {}");
        REQUIRE(parser.parse_function() != 0);
    }

    {
        PlangParser parser;
        parser.load_input("@main) {}");
        REQUIRE(parser.parse_function() != 0);
    }

    {
        PlangParser parser;
        parser.load_input("@(){}");
        REQUIRE(parser.parse_function() != 0);
    }

    {
        PlangParser parser;
        parser.load_input("@main {}");
        REQUIRE(parser.parse_function() != 0);
    }
}

TEST_CASE( "IF statement", "[parser]" ) {


    {
        PlangParser parser;
        parser.load_input("@main() { if (id) {}  }");
        REQUIRE(parser.parse_function() == 0);
    }

}


TEST_CASE( "IF AS statement", "[parser]" ) {


    {
        PlangParser parser;
        parser.load_input("@main() { if (val) as id {} }");
        REQUIRE(parser.parse_function() == 0);
    }

}

TEST_CASE( "IF ELSE statement", "[parser]" ) {
    {
        PlangParser parser;
        parser.load_input("@main() { if (id) {} else {} }");
        REQUIRE(parser.parse_function() == 0);
    }
}


TEST_CASE( "IF AS ELSE statement", "[parser]" ) {
    {
        PlangParser parser;
        parser.load_input("@main() { if (id) as id {} else {} }");
        REQUIRE(parser.parse_function() == 0);
    }
}

TEST_CASE( "block content", "[block]" ) {

    {
        PlangParser parser;
        parser.load_input(R"(
            @main() {
            
                if (long_name_of_variable) {
                    
                }

                if long_name_of_variable) as v {
                
                    if (v) {}
                }
            }
        
        )");
        REQUIRE(parser.parse_function() == 0);
    }

}

