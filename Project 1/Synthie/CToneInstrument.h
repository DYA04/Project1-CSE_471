#pragma once
#include "CInstrument.h"
#include "CSineWave.h"
#include "CAR.h"
#include "CReverb.h"


class CToneInstrument : public CInstrument
{
public:

    CToneInstrument();

    virtual void Start();
    virtual bool Generate();

    void SetNote(CNote* note);

    void SetFreq(double f) { m_sinewave.SetFreq(f); }
    void SetAmplitude(double a) { m_sinewave.SetAmplitude(a); }
    void SetDuration(double d) { m_duration = d; }

    void SetUseReverb(bool use) { m_useReverb = use; }


private:
    CSineWave m_sinewave;
    double m_duration;
    double m_time;
    CAR m_ar;
    CReverb m_reverb;
    bool m_useReverb = false;

};

