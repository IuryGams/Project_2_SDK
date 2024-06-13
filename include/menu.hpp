#pragma once

#include "enums.hpp"
#include <iostream>


namespace ees {

    class Menu 
    {
        public:
            void show_start_menu();
            void run_menu();
            void show_all_lines();
            void show_all_models();
            void show_line(const Lines &name_line);
            void exit_menu();
    };

}; // namespace ees