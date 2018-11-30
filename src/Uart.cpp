#include "Uart.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <chrono>
#include <assert.h>

int open_port(const char* port)
{
    auto fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    if(fd == -1)
    {
        std::cout << "open_port: Unable to open /dev/ttyS0." << std::endl;
        assert(false);
    }
    else
    {
        fcntl(fd, F_SETFL, 0);
        std::cout << "port is open." << std::endl;
    }
    return(fd);
}

int configure_port(int fd)
{
    struct termios port_settings;
    cfsetispeed(&port_settings, B115200);
    cfsetospeed(&port_settings, B115200);
    port_settings.c_cflag &= ~PARENB;
    port_settings.c_cflag &= ~CSTOPB;
    port_settings.c_cflag &= ~CSIZE;
    port_settings.c_cflag |= CS8;
    tcsetattr(fd, TCSANOW, &port_settings);
    return(fd);
}

Uart::Uart(const char* port) {
    m_fd = open_port(port);
    m_fd = configure_port(m_fd);
}

void Uart::send(char charToSend) {
    const char* t = &charToSend;
    auto written = write(m_fd, t, 1);
    assert(written == 1);
}

char Uart::receive() {
    char c;
    size_t readBytes = 0;
    do {
        readBytes += read(m_fd, &c, 1);
    } while(readBytes < 1);
    assert(readBytes == 1);
    return c;
}
