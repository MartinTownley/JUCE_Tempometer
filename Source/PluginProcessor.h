/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "BTrack.h"

#define LAUNCH_LATER_ID "launchLaterButton"
#define LAUNCH_LATER_NAME "LaunchLaterButton"

#define LAUNCH_NOW_ID "launchNowButton"
#define LAUNCH_NOW_NAME "LaunchNowButton"

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

    void runBeatTracker(AudioBuffer<float>& buffer);
    
    double getTimeGrab();
    
    AudioProcessorValueTreeState& getAPVTS() {return mAPVTS;};
                       
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
    
    //RunState enum for the beat tracker:
    enum class RunState
    {
        Running,
        Stopped
    };
    // RunState instance:
    RunState runState; //default is stopped
    
    //std::vector<double> timez;
    //=============================
    
    AudioProcessorValueTreeState mAPVTS;
    
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BpmometerAudioProcessor)
};
