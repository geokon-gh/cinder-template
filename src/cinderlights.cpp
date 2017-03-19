#include <chrono>
#include <iostream>
#include <stdlib.h>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "CinderImGui.h"

using namespace ci;
using namespace ci::app;

class LightControl : public App {
  public:
	void setup() override;
	void update() override;
	void draw() override;
    void cleanup() override;
    
    void keyDown( KeyEvent key_event) override;
};

void LightControl::setup()
{
    ui::initialize();
}
void LightControl::update()
{
    static bool showTestWindow = false;
	static bool showWindowWithMenu = false;
	
	// a few scoped object like ScopedWindow allow to quickly
	// push and pop states
	if( showWindowWithMenu ) {
		ui::ScopedWindow window( "Window with Menu", ImGuiWindowFlags_MenuBar );
		
		// setup the window menu bar
		if( ui::BeginMenuBar() ){
			if( ui::BeginMenu( "Edit" ) ){
				ui::MenuItem( "Copy" );
				ui::MenuItem( "Cut" );
				ui::MenuItem( "Paste" );
				ui::EndMenu();
			}
			ui::EndMenuBar();
		}
		
		// add some text
		ui::Text( "Window Content" );
	}
	
	// create the main menu bar
	{
		ui::ScopedMainMenuBar menuBar;
		
		// add a file menu
		if( ui::BeginMenu( "File" ) ){
			ui::MenuItem( "Open" );
			ui::MenuItem( "Save" );
			ui::MenuItem( "Save As" );
			ui::EndMenu();
		}
		
		// and a view menu
		if( ui::BeginMenu( "View" ) ){
			ui::MenuItem( "TestWindow", nullptr, &showTestWindow );
			ui::MenuItem( "Window with Menu", nullptr, &showWindowWithMenu );
			ui::EndMenu();
		}
	}
	
	if( showTestWindow ){
		// have a look at this function for more examples
		ui::ShowTestWindow();
	}
}
void LightControl::draw()
{
	static float gray = 0.65f;
	gl::clear( ColorA::gray( gray ) );
	
	// any widget added without a window will be added
	// in the default "debug" window
	ui::DragFloat( "Gray", &gray, 0.01f, 0.0f, 1.0f );    
}
void LightControl::cleanup()
{
}

void LightControl::keyDown( KeyEvent key_event)
{
    if( key_event.getCode() == KeyEvent::KEY_q)
    {
        quit();
    }
}
CINDER_APP( LightControl , RendererGl)
