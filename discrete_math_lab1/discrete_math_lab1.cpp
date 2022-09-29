#include "Interface.h"
#include <iostream>
#include <iomanip>


int main()
{
    using namespace KHAS;
    setlocale(LC_ALL, "Russian");
    //* params */
    // first:   size_t          table_width_    | not default
    // second:  std::ostream&   out_            | default: std::cout
    Interface window(100);
    window.loop();


}