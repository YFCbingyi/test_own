#include "Task.h"
#include <iostream>

using namespace std;
Task::Task(/* args */)
{
}

Task::~Task()
{
}

bool Task::start()
{
    on_click.disconnect_all();
    on_click.connect(std::bind(&Task::on_emit_click,this,std::placeholders::_1,std::placeholders::_2));
}

void Task::on_emit_click(bool flag,bool flag2) {
    cout << std::boolalpha << flag << " -- " << flag2 << endl;
}