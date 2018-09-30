#ifndef MONTEUR_H
#define MONTEUR_H

#include <iostream>
#include "fabrique.h"

struct Smartphone : Prototype
{
    Smartphone(PhonePart * phone, PhonePart * glass, PhonePart * battery, Os * os) :
    _phone(phone), _glass(glass), _battery(battery), _os(os)  {}
    Smartphone()
    {
        _phone = nullptr;
        _glass = nullptr;
        _battery = nullptr;
        _os = nullptr;
        std::cout << "Creating a new Smartphone" << std::endl;
    }
    Smartphone(Smartphone const & copy)
    {
        _battery = copy._battery->clone();
        _glass = copy._glass->clone();
        _phone = copy._phone->clone();
        _os = copy._os->clone();
    }
    virtual ~Smartphone()
    {
        delete _phone;
        delete  _glass;
        delete  _battery;
        delete _os;
    }
    Smartphone * clone()
    {
        return (new Smartphone(*this));
    }
    void testPhoneParts()
    {
        if (_phone != nullptr)
            _phone->whichPart();
        if (_glass != nullptr)
            _glass->whichPart();
        if (_os != nullptr)
            _os->showVersion();
        if (_battery != nullptr)
            _battery->whichPart();
    }
    void setPhoneParts(PhonePart * phone, PhonePart * glass, PhonePart * battery, Os * os)
    {
        this->_battery = battery;
        this->_glass = glass;
        this->_os = os;
        this->_phone = phone;
    }
    private:
    PhonePart * _phone;
    PhonePart * _glass;
    PhonePart * _battery;
    Os        * _os;
};

struct Monteur
{
    ~Monteur()
    {
        delete _os;
        delete _sp;
    }

    Monteur()
    {
        _fab.registerNewObject(new Glass, "Glass");
        _fab.registerNewObject(new Battery, "Battery");
        _fab.registerNewObject(new Phone, "Phone");
        _os = new Os;
        _sp = new Smartphone(_fab.create("Phone"), _fab.create("Glass"), _fab.create("Battery"), _os->clone());
    }

    Smartphone * createSmartphone()
    {
        Smartphone * newsmartphone = new Smartphone;
        newsmartphone->setPhoneParts(_fab.create("Phone"), _fab.create("Glass"), _fab.create("Battery"), _os->clone());
        return newsmartphone;
    }

    Smartphone * cloneSmartphone()
    {
        return _sp->clone();
    }

private:
    Fabrique<PhonePart> _fab;
    Os * _os;
    Smartphone * _sp;
};

struct TestMonteur : public Tests
{
    TestMonteur() : Tests ("Test Monteur") {}
    virtual ~TestMonteur() = default;
    virtual bool launchTest()
    {
        Monteur monteur;
        Smartphone * sp = monteur.createSmartphone();
        sp->testPhoneParts();
        Smartphone * newgensp = monteur.cloneSmartphone();
        newgensp->testPhoneParts();

        delete newgensp;
        delete sp;

        return true;
    }
};

#endif // MONTEUR_H
