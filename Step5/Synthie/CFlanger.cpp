#include "stdafx.h"
#include "CFlanger.h"
CFlanger::CFlanger(void)
{
	phase_Angle = 0;

}


CFlanger::~CFlanger(void)
{
}

void CFlanger::ProcessWet(double* frame) {
	int delaySize = int(88.2 * (6 + 4 * sin(phase_Angle)));
	int otherDelaySize = int(88.2 * (10 + 8 * cos(phase_Angle)));
	for (int i = 0; i < 2; i++) {
		inList[(wrloc + i) % 15000] = frame[i];
	}
	phase_Angle += 1.4435827/(10*5);
	for (int i = 0; i < 2; i++) {
		frame[i] += inList[(wrloc + i + delaySize) % 15000] * (0.75 + 0.25 * sin(phase_Angle * 2));
		frame[i] += inList[(wrloc + i + otherDelaySize) % 15000] * (0.75 + 0.25 * sin(2 * phase_Angle * 2));
		frame[i] /= 3;
	}
	for (int i = 0; i < 2; i++) {
		outList[(wrloc + i) / 15000] = frame[i];
	}
	wrloc = (wrloc + 2) %  15000;
}