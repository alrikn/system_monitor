#include "Data.hpp"

#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <limits.h>

#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


Krell::Data::Data()
{
    getSnapshot(_cpu);
    update();
}

Krell::Data::~Data()
{
}

void getSysInfo(struct sysinfo &info)
{
    if (sysinfo(&info) == 0) {
        return;
    }
    info.totalram = 1;
}

void getUtsname(struct utsname &names)
{
    if (uname(&names) == 0)
        return;
}

std::string parseUptime(long seconds)
{
    long days = seconds / 86400;
    seconds %= 86400;
    long hours = seconds / 3600;
    seconds %= 3600;
    long minutes = seconds / 60;
    seconds %= 60;

    std::ostringstream uptime;
    uptime << days << ":"
           << (hours < 10 ? "0" : "") << hours << ":"
           << (minutes < 10 ? "0" : "") << minutes << ":"
           << (seconds < 10 ? "0" : "") << seconds;
    return uptime.str();
}

std::string parseDateTime()
{
    time_t now;
    std::string str;

    time(&now);
    str = ctime(&now);
    str.pop_back();
    return (str);
}

std::string getHostname()
{
    char hostname[HOST_NAME_MAX + 1];
    gethostname(hostname, HOST_NAME_MAX + 1);
    return (hostname);
}

std::string getPrettyName()
{
    std::ifstream file("/etc/os-release");

    if (file.fail())
        return ("Linux");
    std::string line;
    while (std::getline(file, line)) {
        if (line.rfind("PRETTY_NAME=", 0) == 0) {
            size_t start = line.find('"');
            size_t end = line.rfind('"');
            file.close();
            if (start != std::string::npos && end != std::string::npos && start < end) {
                return line.substr(start + 1, end - start - 1);
            }
            return "Linux";
        }
    }
    file.close();
    return ("Linux");
}

double parseBattery()
{
    double bat;
    std::ifstream capacity;

    for (int i = 0;  i < 10; i++) {
        std::stringstream name;
        name << "/sys/class/power_supply/BAT" << i << "/capacity";
        capacity.open(name.str());
        if (!capacity.fail()) {
            break;
        }
    }
    if (capacity.fail()) {
        return (0);
    }
    capacity >> bat;
    capacity.close();
    return (bat);
}

void Krell::Data::update()
{
    struct sysinfo info;
    struct utsname names;
    struct CPUsnapshot snap;

    getSnapshot(snap);
    getSysInfo(info);
    getUtsname(names);
    ramSpace = info.totalram;
    ramPercentage = 100.f - (info.freeram * 100.f / ramSpace);
    uptime = parseUptime(info.uptime);
    dateTime = parseDateTime();
    host = getHostname();
    user = getlogin();
    kernel = names.release;
    os = getPrettyName();
    battery = parseBattery();

    unsigned long active = snap.active - _cpu.active;
    unsigned long total = snap.total - _cpu.total;
    if (total > 10) {
        cpuPercentage = 100.f * active / total;
        _cpu = snap;
    }
}

void getSnapshot(struct CPUsnapshot &cpu)
{
    unsigned long user, nice, sys, idle, iowait, irq, softirq;
    std::ifstream stat("/proc/stat");

    if (stat.fail()) {
        cpu.idle = 0;
        cpu.active = 0;
        cpu.total = 0;
        return;
    }
    stat.ignore(3) >> user >> nice >> sys >> idle >> iowait >> irq >> softirq;
    stat.close();
    cpu.idle = idle + iowait;
    cpu.active = user + nice + sys + irq + softirq;
    cpu.total = cpu.idle + cpu.active;
}


#include <chrono>
#include <thread>

/*int main()
{
    Krell::Data d;

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "OS: " << d.getOs() << std::endl;
        std::cout << "Uptime: " << d.getUptime() << std::endl;
        std::cout << "RAM: " << d.getRamSpace() << std::endl;
        std::cout << "RAM%: " << d.getRamPercentage() << std::endl;
        std::cout << "BAT: " << d.getBattery() << std::endl;
        std::cout << "CPU: " << d.getCpuPercentage() << std::endl;
        std::cout << "Date: " << d.getDateTime() << std::endl;
        std::cout << "Kernel: " << d.getKernel() << std::endl;
        std::cout << "Host: " << d.getHost() << std::endl;
        std::cout << "User: " << d.getUser() << std::endl;
        d.update();
    }
}*/

