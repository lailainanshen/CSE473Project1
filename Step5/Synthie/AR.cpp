#include "stdafx.h"
#include "AR.h"


CAR::CAR(void)
{
	m_attack = .1;
	m_release = .2;
	m_duration = 1;
	m_bpm = 120;
}


CAR::~CAR(void)
{
}

void CAR::Start() {
	m_time = 0;
}

bool CAR::Generate() {
	// Tell the component to generate an audio sample
	m_source->Generate();

	// Read the component's sample and make it our resulting frame.
	if (m_time * m_bpm / 60 < m_attack) {
		double amplitude = 20 * m_time;
		m_frame[0] = amplitude * m_source->Frame(0);
		m_frame[1] = amplitude * m_source->Frame(1);
	}
	else if (m_duration - m_time * m_bpm / 60 < m_release) {
		double amplitude = 20 * ((m_duration - m_time * m_bpm * 60) / (m_duration - m_release));
		m_frame[0] = amplitude * m_source->Frame(0);
		m_frame[1] = amplitude * m_source->Frame(1);
	}
	m_frame[0] = m_source->Frame(0);
	m_frame[1] = m_source->Frame(1);

	// Update time
	m_time += GetSamplePeriod();

	// We return true until the time reaches the duration.
	return m_time * m_bpm / 60 < m_duration;
}
