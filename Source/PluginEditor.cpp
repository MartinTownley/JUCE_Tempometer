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
    
    
    Timer::startTimerHz(60);
    
    //-=====
    
    double val = 37.777779;
    
    double rounded_down = floorf(val * 100) / 100;   /* Result: 37.77 */
    double nearest = roundf(val * 100) / 100;  /* Result: 37.78 */
    double rounded_up = ceilf(val * 100) / 100;      /* Result: 37.78 */
    
    //DBG(rounded_up);
    
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
    
}

BpmometerAudioProcessorEditor::~BpmometerAudioProcessorEditor()
{
    Timer::stopTimer();
}

//==============================================================================
void BpmometerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
//    g.setColour (Colours::white);
//    g.setFont (15.0f);
//
//    std::string tempoString = std::to_string(  processor.getTheTempo() );
//
//
//    g.drawFittedText (tempoString, getLocalBounds(), Justification::centred, 1);
}

void BpmometerAudioProcessorEditor::resized()
{
    myTabs.setBounds( getLocalBounds() );
}

void BpmometerAudioProcessorEditor::timerCallback()
{
    //processor.calculateTempo();
    //repaint();
    //DBG( processor.getTimeGrab() );
    //DBG (processor.getTimeGrab() );
    //calculateInterval();
    //DBG(processor.getTimeGrab());
    
    updateInterval();
    
    meterComp.passBPM( theTempo );
}



void BpmometerAudioProcessorEditor::updateInterval()
{
    // Gets the time of the beat from the processor:
    double currentBeatTime = processor.getTimeGrab();
    
    //DBG( currentBeatTime );
    
    // If the beat time changes, calculate the beatInterval:
    if(currentBeatTime != previousBeatTime)
    {
        // Calculate beat interval based on current and previous beat times:
        beatInterval = (currentBeatTime - previousBeatTime);
        
        // Calculate tempo based on interval:
        theTempo = 60.0f / beatInterval;
        
        //Push tempo value to the circular buffer for averaging:
        //tempoBuffer.addSampleToEnd (theTempo);
        
        //Make for loop here to sum the values.
        
        DBG( theTempo );
        //DBG("Sum: " << tempoSum );
        //DBG("break");
    }
    
    previousBeatTime = currentBeatTime;
    
    
    
}
