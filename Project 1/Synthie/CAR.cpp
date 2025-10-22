#include "pch.h"
#include "CAR.h"


CAR::CAR() 
{
    m_source = nullptr;
    m_attack = 0.05;
    m_release = 0.05;
    m_duration = 0.1;
    m_time = 0;
}

void CAR::Start()
{
    m_time = 0;
    if (m_source) m_source->Start();
}

bool CAR::Generate()
{
    if (!m_source) return false;

    // Generate source first
    bool valid = m_source->Generate();

    // Apply AR envelope
    double amp = 1.0;
    if (m_time < m_attack) amp = m_time / m_attack;
    else if (m_time > m_duration - m_release) amp = (m_duration - m_time) / m_release;
    if (amp < 0) amp = 0;

    for (int c = 0; c < 2; c++)
        m_frame[c] = amp * m_source->Frame(c);

    m_time += GetSamplePeriod();
    return m_time < m_duration && valid;
}