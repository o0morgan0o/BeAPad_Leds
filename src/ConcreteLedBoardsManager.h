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

    void forceLightOff() override;

    void lightAll(uint8_t r, uint8_t g, uint8_t b) override;

    void show() override;

    void update(unsigned long currentTime) override;

    void setRandomColorForEachBoard() override;

    void showSuccessSignal() override;

    const CRGB &getCurrentGlobalColor() override;

    void showErrorSignal() override;

private:
    CRGB currentGlobalColor{0, 0, 120};
};

#endif //GONZYPROJECT_CONCRETELEDBOARDSMANAGER_H