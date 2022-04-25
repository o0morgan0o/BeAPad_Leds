//
// Created by morgan on 4/24/2022.
//

#ifndef PLATFORMIO_PROGRAM_LOGMESSAGES_STORE_H
#define PLATFORMIO_PROGRAM_LOGMESSAGES_STORE_H

#include <cstring>

#define BUFFER_SIZE  100

class LogMessages_Store {
public:
    explicit LogMessages_Store() = default;

    void populateChar(char *ch) {
        strcpy(ch, _message);
    }

    void addMessage(const char ch[]) {
        strncat(_message, ch, BUFFER_SIZE - strlen(_message) - 1);

    }

    size_t getMessageLength() {
        return strlen(_message) + 1;
    }

private:
    char _message[BUFFER_SIZE] = "";

};

#endif //PLATFORMIO_PROGRAM_LOGMESSAGES_STORE_H