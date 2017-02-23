/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class StereoDelayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    StereoDelayAudioProcessor();
    ~StereoDelayAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    int getNumParameters() override;
    float getParameter(int index) override;
    void setParameter(int index, float value) override;
    const String getParameterName(int index) override;
    const String getParameterText(int index) override;
    
    enum Parameters
    {
        kDelayTimeParam = 0,
        kFeedbackParam,
        kNumParameters
    };
    
    float feedback;
    float delayTime;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoDelayAudioProcessor)
    
    AudioSampleBuffer delayBuffer;
    int delayBufferLength;
    int readIndex;
    int writeIndex;
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
