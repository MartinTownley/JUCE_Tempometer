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
    
    //indicatorString = " ";
    
    indicatorSlider.setLookAndFeel (&altLookAndFeel);
    
    indicatorSlider.setRotaryParameters (degreesToRadians(315.0), degreesToRadians(405.0), false );
    
    indicatorSlider.setTextBoxStyle (Slider::TextEntryBoxPosition::NoTextBox, true, 100, 50);
    
    indicatorSlider.setNumDecimalPlacesToDisplay(1);
    
    indicatorSlider.setSliderStyle (Slider::SliderStyle::Rotary);
    
    //turn off mouse response
    indicatorSlider.setInterceptsMouseClicks (false, false);
    
altLookAndFeel.setEllipseColour( juce::Colours::mediumpurple );
    
    //======
    
    previousBeatTime = 0;
    
    beatInterval = 0;
    
    rampLength = 0.3;
    refreshRate = 60;
    
    smoothTempo.reset(refreshRate, rampLength); //same callbackTimer rate.
    
    sliderBool = true;
    
    //====================
    //-----launch buttons
    
    
    
    //----------
    launchLaterButton.setColour(TextButton::buttonColourId, Colours::grey);
    launchLaterButton.setColour(TextButton::textColourOffId, Colours::white);
    
    launchLaterButton.setToggleState(false, NotificationType::dontSendNotification);
    //---------
    
    launchNowButton.setColour(TextButton::buttonColourId, Colours::grey);
    launchNowButton.setColour(TextButton::textColourOffId, Colours::white);
    
    launchNowButton.setToggleState(false, NotificationType::dontSendNotification);
    
    
    buttonDelaySecs = 5;
    
    //LaunchLater Button has a delay
    
    launchLaterButton.onClick = [this]() {
        
        processor.runStateChanged();
        
        Timer::callAfterDelay (buttonDelaySecs * 1000, [this]
        {
            this->initialiseSlider();
            
            this->runSlider();
            
            
        } );
        
    };
    
    launchNowButton.onClick = [this]() {
        DBG ("nowNow");
        
        //processor.testButton();
        this->initialiseSlider();
        this->runSlider();
        
    };
    
    addAndMakeVisible(&launchNowButton);
    addAndMakeVisible(&launchLaterButton);
    
    launchNowButton.addListener(this);
    launchLaterButton.addListener(this);
    
}

MeterComponent::~MeterComponent()
{
    Timer::stopTimer();
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
    
    
    //========== indicator string
    g.setColour (Colours::white);
    g.setFont (40.0f);
    
    
    //g.drawText("Hello", 200, 100, 50, 50, Justification::centred);
    
    
    g.drawFittedText (indicatorString, getLocalBounds(), Justification::centred, 1);
    
    
    //============== INTENTION STRING ==============
    g.setFont (30.0f);
    
    
    
    g.drawFittedText (intentionString,
                     getWidth()/2 - 25,
                     getHeight()/6,
                     50,
                     50,
                     Justification::centred,
                     1);
    
  
    
    
    
}

void MeterComponent::resized()
{
    auto bounds = getLocalBounds();
    if (sliderBool)
        indicatorSlider.setBounds(bounds.removeFromBottom(1000));
    
    
    auto bounds2 = getLocalBounds();

    FlexBox flexbox { FlexBox::Direction::row, FlexBox::Wrap::noWrap, FlexBox::AlignContent::center, FlexBox::AlignItems::center, FlexBox::JustifyContent::center};

    flexbox.items.add (FlexItem(200,75, launchLaterButton) );
    flexbox.items.add (FlexItem(200,75, launchNowButton) );

    flexbox.performLayout(bounds2.removeFromBottom(350) );

    //launchLaterButton.setBounds (50,100,150,75);
    
    //launchNowButton.setBounds (getWidth()-200, 100, 150,75);

    
    
    
    //============
    

}



void MeterComponent::tempoChanged()
{
    // Gets the time of the beat from the processor:
    double currentBeatTime = processor.getTimeGrab();
    
    // If the beat time changes, calculate the beatInterval:
    if(currentBeatTime != previousBeatTime)
    {
        
        //DBG(currentBeatTime - previousBeatTime);
        //DBG("Slider: "<< indicatorSlider.getValue() );
        // Calculate beat interval based on current and previous beat times:
        beatInterval = (currentBeatTime - previousBeatTime);
        
        // Calculate tempo based on interval:
        
        float tempoFloat = 60.0f / beatInterval;
        
        //DBG("TempoFloat: " << tempoFloat);

        // Round to integer:
        tempoInt = roundToInt(tempoFloat);
        
        
        
        auto difference = abs (tempoInt - indicatorSlider.getValue() );
        
        smoothTempo.reset (refreshRate, rampLength * difference );

        // Smooth the value:
        smoothTempo.setTargetValue ( tempoInt );
        
       //DBG( indicatorSlider.getMinimum() );
        
        if (tempoInt < indicatorSlider.getMinimum()
            || tempoInt > indicatorSlider.getMaximum() )
        {
            altLookAndFeel.setEllipseColour(juce::Colours::red);
        } else {
            altLookAndFeel.setEllipseColour(juce::Colours::mediumpurple);
        }
        
    }
    
    auto _theTempo =  smoothTempo.getNextValue() ;
    
    indicatorSlider.setValue( _theTempo );
    //DBG( "smoothed: " << smoothed );
    
    setIndicatorString( _theTempo );
    
    previousBeatTime = currentBeatTime;
    
    repaint();
    
    
    
}

void MeterComponent::setSliderRange(int _intentionBPM)
{
    
    intentionBPM = _intentionBPM;
    
    //centralString = std::to_string ( centralBPM );
    
    std::string question = "?";
    
    int lowerLimit = intentionBPM - 5;
    
    int upperLimit = intentionBPM + 5;
    
    indicatorSlider.setRange (lowerLimit, upperLimit);
    
    
}

void MeterComponent::setIntentionBPMString(int _value)
{
    intentionString = std::to_string (_value);
}

void MeterComponent::setIndicatorString(float value)
{
    
    
    //======== slider value string=======
    indicatorString = std::to_string (roundToInt ( value ) );
    
}

void MeterComponent::runSlider()
{
    if (sliderState == SliderState::Invis)
    {
        sliderState = SliderState::Vis; //visible
        
        Timer::startTimerHz (1);
        addAndMakeVisible (&indicatorSlider);
        
    }
}

void MeterComponent::initialiseSlider()
{
    setSliderRange ( tempoInt );
    setIntentionBPMString ( tempoInt );
}

void MeterComponent::timerCallback()
{
    //DBG ("countup : " << Timer::getTimerInterval() );
    //countdownTime --;
    //DBG(countdownTime);
    //DBG(  indicatorSlider.getMaximum () ) ;
}



void MeterComponent::buttonClicked (Button* inButton)
{
    if (inButton == &launchLaterButton)
    {
        //processor.testButton();
    }
}


