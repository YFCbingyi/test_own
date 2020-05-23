#include "Reptile.h"

int main() {

    
    Reptile t;
    std::string url = "https://mhd366.com/html/manhua/";
    std::cout << url << std::endl;
    t.start(url);
    std::string nurl;
    for(int i = 2; i < 31;i ++) {
        nurl = url+"list_1_"+std::to_string(i) + ".html";
        std::cout << nurl << std::endl;
        t.start(nurl);
    }
    

    return 0;
}