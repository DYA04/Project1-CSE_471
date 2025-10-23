#pragma once
#include "CAudioNode.h"
#include <vector>

/**
 * Simple reverb effect node.
 * Uses a delay buffer with feedback to simulate room reflections.
 */
class CReverb : public CAudioNode
{
public:
    CReverb();

    void Start() override;
    bool Generate() override;

    //! Set the input source node
    void SetSource(CAudioNode* source) { m_source = source; }

    //! Set the delay time in seconds
    void SetDelay(double delay) { m_delay = delay; }

    //! Set feedback amount (0.0 - 1.0)
    void SetFeedback(double feedback) { m_feedback = feedback; }

    //! Set wet mix amount (0.0 - 1.0)
    void SetWet(double wet) { m_wet = wet; }

private:
    CAudioNode* m_source = nullptr;   //!< The audio source feeding this effect
    std::vector<double> m_delayBuffer; //!< Circular delay buffer
    int m_delayPos = 0;               //!< Write position in the circular buffer
    int m_delaySamples = 0;           //!< Delay length in samples

    double m_feedback = 0.4;          //!< Feedback factor
    double m_wet = 0.3;               //!< Wet (reverberated) mix
    double m_delay = 0.25;            //!< Delay time in seconds
};
