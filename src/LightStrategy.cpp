//
// Created by morgan on 4/25/2022.
//

#include "LightStrategy.h"

LightStrategy::LightStrategy(LedBoard *context, unsigned long lifeSpan) {
    _context = context;
    _lifeSpan = lifeSpan;
}