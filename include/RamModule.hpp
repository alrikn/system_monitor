
#ifndef INCLUDED_RAMMODULE_HPP
    #define INCLUDED_RAMMODULE_HPP

#include "IModule.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <sys/utsname.h>
#include <unistd.h>
#include <pwd.h>

class RamModule : public Krell::IModule {
    private:
        float _usage = 0.0f;
    public:
        void update() override;
        std::string get_name() override {return "Ram Usage";}
        int get_height() override {return 2;}

        ModuleValue get_value() override {return _usage;}
        std::string get_string() override {return std::to_string(_usage).append(" %");}
        bool is_percentage() override {return true;}
};

#endif
