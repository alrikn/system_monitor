#include "CpuModule.hpp"










CpuModule::CpuModule() : _initialized(false){}
#include <fstream>
#include <sstream>
#include <iomanip>


CpuModule::CpuTimes CpuModule::readLine(const std::string& line) const
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

std::string CpuModule::name() const
{
    return "CPU";
}

int CpuModule::height() const
{
    if (_usage.empty())
        return 2;
    return static_cast<int>(_usage.size() + 1);
}


/*
https://www.geeksforgeeks.org/cpp/static_cast-in-cpp/
*/
void CpuModule::update()
{
    std::ifstream file("/proc/stat");
    std::string line;
    std::vector<CpuTimes> current;

    while (std::getline(file, line)) {
        if (line.rfind("cpu", 0) != 0)
            break;
        current.push_back(readLine(line));
    }

    if (!_initialized) {
        _previous = current;
        _usage.resize(current.size(), 0.f);
        _initialized = true;
        return;
    }

    for (std::size_t i = 0; i < current.size(); i++) {
        long idle_delta = current[i].idle - _previous[i].idle;
        long total_delta = current[i].total - _previous[i].total;

        if (total_delta > 0) {
            _usage[i] = (1.f - static_cast<float>(idle_delta) / total_delta) * 100.f;
        }
    }

    _previous = current;
}

std::vector<std::string> CpuModule::lines() const
{
    std::vector<std::string> out;
    if (_usage.empty())
        return out;

    std::ostringstream ss;
    ss << std::fixed << std::setprecision(1);

    ss << "Total: " << _usage[0] << "%";
    out.push_back(ss.str());
    ss.str("");
    ss.clear();

    for (std::size_t i = 1; i < _usage.size(); ++i) {
        ss << "Core " << (i - 1) << ": " << _usage[i] << "%";
        out.push_back(ss.str());
        ss.str("");
        ss.clear();
    }

    return out;
}
