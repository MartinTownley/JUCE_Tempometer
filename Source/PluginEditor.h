/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MeterComponent.h"
#include "CircularBuffer.h"

//==============================================================================
/**
*/
class BpmometerAudioProcessorEditor  : public AudioProcessorEditor,
public Timer
{
public:
    BpmometerAudioProcessorEditor (BpmometerAudioProcessor&);
    ~BpmometerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void timerCallback() override;
    
private:
     /** Tabbed layout */
    TabbedComponent myTabs;
    
    /** Meter Component instance */
    MeterComponent meterComp;
    
    /** Timer callback rate Hz */
    int timerValue;
    
    BpmometerAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BpmometerAudioProcessorEditor)
};
