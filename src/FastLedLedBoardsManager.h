//
// Created by morgan on 4/21/2022.
//

#ifndef GONZYPROJECT_CONCRETELEDBOARDSMANAGER_H
#define GONZYPROJECT_CONCRETELEDBOARDSMANAGER_H

#include "LedBoardsManager.h"
#include "LedBoard.h"
#include <vector>

class FastLedLedBoardsManager : public LedBoardsManager {
public:
    explicit FastLedLedBoardsManager(LedBoard_Store_Interface* ledBoardStore);
//
    void init() override;

    void showGlobally(CRGB color) override;
//
//    void forceLightOff() override;
//
//    void lightAll(uint8_t r, uint8_t g, uint8_t b) override;
//
    void show() override;
//
//    void update(unsigned long currentTime) override;
//
//    void setRandomColorForEachBoard() override;
//
//    void showSuccessSignal() override;
//
//    const CRGB &getCurrentGlobalColor() override;
//
//    void showErrorSignal() override;
//
//    void lightWhite() override;
//
private:
//    CRGB currentGlobalColor{0, 0, 120};
};

#endif //GONZYPROJECT_CONCRETELEDBOARDSMANAGER_H