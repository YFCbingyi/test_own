#ifndef PRINTKER_H
#define PRINTKER_H

#include <string>
#include <vector>

struct termios;
class Printker
{
public:
    Printker();
    bool init(std::string &usbname);
    int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop);
    int recv();
    int show_zice();
    int write_str_(unsigned const char str[]);
    int open_ttyfd_(std::string &usbname);
private:
    int _tty_fd;
};

#endif // PRINTKER_H
