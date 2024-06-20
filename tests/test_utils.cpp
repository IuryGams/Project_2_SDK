#pragma once
#include "catch.hpp"
#include "utils.hpp"
#include "enums.hpp"
#include "zeus.hpp"
#include "cronos.hpp"
#include "apolo.hpp"
#include "ares.hpp"
#include "operations.hpp"

#include <sstream>
#include <vector>

namespace ees
{

    TEST_CASE("Testing function convert enum class to string")
    {
        std::string line = "APOLO";
        Lines apolo_line = Lines::APOLO;

        REQUIRE(convert_enumline_to_string(apolo_line) == line);
    };

    TEST_CASE("Testing function is_all_digits")
    {

        SECTION("Receiving a string value with letters.")
        {
            std::string text = "I am developer";
            bool result = is_all_digits(text);

            REQUIRE(result == false);
        };

        SECTION("Receiving a string value with integer numbers")
        {
            std::string numbers = "123";
            
            REQUIRE(is_all_digits(numbers));
        };
    };

    TEST_CASE("Testing function convert string to integer number.")
    {
        // std::stringstream input_stream;
        // std::stringstream output_stream;

        // // Redirect cin and cout
        // std::streambuf *old_cin = std::cin.rdbuf(input_stream.rdbuf());
        // std::streambuf *old_cout = std::cout.rdbuf(output_stream.rdbuf());

        // SECTION("Valid input")
        // {
        //     input_stream.str("123\n"); // Simulate input "123"
        //     int result = convert_string_to_int();
        //     REQUIRE(result == 123);
        // };

        // SECTION("Empty input")
        // {
        //     input_stream.str("\n"); // Simulate input "\n" (empty)
        //     int result = convert_string_to_int();
        //     // Check if the function handles empty input properly
        //     REQUIRE(output_stream.str() == "Entrada inválida. Por favor, digite um dígito de 1 a 9.\n");
        // };

        // SECTION("Invalid input")
        // {
        //     input_stream.str("abc\n"); // Simulate input "abc"
        //     int result = convert_string_to_int();
        //     // Check if the function handles invalid input properly
        //     REQUIRE(output_stream.str() == "Entrada inválida. Por favor, insira um número.\n");
        // };

        // // Restore cin and cout
        // std::cin.rdbuf(old_cin);
        // std::cout.rdbuf(old_cout);
    };

} // namespace ees
