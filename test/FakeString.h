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

    String(std::byte byte){

        standardString =(char) byte;
    }


    String operator+=(const String &b)  {
        this->standardString = this->standardString + b.standardString;
        return *this;
    }

    String operator+=(const std::string &b)  {
        this->standardString = this->standardString + b;
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