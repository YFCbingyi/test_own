#include "peripherals/IDcardbase.h"
#include <unistd.h>
#include <iostream>
int main() {
    IDcardbase *pr = IDcardbase::getInstance();

    pr->start_identify();

    sleep(10);
    pr->stop_identify();
    return 0;
}
