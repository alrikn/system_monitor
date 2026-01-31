
#ifndef INCLUDED_USERMODULE_HPP
    #define INCLUDED_USERMODULE_HPP

#include "IModule.hpp"
#include <string>
#include <unistd.h>
#include <pwd.h>

class UserModule : public Krell::IModule<std::string> { //we have to declare what the type T is for the get_value
    private:
        std::string _username;
    public:
        void update() override {
            _username = getpwuid(geteuid())->pw_name;
        }
        std::string get_name() override {return "Username";}
        int get_height() override {return 1;}

        std::string get_value() override {return _username;}
        std::string get_string() override {return _username;}
        bool is_percentage() override {return false;}
};

#endif
