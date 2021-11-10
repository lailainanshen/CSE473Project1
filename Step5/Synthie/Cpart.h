#pragma once
#include "instrument.h"
#include "SineWave.h"
#include <string>
#include <vector>

class Cpart :
	public CInstrument
{
public:
	Cpart(void);
	Cpart(double);
	virtual ~Cpart(void);

	virtual void Start();
	virtual bool Generate();

	void SetFreq(double f) { m_freq = f; }
	void SetDuration(double d) { m_duration = d; }
	void SetToneWheels(WCHAR* setting);
	virtual void SetNote(CNote* note);

private:
	void AR(double*);
	void Leslie(double*);
	double m_duration;
	double m_time1;
	double m_time2;
	double m_bpm;
	double m_freq;
	double m_amp;
	double m_chorus[2];
	int PlayChorus;
	std::vector<char> m_tonewheels;
	std::vector<double> m_rad1;
	std::vector<double> m_rad2;
};

