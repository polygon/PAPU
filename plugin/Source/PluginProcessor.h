/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "gb_apu/Gb_Apu.h"
#include "gb_apu/Multi_Buffer.h"
#include "slCommon.h"

//==============================================================================
/**
*/
class PAPUAudioProcessorEditor;
class PAPUAudioProcessor : public slProcessor
{
public:
    //==============================================================================
    PAPUAudioProcessor();
    ~PAPUAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    
    static const char* paramPulse1OL;
    static const char* paramPulse1OR;
    static const char* paramPulse1Duty;
    static const char* paramPulse1A;
    static const char* paramPulse1R;
    static const char* paramPulse1Tune;
    static const char* paramPulse1Fine;
    static const char* paramPulse1Sweep;
    static const char* paramPulse1Shift;
    
    static const char* paramPulse2OL;
    static const char* paramPulse2OR;
    static const char* paramPulse2Duty;
    static const char* paramPulse2A;
    static const char* paramPulse2R;
    static const char* paramPulse2Tune;
    static const char* paramPulse2Fine;

    static const char* paramNoiseOL;
    static const char* paramNoiseOR;
    static const char* paramNoiseShift;
    static const char* paramNoiseStep;
    static const char* paramNoiseRatio;
    static const char* paramNoiseA;
    static const char* paramNoiseR;
    
    static const char* paramOutput;
    
private:
    void runUntil (int& done, AudioSampleBuffer& buffer, int pos);
    
    int lastNote = -1;
    int velocity = 0;
    Array<int> noteQueue;
    
    LinearSmoothedValue<float> outputSmoothed;
    Component::SafePointer<PAPUAudioProcessorEditor> editor;
    
    Gb_Apu apu;
    Stereo_Buffer buf;
    
    blip_time_t time = 0;
    
    blip_time_t clock() { return time += 4; }
    
    uint8_t last24 = 0x00;
    uint8_t last25 = 0x00;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PAPUAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
