#ifndef FABRIQUE_H
#define FABRIQUE_H

#include <iostream>
#include "prototype.h"
#include "tests.h"
#include <map>

struct PhonePart : public Prototype
{
    virtual ~PhonePart()
    {
        std::cout << "A phone part has been destroyed." << std::endl;
    }
    virtual void whichPart() = 0;
    virtual PhonePart * clone() = 0;
};

struct Phone : public PhonePart
{
    Phone()
    {
        std::cout << "Creation of a prototype phone." << std::endl;
    }
    Phone(Phone const & copy)
    {
        std::cout << "Cloning a new phone." << std::endl;
    }
    virtual ~Phone() = default;
    virtual Phone * clone()
    {
        return (new Phone(*this));
    }
    virtual void whichPart()
    {
        std::cout << "I am a phone." << std::endl;
    }
};

struct Glass : public PhonePart
{
    Glass()
    {
        std::cout << "Creation of a prototype glass." << std::endl;
    }
    Glass(Glass const & copy)
    {
        std::cout << "Cloning a new glass." << std::endl;
    }
    virtual ~Glass() = default;
    virtual Glass * clone()
    {
        return (new Glass(*this));
    }
    virtual void whichPart()
    {
        std::cout << "I am a glass." << std::endl;
    }
};

struct Battery : public PhonePart
{
    Battery()
    {
        std::cout << "Creation of a prototype battery." << std::endl;
    }
    Battery(Battery const & copy)
    {
        std::cout << "Cloning a new battery." << std::endl;
    }
    virtual ~Battery() = default;
    virtual Battery * clone()
    {
        return (new Battery(*this));
    }
    virtual void whichPart()
    {
        std::cout << "I am a battery." << std::endl;
    }
};

template<class Object, class Key=std::string>
struct Fabrique
{
    ~Fabrique()
    {
        for (auto it = _prototype_list.begin(); it != _prototype_list.end(); it++)
            delete (*it).second;
    }
    std::map<Key, Object *> _prototype_list;
    bool registerNewObject(Object * newobject, Key newkey)
    {
        if (_prototype_list.find(newkey) == _prototype_list.end())
        {
            _prototype_list[newkey] = newobject;
            return true;
        }
        else
        {
            std::cout << "This object already has a prototype" << std::endl;
            return false;
        }
    }
    Object * create(Key const & key)
    {
        Object * newobject = nullptr;
        typename std::map<Key, Object *>::iterator it = _prototype_list.find(key);
        if (it != _prototype_list.end())
        {
            newobject = ((*it).second)->clone();
            return newobject;
        }
        else
            std::cout << "The key :" << key << " doesn't have a prototype." << std::endl;
        return newobject;
    }
};

struct TestFabrique : public Tests
{
    TestFabrique() : Tests ("Test Fabrique") {}
    virtual ~TestFabrique() = default;
    virtual bool launchTest()
    {
        Fabrique<PhonePart> fab;
        PhonePart * glassproto = new Glass();
        if (!fab.registerNewObject(glassproto, "Glass"))
            delete glassproto;
        PhonePart * glassCloned = fab.create("Glass");
        glassCloned->update();
        glassCloned->whichPart();

        PhonePart * glassproto2 = new Glass();
        if (!fab.registerNewObject(glassproto2, "Glass"))
            delete glassproto2;
        PhonePart * batteryproto = new Battery();
        if (!fab.registerNewObject(batteryproto, "Battery"))
            delete batteryproto;
        PhonePart * batteryCloned = fab.create("Battery");
        batteryCloned->whichPart();
        std::cout << "Trying to clone a Phone." << std::endl;
        PhonePart * phoneCloned = fab.create("Phone");
        if (phoneCloned == nullptr)
            std::cout << "Failed Trying to clone a Phone." << std::endl;
        return true;
    }
};

#endif // FABRIQUE_H
