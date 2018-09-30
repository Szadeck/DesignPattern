#ifndef CHAINEDERESPONSABILITE_H
#define CHAINEDERESPONSABILITE_H

#include<iostream>
#include "tests.h"

struct TestChainederesponsabilite : public Tests
{
    TestChainederesponsabilite() : Tests ("Test Chaine de responsabilite") {}
    virtual ~TestChainederesponsabilite() = default;
    virtual bool launchTest()
    {


    }
};


#endif // CHAINEDERESPONSABILITE_H
