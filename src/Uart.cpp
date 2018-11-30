#include "Uart.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <chrono>
#include <assert.h>
#include <sys/ioctl.h>

int open_port(const char* port)
{
    auto fd = open(port, O_RDWR | O_NDELAY | O_NOCTTY);
    if(fd == -1)
    {
        std::cout << "open_port: Unable to open /dev/ttyS0." << std::endl;
        assert(false);
    }
    else
    {
        fcntl(fd, F_SETFL, 0);
        std::cout << "UART works!" << std::endl;
    }
    return(fd);
}

int configure_port(int fd)
{
    struct termios port_settings;
    cfsetispeed(&port_settings, B115200);
    cfsetospeed(&port_settings, B115200);
    port_settings.c_cflag &= ~(PARENB | CSTOPB | CSIZE | CRTSCTS);
    port_settings.c_cflag |= (CLOCAL | CREAD | CS8);
    port_settings.c_cc[VMIN]  = 1;
    port_settings.c_oflag &= ~OPOST;
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
  int availableBytes = 0;
  
  do {
    ioctl(m_fd, FIONREAD, &availableBytes);
  } while(availableBytes == 0);

  char buff[20];
  auto readBytes = read(m_fd, buff, 20);
  if(readBytes > 0) {
    std::cout << "bytes read: " << readBytes << std::endl;
    return buff[0];
  } else {
    std::cerr << "read failed!" << std::endl;
  }
  return 'N';
}
