#include "utils.hpp"
#include "operations.hpp"
#include "menu.hpp"
#include "energy_meter.pb.h"

#include <cstring>
#include <string>
#include <map>

namespace ees
{

    auto convert_enumline_to_string(const ees::Lines &line) -> std::string
    {
        std::map<ees::Lines, std::string> lines_to_string = {
            {ees::Lines::ARES, "ARES"},
            {ees::Lines::APOLO, "APOLO"},
            {ees::Lines::CRONOS, "CRONOS"},
            {ees::Lines::ZEUS, "ZEUS"},
            {ees::Lines::UNKNOWN, "UNKNOWN"},
        };

        return lines_to_string.at(line);
    }

    auto convert_proto_enum_to_cpp_enum(int proto_enum_value) -> ees::Lines
    {
        switch (proto_enum_value)
        {
        case 1:
            return ees::Lines::ARES;
        case 2:
            return ees::Lines::APOLO;
        case 3:
            return ees::Lines::CRONOS;
        case 4:
            return ees::Lines::ZEUS;
        default:
            return ees::Lines::UNKNOWN;
        }
    }

    auto convert_to_proto_enum(ees::Lines line) -> int
    {
        static std::map<ees::Lines, ::Lines> line_map = {
            {ees::Lines::ARES, ::Lines::ARES},
            {ees::Lines::APOLO, ::Lines::APOLO},
            {ees::Lines::CRONOS, ::Lines::CRONOS},
            {ees::Lines::ZEUS, ::Lines::ZEUS},
            // Pode adicionar mais mapeamentos conforme necessário
        };
        auto it = line_map.find(line);
        if (it != line_map.end())
        {
            return it->second;
        }
        else
        {
            return ::Lines::UNKNOWN; // Retorna o valor padrão para casos não mapeados
        }
    }

    auto is_all_digits(const std::string &text) -> bool
    {
        for (char c : text)
        {
            if (!isdigit(c))
            {
                return false;
            }
        }
        return true;
    }

    auto convert_string_to_int() -> int
    {
        std::string tip_text;
        int option;
        while (true)
        {
            getline(std::cin, tip_text); // Ensuring the value is a string
            if (tip_text.empty())        // Checking if the answer is empty.
            {
                std::cout << "Entrada inválida. Por favor, digite um dígito de 1 a 9.\n";
                continue;
            }

            if (is_all_digits(tip_text)) // Checking if the answer is a integer number.
            {
                option = stoi(tip_text);
                break;
            }
            else
            {
                std::cout << "Entrada inválida. Por favor, insira um número.\n";
            }
        }
        return option;
    }

    auto to_uppercase(std::string &text) -> std::string
    {
        if(text.empty())
        {
            throw std::runtime_error("Valor inválido!"); 
        }

        for(char & c : text)
        {
            if(std::islower(c))
            {
                c = std::toupper(c);
            }
        }
        return text;
    }
}