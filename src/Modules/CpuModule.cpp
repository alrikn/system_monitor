/*
** EPITECH PROJECT, 2026
** system_monitor
** File description:
** CpuModule
*/

#include "CpuModule.hpp"



void CpuNumModule::update()
{
    if (!_initialised) {
        std::ifstream file("/proc/stat");
        std::string line;
        while (std::getline(file, line)) {
            if (line.rfind("cpu", 0) != 0)
                break;
            _num += 1;
        }
        _initialised = true;
    }
}



CpuTimes CpuUseModule::readLine(const std::string& line) const
{
    std::istringstream iss(line);
    std::string cpu;
    long user, nice, system, idle, iowait, irq, softirq, steal; //no coding style muahhaha

    iss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

    CpuTimes t;
    t.idle = idle + iowait;
    t.total = user + nice + system + idle + iowait + irq + softirq + steal;
    return t;
}



void CpuUseModule::update()
{
    std::ifstream file("/proc/stat");
    std::string line;
    std::vector<CpuTimes> current;
    _usage = 0;
    _num = 0;

    while (std::getline(file, line)) {
        if (line.rfind("cpu ", 0) == 0) {
            current.push_back(readLine(line));
            _num += 1;
            break;
        }
    }

    if (!_initialised) {
        _previous = current;
        _initialised = true;
        return;
    }
    long idle_delta = 0;
    long total_delta = 0;
    for (std::size_t i = 0; i < current.size(); i++) {
        idle_delta = current[i].idle - _previous[i].idle;
        total_delta = current[i].total - _previous[i].total;
        if (total_delta > 0) {
            _usage += (1.f - (float)idle_delta / total_delta) * 100.f;
        }
    }
    _usage /= _num;
    //_previous = current
}



void CpuNameModule::update()
{
    if (!_initialised) {
        _initialised = true;
        std::ifstream file("/proc/cpuinfo");
        std::string line;
        while (std::getline(file, line)) {
            if (line.rfind("model name", 0) == 0)
                break;
        }
        //model name      : Intel(R) Core(TM) Ultra 5 125U
        std::string key; //"model name" we don't care about
        std::stringstream ss(line);
        std::getline(ss, key, ':');
        std::getline(ss, _cpuname);
    }
}


