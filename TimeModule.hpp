
#ifndef INCLUDED_TIMEMODULE_HPP
    #define INCLUDED_TIMEMODULE_HPP

#include "IModule.hpp"
#include <chrono>
#include <string>


class TimeModule : public Krell::IModule<std::string> { //we have to declare what the type T is for the get_value
    private:
        std::string _time;
    public:
        void update() override {
            auto now = std::chrono::system_clock::now();
            std::time_t t = std::chrono::system_clock::to_time_t(now);
            char buf[64];
            std::strftime(buf, sizeof(buf), "%H:%M:%S", std::localtime(&t));
            _time = buf;
        }

        std::string get_name() override { return "Time"; }
        int get_height() override { return 1; }

        std::string get_value() override {return _time;}
        std::string get_string() override {return _time;}


};



#endif
