#include "stdafx.h"
#include "CEffectbuild.h"
#include <algorithm>

CEffectbuild::CEffectbuild(void)
{
	current_Effect = 0;
}


CEffectbuild::~CEffectbuild(void)
{
}

void CEffectbuild::nextEffect() {
	if (effect_Notes.size() > 0 || current_Effect < effect_Notes.size()) {
		active_Effects[effect_Notes[current_Effect].Instrument()] = effect_Notes[current_Effect];
		current_Effect++;
	}
}

void CEffectbuild::fitEffects(CInstrument* instrument, const std::wstring& instrumentName) {
	if (active_Effects.find(instrumentName) == active_Effects.end()) {
		return;
	}
	CNote effectNote = active_Effects[instrumentName];
	for (int i = 0; i <= 5; i++) {
		instrument->SetSend(i, effectNote.GetSend(i));
	}
}

void CEffectbuild::start() {
	std::sort(effect_Notes.begin(), effect_Notes.end());
}

void CEffectbuild::clear() {
	effect_Notes.clear();
	active_Effects.clear();
	current_Effect = 0;
}