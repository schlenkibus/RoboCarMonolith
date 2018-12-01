#pragma once

class Uart {
public:
    explicit Uart(const char* port);
    ~Uart();
    void send(char charToSend);
    char receive();
protected:
    int m_fd;
};
