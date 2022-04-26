//
// Created by morgan on 4/25/2022.
//

#include "LightStrategy.h"
#include "LedBoard.h"

LightStrategy::LightStrategy(LedBoard *context) {
    _context = context;
    _boardLeds = _context->getBoardLeds();
    //
    _birthTime = _context->getCurrentTime();
    //
    _crgbStrategyColor = CRGB{
        _context->getBoardBaseColor().r,
        _context->getBoardBaseColor().g,
        _context->getBoardBaseColor().b
    };

}

void LightStrategy::reinit() {
    _birthTime = _context->getCurrentTime();
    //
    _crgbStrategyColor = CRGB{
            _context->getBoardBaseColor().r,
            _context->getBoardBaseColor().g,
            _context->getBoardBaseColor().b
    };

}