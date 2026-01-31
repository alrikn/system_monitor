
#ifndef INCLUDED_TIMEMODULE_HPP
    #define INCLUDED_TIMEMODULE_HPP

#include "Imodule.hpp"
#include <chrono>

class TimeModule : public IModule {
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

        std::string name() const override { return "Time"; }
        int height() const override { return 2; }

        std::vector<std::string> lines() const override {
            return { _time };
        }


};



#endif
