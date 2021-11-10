#pragma once
#include "msxml2.h"
#include <list>
#include <vector>
#include "Instrument.h"
#include "CEffect.h"
#include "Note.h"
#include "CEffectbuild.h"
#include "resource.h"

class CSynthesizer
{
public:
	CSynthesizer(void);
	virtual ~CSynthesizer(void);

	//! Number of audio channels
	int GetNumChannels() { return m_channels; }

	//! Sample rate in samples per second
	double GetSampleRate() { return m_sampleRate; }

	//! Sample period in seconds (1/samplerate)
	double GetSamplePeriod() { return m_samplePeriod; }

	//! Set the number of channels
	void SetNumChannels(int n) { m_channels = n; }

	//! Set the sample rate
	void SetSampleRate(double s) { m_sampleRate = s;  m_samplePeriod = 1.0 / s; }


	void Start(void);
	bool Generate(double* frame);

	//! Get the time since we started generating audio
	double GetTime() { return m_time; }

	void Clear(void);

	void OpenScore(CString& filename);

private:
	void XmlLoadScore(IXMLDOMNode* xml);
	void XmlLoadInstrument(IXMLDOMNode* xml);
	void XmlLoadNote(IXMLDOMNode* xml, std::wstring& instrument);
	void XmlLoadEffect(IXMLDOMNode* xml, std::wstring& instrument);

	int		m_channels;
	double	m_sampleRate;
	double	m_samplePeriod;
	double  m_time;

	int     m_beatspermeasure;	//!< Beats per measure
	double  m_secperbeat;		//!< Seconds per beat

	std::list<CInstrument*>  m_instruments;
	CEffect* m_effects[6];
	std::vector<CNote> m_notes;

	CEffectbuild m_factory;

	double  m_bpm;				//!< Beats per minute
	int m_currentNote;          //!< The current note we are playing
	int m_measure;              //!< The current measure
	double m_beat;              //!< The current beat within the measure
};

