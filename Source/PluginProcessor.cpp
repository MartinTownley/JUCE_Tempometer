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
                       ),
mAPVTS(*this, nullptr, "PARAMETERS",
       createParameterLayout() )
#endif
{
}

BpmometerAudioProcessor::~BpmometerAudioProcessor()
{
}

//==============================================================================

AudioProcessorValueTreeState::ParameterLayout BpmometerAudioProcessor::createParameterLayout()
{
    //Create parameterlayout gets used as an argument for treeState at the top of this file (scroll up)
    
    
    // Making a vector of audioParameter unique pointers:
    std::vector <std::unique_ptr <RangedAudioParameter> > params;
    
//    auto launchLaterButtonParam = std::make_unique<AudioParameterBool> (LAUNCH_LATER_ID,
//                                                                  LAUNCH_LATER_NAME,
//                                                                  false);
    
    auto launchNowButtonParam = std::make_unique<AudioParameterBool> (LAUNCH_NOW_ID,
                                                                        LAUNCH_NOW_NAME,
                                                                        false);
    
    //params.push_back (std::move (launchLaterButtonParam));
    params.push_back (std::move (launchNowButtonParam));
    
    return { params.begin(), params.end() };
    
}


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
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    beatCount = 0;
    
    //Samples per block can be changed in the settings at runtime.;;p
//    tempBuffer.setSize(1, samplesPerBlock);
    
    frameCount = 0;
    
    division = 4;
    
    chunkSize = samplesPerBlock / division;
    //this gives us 128sample chunks, assuming bufferSize is 512.
    
    //myHop = chunkSize / 2; //hop size 64
    
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
    
    //        buffer.clear (i, 0, buffer.getNumSamples());
    
    //====================
    
    // 1. Clear tempbuffer
    
    tempBuffer.clear();
    
    runBeatTracker( buffer );
    
    
    
}

void BpmometerAudioProcessor::runBeatTracker(AudioBuffer<float>& buffer)
{
   
    
    if (runState == RunState::Running)
    {
        
        for (int i = 0; i < division; ++i) // [1]
        {
        
            auto* buffReader = buffer.getReadPointer (0, (i * chunkSize) ); // [2]
        
            auto* tempBuffWriter = tempBuffer.getWritePointer (0, 0); // [3]
        
            for (int samp = 0; samp < chunkSize; ++samp)
            {
                tempBuffWriter[samp] = buffReader[samp]; // [4]
            }
        
            tracker.processAudioFrame (tempBuffer.getWritePointer (0,0) ); // [5]
        
            
            if (tracker.beatDueInCurrentFrame() == true)
            {
                beatCount ++;
                
                updateBeatTime (tracker.getBeatTimeInSeconds (frameCount,
                                                              myHop,
                                                              sr) ); // [6]
                
                
            }
            frameCount ++; // [7]
        }
        
    } //end of if statement
}

void BpmometerAudioProcessor::updateBeatTime(double _value)
{
    //This called in processBlock, getsBeatTimein Seconds and returns it here.
    timeGrab = _value;
    //DBG( timeGrab );
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
    //onOff = mAPVTS.getRawParameterValue(LAUNCH_LATER_ID)->load();
    DBG ("button pressed");
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
