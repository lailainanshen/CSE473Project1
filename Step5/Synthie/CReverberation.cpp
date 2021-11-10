#include "stdafx.h"
#include "CReverberation.h"
#include "CCitcuarEffect.h"

CReverberation::CReverberation(void)
{
	inList.resize(88200);
	outList.resize(88200);
}


CReverberation::~CReverberation(void)
{
}

void CReverberation::ProcessWet(double* frame) {
	int i = 0;
	while (i < 2)
	{
		inList[(wrloc + i) % 88200] = frame[i];
		frame[i] += 1 * inList[(wrloc + i + int(88.2 * 100)) % 88200] + 0.5 * inList[(wrloc + i + int(88.2 * 200)) % 88200]
			+ 0.25 * inList[(wrloc + i + int(88.2 * 400)) % 88200] + 0.125 * inList[(wrloc + i + int(88.2 * 800)) % 88200];
		frame[i] /= 2.75;
		outList[(wrloc + i) / 88200] = frame[i];
		i++;
	}

	wrloc = (wrloc+2)% 88200;
}