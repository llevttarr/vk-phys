#ifndef WRENDERER_HPP
#define WRENDERER_HPP

#include "rdevice.hpp"
#include "rswapchain.hpp"

class WRenderer{
private:

public:
    virtual void init(RDevice&,RSwapchain&);
};

class UIRenderer: public WRenderer{

};
class SceneRenderer: public WRenderer{

};

#endif // WRENDERER_HPP