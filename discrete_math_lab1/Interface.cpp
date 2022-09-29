#include "Interface.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

namespace KHAS {

    void Interface::loop()
    {
        for (; !(GetAsyncKeyState(VK_ESCAPE) & 0x01);) {

            showHeader();

            std::cin.get();
        }
        
    }
}