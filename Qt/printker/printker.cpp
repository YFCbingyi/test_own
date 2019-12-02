#include "printker.h"
#include <termios.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <iostream>
Printker::Printker() {

}

bool Printker::init(std::string &usbname) {
    if(open_ttyfd_(usbname) <= 0) {
        std::cerr << "open "<< usbname << "failed" <<std::endl;
    }
    std::cout << "tty_fd "<<_tty_fd << std::endl;
    if(set_opt(_tty_fd,9600,8,'N',1) < 0) {
        std::cerr << "set port failed"<<std::endl;
    }
}

int Printker::open_ttyfd_(std::string &usbname) {
    return _tty_fd = open(usbname.c_str(),O_RDWR|O_NOCTTY|O_NDELAY),_tty_fd;
}

int Printker::write_str_(unsigned const char str[]) {
    return write(_tty_fd,str, strlen((const char*)str));
}

int Printker::show_zice() {
    unsigned char str[4];
    str[0] = 0x1B;
    str[1] = 0x40;
    str[2] = 0x12;
    str[3] = 0x54;
    return write_str_(str);
}

int Printker::recv() {
    char buffer[512];
    int nByte = read(_tty_fd, buffer, 512);
    if(nByte <= 0) {
        return nByte;
    } else {
        printf("buffer : %s\n",buffer);
    }
    return nByte;
}

int Printker::set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
    struct termios newtio,oldtio;
    if  ( tcgetattr( fd,&oldtio)  !=  0) {
        perror("SetupSerial 1");
        return -1;
    }
    bzero( &newtio, sizeof( newtio ) );
    newtio.c_cflag  |=  CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;

    //数据位数
    switch( nBits )
    {
        case 7:
            newtio.c_cflag |= CS7;
            break;
        case 8:
            newtio.c_cflag |= CS8;
            break;
    }

    //奇偶校验
    switch( nEvent )
    {
    case 'O':
        newtio.c_cflag |= PARENB;
        newtio.c_cflag |= PARODD;
        newtio.c_iflag |= (INPCK | ISTRIP);
        break;
    case 'E':
        newtio.c_iflag |= (INPCK | ISTRIP);
        newtio.c_cflag |= PARENB;
        newtio.c_cflag &= ~PARODD;
        break;
    case 'N':
        newtio.c_cflag &= ~PARENB;
        break;
    }


    //波特率
    switch( nSpeed )
    {
        case 2400:
            cfsetispeed(&newtio, B2400);
            cfsetospeed(&newtio, B2400);
            break;
        case 4800:
            cfsetispeed(&newtio, B4800);
            cfsetospeed(&newtio, B4800);
            break;
        case 9600:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
        case 115200:
            cfsetispeed(&newtio, B115200);
            cfsetospeed(&newtio, B115200);
            break;
        case 460800:
            cfsetispeed(&newtio, B460800);
            cfsetospeed(&newtio, B460800);
            break;
        default:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
    }
    //停止位
    if( nStop == 1 )
        newtio.c_cflag &=  ~CSTOPB;
    else if ( nStop == 2 )
        newtio.c_cflag |=  CSTOPB;
        newtio.c_cc[VTIME]  = 0;
        newtio.c_cc[VMIN] = 0;
        tcflush(fd,TCIFLUSH);
    if((tcsetattr(fd,TCSANOW,&newtio))!=0)
    {
        perror("com set error");
        return -1;
    }
    //配置完成
    printf("set done!\n\r");
    return 0;
}


