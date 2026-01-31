
#ifndef INCLUDED_KERNELMODULE_HPP
    #define INCLUDED_KERNELMODULE_HPP

#include "IModule.hpp"
#include <string>
#include <sys/utsname.h>
#include <unistd.h>
#include <pwd.h>

class KernelModule : public Krell::IModule<std::string> { //we have to declare what the type T is for the get_value
    private:
        std::string _release;
    public:
        void update() override { //https://lindevs.com/get-linux-kernel-version-using-cpp
            struct utsname buf;

            uname(&buf);
            _release = buf.release;
        }
        std::string get_name() override {return "Kernel Version";}
        int get_height() override {return 1;}

        std::string get_value() override {return _release;}
        std::string get_string() override {return _release;}
        bool is_percentage() override {return false;}
};

#endif
