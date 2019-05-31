/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace gin;

const char* PAPUAudioProcessor::paramPulse1Sweep      = "sweep1";
const char* PAPUAudioProcessor::paramPulse1Shift      = "shift1";
const char* PAPUAudioProcessor::paramPulse1Duty       = "duty1";
const char* PAPUAudioProcessor::paramPulse1A          = "A1";
const char* PAPUAudioProcessor::paramPulse1R          = "R1";
const char* PAPUAudioProcessor::paramPulse1OL         = "OL1";
const char* PAPUAudioProcessor::paramPulse1OR         = "OR1";
const char* PAPUAudioProcessor::paramPulse1Tune       = "tune1";
const char* PAPUAudioProcessor::paramPulse1Fine       = "fine1";

const char* PAPUAudioProcessor::paramPulse2Duty       = "duty2";
const char* PAPUAudioProcessor::paramPulse2A          = "A2";
const char* PAPUAudioProcessor::paramPulse2R          = "R2";
const char* PAPUAudioProcessor::paramPulse2OL         = "OL2";
const char* PAPUAudioProcessor::paramPulse2OR         = "OR2";
const char* PAPUAudioProcessor::paramPulse2Tune       = "tune2";
const char* PAPUAudioProcessor::paramPulse2Fine       = "fine2";

const char* PAPUAudioProcessor::paramNoiseOL          = "OLN";
const char* PAPUAudioProcessor::paramNoiseOR          = "ORL";
const char* PAPUAudioProcessor::paramNoiseShift       = "shiftN";
const char* PAPUAudioProcessor::paramNoiseStep        = "stepN";
const char* PAPUAudioProcessor::paramNoiseRatio       = "ratioN";
const char* PAPUAudioProcessor::paramNoiseA           = "AN";
const char* PAPUAudioProcessor::paramNoiseR           = "AR";

const char* PAPUAudioProcessor::paramOutput           = "output";

//==============================================================================
String percentTextFunction (const Parameter& p, float v)
{
    return String::formatted("%.0f%%", v / p.getUserRangeEnd() * 100);
}

String enableTextFunction (const Parameter&, float v)
{
    return v > 0.0f ? "On" : "Off";
}

String dutyTextFunction (const Parameter&, float v)
{
    const int duty = int (v);
    switch (duty)
    {
        case 0: return "12.5%";
        case 1: return "25%";
        case 2: return "50%";
        case 3: return "75%";
    }
    return "";
}

String arTextFunction (const Parameter&, float v)
{
    return String::formatted("%.1f s", v * 1.0/64.0 * 16);
}

String stTextFunction (const Parameter&, float v)
{
    String str;
    switch (abs (int (v)))
    {
        case 0: str = "Off"; break;
        case 1: str = "7.8 ms"; break;
        case 2: str = "15.6 ms"; break;
        case 3: str = "23.4 ms"; break;
        case 4: str = "31.3 ms"; break;
        case 5: str = "39.1 ms"; break;
        case 6: str = "46.9 ms"; break;
        case 7: str = "54.7 ms"; break;
    }
    
    if (v < 0)
        str = "-" + str;
    
    return str;
}

String stepTextFunction (const Parameter&, float v)
{
    return v > 0.0f ? "15" : "7";
}

String intTextFunction (const Parameter&, float v)
{
    return String (int (v));
}

