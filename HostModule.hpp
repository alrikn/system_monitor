
#ifndef INCLUDED_HOSTMODULE_HPP
    #define INCLUDED_HOSTMODULE_HPP

#include "IModule.hpp"
#include <string>
#include <unistd.h>


class HostModule : public Krell::IModule<std::string> { //we have to declare what the type T is for the get_value
    private:
        std::string _hostname = "Unknown";
    public:
        void update() override { //https://www.ibm.com/docs/en/zos/2.5.0?topic=calls-gethostname
            char buf[256];

            gethostname(buf, sizeof(buf));
            _hostname = buf;
        }
        std::string get_name() override {return "Hostname";}
        int get_height() override {return 1;}

        std::string get_value() override {return _hostname;}
        std::string get_string() override {return _hostname;}
        bool is_percentage() override {return false;}
};

#endif
