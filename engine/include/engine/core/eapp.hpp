#ifndef EAPP_HPP
#define EAPP_HPP

#include <vector>
#include <memory>
#include <optional>

#include "window.hpp"

class App{
public:
    App(const App&) = delete;
    App& operator=(const App&) = delete;
    App(const App&&) = delete;
    App& operator=(const App&&) = delete;
    
    static App& getInstance(){
        static App instance;
        return instance;
    }
    std::optional<Window&> getCurrWindow(){ 
        if (currWindowI >= windows.size()){
            return std::nullopt;
        }
        return windows[currWindowI];
    }
    bool run();
private:
    App(){init();}
    ~App(){destroy();}
    void init();
    void destroy();
    std::vector<Window&> windows;
    int8_t currWindowI;
};

#endif // EAPP_HPP