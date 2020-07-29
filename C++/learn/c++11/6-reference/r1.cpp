#include <iostream>
#include <string>

int main()
{
 int first = 10;
 int sec = 5;
 // Make Reference ref_1 to point towards variable first.
 int & ref_1 = first;
 
 std::cout<<"first = "<<first<<std::endl;
 std::cout<<"sec = "<<sec<<std::endl;
 std::cout<<"ref_1 = "<<ref_1<<std::endl;


 // Now if you try to point the reference ref_1 to an another variable i.e. sec
 // then reference will not change its reference point, this kind of assignment
 // will only change the value of variable to which refernce was pointing.
 ref_1 = sec;
 
 std::cout<<"After changing the ref_1 value"<<std::endl;
 std::cout<<"first = "<<first<<std::endl;
 std::cout<<"sec = "<<sec<<std::endl;
 std::cout<<"ref_1 = "<<ref_1<<std::endl;
 
 int * ptr = &first;
 std::cout<<"ptr = "<<ptr<<" :: *ptr = "<<(*ptr)<<std::endl;
 
 sec = 9;
 ptr = &sec;
 
 std::cout<<"ptr = "<<ptr<<" :: *ptr = "<<(*ptr)<<std::endl;
 return 0;
}
