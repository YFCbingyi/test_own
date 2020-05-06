#include "my_template.h"
#include "debug_log.h"
my_template::my_template()
{

}

void my_template::run() {
    int a = 1, b = 2;
    swap(a,b);
    LOG(INFO) << a << " - " << b;
    double c = 1.23,d = 2.42;
    swap(c,d);
    LOG(INFO) << c << " - "<<d;

}
