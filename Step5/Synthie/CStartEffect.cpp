#include "stdafx.h"
#include "CStartEffect.h"
#include <algorithm>

CStartEffect::CStartEffect(void)
{
	currentEffect = 0;
}


CStartEffect::~CStartEffect(void)
{
}

void CStartEffect::nextEffect() {
	if (m_effectNotes.size() > 0 || currentEffect < m_effectNotes.size()) {
		m_activeEffects[m_effectNotes[currentEffect].Instrument()] = m_effectNotes[currentEffect];
		currentEffect++;
	}
}

void CStartEffect::fitEffects(CInstrument* instrument, const std::wstring& instrumentName) {
	if (m_activeEffects.find(instrumentName) == m_activeEffects.end()) {
		return;
	}
	CNote effectNote = m_activeEffects[instrumentName];
	for (int i = 0; i <= 5; i++) {
		instrument->SetSend(i, effectNote.GetSend(i));
	}
}

void CStartEffect::start() {
	std::sort(m_effectNotes.begin(), m_effectNotes.end());
}

void CStartEffect::clear() {
	m_effectNotes.clear();
	m_activeEffects.clear();
	currentEffect = 0;
}