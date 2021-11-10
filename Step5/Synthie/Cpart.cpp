#include "stdafx.h"
#include "Cpart.h"
#include "Notes.h"

Cpart::Cpart(void)
{
	m_duration = 0.1;
	m_bpm = 120;
}
Cpart::Cpart(double bpm)
{
	m_bpm = bpm;
}

Cpart::~Cpart(void)
{
}

void Cpart::Start()
{
	m_time1 = 0;
	m_time2 = 0;
	m_chorus[0] = 0;
	m_chorus[1] = 0;
	PlayChorus = 0;
	m_duration = m_duration * (1 / (m_bpm / 60));
}


bool Cpart::Generate()
{
	if (PlayChorus)
	{
		m_time1 += GetSamplePeriod() / 2;
		m_frame[0] = m_chorus[0];
		m_frame[1] = m_chorus[1];
		AR(m_frame);
		PlayChorus = 0;
		return m_time1 < m_duration;
	}

	m_frame[0] = 0;
	m_frame[1] = 0;

	double bar_freq = 0;

	for (unsigned i = 0; i < m_tonewheels.size(); i++)
	{
		switch (i)
		{
		case 0:
			bar_freq = m_freq * 1;
			break;
		case 1:
			bar_freq = m_freq * 3;
			break;
		case 2:
			bar_freq = m_freq * 2;
			break;
		case 3:
			bar_freq = m_freq * 4;
			break;
		case 4:
			bar_freq = m_freq * 6;
			break;
		case 5:
			bar_freq = m_freq * 8;
			break;
		case 6:
			bar_freq = m_freq * 10;
			break;
		case 7:
			bar_freq = m_freq * 12;
			break;
		case 8:
			bar_freq = m_freq * 16;
			break;
		}

		switch (m_tonewheels[i])
		{
		case 0:
			m_amp = 0;
			break;
		case 1:
			m_amp = 0.0089;
			break;
		case 2:
			m_amp = 0.0126;
			break;
		case 3:
			m_amp = 0.0178;
			break;
		case 4:
			m_amp = 0.0251;
			break;
		case 5:
			m_amp = 0.0355;
			break;
		case 6:
			m_amp = 0.0501;
			break;
		case 7:
			m_amp = 0.0708;
			break;
		case 8:
			m_amp = 0.1;
			break;
		}

		m_frame[0] += m_amp * sin(m_rad1[i]);
		m_frame[1] = m_frame[0];

		double diff = bar_freq * (0.2 * sin(m_rad2[i]));

		m_rad1[i] += (2 * PI * (bar_freq + diff)) / GetSampleRate();
		m_rad2[i] += (2 * PI * bar_freq) / GetSampleRate();
	}

	Leslie(m_frame);

	AR(m_frame);

	m_chorus[0] = m_frame[0];
	m_chorus[1] = m_frame[1];

	m_time1 += GetSamplePeriod() / 2;

	PlayChorus = 1;

	return m_time1 < m_duration;
}

void Cpart::Leslie(double* frame)
{
	m_frame[0] = m_frame[0] * (1 - (0.4 * sin(2 * PI * m_time2)));
	m_frame[1] = m_frame[1] * (1 - (0.4 * cos(2 * PI * m_time2)));
	m_time2 += GetSamplePeriod() * 3;
}

void Cpart::AR(double* frame)
{
	if (m_time1 < 0.05)
	{
		frame[0] = frame[0] * (m_time1 / 0.05);
		frame[1] = frame[1] * (m_time1 / 0.05);
	}

	else if (m_duration - m_time1 < 0.05)
	{
		frame[0] = frame[0] * (m_duration - m_time1) / 0.05;
		frame[1] = frame[1] * (m_duration - m_time1) / 0.05;
	}
}

void Cpart::SetToneWheels(WCHAR* setting)
{
	m_tonewheels.resize(9);
	m_rad1.resize(9);
	m_rad2.resize(9);
	int count = 0;
	int num = wcslen(setting);

	for (int i = 0; i < num; i++)
	{
		m_tonewheels[count] = (char)setting[i];
		count++;
	}
}

void Cpart::SetNote(CNote* note)
{
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i < len; i++)
	{
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		CComBSTR name;
		attrib->get_nodeName(&name);

		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			SetDuration(value.dblVal);
		}
		else if (name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
		}
		else if (name == "drawbar")
		{
			SetToneWheels(value.bstrVal);
		}

	}

}