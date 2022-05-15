#include <gtest/gtest.h>
#include <gmock/gmock.h>
#define  IN_TESTING
//static const uint8_t T0 = 4;
//static const uint8_t T1 = 0;
//static const uint8_t T2 = 2;
//static const uint8_t T3 = 15;
//static const uint8_t T4 = 13;
//static const uint8_t T5 = 12;
//static const uint8_t T6 = 14;
//static const uint8_t T7 = 27;
//static const uint8_t T8 = 33;
//static const uint8_t T9 = 32;

#include "Fake_Arduino.h"
#include "../src/NoLightStrategy.cpp"
#include "../src/FullLightStrategy.cpp"
#include "../src/LightStrategy.cpp"
#include "../src/FadeOutLightStrategy.cpp"
#include "../src/FadeInFadeOutLightStrategy.cpp"
#include "../src/CapacitiveTouch_Dispatcher.cpp"
#include "../src/ShiftKeyLightStrategy.cpp"
#include "../src/NoSpecialEffect_Strategy.cpp"
#include "../src/SerpentinLightStrategy.cpp"
#include "../src/StromboscopeSpecialEffect_Strategy.cpp"
#include "../src/SpecialEffect_Factory.cpp"
#include "../src/NoSpecialEffect_Strategy.cpp"
#include "../src/SpecialEffects_Strategy.cpp"
#include "../src/Midi_Handler.cpp"

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();

}