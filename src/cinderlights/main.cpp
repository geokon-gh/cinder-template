#include <chrono>
#include <iostream>
#include <stdlib.h>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "CinderImGui.h"
// #include "CinderAsio.h" // includes ASIO (already part of Cinder!!)
#include "UdpClient.h" // part of Cinder-Asio

//for the gaussian
#include "cinder/Filter.h"
#include "GaussianWave.h"


using namespace ci;
using namespace ci::app;

class LightControl : public App {
public:
    void setup() override;
    void update() override;
    void draw() override;
    void cleanup() override;
    
    void keyDown( KeyEvent key_event) override;
    
    // ASIO
    UdpClientRef				m_client;    // the thing that connects
    std::string					m_host;     // URL/IP
    int32_t						m_port;    // Port number
    // on connection the client generates a session through this callback
    void						onConnect( UdpSessionRef session );
    UdpSessionRef				m_session;
    
    void						onError( std::string err, size_t bytesTransferred );
    void						onWrite( size_t bytesTransferred );
    
    void connectToESP();
    void writeToESP();
    int                    m_number_of_lights;
    Color                  m_led_color;
    std::string            m_ESP_IP;
    //    std::string            m_previous_ESP_IP;
    bool                   m_sawtooth_brightness;
    
    //gaussian stuff
    GaussianWave m_wave;
};

