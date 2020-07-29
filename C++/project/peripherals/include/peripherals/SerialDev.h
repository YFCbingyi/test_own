#ifndef SERIAL_DEV_H
#define SERIAL_DEV_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/types.h>

#ifndef RET_OK
#define RET_OK       0
#endif
#ifndef RET_ERR
#define RET_ERR     -1
#endif

class SerialDev {
private:
#ifndef CMSPAR
    static const int CMSPAR = 010000000000;
#endif

    int mFd;

    int setBaudRate(struct termios &opt, int speed) 
    {
        speed_t s;

        switch (speed) {
        case 0       : s = B0;       break;
        case 50      : s = B50;      break;
        case 75      : s = B75;      break;
        case 110     : s = B110;     break;
        case 134     : s = B134;     break;
        case 150     : s = B150;     break;
        case 200     : s = B200;     break;
        case 300     : s = B300;     break;
        case 600     : s = B600;     break;
        case 1200    : s = B1200;    break;
        case 1800    : s = B1800;    break;
        case 2400    : s = B2400;    break;
        case 4800    : s = B4800;    break;
        case 9600    : s = B9600;    break;
        case 19200   : s = B19200;   break;
        case 38400   : s = B38400;   break;
        case 57600   : s = B57600;   break;
        case 115200  : s = B115200;  break;
        case 230400  : s = B230400;  break;
        default:
            perror("invalid baud rate\n");
            return RET_ERR;
        }

        cfsetispeed(&opt, s);  
        cfsetospeed(&opt, s);
        return RET_OK;   
    }

    int setDataBits(struct termios &opt, int data_bits) 
    {
        opt.c_cflag &= ~CSIZE; 
        
        switch (data_bits) {
        case 5: opt.c_cflag |= CS5; break;
        case 6: opt.c_cflag |= CS6; break; 
        case 7: opt.c_cflag |= CS7; break;
        case 8: opt.c_cflag |= CS8; break;
        default:    
            perror("invalid data bits\n");
            return RET_ERR;  
        }
        opt.c_iflag &= ~ (IXON | IXOFF | IXANY);
        opt.c_lflag &= ~ (ICANON | ECHO | ECHOE | ISIG);
        opt.c_iflag &= ~ (INLCR | ICRNL | IGNCR);
        opt.c_oflag &= ~(ONLCR | OCRNL);

        return RET_OK;
    }
 
    int setParityChecking(struct termios &opt, char parity) 
    {
        switch (parity) {
        case 'n':
        case 'N':
            opt.c_cflag &= ~PARENB;            
            break;
        case 'o':
        case 'O':
            opt.c_cflag |= PARENB;
            opt.c_cflag |= PARODD;        
            break;
        case 'e':
        case 'E':
            opt.c_cflag |= PARENB;
            opt.c_cflag &= ~PARODD;                       
            break;
        case 'm':
        case 'M':
            opt.c_cflag |= PARENB | CS8 | PARODD | CMSPAR;   
            break;
        case 's':
        case 'S':
            opt.c_cflag |= PARENB | CS8 | CMSPAR;
            break;
        default:    
            perror("invalid parity\n");
            return RET_ERR;  
        }
        return RET_OK;
    }

    int setStopBits(struct termios &opt, int stop_bits) 
    {
        switch (stop_bits) {   
        case 1:    
            opt.c_cflag &= ~CSTOPB;  
            break;  
        case 2:    
            opt.c_cflag |= CSTOPB;  
            break;
        default:    
            perror("invalid stop bits\n");  
            return RET_ERR; 
        }
        return RET_OK;
    }

    int setCanonicalMode(struct termios &opt, bool icanon) 
    {
        if (icanon) {
            opt.c_lflag |= ICANON; 
        } else {
            opt.c_lflag &= ~ICANON;
        }
        return RET_OK;
    }

    int setNoncanonicalOpt(struct termios &opt, unsigned char vmin, unsigned char vtime) 
    {
        opt.c_cc[VMIN] = vmin;
        opt.c_cc[VTIME] = vtime;
        return RET_OK;
    }

    bool opened() { return mFd != -1; }

public:
    SerialDev() : mFd(-1) {          }
    ~SerialDev()          { close(); }

    int open(const char *dev, int flags = O_RDWR) 
    {
        if ((mFd = ::open(dev, flags)) == RET_ERR) {
            perror("open file failed\n");
            return RET_ERR;
        }
        return RET_OK;
    }

    int init(int speed, int data_bits, char parity, int stop_bits) 
    {
        struct  termios opt;

        if (tcgetattr(mFd, &opt) == -1) {
            perror("get attribute failed\n");
            return RET_ERR;
        }
        if (setBaudRate(opt, speed) == RET_ERR) {
            return RET_ERR;
        }
        if (setDataBits(opt, data_bits) == RET_ERR) {
            return RET_ERR;
        }
        if (setParityChecking(opt, parity) == RET_ERR) {
            return RET_ERR;
        }
        if (setStopBits(opt, stop_bits) == RET_ERR) {
            return RET_ERR;
        }
        if (tcsetattr(mFd, TCSANOW, &opt) == -1) {
            perror("set attribute failed\n");
            return RET_ERR;
        }
        tcflush(mFd,TCIOFLUSH);    
        return RET_OK;
    }

