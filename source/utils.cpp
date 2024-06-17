#include "utils.hpp"
#include "operations.hpp"
#include "menu.hpp"

#include <cstring>
#include <string>
#include <map>


namespace ees
{

    auto convert_enumline_to_string(const Lines &line) -> std::string
    {
        std::map<Lines, std::string> lines_to_string = {
            {Lines::ARES, "ARES"},
            {Lines::APOLO, "APOLO"},
            {Lines::CRONOS, "CRONOS"},
            {Lines::ZEUS, "ZEUS"},
            {Lines::UNKNOWN, "UNKNOWN"},
        };

        return lines_to_string.at(line);
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

    auto read_option_menu() -> int
    {
        std::string tip_text;
        int option;
        while (true)
        {
            getline(std::cin, tip_text); // Ensuring the value is a string
            if (tip_text.empty()) // Checking if the answer is empty.
            {
                std::cout << "Entrada inválida. Por favor, digite um digito de 1 a 9.\n";
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

} // namespace ees