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
    
    myTabs.addTab("Meter",
                  Colours::orange,
                  &meterComp,
                  false);
    
    setSize (800, 600);
    
    timerValue = meterComp.getRefreshRate(); //sync timer with refresh rate of meter component
    
    Timer::startTimerHz( timerValue );
    
    
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
    meterComp.tempoChanged();
}




