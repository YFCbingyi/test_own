 /***************************************************
 @File Name : main.cpp
 @Project : 
 @Author : chen bingyi 
 @Mail : chenbingyi@riseauto.cn
 @CreateTime :2020-08-19 11:28:51
 ****************************************************/
 
 #include <iostream>
 #include <thread>
 #include <chrono>

 #include "Task.h"

 using namespace std;
 
 int main(int argc,char **argv)
 {
     Task t;
     t.start();

     t.on_click.emit(true,false);
     std::this_thread::sleep_for(std::chrono::milliseconds(200));
     t.on_click.emit(false,true);
     std::this_thread::sleep_for(std::chrono::milliseconds(200));

     return 0;
 }
 