    int setBaudRate(int speed) 
    {
        struct  termios opt; 

        if (tcgetattr(mFd, &opt) == -1) {
            perror("get attribute failed\n");
            return RET_ERR;
        }
        if (setBaudRate(opt, speed) == RET_ERR) {
            return RET_ERR;
        }   
        if (tcsetattr(mFd, TCSANOW, &opt) == -1) {
            perror("set attribute failed\n");
            return RET_ERR;
        }
        tcflush(mFd,TCIOFLUSH);
        return RET_OK;
    }

    int setDataBits(int data_bits) 
    {
        struct  termios opt;
       
        if (tcgetattr(mFd, &opt) == -1) {
            perror("get attribute failed\n");
            return RET_ERR;
        }
        if (setDataBits(opt, data_bits) == RET_ERR) {
            return RET_ERR;
        }
        if (tcsetattr(mFd, TCSANOW, &opt) == -1) {
            perror("set attribute failed\n");
            return RET_ERR;
        }
        tcflush(mFd,TCIOFLUSH);
        return RET_OK;
    }

    int setParityChecking(char parity) 
    {
        struct  termios opt;
       
        if (tcgetattr(mFd, &opt) == -1) {
            perror("get attribute failed\n");
            return RET_ERR;
        }
        if (setParityChecking(opt, parity) == RET_ERR) {
            return RET_ERR;
        }         
        if (tcsetattr(mFd, TCSANOW, &opt) == -1) {
            perror("set attribute failed\n");
            return RET_ERR;
        }
        tcflush(mFd,TCIOFLUSH);
        return RET_OK;
    }

    int setStopBits(int stop_bits) 
    {
        struct  termios opt;
       
        if (tcgetattr(mFd, &opt) == -1) {
            perror("get attribute failed\n");
            return RET_ERR;
        }
        if (setStopBits(opt, stop_bits) == RET_ERR) {
            return RET_ERR;
        }
        if (tcsetattr(mFd, TCSANOW, &opt) == -1) {
            perror("set attribute failed\n");
            return RET_ERR;
        }
        tcflush(mFd,TCIOFLUSH);
        return RET_OK;
    }

    int setCanonicalMode(bool icanon) 
    {
        struct  termios opt;

        if (tcgetattr(mFd, &opt) == -1) {
            perror("get attribute failed\n");
            return RET_ERR;
        }
        if (setCanonicalMode(opt, icanon) == RET_ERR) {
            return RET_ERR;
        }
        if (tcsetattr(mFd, TCSANOW, &opt) == -1) {
            perror("set attribute failed\n");
            return RET_ERR;
        }
        tcflush(mFd,TCIOFLUSH);
        return RET_OK;
    }

    int setNoncanonicalOpt(unsigned char vmin, unsigned char vtime) 
    {
        struct  termios opt;

        if (tcgetattr(mFd, &opt) == -1) {
            perror("get attribute failed\n");
            return RET_ERR;
        }
        if (setNoncanonicalOpt(opt, vmin, vtime) == RET_ERR) {
            return RET_ERR;
        }
        if (tcsetattr(mFd, TCSANOW, &opt) == -1) {
            perror("set attribute failed\n");
            return RET_ERR;
        }
        tcflush(mFd,TCIOFLUSH);
        return RET_OK;
    }

    int available(void) 
    {
        return 0; 
    }
    
    ssize_t read(void *buf, size_t len) 
    {
        return ::read(mFd, buf, len); 
    }
    
    ssize_t write(const void *buf, size_t len) 
    {
        return ::write(mFd, buf, len);
    }

    int print(const char *str) 
    {
        int ret_val = RET_ERR;  

        if (str != NULL) {
#if 1
            printf("%s\n", str);
            int len = strlen(str);
            
            if (this->write(str, len) == len) {
                ret_val = RET_OK;
            }
#else
            ret_val = RET_OK;
            printf("%s\n", str);
#endif
        }
        return ret_val;
    }
    
    int println(const char *str) 
    {
        if (this->print(str) == RET_ERR || this->print("\n") == RET_ERR) {
            return RET_ERR;
        }
        return RET_OK;
    }

    int flush(void) 
    {
        if (tcflush(mFd, TCIOFLUSH) == -1) {
            return RET_ERR;
        }
        return RET_OK;
    }
    
    void close(void) 
    {
        if (opened()) {
            ::close(mFd);
            mFd = -1;
        } 
    }

    int getFd(void) 
    {
        return mFd;
    }
};

#endif

