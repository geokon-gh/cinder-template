#include <vector>
#include "cinder/Filter.h"

class GaussianWave
{
public:
    GaussianWave();
    void SetLEDs(int number_of_LEDs, double shift = 0.0);
    
    void SetTime(double time);
    float GetValue(int index);
    
    void Fade(bool on_off);
    void On(double time);
    void Off(double time);
    bool IsOn(){return m_on;}
    
    void SetEasingTime(float easing_time){m_easing_time = easing_time;}
    void SetWidth(float width){m_width = width;}
    
    float   m_width;
    float   m_time_of_one_loop;
private:
    void Resize(int number_ofLEDs);
    int m_number_of_LEDs;
    std::vector<float> m_led_values;
    double m_current_time;
    double m_on_time;
    double m_off_time;
    
    bool m_on;
    bool m_fade;
    bool m_loop_back;
    
    float m_easing_factor;
    float m_easing_time;
    float m_max_easing_factor;
    
    cinder::FilterGaussian m_gaussian_filter;
    
};
