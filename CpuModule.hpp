
#ifndef INCLUDED_CPUMODULE_HPP
    #define INCLUDED_CPUMODULE_HPP

#include "IModule.hpp"
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

class CpuNumModule : public Krell::IModule { //we have to declare what the type T is for the get_value
    private:
        int _num = -1;
        bool _initialised = false; //the number of cores will not change in the middle of runtime, we can just get the info once
    public:
        void update() override {
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

        std::string get_name() override { return "Cpu Number"; }
        int get_height() override { return 1; }

        ModuleValue get_value() override {return _num;}
        std::string get_string() override {return std::to_string(_num);}
        bool is_percentage() override {return false;}

};



/*
Cpu module : calculating use percentage
*/
class CpuUseModule : public Krell::IModule { //we have to declare what the type T is for the get_value
    private:
        int _num = 0;
        float _use_percentage = 0;
        bool _initialised = false;
        struct CpuTimes {
            long idle;
            long total;
        };
        std::vector<CpuTimes> _previous;
        float _usage = 0;


        CpuTimes readLine(const std::string& line) const
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
    public:
        //https://stackoverflow.com/questions/3017162/how-to-get-total-cpu-usage-in-linux-using-c
        void update() override {
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
            //_previous = current;

        }

        std::string get_name() override { return "Cpu Usage"; }
        int get_height() override { return 2; }

        ModuleValue get_value() override {return _usage;}
        std::string get_string() override {return std::to_string(_usage).append(" %");}
        bool is_percentage() override {return true;}

};

/*
gets name of module
*/
class CpuNameModule : public Krell::IModule { //we have to declare what the type T is for the get_value
    private:
        std::string _cpuname = "";
        bool _initialised = false; //cpu name is not gonna change
    public:
        //https://www.redhat.com/en/blog/get-cpu-information-linux
        void update() override {
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
        std::string get_name() override {return "CPU name";}
        int get_height() override {return 1;}

        ModuleValue get_value() override {return _cpuname;}
        std::string get_string() override {return _cpuname;}
        bool is_percentage() override {return false;}
};


#endif
