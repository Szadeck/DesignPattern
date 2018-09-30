#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <iostream>
#include <memory>

#include "tests.h"

struct Prototype
{
    virtual ~Prototype() = default;
    virtual Prototype * clone() = 0;
    void update()
    {
        doUpdate();
    }
    virtual void doUpdate() {}
};

struct Os : public Prototype
{
    Os() : _version(0) {}
    virtual ~Os() = default;
    virtual Os * clone()
    {
        this->update();
        return (new Os(*this));
    }
    virtual void doUpdate()
    {
        std::cout << "Os updated." << std::endl;
        _version++;
    }
    void showVersion()
    {
        std::cout << "Os version : " << this->_version << std::endl;
    }
private:
    int _version;
};

struct TestPrototype : public Tests
{
    TestPrototype() : Tests("Test Prototype") {}

    virtual ~TestPrototype() = default;
    virtual bool launchTest()
    {
        Os first;
        first.showVersion();
        Os * second = first.clone();
        second->showVersion();
        Os * third = first.clone();
        third->showVersion();

        delete second;
        delete third;

        return true;
    }
};



#endif // PROTOTYPE_H