//==============================================================================
PAPUAudioProcessor::PAPUAudioProcessor()
{
    addPluginParameter (new Parameter (paramPulse1OL,        "Pulse 1 OL",         "Left",        "",   0.0f, 1.0f, 1.0f, 1.0f, 1.0f, enableTextFunction));
    addPluginParameter (new Parameter (paramPulse1OR,        "Pulse 1 OR",         "Right",       "",   0.0f, 1.0f, 1.0f, 1.0f, 1.0f, enableTextFunction));
    addPluginParameter (new Parameter (paramPulse1Duty,      "Pulse 1 Duty",       "PW",          "",   0.0f, 3.0f, 1.0f, 0.0f, 1.0f, dutyTextFunction));
    addPluginParameter (new Parameter (paramPulse1A,         "Pulse 1 A",          "Attack",      "",   0.0f, 7.0f, 1.0f, 1.0f, 1.0f, arTextFunction));
    addPluginParameter (new Parameter (paramPulse1R,         "Pulse 1 R",          "Release",     "",   0.0f, 7.0f, 1.0f, 1.0f, 1.0f, arTextFunction));
    addPluginParameter (new Parameter (paramPulse1Tune,      "Pulse 1 Tune",       "Tune",        "", -48.0f, 48.0f, 1.0f, 0.0f, 1.0f, intTextFunction));
    addPluginParameter (new Parameter (paramPulse1Fine,      "Pulse 1 Tune Fine",  "Fine",        "", -100.0f, 100.0f, 1.0f, 0.0f, 1.0f, intTextFunction));
    addPluginParameter (new Parameter (paramPulse1Sweep,     "Pulse 1 Sweep",      "Sweep",       "",  -7.0f, 7.0f, 1.0f, 0.0f, 1.0f, stTextFunction));
    addPluginParameter (new Parameter (paramPulse1Shift,     "Pulse 1 Shift",      "Shift",       "",   0.0f, 7.0f, 1.0f, 0.0f, 1.0f, intTextFunction));
    
    addPluginParameter (new Parameter (paramPulse2OL,        "Pulse 2 OL",         "Left",        "",   0.0f, 1.0f, 1.0f, 0.0f, 1.0f, enableTextFunction));
    addPluginParameter (new Parameter (paramPulse2OR,        "Pulse 2 OR",         "Right",       "",   0.0f, 1.0f, 1.0f, 0.0f, 1.0f, enableTextFunction));
    addPluginParameter (new Parameter (paramPulse2Duty,      "Pulse 2 Duty",       "PW",          "",   0.0f, 3.0f, 1.0f, 0.0f, 1.0f, dutyTextFunction));
    addPluginParameter (new Parameter (paramPulse2A,         "Pulse 2 A",          "Attack",      "",   0.0f, 7.0f, 1.0f, 1.0f, 1.0f, arTextFunction));
    addPluginParameter (new Parameter (paramPulse2R,         "Pulse 2 R",          "Release",     "",   0.0f, 7.0f, 1.0f, 1.0f, 1.0f, arTextFunction));
    addPluginParameter (new Parameter (paramPulse2Tune,      "Pulse 2 Tune",       "Tune",        "", -48.0f, 48.0f, 1.0f, 0.0f, 1.0f, intTextFunction));
    addPluginParameter (new Parameter (paramPulse2Fine,      "Pulse 2 Tune Fine",  "Fine",        "", -100.0f, 100.0f, 1.0f, 0.0f, 1.0f, intTextFunction));
    
    addPluginParameter (new Parameter (paramNoiseOL,         "Noise OL",           "Left",        "",   0.0f, 1.0f, 1.0f, 0.0f, 1.0f, enableTextFunction));
    addPluginParameter (new Parameter (paramNoiseOR,         "Noise OR",           "Right",       "",   0.0f, 1.0f, 1.0f, 0.0f, 1.0f, enableTextFunction));
    addPluginParameter (new Parameter (paramNoiseA,          "Noise A",            "Attack",      "",   0.0f, 7.0f, 1.0f, 1.0f, 1.0f, arTextFunction));
    addPluginParameter (new Parameter (paramNoiseR,          "Noise R",            "Release",     "",   0.0f, 7.0f, 1.0f, 1.0f, 1.0f, arTextFunction));
    addPluginParameter (new Parameter (paramNoiseShift,      "Noise Shift",        "Shift",       "",   0.0f, 13.0f, 1.0f, 0.0f, 1.0f, intTextFunction));
    addPluginParameter (new Parameter (paramNoiseStep,       "Noise Step",         "Steps",       "",   0.0f, 1.0f, 1.0f, 0.0f, 1.0f, stepTextFunction));
    addPluginParameter (new Parameter (paramNoiseRatio,      "Noise Ratio",        "Ratio",       "",   0.0f, 7.0f, 1.0f, 0.0f, 1.0f, intTextFunction));
    
    addPluginParameter (new Parameter (paramOutput,          "Output",             "Output",      "",   0.0f, 7.0f, 1.0f, 15.0f, 1.0f, percentTextFunction));
}

