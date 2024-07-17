#pragma once
#include "catch.hpp"
#include "utils.hpp"
#include "enums.hpp"
#include "zeus.hpp"
#include "cronos.hpp"
#include "apolo.hpp"
#include "ares.hpp"
#include "operations.hpp"
#include "energy_meter.pb.h"

#include <sstream>
#include <vector>

TEST_CASE("Testing function convert enum class to string") // Function enum_to_string()
{
    std::string line = "APOLO";
    ees::Lines apolo_line = ees::Lines::APOLO;

    REQUIRE(ees::convert_enumline_to_string(apolo_line) == line);
};

TEST_CASE("Testing function convert enum_proto to enum_cpp") // Testing OK
{
    ees::Operations op;
    std::vector<ees::Lines> lines = op.get_all_lines();

    for (size_t i = 0; i < 5; i++)
    {
        REQUIRE(ees::convert_proto_enum_to_cpp_enum(i + 1) == lines[i]);
    }
}

TEST_CASE("Testing function convert EnumLinesCpp to EnumProto")
{
    REQUIRE(ees::convert_enum_cpp_to_proto_enum(ees::Lines::ARES) == ::Lines::ARES);
    REQUIRE(ees::convert_enum_cpp_to_proto_enum(ees::Lines::APOLO) == ::Lines::APOLO);
    REQUIRE(ees::convert_enum_cpp_to_proto_enum(ees::Lines::CRONOS) == ::Lines::CRONOS);
    REQUIRE(ees::convert_enum_cpp_to_proto_enum(ees::Lines::ZEUS) == ::Lines::ZEUS);
    REQUIRE(convert_enum_cpp_to_proto_enum(static_cast<ees::Lines>(999)) == ::Lines::UNKNOWN);
}

TEST_CASE("Testing function is_all_digits") // Testing OK
{

    SECTION("Receiving a string value with letters.")
    {
        std::string text = "I am developer";
        bool result = ees::is_all_digits(text);

        REQUIRE(result == false);
    };

    SECTION("Receiving a string value with integer numbers")
    {
        std::string numbers = "123";

        REQUIRE(ees::is_all_digits(numbers));
    };
};

TEST_CASE("Testing function to_uppercase", "[to_uppercase]") // Testing OK
{
    SECTION("Convert lowercase to uppercase")
    {
        std::string input = "hello";
        std::string expected = "HELLO";
        REQUIRE(ees::to_uppercase(input) == expected);
    }

    SECTION("String already in uppercase")
    {
        std::string input = "WORLD";
        std::string expected = "WORLD";
        REQUIRE(ees::to_uppercase(input) == expected);
    }

    SECTION("Mixed case string")
    {
        std::string input = "HeLLo WoRLD";
        std::string expected = "HELLO WORLD";
        REQUIRE(ees::to_uppercase(input) == expected);
    }

    SECTION("String with numbers and symbols")
    {
        std::string input = "Hello123!@#";
        std::string expected = "HELLO123!@#";
        REQUIRE(ees::to_uppercase(input) == expected);
    }

    SECTION("Empty string throws exception")
    {
        std::string input = "";
        REQUIRE_THROWS_AS(ees::to_uppercase(input), std::runtime_error);
    }
}
