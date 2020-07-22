/*
  ==============================================================================

    MeterComponent.h
    Created: 22 Jul 2020 3:49:43pm
    Author:  sierra

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class MeterComponent    : public Component
{
public:
    MeterComponent();
    ~MeterComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterComponent)
};
