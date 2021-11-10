#pragma once
#define _USE_MATH_DEFINES 
#include <cmath>
#include "CCitcuarEffect.h"

/*
Generate chorus
*/

class CCorus :
	public CCitcuarEffect
{
public:
	CCorus(void);
	virtual ~CCorus(void);
	virtual void ProcessWet(double* frame);
private:
	double phase_Angle;
};
