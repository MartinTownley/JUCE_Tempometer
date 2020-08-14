/*
  ==============================================================================

    MeterComponent.h
    Created: 22 Jul 2020 3:49:43pm
    Author:  sierra

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


class AltLookAndFeel : public juce::LookAndFeel_V4
{
public:
    AltLookAndFeel ()
    {
        setColour (juce::Slider::thumbColourId, juce::Colours::red);
        
    }
    
    
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                      const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        auto outline = slider.findColour (Slider::rotarySliderOutlineColourId);
        //auto fill    = slider.findColour (Slider::rotarySliderFillColourId);
        
        auto fill = Colours::lightgrey;
        
        auto bounds = Rectangle<int> (x, y, width, height).toFloat().reduced (10);
        
        auto radius = jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = jmin (2.0f, radius * 0.5f);
        auto arcRadius = radius - lineW * 0.5f;
        
        Path backgroundArc;
        backgroundArc.addCentredArc (bounds.getCentreX(),
                                     bounds.getCentreY(),
                                     arcRadius,
                                     arcRadius,
                                     0.0f,
                                     rotaryStartAngle,
                                     rotaryEndAngle,
                                     true);
        
        g.setColour (outline);
        g.strokePath (backgroundArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));
        
        if (slider.isEnabled())
        {
            Path valueArc;
            valueArc.addCentredArc (bounds.getCentreX(),
                                    bounds.getCentreY(),
                                    arcRadius,
                                    arcRadius,
                                    0.0f,
                                    rotaryStartAngle,
                                    toAngle,
                                    true);
            
            g.setColour (fill);
            g.strokePath (valueArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::square));
        }
        
        auto thumbWidth = lineW * 10.0f;
        //auto thumbWidth = 8.0f;
        Point<float> thumbPoint (bounds.getCentreX() + arcRadius * std::cos (toAngle - MathConstants<float>::halfPi),
                                 bounds.getCentreY() + arcRadius * std::sin (toAngle - MathConstants<float>::halfPi));
        
        g.setColour (ellipseColour);
        
        g.fillEllipse (Rectangle<float> (thumbWidth, thumbWidth).withCentre (thumbPoint));
    
    }
    
    void setEllipseColour (juce::Colour colour)
    {
        
        ellipseColour = colour;
        //DBG("ding ding");
    }
private:
    Colour ellipseColour;
    
};
//==============================================================================
/*
*/
class MeterComponent    :   public Component,
                            public Timer,
                            public TextButton::Listener

{
public:
    MeterComponent(BpmometerAudioProcessor&);
    
    ~MeterComponent();

    void paint (Graphics&) override;
    
    //void paintCircle (int radius);
    
    void resized() override;
    
    
    /** Takes argument, rounds it to an int, converts value to a string, and sets that to the current slider value that is drawn on the screen
     * @param value the slider value to be converted to a string
     */
    void setIndicatorString(float value);
    
    /** Sets the intention string, a string of the intention BPM value, drawn at 12'oclock in relation to the slider
     * @param string the string to be drawn
     */
    void setIntentionBPMString(int _value);
    
    /** Sets the lower-and-upper limits of the slider
     * @param intentionBPM the "12 o'clock" target BPM that the musician wishes to maintain
     */
    void setSliderRange(int _intentionBPM);
    
    /** Checks if beat time has changed, makes appropriate tempo calculations if so. Sets indicatorSlider value accordingly, and calls setSliderStrings */
    void tempoChanged();
    
    /** Allows the refresh rate to be seen by other components, so that they can sync their timer callbacks */
    int getRefreshRate(){
        return refreshRate;
    }
    
    /** Makes the slider visible */
    void runSlider();
    
    void initialiseSlider();
    
    
    void timerCallback() override;
    
    void testFunction();
    
    void buttonClicked (Button*) override;
    

private:
    
    const Colour customBrown {0xff523f43};
   
    AltLookAndFeel altLookAndFeel;
    
    Slider indicatorSlider;
    
    double previousBeatTime;
    
    double beatInterval;
    
    //float smoothNext;
    
    SmoothedValue<float> smoothTempo;
                
    //float _theTempo; //the value displayed and given to the slider.
    
    int intentionBPM; // this is the 12 o'clock BPM.
    
    int refreshRate;
    
    float rampLength;
    
    int bpmRange; //range for the slider, +/- the target.
    
    int tempoInt;
    //====== Buttons
    
    TextButton launchLaterButton {"Run Later"};
    
    TextButton launchNowButton { "Run Now" };
    
    int buttonDelaySecs;
    
    
    
    //-------- Button enum
    
    enum class SliderState
    {
        Vis,
        Invis
    };
    //-------- RunState object
    
    SliderState sliderState { SliderState::Invis }; //default
    
    
    
    //========
    
    bool sliderBool; //flips to make the slider appear.
    
    //========
    std::string intentionString;
    
    std::string indicatorString;
    

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BpmometerAudioProcessor& processor;
    
    
    
    
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterComponent)
};
