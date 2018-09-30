#ifndef TESTS_H
#define TESTS_H

#include <iostream>

class Tests
{
public:
    Tests(std::string testname) : _testname(testname) {}
    virtual ~Tests() = default;

    virtual bool launchTest() = 0;
    void doTest();

private:
    std::string _testname;
};

#endif // TESTS_H
