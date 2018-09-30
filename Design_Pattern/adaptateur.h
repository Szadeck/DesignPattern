#ifndef ADAPTATEUR_H
#define ADAPTATEUR_H

#include <iostream>

#include "tests.h"

struct Box
{
    Box() : _is_closed(true) {}
    virtual ~Box() = default;
    void open()
    {
        if(!this->isClosed())
            std::cout << "Box is already open." << std::endl;
        else
        {
            doOpen();
            std::cout << "Box is now opened" << std::endl;
        }
    }
    void close()
    {
        if(this->isClosed())
            std::cout << "Box is already closed." << std::endl;
        else
        {
            doClose();
            std::cout << "Box is now closed" << std::endl;
        }
    }
    virtual void doOpen()
    {
        _is_closed = false;
    }
    virtual void doClose()
    {
        _is_closed = true;
    }
    virtual bool isClosed()
    {
        return _is_closed;
    }

private:
    bool _is_closed;
};


struct Chest
{
    Chest() : _lock(true), _is_closed_chest(true) {}
    void openChest()
    {
        if (_lock)
        {
            std::cout << "Can't open, the chest is locked." << std::endl;
            return;
        }
        std::cout << "Chest is now opened" << std::endl;
        _is_closed_chest = false;
    }
    void closeChest()
    {
        std::cout << "Chest is now closed." << std::endl;
        _is_closed_chest = true;
    }
    void lock()
    {
        if (!_is_closed_chest)
        {
            std::cout << "Can't lock, the chest is opened" << std::endl;
            return;
        }
        std::cout << "Chest is now locked." << std::endl;
        _lock = true;
    }
    void unlock()
    {
        std::cout << "Chest is now unlocked" << std::endl;
        _lock = false;
    }
    bool isClosedChest()
    {
        return _is_closed_chest;
    }

private:
    bool _lock;
    bool _is_closed_chest;
};

struct ChestAdapter : public Box, private Chest
{
    virtual ~ChestAdapter() = default;
    virtual void doOpen()
    {
        this->unlock();
        this->openChest();
    }
    virtual void doClose()
    {
        this->closeChest();
        this->lock();
    }
    virtual bool isClosed()
    {
        return this->isClosedChest();
    }
};


struct TestAdaptateur : public Tests
{
    TestAdaptateur() : Tests ("Test Adaptateur") {}
    virtual ~TestAdaptateur() = default;
    virtual bool launchTest()
    {
        Box * box = new Box();
        box->open();
        box->open();
        box->close();
        std::cout << std::endl;
        Box * chest = new ChestAdapter();
        chest->open();
        chest->open();
        chest->close();

        return true;
    }
};

#endif // ADAPTATEUR_H
