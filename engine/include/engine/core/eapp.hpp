#ifndef EAPP_HPP
#define EAPP_HPP

#include <vector>
#include <memory>
#include <stdexcept>

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
    /*Window& getCurrWindow(){ 
        if (currWindowIdx >= windows.size()){
            throw std::runtime_error("invalid currWindowIdx");
        }
        return windows[currWindowIdx];
    }*/
    void addWindow(Window&& w){
        windows.push_back(w);
    }
    bool run();
private:
    App(){init();}
    ~App(){destroy();}
    void init();
    void destroy();
    std::vector<Window> windows;
    // int8_t currWindowIdx;
};

#endif // EAPP_HPP