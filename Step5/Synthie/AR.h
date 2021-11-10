#pragma once
#include "AudioNode.h"
class CAR : public CAudioNode
{
public:
	CAR(void);
	virtual ~CAR(void);
	void SetSource(CAudioNode& node) { m_source = &node; }
	void Start();
	bool Generate();
	void SetBpm(double bpm) { m_bpm = bpm; }
	void SetAttack(double attack) { m_attack = attack; }
	void SetRelease(double release) { m_release = release; }

private:
	double m_attack;
	double m_release;
	double m_duration;
	double m_time;
	double m_bpm;
	CAudioNode* m_source;
};

