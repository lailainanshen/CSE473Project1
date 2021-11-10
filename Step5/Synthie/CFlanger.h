#pragma once
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include "CCitcuarEffect.h"

class CFlanger:
	public CCitcuarEffect
{
public:
	CFlanger(void);
	virtual ~CFlanger(void);
	virtual void ProcessWet(double* frame);
private:
	double phase_Angle;
};

