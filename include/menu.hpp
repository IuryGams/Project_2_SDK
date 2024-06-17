#pragma once

#include "enums.hpp"
#include <iostream>


namespace ees {

    class Menu 
    {
        public:
            void show_inicial_menu();
            void show_lines_menu();
            void run_menu();
            void show_all_lines();
            void show_all_models();
            void show_line(const Lines &name_line);
            void selected_new_meter();
            void selected_remove_meter();
            void exit_menu();
    };

}; // namespace ees