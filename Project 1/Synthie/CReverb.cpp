#include "pch.h"
#include "CReverb.h"
#include <algorithm>
#undef max
#undef min


CReverb::CReverb()
{
}

void CReverb::Start()
{
    if (m_source)
        m_source->Start();

    // Convert delay time to number of samples
    m_delaySamples = int(m_delay * GetSampleRate() + 0.5);

    // Make sure we have at least one second of buffer
    int bufferSize = std::max(m_delaySamples, int(GetSampleRate())) * 2; // stereo
    m_delayBuffer.assign(bufferSize, 0.0);

    m_delayPos = 0;
}

bool CReverb::Generate()
{
    if (!m_source)
        return false;

    // Generate a frame from the source node
    if (!m_source->Generate())
        return false;

    double inL = m_source->Frame(0);
    double inR = m_source->Frame(1);

    // Compute read position (delay tap)
    int len = (int)m_delayBuffer.size();
    int readPos = (m_delayPos - m_delaySamples * 2 + len) % len; // *2 for stereo interleaving

    // Get delayed samples
    double delayedL = m_delayBuffer[readPos];
    double delayedR = m_delayBuffer[readPos + 1];

    // Mix input and delayed signals
    double outL = (1.0 - m_wet) * inL + m_wet * delayedL;
    double outR = (1.0 - m_wet) * inR + m_wet * delayedR;

    // Write new samples into the delay buffer with feedback
    m_delayBuffer[m_delayPos] = inL + delayedL * m_feedback;
    m_delayBuffer[m_delayPos + 1] = inR + delayedR * m_feedback;

    // Move circular buffer index
    m_delayPos = (m_delayPos + 2) % len;

    // Set output frame
    auto clamp = [](double x, double low, double high)
    {
        return x < low ? low : (x > high ? high : x);
    };

    m_frame[0] = clamp(outL, -1.0, 1.0);
    m_frame[1] = clamp(outR, -1.0, 1.0);

    return true;
}
