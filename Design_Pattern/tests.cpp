#include "tests.h"

void Tests::doTest()
{
    std::cout << "Test -" << this->_testname << "- starting ..." << std::endl;

    bool test_result = this->launchTest();
    if (test_result)
        std::cout << "... Test OK ..." << std::endl << std::endl;
    else
        std::cout << ".. Test FAIL .." << std::endl << std::endl;
}
