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
MeterComponent::MeterComponent(BpmometerAudioProcessor& p) : processor(p)
{
    
    //=======
//    header.setButtonText ("Header");
//    addAndMakeVisible (header);
    
    //=======
    
    
    indicatorSlider.setLookAndFeel (&altLookAndFeel);
    
    
    
    indicatorSlider.setRotaryParameters (degreesToRadians(315.0), degreesToRadians(405.0), false );
    
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
    //DRAW NUMBER:
    
    
    //========
    auto area = getLocalBounds();
    
    auto radius =  540;
    auto halfRad = radius/2;
    
    auto centrePoint = juce::Point<float> (getWidth()/2, getHeight()/2);
    
    
    
    g.fillAll(juce::Colour (customBrown));
    
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    
    
    indicatorSlider.setCentrePosition(getWidth()/2, 3* getHeight()/4);
    //======CIRCLE
//    g.setColour (Colours::white);
//    g.drawEllipse(getWidth()/2 - (radius/2),getHeight()/2 - (radius/2)  , radius,radius,1.0);
    //=========
    
    
    //=========== PATH orange
//    g.setColour (juce::Colours::orange);
//    Path arcPath;
//
//    arcPath.addCentredArc(100, 100, 50, 50, 0, -0.8 *float_Pi, 0.8* float_Pi, true);
//
//    auto myStroke = PathStrokeType(1.0, juce::PathStrokeType::JointStyle::curved, juce::PathStrokeType::EndCapStyle::rounded);
//
//    myStroke.createStrokedPath(arcPath, arcPath);
//
//    g.fillPath (arcPath);
   
    //========
    //PIE: yellow
    g.setColour(juce::Colours::yellow);
    
    
    //=============== WO Lambda
    
    const auto division = 10;
    
    const auto sixteenth = float_Pi / 8;
    
    const auto thirty2nd = float_Pi / 16;
    
    const auto fortyFive = float_Pi / 4;
    
    const auto ninety = float_Pi / 2;
    
    const auto oneEighty = float_Pi;
    
    const auto rotation = ninety / division;
    
    const auto angle = degreesToRadians(315.0); //vertical angle 12 oclock
    
    const auto centre = area.getCentre().toFloat(); //get centre
    
    auto threeQuart = juce::Point<float> (getWidth()/2, 3*getHeight()/4);
    
    
    const auto markerLength = 20; //length of the notches
    
    const auto numLines = division + 1; //how many notches
    
    auto line = juce::Line<float>::fromStartAndAngle (threeQuart,
                                                      halfRad + markerLength,
                                                      angle);
    line = line.withShortenedStart ( halfRad ); //dont draw the bit of the line inside circle
    
    g.saveState();

    for (int i = 0; i < numLines; ++i)
    {
        g.drawLine (line, 1.0f);
        g.addTransform(AffineTransform::rotation (rotation,
                                                  getWidth()/2,
                                                  3*getHeight()/4) );
    }
    
    g.restoreState();
    
    
    //Alternative drawing:=======
//    auto x1 = getWidth()/2 + cos(0) * 100;
//    auto y1 = getHeight()/2 + sin(0) * 100;
//    auto x2 = getWidth()/2 + cos(0) * 200;
//    auto y2 = getHeight()/2 + sin(0) * 200;
//
//    g.setColour(juce::Colours::pink);
//    for ( int i =0; i<50; ++i)
//    {
//    g.drawLine(x1, y1, x2, y2);
//        g.addTransform(AffineTransform::rotation (thirty2nd, getWidth()/2, getHeight()/2) );
//    }
    
//    g.setColour (Colours::white);
//    g.setFont (40.0f);
//    
//    std::string tempoString = std::to_string(  processor.getTheTempo() );
//    
//    g.drawFittedText (tempoString, getLocalBounds(), Justification::centred, 1);
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
    auto indiSliderHeight = 2000;

    indicatorSlider.setBounds(area.removeFromBottom(3000));
    
    
//    indicatorSlider.setBounds(-100, getHeight()/2 - 200, 1000, 1000);

}
