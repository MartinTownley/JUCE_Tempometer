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

    /** Run the beat-tracking code
     * @param buffer takes a reference to the audio buffer
     */
    void runBeatTracker(AudioBuffer<float>& buffer);
    
    /** Returns the timeGrab private member variable */
    double getTimeGrab();
    
    /** Changes the RunState enum */
    void runStateChanged();
    
private:
    
    /**  How many equal parts into which to split the audio buffer */
    int division;
    
    /** The size of each sub-section of the audio buffer (dependent on the division variable) */
    int chunkSize;
    
    /** To keep track of how many beats have occurred */
    int beatCount;
    
    /** The hop size for initialising the BTrack object */
    int myHop = 32;
    
    /** The sample rate */
    int sr = 44100;
    
    /** Required for BTrack's getBeatTimeInSeconds() function */
    long frameCount;
    
    /** Expresses the time that a beat occurs */
    double timeGrab;
    
    /** Update the timeGrab value
     * @param _value the value with which to update the timeGrab
     */
     void updateBeatTime(double _value);
    
    /** BTrack instance */
    BTrack tracker { myHop, 128 };
    
    /** Temprary buffer for copying the audio buffer */
    AudioBuffer<double> tempBuffer;
    
    /** Toggles whethere the BTrack is running or stopped */
    enum class RunState
    {
        Running,
        Stopped
    };
    
    /** Runstate instance */
    RunState runState;
    
    //=============================
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BpmometerAudioProcessor)
};
