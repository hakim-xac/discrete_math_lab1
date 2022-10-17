#include "Interface.h"
#include <unordered_set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

namespace KHAS {
    void Interface::addingAPairToASet()
    {
        std::cout << "add\n";
    }
    void Interface::deletingAPairFromASet()
    {
        std::cout << "delete\n";
    }
    void Interface::loop()
    {
        auto activeCommand{ Commands::None };

        while (activeCommand != Commands::Exit) {
            system("cls");
            printHeader();

            switch (activeCommand)
            {
            case KHAS::Commands::AddingAPair:
                break;
            case KHAS::Commands::DeletingAPair:
                break;
            case KHAS::Commands::RemovingAPair:
                break;
            case KHAS::Commands::Exit:
                break;
            case KHAS::Commands::Unknown:
                printUnknown();
                break;
            case KHAS::Commands::None:
            case KHAS::Commands::SetNewSET:
                base_set_.clear();
                base_vec_.clear();
                pairs_.clear();

                auto power{ inputPowerSet<Type>() };
                base_set_.reserve(power);
                pairs_.reserve(power * power);
                base_vec_.resize(power * power, Type{});
                inputElemsSet(power);
                pairsInput<Type>();
                applyPairs(power);
                printMatrix(power);
                printProperties(power);
                break;
            }            

            printMenu();

            activeCommand = selectCommand();
        }
    }
}