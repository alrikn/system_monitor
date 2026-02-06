
#ifndef INCLUDED_DATEMODULE_HPP
    #define INCLUDED_DATEMODULE_HPP

#include "IModule.hpp"
#include <chrono>
#include <string>
#include <ctime>


class DateModule : public Krell::IModule { //we have to declare what the type T is for the get_value
    private:
        std::string _date = "";
    public:
        //https://stackoverflow.com/questions/27934034/get-current-time-in-mm-dd-yyyy-in-c
        void update() override;

        std::string get_name() override { return "Date"; }
        int get_height() override { return 1; }

        ModuleValue get_value() override {return _date;}
        std::string get_string() override {return _date;}
        bool is_percentage() override {return false;}

};


#endif
