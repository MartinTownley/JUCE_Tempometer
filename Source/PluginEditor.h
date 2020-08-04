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
    
    //void calculateInterval();
    
    void calculateTempo();
    
    //float smoothTempo(float _tempo); //stays as float here so that it can animate smoothly. Change the value to int in the metercomponent.
    
    //float singlePoleFilter (const float tempo, float prev_val);
    
    
private:
    
    
    
    TabbedComponent myTabs;
    
    MeterComponent meterComp;
    
    //SmoothedValue<float, ValueSmoothingTypes::Linear> smoothed;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    int timerValue;
    
    
    float theTempo;
    
    double beatInterval;
    
    double previousBeatTime;
    
    // Create a circular buffer for averaging:
    CircularBuffer tempoBuffer;
    
    int tempoBufferSize;
    //int initialSize;
    
    // This increments as the buffer gets filled with non zeros, and the sum is divided by this value to exclude zero values from the averaging.
    int bufferCounter;
    
    double sum;
    
    BpmometerAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BpmometerAudioProcessorEditor)
};
