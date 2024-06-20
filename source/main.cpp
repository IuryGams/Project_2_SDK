#include "menu.hpp"

#include <locale.h>
#include <iostream>

int main () 
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    ees::Menu menu; 

    std::cout << "Seja bem-vindo ao menu de consulta de medidores!" << std::endl;
    menu.run_menu();
    return 0;
}
