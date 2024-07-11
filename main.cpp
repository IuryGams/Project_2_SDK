#include "menu.hpp"
#include "server.hpp"
#include <locale.h>
#include <iostream>

int main () 
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    energy::RunServer();
    return 0;
}
