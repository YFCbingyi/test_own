#ifndef MY_THETA_H
#define MY_THETA_H
#include "testbase.h"

class my_theta : public TestBase
{
public:

    my_theta();
    void test();

    void LineAngle1();
    void LineAngle2();
private:
    typedef struct
    {
        double X;
        double Y;
    }point;

     typedef struct
    {
        point A;
        point B;
        double deg;
    }line;

    line lineA;
    line lineB;


};

#endif // MY_THETA_H
