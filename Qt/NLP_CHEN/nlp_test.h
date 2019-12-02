#ifndef NLP_TEST_H
#define NLP_TEST_H

#include <thread>
class nlp_test
{
public:
    nlp_test();

    void run();
    void _func1_();
    std::thread thread1;
    std::thread thread2;
    std::thread thread3;

};

#endif // NLP_TEST_H
