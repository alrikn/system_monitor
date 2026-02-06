
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
        void update() override;

        std::string get_name() override { return "Cpu Number"; }
        int get_height() override { return 1; }

        ModuleValue get_value() override {return _num;}
        std::string get_string() override {return std::to_string(_num);}
        bool is_percentage() override {return false;}

};


struct CpuTimes {
            long idle;
            long total;
        };

/*
Cpu module : calculating use percentage
*/
class CpuUseModule : public Krell::IModule { //we have to declare what the type T is for the get_value
    private:
        int _num = 0;
        bool _initialised = false;
        std::vector<CpuTimes> _previous;
        float _usage = 0;


        CpuTimes readLine(const std::string& line) const;
    public:
        //https://stackoverflow.com/questions/3017162/how-to-get-total-cpu-usage-in-linux-using-c
        void update() override;

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
        void update() override;
        std::string get_name() override {return "CPU name";}
        int get_height() override {return 1;}

        ModuleValue get_value() override {return _cpuname;}
        std::string get_string() override {return _cpuname;}
        bool is_percentage() override {return false;}
};


#endif
