//
// Created by morgan on 4/24/2022.
//

#ifndef PLATFORMIO_PROGRAM_LEDBOARD_STORE_INTERFACE_H
#define PLATFORMIO_PROGRAM_LEDBOARD_STORE_INTERFACE_H

#include <vector>
#include "LedBoard.h"

class LedBoard_Store_Interface {
public:
    virtual void addBoard(LedBoard *ledBoard) { _ledBoards.emplace_back(ledBoard); };

    std::vector<LedBoard *> getLedBoards() { return _ledBoards; }

protected:
    std::vector<LedBoard *> _ledBoards;

};

#endif //PLATFORMIO_PROGRAM_LEDBOARD_STORE_INTERFACE_H