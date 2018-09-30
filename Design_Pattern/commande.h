#ifndef COMMANDE_H
#define COMMANDE_H

#include <iostream>
#include <chrono>
#include <thread>
#include "tests.h"

struct Command
{
    virtual ~Command() = default;
    virtual void execute() = 0;
};


struct TimeRemote
{

    TimeRemote(Command & startcommand, Command & stopcommand, Command & showcommand) :
        _start_command(startcommand), _stop_command(stopcommand), _show_command(showcommand) {}

    void startChrono()
    {
        _start_command.execute();
    }

    void stopChrono()
    {
        _stop_command.execute();
    }

    void showChrono()
    {
        _show_command.execute();
    }

private:
    Command & _start_command;
    Command & _stop_command;
    Command & _show_command;

};


struct TimeChrono
{
    TimeChrono()
    {
        _start = std::chrono::system_clock::now();
        _end = std::chrono::system_clock::now();
    }

    void start()
    {
        _start = std::chrono::system_clock::now();
        _end = _start;
    }

    void stop()
    {
        _end = std::chrono::system_clock::now();
    }

    void showChrono()
    {
        int elapsedtime = std::chrono::duration_cast<std::chrono::seconds> (_end - _start).count();
        std::cout << "Chrono time : " << elapsedtime << "s" << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> _start;
    std::chrono::time_point<std::chrono::system_clock> _end;

};

struct StartChronoCommand : public Command
{
    TimeChrono & _time_chrono;

    StartChronoCommand(TimeChrono & timer) : _time_chrono(timer) {}
    virtual ~StartChronoCommand() = default;
    virtual void execute()
    {
        _time_chrono.start();
    }
};

struct StopChronoCommand : public Command
{
    TimeChrono & _time_chrono;

    StopChronoCommand(TimeChrono & timer) : _time_chrono(timer) {}
    virtual ~StopChronoCommand() = default;
    virtual void execute()
    {
        _time_chrono.stop();
    }
};

struct ShowChronoCommand : public Command
{
    TimeChrono & _time_chrono;

    ShowChronoCommand(TimeChrono & timer) : _time_chrono(timer) {}
    virtual ~ShowChronoCommand() = default;
    virtual void execute()
    {
        _time_chrono.showChrono();
    }
};

struct TestCommand : public Tests
{
    TestCommand() : Tests ("Test Command") {}
    virtual ~TestCommand() = default;
    virtual bool launchTest()
    {
        TimeChrono timeChrono;
        ShowChronoCommand showC(timeChrono);
        StartChronoCommand startC(timeChrono);
        StopChronoCommand stopC(timeChrono);
        TimeRemote remote(startC, stopC, showC);

        remote.showChrono();
        remote.stopChrono();
        remote.showChrono();
/*        std::this_thread::sleep_for(std::chrono::seconds(2));
        remote.stopChrono();
        remote.showChrono();
        remote.startChrono();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        remote.stopChrono();
        remote.showChrono();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        remote.stopChrono();
        remote.showChrono();
        remote.startChrono();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        remote.stopChrono();
        remote.showChrono();
*/
        return true;
    }
};


#endif // COMMANDE_H
