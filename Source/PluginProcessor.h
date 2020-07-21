/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "BTrack.h"

//==============================================================================
/**
*/
class BpmometerAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    BpmometerAudioProcessor();
    ~BpmometerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;
    
    void calculateBPM (long frame);
    
    float getTheTempo() {
        return theTempo;
    }

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //void calculateBPM (

    
                       
private:
    
    int beatCount;
    
    int myHop = 256;
    
    int sr = 44100;
    
    long frameCount;
    
    float previousBeatTime;
    
    float theTempo;
    
    BTrack tracker { myHop };
    
    AudioBuffer<double> tempBuffer;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BpmometerAudioProcessor)
};
