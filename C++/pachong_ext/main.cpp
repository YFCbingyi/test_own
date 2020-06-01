#include <iostream>
#include "Cartoon.h"

int main(int argc, char const *argv[])
{
    Cartoon cartoon;
    std::string url = "https://mhd488.com/html/manhua/";
    cartoon.start(url);
    
    return 0;
}
