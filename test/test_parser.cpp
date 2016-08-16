#include "catch.hpp"

#include "plang_parser.h"

TEST_CASE( "Parse funcion (basic)", "[parser]") {

    // Simple @main funtcion with empty block

    PlangParser parser;

    const char * str_main = "@main() {}";

    parser.load_input(str_main);

    REQUIRE( parser.parse_function() == 0);
}
