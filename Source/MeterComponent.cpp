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
    
    indicatorSlider.setLookAndFeel (&altLookAndFeel);
    
    indicatorSlider.setRotaryParameters (degreesToRadians(315.0), degreesToRadians(405.0), false );
    
    indicatorSlider.setTextBoxStyle (Slider::TextEntryBoxPosition::NoTextBox, true, 100, 50);
    
    indicatorSlider.setNumDecimalPlacesToDisplay(1);
    
    indicatorSlider.setSliderStyle (Slider::SliderStyle::Rotary);
    
    //indicatorSlider.setCentrePosition(getWidth()/2, 3* getHeight()/4);
    addAndMakeVisible (indicatorSlider);
    
    //======
    //RANGE:
    //this->initSliderValues(100);
    //======
    
    //this->setCentralString("?");
    
    
    
    previousBeatTime = 0;
    
    beatInterval = 0;
    
    //
    smoothTempo.reset(refreshRate, 0.3); //same callbackTimer rate.
    
    

}

MeterComponent::~MeterComponent()
{
}

void MeterComponent::paint (Graphics& g)
{
    //=== background
    g.fillAll(juce::Colour (Colours::darkslategrey));
    
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    //======== slider
    auto area = getLocalBounds();
    
    auto radius =  540;
    auto halfRad = radius/2;
    
    auto centrePoint = juce::Point<float> (getWidth()/2, getHeight()/2);
    
    
   indicatorSlider.setCentrePosition(getWidth()/2, 3* getHeight()/4);
    
    
    //========== Sections:
    g.setColour(juce::Colours::lightgrey);
    
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
        g.drawLine (line, 2.0f);
        g.addTransform(AffineTransform::rotation (rotation,
                                                  getWidth()/2,
                                                  3*getHeight()/4) );
    }
    
    g.restoreState();
    
    
    //========== slider string
    g.setColour (Colours::white);
    g.setFont (40.0f);
    
    //setSliderString();
    
    g.drawFittedText (sliderString, getLocalBounds(), Justification::centred, 1);
    
    
    //============== CENTRAL ==============
    g.setFont (30.0f);
    g.drawFittedText(centralString, getWidth()/2 - 25, getWidth()/10, 50, 50, Justification::centred, 1);
    
    
}

void MeterComponent::resized()
{
    //============
    auto area = getLocalBounds();

    //============
    auto indiSliderHeight = 2000;

    indicatorSlider.setBounds(area.removeFromBottom(3000));
}

void MeterComponent::passBPM(float bpmValue)
{
    //meterBPM is a float
    
    //_theTempo = bpmValue; //this goes to the slider.
    
    //DBG(_theTempo);
    //bpmInt = roundToInt(meterBPM);
    
    
    //rounded_down = floorf(meterBPM * 100) / 100;   /* Result: 37.77 */
    
    //    double rounded_down = floorf(_tempo * 100) / 100;
    //
    //    int tempoInt = roundToInt(_tempo);
    
    
    
    //lowerLimit = centralBPM - 5;
    
    //upperLimit = centralBPM + 5;
    
    
    
    
}

void MeterComponent::tempoChanged()
{
    // Gets the time of the beat from the processor:
    double currentBeatTime = processor.getTimeGrab();
    
    // If the beat time changes, calculate the beatInterval:
    if(currentBeatTime != previousBeatTime)
    {
        // Calculate beat interval based on current and previous beat times:
        beatInterval = (currentBeatTime - previousBeatTime);
        
        // Calculate tempo based on interval:
        
        //smoothTempo.setTargetValue ( 60.0f / beatInterval );
        
        
        float tempoFloat = 60.0f / beatInterval;

        int tempoInt = roundToInt(tempoFloat);

        smoothTempo.setTargetValue ( tempoInt );
        
    }
    
    auto _theTempo =  smoothTempo.getNextValue() ;
    
    indicatorSlider.setValue( _theTempo );
    //DBG( "smoothed: " << smoothed );
    
    setSliderStrings( indicatorSlider.getValue()  );
   
    previousBeatTime = currentBeatTime;
    
    repaint();
    
}

void MeterComponent::setSliderValues(int _centralBPM)
{
    // Funciton gets called in constructor.
    centralBPM = _centralBPM;
    
    //centralString = std::to_string ( centralBPM );
    
    std::string question = "?";
    
    
    int lowerLimit = centralBPM - 5;
    
    int upperLimit = centralBPM + 5;
    
    indicatorSlider.setRange (lowerLimit, upperLimit);
    
    
}

void MeterComponent::setCentralString(std::string string)
{
    centralString = string;
}

void MeterComponent::setSliderStrings(float value)
{
    
    
    //======== slider value string=======
    sliderString = std::to_string (roundToInt ( value ) );
    //sliderString = std::to_string ( _theTempo );
    
    
}
