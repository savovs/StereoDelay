/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
StereoDelayAudioProcessor::StereoDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    feedback = 0.5;
    delayTime = 0.25;
    readIndex = 0;
    
    writeIndex = delayTime;
    delayBufferLength = 0;
}

StereoDelayAudioProcessor::~StereoDelayAudioProcessor()
{
}

//==============================================================================
const String StereoDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int StereoDelayAudioProcessor::getNumParameters()
{
    return kNumParameters;
}

float StereoDelayAudioProcessor::getParameter(int index)
{
    // This method will be called by the host, probably on the audio thread, so
    // it's absolutely time-critical. Don't use critical sections or anything
    // UI-related, or anything at all that may block in any way!
    switch(index)
    {
        case kDelayTimeParam:
            return delayTime;
        
        case kFeedbackParam:
            return feedback;
            
        default:
            return 0.0f;
    }
}

const String StereoDelayAudioProcessor::getParameterName(int index)
{
    switch(index)
    {
        case kDelayTimeParam:
            return "Delay Time";
            
        case kFeedbackParam:
            return "Feedback";
            
        default:
            break;
    }
    
    return String::empty;
}

void StereoDelayAudioProcessor::setParameter(int index, float value)
{
    // This method will be called by the host, probably on the audio thread, so
    // it's absolutely time-critical. Don't use critical sections or anything
    // UI-related, or anything at all that may block in any way!
    switch(index)
    {
        case kDelayTimeParam:
            delayTime = value;
            
            // IMPORTANT: calculate the position of the readIndex relative to the write
            // i.e. the delay time in samples
            readIndex = (int)(writeIndex - (delayTime * delayBufferLength) + delayBufferLength) % delayBufferLength;
            break;
        case kFeedbackParam:
            feedback = value;
            break;
        
        default:
            break;
    }
}

const String StereoDelayAudioProcessor::getParameterText(int index)
{
    return String (getParameter(index), 2);
}

bool StereoDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StereoDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double StereoDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StereoDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int StereoDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StereoDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String StereoDelayAudioProcessor::getProgramName (int index)
{
    return String();
}

void StereoDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void StereoDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    // Maximum delay of 1 second
    delayBufferLength = (int)(sampleRate);
    
    // Set the bufer to 1 channel of the size of delayBufferLength
    delayBuffer.setSize(1, delayBufferLength);
    
    // Set all samples in the buffer to zero
    delayBuffer.clear();
    
    // IMPORTANT
    // Calculate the position of the read index relative to the write index
    // i.e. the delay time in samples
    readIndex = (int)(writeIndex - (delayTime * delayBufferLength) + delayBufferLength) % delayBufferLength;
}

void StereoDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool StereoDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void StereoDelayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    float* delayData = delayBuffer.getWritePointer(0);
    float wetMix = 0.5;
    
    float* channelData = buffer.getWritePointer (0);
    // ..do something to the data...
    
    for (int i = 0; i < buffer.getNumSamples(); i++)
    {
        // Calculate the next output sample (current input sample + delayed version)
        float outputSample = (channelData[i] + (wetMix * delayData[readIndex]));
        
        // Write the current input into the delay buffer along with the delayed sample
        delayData[writeIndex] = channelData[i] + (delayData[readIndex] * feedback);
        
        // Increment read and write index, check to see if it's greater than buffer length
        // if yes, wrap back around to zero
        if (++readIndex >= delayBufferLength)
        {
            readIndex = 0;
        }
        
        if (++writeIndex >= delayBufferLength)
        {
            writeIndex = 0;
        }
        
        // Play the resulting calculated output sample
        channelData[i] = outputSample;
    }
}

//==============================================================================
bool StereoDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* StereoDelayAudioProcessor::createEditor()
{
    return new StereoDelayAudioProcessorEditor (*this);
}

//==============================================================================
void StereoDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void StereoDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StereoDelayAudioProcessor();
}
