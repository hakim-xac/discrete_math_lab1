#include "Interface.h"
#include <unordered_set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

namespace KHAS {


    void Interface::loop()
    {
        auto activeCommand{ Commands::None };
        system("cls");
        printHeader();
        auto power{ inputPowerSet<Type>() };

        while (activeCommand != Commands::Exit) {

            switch (activeCommand)
            {
            case KHAS::Commands::AddingAPair:
            {
                pairsInput<Type>();
                applyPairs(power);
                printMatrix(power);
                printProperties(power);
            }
                break;
            case KHAS::Commands::DeletingAPair:     deletingAPairFromASet(power); break;
            case KHAS::Commands::RemovingAPair:     removingAPairFromASet(power); break;
            case KHAS::Commands::Unknown:           printUnknown(); break;
            case KHAS::Commands::SetNewSET:         power = inputPowerSet<Type>();
            case KHAS::Commands::None:
            {
                base_set_.clear();
                base_vec_.clear();
                pairs_.clear();

                base_set_.reserve(power);
                pairs_.reserve(power * power);
                base_vec_.resize(power * power, Type{});
                inputElemsSet(power);
                pairsInput<Type>();
                applyPairs(power); 
            }
                break;
            }            

            printMatrix(power);
            printProperties(power);
            printMenu();

            activeCommand = selectCommand();

            system("cls");
            printHeader();
        }
        push(delimiter('-'));
        push(stringGeneration(' ', "Выход из программы выполнен!"));
        push(delimiter('-'));
        flush();
    }
}