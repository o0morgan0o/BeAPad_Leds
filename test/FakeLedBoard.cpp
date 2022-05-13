//
// Created by morgan on 4/25/2022.
//

#include "FakeLedBoard.h"
#include "../src/LedBoard.cpp"

FakeLedBoard::FakeLedBoard(uint8_t nb_pixels, LightStrategy_Factory *factory) : LedBoard(nb_pixels, factory) {}