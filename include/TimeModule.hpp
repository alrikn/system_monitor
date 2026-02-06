
#ifndef INCLUDED_TIMEMODULE_HPP
    #define INCLUDED_TIMEMODULE_HPP

#include "IModule.hpp"
#include <chrono>
#include <string>


class TimeModule : public Krell::IModule { //we have to declare what the type T is for the get_value
    private:
        std::string _time = "";
    public:
        void update() override;

        std::string get_name() override { return "Time"; }
        int get_height() override { return 1; }

        ModuleValue get_value() override {return _time;}
        std::string get_string() override {return _time;}
        bool is_percentage() override {return false;}

};



#endif