PAPUAudioProcessor::~PAPUAudioProcessor()
{
}

//==============================================================================
void PAPUAudioProcessor::prepareToPlay (double sampleRate, int /*samplesPerBlock*/)
{
    outputSmoothed.reset (sampleRate, 0.05);
    
    apu.treble_eq( -20.0 ); // lower values muffle it more
    buf.bass_freq( 461 ); // higher values simulate smaller speaker
    
    buf.clock_rate (4194304);
    buf.set_sample_rate (long (sampleRate));

    apu.output (buf.center(), buf.left(), buf.right());

    writeReg (0xff26, 0x8f, true);
}

void PAPUAudioProcessor::releaseResources()
{
}

void PAPUAudioProcessor::runUntil (int& done, AudioSampleBuffer& buffer, int pos)
{
    int todo = jmin (pos, buffer.getNumSamples()) - done;

    while (todo > 0)
    {
        if (buf.samples_avail() > 0)
        {
            blip_sample_t out[1024];
            
            int count = int (buf.read_samples (out, jmin (todo, 1024 / 2, (int) buf.samples_avail())));
        
            float* data0 = buffer.getWritePointer (0, done);
            float* data1 = buffer.getWritePointer (1, done);
            
            for (int i = 0; i < count; i++)
            {
                data0[i] = out[i * 2 + 0] / 32768.0f;
                data1[i] = out[i * 2 + 1] / 32768.0f;
            }
            
            done += count;
            todo -= count;
        }
        else
        {
            time = 0;

            bool stereo = apu.end_frame (1024);
            buf.end_frame (1024, stereo);
        }
    }
}

void PAPUAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midi)
{
    uint16_t reg;
    
    reg = uint16_t (0x08 | parameterIntValue (paramOutput));
    writeReg (0xff24, reg, false);
    
    reg = (parameterIntValue (paramPulse1OL) ? 0x10 : 0x00) |
          (parameterIntValue (paramPulse1OR) ? 0x01 : 0x00) |
          (parameterIntValue (paramPulse2OL) ? 0x20 : 0x00) |
          (parameterIntValue (paramPulse2OR) ? 0x02 : 0x00) |
          (parameterIntValue (paramNoiseOL)  ? 0x80 : 0x00) |
          (parameterIntValue (paramNoiseOR)  ? 0x08 : 0x00);
    
    writeReg (0xff25, reg, false);
    
    int done = 0;
    runOscs (lastNote, false);
    runUntil (done, buffer, 0);
    
    int pos = 0;
    MidiMessage msg;
    MidiBuffer::Iterator itr (midi);
    while (itr.getNextEvent (msg, pos))
    {
        runUntil (done, buffer, pos);
        
        if (msg.isNoteOn())
        {
            noteQueue.add (msg.getNoteNumber());
            velocity = msg.getVelocity();
        }
        else if (msg.isNoteOff())
        {
            noteQueue.removeFirstMatchingValue (msg.getNoteNumber());
            
        }
        else if (msg.isAllNotesOff())
        {
            noteQueue.clear();
        }
        
        const int curNote = noteQueue.size() > 0 ? noteQueue.getLast() : -1;
        
        if (lastNote != curNote)
        {
            runOscs (curNote, true);
            lastNote = curNote;
        }
    }
    
    runUntil (done, buffer, buffer.getNumSamples());
    
    float* dataL = buffer.getWritePointer (0);
    float* dataR = buffer.getWritePointer (1);
    
    ScopedLock sl (editorLock);
    if (editor)
    {
        float* mono = (float*) alloca (buffer.getNumSamples() * sizeof (float));
        
        for (int i = 0; i < buffer.getNumSamples(); i++)
            mono[i] = (dataL[i] + dataR[i]) / 2.0f;
        
        editor->scope.addSamples (mono, buffer.getNumSamples());
    }
}

