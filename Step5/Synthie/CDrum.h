#pragma once
#include "instrument.h"
#include <vector>
#include "AR.h"
#include "SineWave.h"
#include "audio/wave.h"
#include "audio/DirSoundStream.h"
#include "audio/DirSoundSource.h"
#include "audio/WaveformBuffer.h"

enum Types { electric, tom1, tom2, snare, bass, cymbal };

class CDrum :
	public CInstrument
{
public:
	CDrum(void);
	CDrum(double bpm);
	virtual ~CDrum(void);
	virtual void SetNote(CNote* note);
	virtual void Start();
	virtual bool Generate();
	void SetDuration(double duration) { m_duration = duration; }
	void SetFreq(double f) { sine_Wave.SetFreq(f); m_freq = f; }
private:
	double white_Noise[44100];
	std::vector<double> m_queue;
	Types m_category;
	std::vector<double> m_tom1;
	std::vector<double> m_tom2;
	double m_cymbals[100000];
	double m_bass[100000];
	double m_snare[100000];
	double m_duration;
	double m_time;
	double m_bpm;
	double m_freq;
	bool m_attack;
	CSineWave   sine_Wave;
	CAR m_ar;
	CDirSoundSource   m_wavein;
	int      m_numChannels;
	int      m_numSampleFrames;
	double m_clipSampleRate;
};

