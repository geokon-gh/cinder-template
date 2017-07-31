#include "GaussianWave.h"
#include "cinder/Easing.h"

#include <iostream>
#include <vector>
using namespace std;
using namespace cinder;

GaussianWave::GaussianWave() :
m_width(.5f),
m_time_of_one_loop(5.0),
m_number_of_LEDs(0),
m_led_values(std::vector<float>(0)),
m_current_time(0.0),
m_on_time(0.0),
m_off_time(0.0),
m_on(false),
m_easing_time(10.0f),
m_max_easing_factor(1.0f),
m_gaussian_filter()
{}

void GaussianWave::SetLEDs(int number_of_LEDs, double shift)
{
//        Resize(number_of_LEDs);
    m_led_values.clear();
    m_number_of_LEDs = number_of_LEDs;
    for(int index = 0; index !=m_number_of_LEDs ;++index)
    {
        auto sampling_point = index*2.0/m_number_of_LEDs;
        m_led_values.push_back(m_gaussian_filter((sampling_point-1.0+shift)/m_width));
    }
}


void GaussianWave::SetTime(double time)
{
    m_current_time = time;
    if(m_on)
    {
        const auto time_since_on = time - m_on_time;
        if(time_since_on < m_easing_time)
        m_easing_factor = easeOutAtan(time_since_on/ m_easing_time);
    }
    else
    {
        const auto time_since_on =  m_easing_time - (time - m_off_time);
        if(time_since_on <  m_easing_time)
        m_easing_factor = m_max_easing_factor *easeInAtan( time_since_on/ m_easing_time);
    }
}
float GaussianWave::GetValue(int index)
{
    SetLEDs(
        m_number_of_LEDs,
        m_current_time-m_time_of_one_loop*floor(m_current_time/m_time_of_one_loop) - m_time_of_one_loop/2.0);
    if(index > m_number_of_LEDs)
    {
        std::cerr << "You are trying to get a value off the end of the vector!" << index << std::endl;
        return m_easing_factor*m_led_values[m_number_of_LEDs];
    }
    else
    {
        return m_easing_factor*m_led_values[index];
    }
}

void GaussianWave::Fade(bool fade)
{
    m_fade = fade;
}
void GaussianWave::On(double time)
{
    m_on = true;
    m_on_time = time;
    m_off_time = 0.0f;
}
void GaussianWave::Off(double time)
{
    m_on = false;
    m_on_time = 0.0f;
    m_off_time = time;
    m_max_easing_factor = m_easing_factor;
}

void GaussianWave::Resize(int number_of_LEDs)
{
    m_number_of_LEDs = number_of_LEDs;
}