void PAPUAudioProcessor::runOscs (int curNote, bool force)
{
    if (curNote != -1)
    {
        // Ch 1
        uint8_t sweep = uint8_t (std::abs (parameterIntValue (paramPulse1Sweep)));
        uint8_t neg   = parameterIntValue (paramPulse1Sweep) < 0;
        uint8_t shift = uint8_t (parameterIntValue (paramPulse1Shift));
        
        writeReg (0xff10, (sweep << 4) | ((neg ? 1 : 0) << 3) | shift, force);
        writeReg (0xff11, (parameterIntValue (paramPulse1Duty) << 6), force);
        
        float freq1 = float (getMidiNoteInHertz (curNote + parameterIntValue (paramPulse1Tune) + parameterIntValue (paramPulse1Fine) / 100.0f));
        uint16_t period1 = uint16_t (((4194304 / freq1) - 65536) / -32);
        writeReg (0xff13, period1 & 0xff, force);
        uint8_t a1 = uint8 (parameterIntValue (paramPulse1A));
        writeReg (0xff12, a1 ? (0x00 | (1 << 3) | a1) : 0xf0, force);
        writeReg (0xff14, 0x80 | ((period1 >> 8) & 0x07), force);
        
        // Ch 2
        writeReg (0xff16, (parameterIntValue (paramPulse2Duty) << 6), force);
        
        float freq2 = float (getMidiNoteInHertz (curNote + parameterIntValue (paramPulse2Tune) + parameterIntValue (paramPulse2Fine) / 100.0f));
        uint16_t period2 = uint16_t (((4194304 / freq2) - 65536) / -32);
        writeReg (0xff18, period2 & 0xff, force);
        uint8_t a2 = uint8_t (parameterIntValue (paramPulse2A));
        writeReg (0xff17, a2 ? (0x00 | (1 << 3) | a2) : 0xf0, force);
        writeReg (0xff19, 0x80 | ((period2 >> 8) & 0x07), force);
        
        // Noise
        uint8_t aN = uint8_t (parameterIntValue (paramNoiseA));
        writeReg (0xff21, aN ? (0x00 | (1 << 3) | aN) : 0xf0, force);
        writeReg (0xff22, (parameterIntValue (paramNoiseShift) << 4) |
                            (parameterIntValue (paramNoiseStep)  << 3) |
                            (parameterIntValue (paramNoiseRatio)), force);
        writeReg (0xff23, 0x80, force);
    }
    else
    {
        uint8_t r1 = uint8_t (parameterIntValue (paramPulse1R));
        writeReg (0xff12, r1 ? (0xf0 | (0 << 3) | r1) : 0, force);
        
        uint8_t r2 = uint8_t (parameterIntValue (paramPulse2R));
        writeReg (0xff17, r2 ? (0xf0 | (0 << 3) | r2) : 0, force);
        
        uint8_t rN = uint8_t (parameterIntValue (paramNoiseR));
        writeReg (0xff21, rN ? (0xf0 | (0 << 3) | rN) : 0, force);
    }
}

void PAPUAudioProcessor::writeReg (int reg, int value, bool force)
{
    auto itr = regCache.find (reg);
    if (force || itr == regCache.end() || itr->second != value)
    {
        regCache[reg] = value;
        apu.write_register (clock(), reg, value);
    }
}
//==============================================================================
bool PAPUAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* PAPUAudioProcessor::createEditor()
{
    editor = new PAPUAudioProcessorEditor (*this);
    return editor;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PAPUAudioProcessor();
}
