/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_F163B3138F7FE248__
#define __JUCE_HEADER_F163B3138F7FE248__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class StereoDelayAudioProcessorEditor  : public AudioProcessorEditor,
                                         public Timer,
                                         public SliderListener
{
public:
    //==============================================================================
    StereoDelayAudioProcessorEditor (StereoDelayAudioProcessor& p);
    ~StereoDelayAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    StereoDelayAudioProcessor& processor;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> sliderDelayTime;
    ScopedPointer<Label> labelDelayTime;
    ScopedPointer<Slider> sliderFeedback;
    ScopedPointer<Label> labelFeedback;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoDelayAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_F163B3138F7FE248__
