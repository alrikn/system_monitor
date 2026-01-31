//
//
// This is the baseline for making classes that fetch and update values to be able to display it
//
//


#ifndef INCLUDED_IMODULE_HPP
    #define INCLUDED_IMODULE_HPP


#include <string>
#include <vector>
class Imodule
{
    protected:
    public:
        virtual ~Imodule() = default;
        virtual void update() = 0;
        //title of the what is being returned
        virtual std::string name() const = 0;
        //how many line are gonna be returned by the lines func (title included)
        virtual int height() const = 0;

        //good for ncurses
        virtual std::vector<std::string> lines() const = 0;
};

#endif
