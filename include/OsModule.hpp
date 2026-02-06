
#ifndef INCLUDED_OSMODULE_HPP
    #define INCLUDED_OSMODULE_HPP

#include "IModule.hpp"
#include <string>
#include <sys/utsname.h>
#include <unistd.h>
#include <pwd.h>

class OsModule : public Krell::IModule { //we have to declare what the type T is for the get_value
    private:
        std::string _osname = "Unknown";
    public:
        void update() override;
        std::string get_name() override {return "Os Name";}
        int get_height() override {return 1;}

        ModuleValue get_value() override {return _osname;}
        std::string get_string() override {return _osname;}
        bool is_percentage() override {return false;}
};

#endif
