/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

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
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    float _theTempo;
    
    BpmometerAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BpmometerAudioProcessorEditor)
};
