/*
** EPITECH PROJECT, 2023
** rush 3
** File description:
** data
*/

#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <ctime>

struct CPUsnapshot {
    unsigned long total;
    unsigned long active;
    unsigned long idle;
};

namespace Krell {
    class Data {
    private:
        struct CPUsnapshot _cpu;

        std::string host;
        std::string user;
        std::string os;
        std::string kernel;
        std::string dateTime;
        std::string uptime;
        double cpuPercentage;
        double ramPercentage;
        std::size_t ramSpace;
        double battery;
    public:
        Data();
        ~Data();

        std::string getHost();
        std::string getUser();
        std::string getOs();
        std::string getKernel();
        std::string getDateTime();
        std::string getUptime();
        double getCpuPercentage();
        double getRamPercentage();
        std::size_t getRamSpace();
        double getBattery();
        void update();
    };
}

void getSnapshot(struct CPUsnapshot &cpu);

#endif
