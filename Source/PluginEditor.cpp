/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <numeric>


//==============================================================================
BpmometerAudioProcessorEditor::BpmometerAudioProcessorEditor (BpmometerAudioProcessor& p)
    : AudioProcessorEditor (&p),
        processor (p),
        myTabs(TabbedButtonBar::TabsAtTop),
        meterComp(p)

{
    
    addAndMakeVisible(myTabs);
    
    myTabs.addTab("Meter", Colours::orange,
                  &meterComp, false);
    
    setSize (800, 600);
    
    timerValue = meterComp.getRefreshRate();
    
    Timer::startTimerHz( timerValue );
    
    previousBeatTime = 0;
    
    beatInterval = 0;
    
    //---------
    //Set size of tempos circular buffer
    
    tempoBufferSize = 20;
    
    tempoBuffer.resize( tempoBufferSize );
    //Initialise values to zero:
    for (int i=0; i < tempoBufferSize; i++)
    {
        tempoBuffer[i] = 0;
    }
    
    //Initialise bufferCounter:
    bufferCounter = 0;
    
    sum = 0;
    
    //meterComp.getSmoothTempo().reset(timerValue, 0.3);
    
}

BpmometerAudioProcessorEditor::~BpmometerAudioProcessorEditor()
{
    Timer::stopTimer();
}

//==============================================================================
void BpmometerAudioProcessorEditor::paint (Graphics& g)
{
    
}

void BpmometerAudioProcessorEditor::resized()
{
    myTabs.setBounds( getLocalBounds() );
}

void BpmometerAudioProcessorEditor::timerCallback()
{
    //mySmoothed.setTargetValue ( updateTempo() );
    
    //meterComp.passBPM( mySmoothed.getNextValue() );
    
    //meterComp.passBPM( mySmoothed.getNextValue() );
    
    //meterComp.passBPM ( calculateTempo() );
    
    //calculateTempo(); //tempo continually calculated
    
    meterComp.tempoChanged();
    
    //meterComp.passBPM ( theTempo );
    
}



//void BpmometerAudioProcessorEditor::calculateTempo()
//{
//    // Gets the time of the beat from the processor:
//    double currentBeatTime = processor.getTimeGrab();
//    
//    // If the beat time changes, calculate the beatInterval:
//    if(currentBeatTime != previousBeatTime)
//    {
//        // Calculate beat interval based on current and previous beat times:
//        beatInterval = (currentBeatTime - previousBeatTime);
//        
//        // Calculate tempo based on interval:
//        theTempo = 60.0f / beatInterval;
//        
//        DBG("theTempo: " << theTempo);
//        
//        //call tempoChange function in metercomponent
//        
//    }
//    
//    previousBeatTime = currentBeatTime;
//    
//    
//    
//}

//float BpmometerAudioProcessorEditor::smoothTempo(float _tempo)
//{
//    
//    //Get rid of decimals here.
//    //double rounded_down = floorf(_tempo * 100) / 100;
//
//    //int tempoInt = roundToInt(_tempo);
//    
//    //smoothed.setTargetValue ( tempoInt ); //smoothe incoming value
//    
//    //float nextTempo = smoothed.getNextValue();
//    //DBG(nextTempo);
//    
//    return;
//}

