/*
  ==============================================================================

    MeterComponent.h
    Created: 22 Jul 2020 3:49:43pm
    Author:  sierra

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


class AltLookAndFeel : public juce::LookAndFeel_V4
{
public:
    AltLookAndFeel ()
    {
        setColour (juce::Slider::thumbColourId, juce::Colours::red);
    }
};
//==============================================================================
/*
*/
class MeterComponent    : public Component
{
public:
    MeterComponent(BpmometerAudioProcessor&);
    ~MeterComponent();

    void paint (Graphics&) override;
    
    void paintCircle (int radius);
    void resized() override;
    
    void passBPM(float bpmValue);
    
    void setSliderString(float value);
    
    void initSliderValues();
    
    void tempoChanged();
    
    int getRefreshRate(){
        return refreshRate;
    }
    
     

private:
    
    const Colour customBrown {0xff523f43};
   
    AltLookAndFeel altLookAndFeel;
    
    Slider indicatorSlider;
    
    double previousBeatTime;
    
    double beatInterval;
    
    //float smoothNext;
    
    SmoothedValue<float> smoothTempo;
                
    //float _theTempo; //the value displayed and given to the slider.
    
    //float roundedDown;
    
    int centralBPM; // this is the 12 o'clock BPM.
    
    int refreshRate { 60 };
    
    int bpmRange; //range for the slider, +/- the target.
    
    int upperLimit;
    
    int lowerLimit;
    
    TextButton header;
    
    std::string centralString;
    
    std::string sliderString;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BpmometerAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterComponent)
};
