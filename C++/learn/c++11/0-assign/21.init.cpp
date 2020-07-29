#include <iostream>
#include <vector>
#include <map>
#include <initializer_list>


template <class T>
struct S {
    std::vector<T> v;
    S(std::initializer_list<T> l) : v(l) {
         std::cout << "constructed with a " << l.size() << "-element list\n";
    }
	S(T a) {
         v.insert(v.end(), a);
    }
    void append(std::initializer_list<T> l) {
        v.insert(v.end(), l.begin(), l.end());
    }
    std::pair<const T*, std::size_t> c_arr() const {
        return {&v[0], v.size()};  // copy list-initialization in return statement
                                   // this is NOT a use of std::initializer_list
    }
};

int main() {
    S<int> s = {1, 2, 3, 4, 5}; // copy list-initialization
    s.append({6, 7, 8});      // list-initialization in function call
 
    std::cout << "The vector size is now " << s.c_arr().second << " ints:\n";
 
    for (auto n : s.v)
        std::cout << n << ' ';
    std::cout << '\n';
 
	S<int> s2 (100);
	std::cout << "The vector size is now " << s2.c_arr().second << " ints:\n";

    auto al = {10, 11, 12};   // special rule for auto
 
    std::cout << "The list bound to auto has size() = " << al.size() << '\n';
}
