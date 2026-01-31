
#ifndef INCLUDED_CPUMODULE_HPP
    #define INCLUDED_CPUMODULE_HPP

#include "Imodule.hpp"
#include <iostream>

class CpuModule : public IModule
{
    private:
        struct CpuTimes {
            long idle;
            long total;
        };

        CpuTimes readLine(const std::string& line) const;

        std::vector<CpuTimes> _previous;
        std::vector<float> _usage;
        bool _initialized;
    protected:
    public:
        CpuModule();

        void update() override;
        std::string name() const override;
        int height() const override;
        std::vector<std::string> lines() const override;
};


#endif
