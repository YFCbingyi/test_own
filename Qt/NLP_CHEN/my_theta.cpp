#include "my_theta.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "debug_log.h"
#define pi 3.1415926
my_theta::my_theta()
{

}

void my_theta::test() {
    LineAngle1();
    LineAngle2();
    LOG(INFO) << "两条直线角度差:" << fabs(lineA.deg-lineB.deg);
}

void my_theta::LineAngle1()
{
    double tmp;
    double angle;
    lineA.A.X = 1.74;
    lineA.A.Y = 3.32;
    lineA.B.X = -0.76;
    lineA.B.Y = -7.65;
    LOG(INFO) << "第一个 "<<lineA.A.X <<","<<lineA.A.Y;
    LOG(INFO) << "第二个 "<<lineA.B.X <<","<<lineA.B.Y;
    //求角度
    tmp=(lineA.B.Y-lineA.A.Y)/(lineA.B.X-lineA.A.X);
    lineA.deg=atan(tmp);  //弧度
    lineA.deg=lineA.deg*(double)180/pi;
//   angle=atan2((lineA.B.Y-lineA.A.Y),(lineA.B.X-lineA.A.X))*(double)180/pi;  //atan 无方向,atan2 有方向 （矢量）
   angle=atan2((lineA.B.Y-lineA.A.Y),(lineA.B.X-lineA.A.X))*(double)180/pi;  //atan 无方向,atan2 有方向 （矢量）

    LOG(INFO) << "第一条直线斜线角度:" << tmp << " "<< lineA.deg;
    LOG(INFO) << "angle:" << angle;
}
void my_theta::LineAngle2()
{
    double tmp;
    double angle;
    lineB.A.X = 3;
    lineB.A.Y = 1;
    lineB.B.X = 4;
    lineB.B.Y = 2;
    LOG(INFO) << "第一个 "<<lineB.A.X <<","<<lineB.A.Y;
    LOG(INFO) << "第二个 "<<lineB.B.X <<","<<lineB.B.Y;

    //求角度
    tmp=(lineB.B.Y-lineB.A.Y)/(lineB.B.X-lineB.A.X);
    lineB.deg=atan(tmp);
    lineB.deg=lineB.deg*(double)180/pi;
    LOG(INFO) << "第二条直线斜线角度:" << tmp << " " <<lineB.deg;
    angle=atan2((lineB.B.Y-lineB.A.Y),(lineB.B.X-lineB.A.X))*(double)180/pi;  //atan 无方向,atan2 有方向 （矢量）
    LOG(INFO) << "angle:" << angle;
}
