#pragma once

class Uart {
public:
    explicit Uart(const char* port);
    void send(char charToSend);
    char receive();
protected:
    int m_fd;
};
