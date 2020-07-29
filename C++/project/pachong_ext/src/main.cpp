#include <iostream>
#include "Cartoon.h"

#ifdef ALLOW_SEARCH

int main(int argc, char const *argv[])
{
    if(argc < 2 || argc > 3) {
        printf("格式输入有误");
        return -1;
    }
    std::string search_name = argv[1];
    Cartoon cartoon;
    std::string url = "https://mhd488.com/html/manhua/";
    cartoon.start(url,search_name);
    
    return 0;
}

#else

int main(int argc, char const *argv[])
{
    Cartoon cartoon;
    std::string url = "https://mhd488.com/html/manhua/";
    cartoon.start(url);
    
    return 0;
}

#endif
