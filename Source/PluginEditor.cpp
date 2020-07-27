/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

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
}

void BpmometerAudioProcessorEditor::calculateInterval()
{
    //Timestamp of the current beat:
    double currentBeatTime = processor.getTimeGrab();
    
    // Calculate difference in time between beats:
    beatInterval = (currentBeatTime - previousBeatTime);
    DBG(beatInterval);
    
    theTempo = 60.0f / beatInterval;
    
    if (currentBeatTime != previousBeatTime)
    {
        previousBeatTime = currentBeatTime;
         DBG(theTempo);
        repaint();
    }
    
//    int currentBeat = beat;
//
//    float currentInterval = interval;
//
//    float currentTempo = tempo;
//
//    if (currentBeat != previousBeat)
//    {
//        previousBeat = currentBeat;
//
//        previousInterval = currentInterval;
//
//        previousTempo = currentTempo;
//
//        repaint();
}

void BpmometerAudioProcessorEditor::updateInterval()
{
    double currentBeatTime = processor.getTimeGrab();
    
    beatInterval = (currentBeatTime - previousBeatTime);
    
    if(currentBeatTime != previousBeatTime)
    {
        //DBG("CBTif: " << currentBeatTime);
        //DBG("PBTif: " <<previousBeatTime);
        //DBG ("Interval: " << beatInterval);
        DBG( beatInterval );
    }
    
    
    
    //DBG("CBT: " << currentBeatTime);
    
    //DBG("PBT: " << previousBeatTime);
    
    previousBeatTime = currentBeatTime;
    
    //DBG("CBTNOW: " << currentBeatTime);
    //DBG("PBTNOW: " <<previousBeatTime);
    //Previous = 2.
    //Current = 2.
//    if (currentBeatTime != previousBeatTime)
//    {
//        previousBeatTime = currentBeatTime;
//    }
    
}
