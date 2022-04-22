//
// Created by morgan on 4/21/2022.
//

#ifndef GONZYPROJECT_CONCRETELEDBOARDSMANAGER_H
#define GONZYPROJECT_CONCRETELEDBOARDSMANAGER_H

#include "ILedBoardsManager.h"
#include "ILedBoard.h"
#include <vector>

class ConcreteLedBoardsManager : public ILedBoardsManager {
public:
    explicit ConcreteLedBoardsManager(const std::vector<ILedBoard *> &ledBoards);

    void init() override;

    void lightAll() override;

    void show() override;

    void update(unsigned long currentTime) override;

    void setRandomColorForEachBoard() override;

private:
};

#endif //GONZYPROJECT_CONCRETELEDBOARDSMANAGER_H