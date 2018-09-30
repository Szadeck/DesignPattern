#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <iostream>
#include <forward_list>

#include "tests.h"

struct Character
{
    virtual ~Character() = default;
    virtual void move() = 0;
};

struct Wizard : public Character
{
    virtual ~Wizard() = default;
    virtual void move()
    {
        std::cout << "Wizard teleported from A to B." << std::endl;
    }
};

struct Ranger : public Character
{
    virtual ~Ranger() = default;
    virtual void move()
    {
        std::cout << "Ranger walked from A to B." << std::endl;
    }
};

struct Angel : public Character
{
    virtual ~Angel() = default;
    virtual void move()
    {
        std::cout << "Angel flied from A to B." << std::endl;
    }
};

struct Composite : public Character
{
private:
    std::forward_list<Character *> _char_list;
public:
    virtual ~Composite() = default;
    void addCharacter(Character * newchar)
    {
        _char_list.push_front(newchar);
    }
    void deleteCharacter(Character * chartodelete)
    {
        _char_list.remove(chartodelete);
    }
    virtual void move()
    {
        for (auto it = _char_list.begin(); it != _char_list.end(); it++)
            (*it)->move();
    }

};

struct TestComposite : public Tests
{
    TestComposite() : Tests ("Test Composite") {}
    virtual ~TestComposite() = default;
    virtual bool launchTest()
    {
        Character * angel = new Angel;
        Character * ranger = new Ranger;
        Character * wizard = new Wizard;

        std::cout << "Moving one by one :" << std::endl;
        angel->move();
        ranger->move();
        wizard->move();

        Composite composite;
        composite.addCharacter(angel);
        composite.addCharacter(ranger);
        composite.addCharacter(wizard);

        std::cout << "Moving with composite :" << std::endl;
        composite.move();

        delete angel;
        delete ranger;
        delete wizard;
        return true;
    }
};


#endif // COMPOSITE_H
