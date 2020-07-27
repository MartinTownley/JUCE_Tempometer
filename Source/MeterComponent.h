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

private:
    
    AltLookAndFeel altLookAndFeel;
    
    Slider indicatorSlider;
    
    Path p;
    
    const Colour customBrown {0xff523f43};
    
    TextButton header;
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BpmometerAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterComponent)
};
