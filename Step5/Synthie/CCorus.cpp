#include "stdafx.h"
#include "CCorus.h"

CCorus::CCorus(void)
{
	phase_Angle = 0;
}


CCorus::~CCorus(void)
{
}

void CCorus::ProcessWet(double* frame) {
	for (int i = 0; i < 2; i++) {
		inList[(wrloc + i) % 15000] =  frame[i];
	}
	int delaySize = int(88.2 * (25 + 2 * sin(phase_Angle)));
	phase_Angle += 2.849517098;
	for (int i = 0; i < 2; i++) {
		frame[i] = (inList[(wrloc + i + delaySize) % 15000]+frame[i])/2;
		outList[(wrloc + i) / 15000] = frame[i];
	}

	wrloc = (wrloc+2) % 15000;
}