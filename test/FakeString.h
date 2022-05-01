//
// Created by morgan on 4/24/2022.
//

#ifndef GONZY_PROJECT_TEST_FAKESTRING_H
#define GONZY_PROJECT_TEST_FAKESTRING_H

#include <string>

class String {
public:
    explicit String(const std::string &mString) {
        standardString = mString;
    }

    String(){
        standardString="";
    }

    String(std::byte byte){

        standardString =(char) byte;
    }

    String(uint8_t num){
        standardString =std::to_string(num);
    }

    String(uint16_t num) {
        standardString = std::to_string(num);
    }

    int length(){
        return standardString.length();
    }


    String operator+=(const String &b)  {
        this->standardString = this->standardString + b.standardString;
        return *this;
    }

//     operator String(){
//        return ;
//    }

    String operator+=(const uint8_t num){
        this->standardString = this->standardString + std::to_string(num);
        return *this;
    }

    String operator+=(const std::string &b)  {
        this->standardString = this->standardString + b;
        return *this;
    }

    String operator+=(const char m[]){
        this->standardString = this->standardString+ m;
        return *this;
    }


    bool operator==(const String &b) const {
        if (standardString == b.standardString) {
            return true;
        } else {
            return false;
        }
    }

    bool operator==(const std::string &b) const {
        if (standardString == b) {
            return true;
        } else {
            return false;
        }
    }

    String& operator=(const std::string &b){
        this->standardString = b;
        return *this;
    }

public:
    std::string standardString{};

};

#endif //GONZY_PROJECT_TEST_FAKESTRING_H