#ifndef DECORATEUR_H
#define DECORATEUR_H

#include <iostream>
#include "tests.h"

struct ICar
{
    virtual ~ICar() = 0;
    void drive()
    {
        std::cout << "The car is driving" << std::endl;
    }
    virtual std::string description()
    {
        return ("This is car");
    }
    void afficher()
    {
        std::cout << this->description() << std::endl;
    }
};

inline
ICar::~ICar()
{
    std::cout << "Car is deleting" << std::endl;
}

struct Car : public ICar
{
};

struct CarDecorateur : public ICar
{
    CarDecorateur(ICar * car) : _car(car) {}
    virtual ~CarDecorateur() = 0;
    ICar * getCar()
    {
        return _car;
    }

protected:
    ICar * _car;
};

inline
CarDecorateur::~CarDecorateur() {}


struct CarGPS : public CarDecorateur
{
    CarGPS(ICar * car) : CarDecorateur (car) {}
    virtual ~CarGPS()
    {
        std::cout << "GPS is deleting" << std::endl;
        delete _car;
    }
    void activateGPS()
    {
        std::cout << "GPS is tracing your way." << std::endl;
    }
    std::string description()
    {
        return (getCar()->description() + " with a gps");
    }
};

struct CarRadio : public CarDecorateur
{
    CarRadio(ICar * car) : CarDecorateur (car) {}
    virtual ~CarRadio()
    {
        std::cout << "Radio is deleting" << std::endl;
        delete _car;
    }
    std::string description()
    {
        return (getCar()->description() + " with a radio");
    }
    void useRadio()
    {
        std::cout << "The radio is playing music." << std::endl;
    }

};

struct TestDecorateur : public Tests
{
    TestDecorateur() : Tests ("Test Decorateur") {}
    virtual ~TestDecorateur() = default;
    virtual bool launchTest()
    {
        ICar * mycar = new Car;
        mycar->drive();
        mycar->afficher();
        mycar = new CarRadio(mycar);
        mycar->drive();
        static_cast<CarRadio *>(mycar)->useRadio();
        mycar->afficher();
        delete mycar;
        mycar = new CarGPS(new CarRadio(new Car()));
        mycar->drive();
        mycar->afficher();
        static_cast<CarRadio *>(mycar)->useRadio();
        static_cast<CarGPS*>(mycar)->activateGPS();
        delete mycar;

        return true;

    }
};


#endif // DECORATEUR_H
