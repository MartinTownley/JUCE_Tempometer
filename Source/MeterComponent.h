/*
  ==============================================================================

    MeterComponent.h
    Created: 22 Jul 2020 3:49:43pm
    Author:  sierra

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


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
    MeterComponent();
    ~MeterComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    AltLookAndFeel altLookAndFeel;
    
    Slider indicatorSlider;
    
    
    
    const Colour customBrown {0xff523f43};
    
    TextButton header;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterComponent)
};
