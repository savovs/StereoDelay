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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
StereoDelayAudioProcessorEditor::StereoDelayAudioProcessorEditor (StereoDelayAudioProcessor& p)
    : AudioProcessorEditor(p), processor(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    startTimer(200);


    //[/Constructor_pre]

    addAndMakeVisible (sliderDelayTime = new Slider ("Delay Time Slider"));
    sliderDelayTime->setRange (0.01, 1, 0);
    sliderDelayTime->setSliderStyle (Slider::LinearHorizontal);
    sliderDelayTime->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    sliderDelayTime->addListener (this);

    addAndMakeVisible (labelDelayTime = new Label ("Delay Time Label",
                                                   TRANS("Delay Time (seconds)")));
    labelDelayTime->setFont (Font (15.00f, Font::plain));
    labelDelayTime->setJustificationType (Justification::centredLeft);
    labelDelayTime->setEditable (false, false, false);
    labelDelayTime->setColour (TextEditor::textColourId, Colours::black);
    labelDelayTime->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sliderFeedback = new Slider ("Feedback Slider"));
    sliderFeedback->setRange (0, 0.95, 0);
    sliderFeedback->setSliderStyle (Slider::LinearHorizontal);
    sliderFeedback->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    sliderFeedback->addListener (this);

    addAndMakeVisible (labelFeedback = new Label ("Feedback Label",
                                                  TRANS("Feedback")));
    labelFeedback->setFont (Font (15.00f, Font::plain));
    labelFeedback->setJustificationType (Justification::centredLeft);
    labelFeedback->setEditable (false, false, false);
    labelFeedback->setColour (TextEditor::textColourId, Colours::black);
    labelFeedback->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    startTimer(200);//starts timer with interval of 200mS
    //[/Constructor]
}

StereoDelayAudioProcessorEditor::~StereoDelayAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    sliderDelayTime = nullptr;
    labelDelayTime = nullptr;
    sliderFeedback = nullptr;
    labelFeedback = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void StereoDelayAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void StereoDelayAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    sliderDelayTime->setBounds (64, 80, 224, 24);
    labelDelayTime->setBounds (64, 56, 150, 24);
    sliderFeedback->setBounds (64, 160, 224, 24);
    labelFeedback->setBounds (64, 136, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void StereoDelayAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sliderDelayTime)
    {
        //[UserSliderCode_sliderDelayTime] -- add your slider handling code here..
        processor.setParameterNotifyingHost(
            StereoDelayAudioProcessor::kDelayTimeParam,
            (float)sliderDelayTime->getValue()
        );
        //[/UserSliderCode_sliderDelayTime]
    }
    
    else if (sliderThatWasMoved == sliderFeedback)
    {
        //[UserSliderCode_sliderFeedback] -- add your slider handling code here..
        processor.setParameterNotifyingHost(
            StereoDelayAudioProcessor::kFeedbackParam,
            (float)sliderFeedback->getValue()
        );
        //[/UserSliderCode_sliderFeedback]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void StereoDelayAudioProcessorEditor::timerCallback()
{
    sliderDelayTime->setValue(processor.delayTime, dontSendNotification);
    sliderFeedback->setValue(processor.feedback, dontSendNotification);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="StereoDelayAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="StereoDelayAudioProcessor&amp; p" variableInitialisers="AudioProcessorEditor(p), processor(p)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="Delay Time Slider" id="2f31b6a967aebb9e" memberName="sliderDelayTime"
          virtualName="" explicitFocusOrder="0" pos="64 80 224 24" min="0.010000000000000000208"
          max="1" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <LABEL name="Delay Time Label" id="8a20417a59ca51c3" memberName="labelDelayTime"
         virtualName="" explicitFocusOrder="0" pos="64 56 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Delay Time (seconds)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="Feedback Slider" id="8258d034ac1c459c" memberName="sliderFeedback"
          virtualName="" explicitFocusOrder="0" pos="64 160 224 24" min="0"
          max="0.94999999999999995559" int="0" style="LinearHorizontal"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="Feedback Label" id="f5c7ae60842edade" memberName="labelFeedback"
         virtualName="" explicitFocusOrder="0" pos="64 136 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Feedback" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
