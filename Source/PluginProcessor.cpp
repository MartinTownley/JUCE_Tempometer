/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
BpmometerAudioProcessor::BpmometerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

BpmometerAudioProcessor::~BpmometerAudioProcessor()
{
}

//==============================================================================




//==============================================================================
const String BpmometerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BpmometerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BpmometerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BpmometerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BpmometerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BpmometerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BpmometerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BpmometerAudioProcessor::setCurrentProgram (int index)
{
}

const String BpmometerAudioProcessor::getProgramName (int index)
{
    return {};
}

void BpmometerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BpmometerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    beatCount = 0;
    
    frameCount = 0;
    
    division = 4;
    
    chunkSize = samplesPerBlock / division;
    //this gives us 128sample chunks, assuming bufferSize is 512.
    
    tempBuffer.setSize(1, chunkSize);// 512
    
    runState = RunState::Stopped;
}

void BpmometerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BpmometerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BpmometerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    const auto numSamples = buffer.getNumSamples();
    
    tempBuffer.clear();
    
    runBeatTracker( buffer );
    
}

void BpmometerAudioProcessor::runBeatTracker(AudioBuffer<float>& buffer)
{
   
    
    if (runState == RunState::Running)
    {
        
        for (int i = 0; i < division; ++i) // [1] An outer loop is created, with iterations corresponding to the division of the audio buffer (e.g., to split the buffer into equal 128 length chunks, the division would be 4 (assuming buffer size is 512) ).
        {
        
            auto* buffReader = buffer.getReadPointer (0, (i * chunkSize) ); // [2] Inside the outer loop, get a read pointer, “buffReader” into the audio buffer, and advance the start sample of the read pointer by the chunkSize on each iteration (the chunkSize is the audio buffer size divided by the division, e.g. 512 / 4 = 128).
        
            auto* tempBuffWriter = tempBuffer.getWritePointer (0, 0); // [3] Get a write pointer, “tempBuffWriter”, to prepare to write into the temporary buffer. This always starts at zero, as the temporary buffer is the same length as the chunkSize, so gets overwritten at each iteration, subsequent to processing.
        
            for (int samp = 0; samp < chunkSize; ++samp)
            {
                tempBuffWriter[samp] = buffReader[samp]; // [4] In a nested loop, the samples within the chunk of audio are iterated, and their data copied from the audio buffer to the temporary buffer.
            }
        
            tracker.processAudioFrame (tempBuffer.getWritePointer (0,0) ); // [5] Having exited the inner loop, but still in the outer loop, the temporary buffer is processed by the beat tracker. Since this is still inside the outer loop, this will happen multiple times per audio buffer (in this case, four).
        
            
            if (tracker.beatDueInCurrentFrame() == true)
            {
                beatCount ++;
                
                updateBeatTime (tracker.getBeatTimeInSeconds (frameCount,
                                                              myHop,
                                                              sr) ); // [6] A BTrack function is called to check if a beat is due in the current frame. If it is, the beat time is reported by the BTrack, and this value is used elsewhere to calculate the tempo.
                
                
            }
            frameCount ++; // [7] The frameCount is advanced – this value is used as an argument for the BTrack’s “getBeatTimeInSeconds()” function in the previous step, so it must be updated after each audio frame is processed.
            

        }
        
    } //end of if statement
}

void BpmometerAudioProcessor::updateBeatTime(double _value)
{
    timeGrab = _value;
}



double BpmometerAudioProcessor::getTimeGrab()
{
    return timeGrab;
}

//==============================================================================
bool BpmometerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BpmometerAudioProcessor::createEditor()
{
    return new BpmometerAudioProcessorEditor (*this);
}

//==============================================================================
void BpmometerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BpmometerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void BpmometerAudioProcessor::runStateChanged()
{
    if (runState == RunState::Stopped)
    {
        runState = RunState::Running;
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BpmometerAudioProcessor();
}
