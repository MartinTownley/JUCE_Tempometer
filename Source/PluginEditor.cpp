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
        myTabs(TabbedButtonBar::TabsAtTop)
{
    
    addAndMakeVisible(myTabs);
    
    myTabs.addTab("Meter", Colours::orange,
                  &meterComp, false);
    
    setSize (800, 600);
    
    Timer::startTimerHz(60);
}

BpmometerAudioProcessorEditor::~BpmometerAudioProcessorEditor()
{
    Timer::stopTimer();
}

//==============================================================================
void BpmometerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    
    std::string tempoString = std::to_string(  processor.getTheTempo() );
    
    g.drawFittedText (tempoString, getLocalBounds(), Justification::centred, 1);
}

void BpmometerAudioProcessorEditor::resized()
{
    myTabs.setBounds( getLocalBounds() );
}

void BpmometerAudioProcessorEditor::timerCallback()
{
    processor.calculateTempo();
    repaint();
}
