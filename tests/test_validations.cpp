#pragma once
#include "catch.hpp"
#include "validations.hpp"
#include "energy_meter.hpp"
#include "project_exceptions.hpp"
#include "utils.hpp"

ees::Validations validations;

TEST_CASE("Testing function check already exists meter", "[already_exists_meter]")
{
    SECTION("Meter does not exist")
    {
        REQUIRE(validations.check_if_meter_already_exists({18, ees::Lines::APOLO, "Model 1"}));
    };

    SECTION("Meter already exists")
    {
        REQUIRE_THROWS_AS(validations.check_if_meter_already_exists(ees::EnergyMeter{1, ees::Lines::APOLO, "Model 1"}), expections::AlreadyExists);
    }
}

TEST_CASE("Testing function check already exists line", "[check_if_line_exists]")
{
    std::vector<ees::Lines> list_line = {
        ees::Lines::APOLO,
        ees::Lines::ARES,
        ees::Lines::ZEUS,
        ees::Lines::CRONOS,
        ees::Lines::UNKNOWN};

    SECTION("Line exists")
    {
        REQUIRE(validations.check_if_line_exists(ees::convert_enumline_to_string(ees::Lines::APOLO)));
    };

    SECTION("Line does not exists")
    {
        REQUIRE_THROWS_AS(validations.check_if_line_exists("KRATOS"), expections::NotExists);
    }
}

TEST_CASE("Testing function check if line is not equal to UNKNOWN", "[check_if_is_unknown]")
{

    SECTION("line is UNKNOWN")
    {
        REQUIRE_THROWS_AS(validations.check_if_is_unknown("UNKNOWN"), expections::NotExists);
    }

    SECTION("line does not UNKNOWN")
    {
        REQUIRE_NOTHROW(validations.check_if_is_unknown("KRATOS"));
        REQUIRE_NOTHROW(validations.check_if_is_unknown("Test"));
        REQUIRE_NOTHROW(validations.check_if_is_unknown(""));
    }
}