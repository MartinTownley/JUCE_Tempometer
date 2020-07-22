/*
  ==============================================================================

    MeterComponent.cpp
    Created: 22 Jul 2020 3:49:43pm
    Author:  sierra

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MeterComponent.h"

//==============================================================================
MeterComponent::MeterComponent()
{
    
    //=======
//    header.setButtonText ("Header");
//    addAndMakeVisible (header);
    
    //=======
    
    
    indicatorSlider.setLookAndFeel (&altLookAndFeel);
    
    //indicatorSlider.setRotaryParameters (degreesToRadians(310.0), degreesToRadians(410.0), false );
    
    indicatorSlider.setTextBoxStyle (Slider::TextEntryBoxPosition::NoTextBox, true, 100, 50);
    
    
    DBG( "pos: " << indicatorSlider.getTextBoxPosition() );
    //indicatorSlider.setMinValue(0);
    
    indicatorSlider.setSliderStyle (Slider::SliderStyle::Rotary);
    addAndMakeVisible (indicatorSlider);
    indicatorSlider.setRange (0, 1.0);
    indicatorSlider.setTextValueSuffix (" ?");
    
    indicatorSlider.setNumDecimalPlacesToDisplay(1);

}

MeterComponent::~MeterComponent()
{
}

void MeterComponent::paint (Graphics& g)
{
    
    auto area = getLocalBounds();
    g.fillAll(juce::Colour (customBrown));
    
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    g.setColour (Colours::white);
    g.setFont (14.0f);
    
    auto radius = 500;
    //=========
    g.drawEllipse(getWidth()/2 - (radius/2),getHeight()/2 - (radius/2)  , radius,radius,1.0);
    //=========
    
    auto centrePoint = juce::Point<float> (getWidth()/2, getHeight()/2);
    // Horizontal line
    //juce::Line<float> horiLine (leftCentre, rightCentre);
    
    g.drawVerticalLine(getWidth()/2, 0, getHeight()/2);
    
    //g.drawLine (horiLine);
    //g.drawLine (vertiLine);
    
    
}

void MeterComponent::resized()
{
    //============
    auto area = getLocalBounds();
    
    
    //============
//    auto headerFooterHeight = 36;
//    header.setBounds (area.removeFromTop (headerFooterHeight));
    //============
    //============
    //============
    auto indiSliderHeight = 5000;

    indicatorSlider.setBounds(area.removeFromTop (indiSliderHeight));
//    indicatorSlider.setBounds(-100, getHeight()/2 - 200, 1000, 1000);

}
