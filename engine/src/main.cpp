
#include "eapp.hpp"

int main(int argc, char* argv[]) {
    App& app = App::getInstance();
    while (true){
        bool run = app.run();
        if (!run){ break; }
    }
    return 0;
}