void LightControl::setup()
{
    m_number_of_lights = 288;
    std::cout << "starting setup" << std::endl;
    m_led_color = Color( 0.1f,0.2f,0.5f );
    ui::initialize();
    
    m_client = UdpClient::create( io_service() );
    // io_service is from the Base App
    // "ci::App already has one that it polls on update, so we'll use that."
    
    // set up the m_client call backs (what to do when it connects or doesnt)
    // either takes a function or a class method address + object pointer 
    // class-method + object-pointer
    m_client->connectConnectEventHandler(&LightControl::onConnect,this); 
    m_client->connectErrorEventHandler(&LightControl::onError,this);
    // function/lambda
    m_client->connectResolveEventHandler( [ & ]() 
					  {
					      std::cout << "Endpoint resolved" << std::endl;
					  } );
    
    m_ESP_IP = "192.168.1.3";
    connectToESP();
    
    m_wave.On(getElapsedSeconds());
    m_wave.SetLEDs(m_number_of_lights);
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
	    ui::MenuItem( "Sawtooth Brightness", nullptr, &m_sawtooth_brightness );
	    ui::MenuItem( "Window with Menu", nullptr, &showWindowWithMenu );
	    ui::EndMenu();
	}
    }
	
    if( showTestWindow ){
	// have a look at this function for more examples
	ui::ShowTestWindow();
    }
}
float gaussian_forwarder(void* p_gaussian_wave, int index) {
    return static_cast<GaussianWave*>(p_gaussian_wave)->GetValue(index);
}
void LightControl::draw()
{
    //     std::cout << std::endl <<
    //         "float - r:" << m_led_color.get(CM_RGB).x <<
    //         " g:" << m_led_color.get(CM_RGB).y << 
    //         " b:" << m_led_color.get(CM_RGB).z << std::endl;
    //     auto int_gray = Color8u(m_led_color);
    //     unsigned char* mem_gray = (unsigned char*)&int_gray;
    //     std::cout << 
    //         "int - r:" << int_gray.get(CM_RGB).x <<
    //         " g:" << int_gray.get(CM_RGB).y << 
    //         " b:" << int_gray.get(CM_RGB).z << std::endl <<
    //         " whole:" << static_cast<int>(mem_gray[0]) <<" "<< static_cast<int>(mem_gray[1]) << " " << static_cast<int>(mem_gray[2]) << std::endl;
    gl::clear( m_led_color );
	
    // any widget added without a window will be added
    // in the default "debug" window
    //     if( ui::InputText( "ESP's IP", &m_ESP_IP, ImGuiInputTextFlags_EnterReturnsTrue) )
    //     {
    //         connectToESP();
    //     }
    //     if ( m_session && m_session->getSocket()->is_open() ) 
    //     {
    //         ui::PushStyleColor(ImGuiCol_Button, ImColor(0.0f, 1.0f, 0.0f));
    //         ui::PushStyleColor(ImGuiCol_ButtonHovered,ImColor(0.0f, 1.0f, 0.0f));
    //         ui::PushStyleColor(ImGuiCol_ButtonActive,ImColor(0.0f, 1.0f, 0.0f));
    //         ui::Button("Connected");
    //         ui::PopStyleColor(3);
    //     }
    //     else
    //     {
    //         ui::PushStyleColor(ImGuiCol_Button, ImColor(1.0f, 0.0f, 0.0f));
    //         ui::PushStyleColor(ImGuiCol_ButtonHovered,ImColor(1.0f, 0.0f, 0.0f));
    //         ui::PushStyleColor(ImGuiCol_ButtonActive,ImColor(1.0f, 0.0f, 0.0f));
    //         ui::Button("Not Connected");
    //         ui::PopStyleColor(3);
    //     }
    auto on_off = m_wave.IsOn();
    if(ui::Checkbox("", &on_off))
	{
	    if(on_off)
		m_wave.On(getElapsedSeconds());
	    else
		m_wave.Off(getElapsedSeconds());
	}
    
    m_wave.SetTime(getElapsedSeconds());
    if(ui::SliderInt( "Number Of Lights", &m_number_of_lights, 0, 288 ))
	{
	    m_wave.SetLEDs(m_number_of_lights);
	}
    if(ui::SliderFloat( "Width of Gaussian", &m_wave.m_width, 0.0f, 1.0f ))
	{
	    m_wave.SetLEDs(m_number_of_lights);
	}
    ui::PlotLines(
		  "just a Guassian",
		  gaussian_forwarder,
		  &m_wave,
		  m_number_of_lights,
		  0,
		  NULL,
		  0.0f,
		  1.0f,
		  ImVec2(0,80));
    ui::PlotHistogram(
		      "just a Guassian",
		      gaussian_forwarder,
		      &m_wave,
		      m_number_of_lights,
		      0,
		      NULL,
		      0.0f,
		      1.0f,
		      ImVec2(0,80));
    //    ui::ColorEdit3("Color Editor 1", &gray);
    ui::ColorPicker3("Color Picker", (float*)&m_led_color);
    //    ui::ColorEditMode();
    writeToESP();
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

void LightControl::onConnect(UdpSessionRef session)
{
    std::cout << "UDP Client on" << std::endl;
    m_session = session;
    m_session->connectErrorEventHandler(&LightControl::onError, this);
    m_session->connectWriteEventHandler(&LightControl::onWrite, this);
}
void LightControl::onError( std::string err, size_t bytesTransferred )
{
    std::cout << "EEROROEOPWRU error" << std::endl;
}
void LightControl::onWrite( size_t bytesTransferred )
{
    std::cout << "session writing";
}
void LightControl::connectToESP()
{
    std::cout << std::endl << "Trying to connect to" << m_ESP_IP << std::endl;
    m_client->connect(m_ESP_IP, (uint16_t)6969 );
}
void LightControl::writeToESP()
{
    auto sawtooth_brightness_factor = 1.0f;
    if(m_sawtooth_brightness)
	{
	    const auto cycle_time = 5.0f; // seconds
	    const auto elapsed_time = 1.0f/cycle_time * getElapsedSeconds();
	    sawtooth_brightness_factor = elapsed_time - trunc(elapsed_time);
	}
    
    auto buffer_color = std::vector<Color8u>();
    //m_number_of_lights,sawtooth_brightness_factor*Color8u(m_led_color));
    for(int LED_index = 0; LED_index != m_number_of_lights; ++LED_index)
	{
	    buffer_color.push_back(m_led_color*sawtooth_brightness_factor * m_wave.GetValue(LED_index));
	    //std::cout << "index:" << LED_index << " value: " << m_wave.GetValue(LED_index) << std::endl;
	}
    if ( m_session && m_session->getSocket()->is_open() ) {
        std::cout << "sending.." ;
        // Write data is packaged as a ci::Buffer. This allows 
        // you to send any kind of data. Because it's more common to
        // work with strings, the session object has static convenience 
        // methods for converting between std::string and ci::Buffer.
        m_session->write( 
			 Buffer::create(
					buffer_color.data(),
					m_number_of_lights*sizeof(Color8u)));
    }
    else
	{
	    std::cerr << " there is some problem communicating with the ESP " << std::endl;
	}
}

CINDER_APP( LightControl , RendererGl)
