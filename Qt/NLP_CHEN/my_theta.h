#ifndef MY_THETA_H
#define MY_THETA_H


class my_theta
{
public:

    my_theta();
    void start();

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
