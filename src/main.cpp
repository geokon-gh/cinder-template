
#include <stdlib.h>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class Template : public App {
public:
    void setup() override;
    void update() override;
    void draw() override;
    void cleanup() override;
    
};

void Template::setup()
{
}
void Template::update()
{
}
void Template::draw()
{
}
void Template::cleanup()
{
}
CINDER_APP( Template , RendererGl)
