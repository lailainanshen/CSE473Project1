#pragma once
#include<vector>
#include<map>
#include"Note.h"
#include"Instrument.h"

class CEffectbuild
{
public:
	CEffectbuild(void);
	virtual ~CEffectbuild(void);
	void fitEffects(CInstrument* instrument, const std::wstring& instrumentName);
	void addEffectNode(CNote& note) { effect_Notes.push_back(note); }
	void nextEffect();
	void start();
	void clear();
private:
	std::vector<CNote> effect_Notes;
	std::map<const std::wstring, CNote> active_Effects;
	int current_Effect;
};

