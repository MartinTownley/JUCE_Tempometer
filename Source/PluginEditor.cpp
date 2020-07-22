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
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
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
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void BpmometerAudioProcessorEditor::timerCallback()
{
    processor.calculateTempo();
    repaint();
}
