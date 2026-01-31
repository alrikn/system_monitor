//
//
// This is the baseline for making classes that fetch and update values to be able to display it
//
//


#ifndef INCLUDED_IMODULE_HPP
    #define INCLUDED_IMODULE_HPP


#include <string>
#include <variant>
#include <vector>

using ModuleValue = std::variant<float, std::string, int>;

namespace Krell {

class IModule
{
    protected:
        bool display = true;
    public:
        virtual ~IModule() = default;
        virtual void update() = 0;
        virtual ModuleValue get_value() = 0;
        virtual std::string get_string() = 0;
        virtual std::string get_name() = 0;
        virtual int get_height() = 0;
        virtual bool is_percentage() = 0;
        bool get_display() {return display;}
        void set_display(bool val) {display = val;}
};

}  // namespace Krell

#endif