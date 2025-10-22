#pragma once
#include "CAudioNode.h"
class CAR : public CAudioNode
{
public:
	CAR();

    void SetSource(CAudioNode* source) { m_source = source; }
    void Start();
    bool Generate();

    void SetAttack(double a) { m_attack = a; }
    void SetRelease(double r) { m_release = r; }
    void SetDuration(double d) { m_duration = d; }

private:
    CAudioNode* m_source = nullptr;
    double m_attack = 0.05;
    double m_release = 0.05;
    double m_duration = 0.1;
    double m_time = 0;
};

