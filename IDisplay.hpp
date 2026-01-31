
#ifndef INCLUDED_IDISPLAY_HPP
    #define INCLUDED_IDISPLAY_HPP

#include <vector>
#include <memory>
#include <string>
#include "IModule.hpp"

namespace Krell {
class IDisplay
{
    public:

        virtual ~IDisplay() = default;
        
        virtual void run(const std::vector<std::shared_ptr<Imodule>>& modules) = 0;

        // handle window lifecycle
        class Window {
            public:
                Window() {}
                virtual ~Window() = default;

                virtual void create() = 0;
                
                virtual void destroy() = 0;                
   
                // handle input events (keyboard, mouse, window events)
                //virtual void handleEvents() = 0;
        };


        // below old stuff
        //place to store all the Imodule pointer to update all at once
        //virtual void update(const std::vector<std::shared_ptr<Imodule>>& modules) = 0;

        //da display name
        //virtual std::string getName() const = 0;

        //handle events? (maybe), like to change displays
        //virtual void handleEvents() = 0;
};

}

#endif
