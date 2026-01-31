
#ifndef INCLUDED_OSMODULE_HPP
    #define INCLUDED_OSMODULE_HPP

#include "IModule.hpp"
#include <string>
#include <sys/utsname.h>
#include <unistd.h>
#include <pwd.h>

class OsModule : public Krell::IModule<std::string> { //we have to declare what the type T is for the get_value
    private:
        std::string _osname = "Unknown";
    public:
        void update() override { //https://www.ibm.com/docs/en/zvm/7.3.0?topic=descriptions-uname-display-current-operating-system-name
            struct utsname buf;

            uname(&buf);
            _osname = buf.sysname;
        }
        std::string get_name() override {return "Os Name";}
        int get_height() override {return 1;}

        std::string get_value() override {return _osname;}
        std::string get_string() override {return _osname;}
        bool is_percentage() override {return false;}
};

#endif
