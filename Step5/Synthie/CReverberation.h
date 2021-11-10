#pragma once
#include "CCitcuarEffect.h"

class CReverberation :
	public CCitcuarEffect
{
public:
	CReverberation(void);
	virtual ~CReverberation(void);
	virtual void ProcessWet(double* frame);
};



