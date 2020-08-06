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
        
        g.setColour (Colours::mediumpurple);
        g.fillEllipse (Rectangle<float> (thumbWidth, thumbWidth).withCentre (thumbPoint));
    }
};
//==============================================================================
/*
*/
class MeterComponent    : public Component,
                        public Timer

{
public:
    MeterComponent(BpmometerAudioProcessor&);
    ~MeterComponent();

    void paint (Graphics&) override;
    
    void paintCircle (int radius);
    
    void resized() override;
    
    
    
    void setSliderStrings(float value);
    
    void setCentralString(std::string string);
    
    void setSliderValues(int _centralBPM);
    
    void tempoChanged();
    
    int getRefreshRate(){
        return refreshRate;
    }
    
    void runCountdown();
    
    void timerCallback() override;
    
    void testFunction();
    
    //static void JUCE_CALLTYPE Timer::callAfterDe

private:
    
    const Colour customBrown {0xff523f43};
   
    AltLookAndFeel altLookAndFeel;
    
    Slider indicatorSlider;
    
    double previousBeatTime;
    
    double beatInterval;
    
    //float smoothNext;
    
    SmoothedValue<float> smoothTempo;
                
    //float _theTempo; //the value displayed and given to the slider.
    
    int centralBPM; // this is the 12 o'clock BPM.
    
    int refreshRate { 60 };
    
    int bpmRange; //range for the slider, +/- the target.
    
    //====== Button
    
    TextButton launchLaterButton {"Launch Later"};
    
    int buttonDelayTime;
    
    std::unique_ptr <AudioProcessorValueTreeState::ButtonAttachment> launchLaterAttach;
    
    //-------- Button enum
    
    enum class CountdownState
    {
        Run,
        Stop
    };
    //-------- CountdownState object
    
    CountdownState countdownState { CountdownState::Stop }; //default
    
    TextButton launchNowButton { "Launch Now" };
    
    int countdownTime;
    
    
    std::unique_ptr <AudioProcessorValueTreeState::ButtonAttachment> launchNowAttach;
    
    //========
    
    bool sliderBool; //flips to make the slider appear.
    
    //========
    std::string centralString;
    
    std::string sliderString;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BpmometerAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterComponent)
};
