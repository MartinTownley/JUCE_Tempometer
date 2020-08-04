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
    
    
    void calculateTempo ();
    
    // Getter function
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

    
    
    double getTimeGrab();
    
                       
private:
    
    //void calculateInterval (long frame);
    
    int division;
    
    int chunkSize;
    
    int beatCount;
    
    int myHop = 64;
    
    //int trackBufferSize = myHop * 2;
    
    int sr = 44100;
    
    long frameCount;
    
    //float previousBeatTime;
    
    float beatInterval;
    
    float theTempo;
    
    double timeGrab;
    
    void updateBeatTime(double _value);
    
    BTrack tracker { myHop, 128 };
    
    AudioBuffer<double> tempBuffer;
    
    //std::vector<double> timez;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BpmometerAudioProcessor)
};
