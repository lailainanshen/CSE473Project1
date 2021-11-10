#include "stdafx.h"
#include "CDrum.h"
#include "Notes.h"
#include <math.h>
#include <random>

bool CDrum::Generate(void)
{

	int num_fram = (int)(m_time * GetSampleRate()) % 44100;
	double num_r = .995;
	double cosine = (2 * num_r * cos(2 * 3.14159 * (300)) / (1 + pow(num_r, 2)));
	double a = (1 - pow(num_r, 2)) * sin(acos(cosine));
	double amplitude = 1;
	if (m_time < .05) {
		amplitude = 20 * m_time;
	}
	else if (m_duration * 60 / m_bpm - m_time < .05)
	{
		amplitude = 20 * (m_duration * 60 / m_bpm - m_time);
	}


	sine_Wave.Generate();
	if (num_fram >= 2) {

		m_frame[0] = amplitude * (a * (white_Noise[num_fram] + sine_Wave.Frame(0))
			+ 2 * num_r * cosine * m_queue[(num_fram - 1)
			% m_queue.size()] - pow(num_r, 2) * m_queue[(num_fram - 2) % m_queue.size()]);

	}
	else
	{
		m_frame[0] = amplitude * (white_Noise[num_fram] + sine_Wave.Frame(0));

	}
	m_frame[1] = m_frame[0];
	m_queue[num_fram] = m_frame[0];

	sine_Wave.SetFreq(sine_Wave.GetFreq() - 1 / GetSampleRate() * sine_Wave.GetFreq());
	m_time += 1 / GetSampleRate();
	sine_Wave.UpdatePhase();
	return m_time * m_bpm / 60 < m_duration;

	return false;
}

void CDrum::Start(void)
{
	m_time = 0;
	return;
}

void CDrum::SetNote(CNote* note)
{
	// Get nodes and the length
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	for (int i = 0; i < len; i++)
	{

		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		CComBSTR m_name;
		attrib->get_nodeName(&m_name);

		CComVariant m_value;
		attrib->get_nodeValue(&m_value);

		if (m_name == "duration")
		{
			m_value.ChangeType(VT_R8);
			SetDuration(m_value.dblVal);
		}
		else if (m_name == "note")
		{
			SetFreq(NoteToFrequency(m_value.bstrVal));
		}
		else if (m_name == "type")
		{
			if ((char*)m_value.bstrVal == "electric")
				m_category = electric;
			else if ((char*)m_value.bstrVal == "tom1")
				m_category = tom1;
		}
	}
	return;
}

CDrum::CDrum(double bpm) : m_freq(500)
{
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0, 0.02);
	m_queue.resize(100000);

	sine_Wave.SetSampleRate(GetSampleRate());
	sine_Wave.Start();
	sine_Wave.SetAmplitude(0.3);
	m_attack = false;

	for (int i = 0; i < 44100; i++)
	{
		double m_number = distribution(generator);
		if (m_number <= 1.0 && m_number >= -1.0)
		{
			white_Noise[i] = m_number;
		}
	}
	m_bpm = bpm;
}

CDrum::CDrum(void) : m_freq(500)
{
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0, 0.1);
	m_queue.resize(100000);

	sine_Wave.SetSampleRate(GetSampleRate());
	sine_Wave.Start();
	sine_Wave.SetAmplitude(0.3);
	m_attack = false;

	for (int i = 0; i < 44100; i++)
	{
		double m_number = distribution(generator);
		if (m_number <= 1.0 && m_number >= -1.0)
		{
			white_Noise[i] = m_number;
		}
	}
}


CDrum::~CDrum(void)
{
}





