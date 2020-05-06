#ifndef TESTBASE_H
#define TESTBASE_H


class TestBase
{
public:
    TestBase();
    ~TestBase();
    
    virtual void test() = 0;
    
};

#endif // TESTBASE_H