#include "my_vector.h"

my_vector::my_vector()
{

}

void my_vector::my_float32_vector() {
    double a = 3.005000114440918;
    std::cout << "double "<< a << std::endl;
}

void my_vector::find() {
    std::vector<int> muster;
    for(int i =0 ;i < 5;i++)
        muster.push_back(i);
    for(int i = 0;i < 5;i++)
        std::cout << muster[i] << std::endl;
    
    int aa = muster.back();
    std::cout << "AA "<<aa << std::endl;

    auto iter = std::find(muster.begin(),muster.end(),6);
    if(iter != muster.end())
        std::cout << "存在" <<std::endl;
    else
        std::cout << "不存在" << std::endl;
}
