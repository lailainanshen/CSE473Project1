#include "stdafx.h"
#include "CEffect.h"

CEffect::CEffect(void)
{
	wet = 1.0;
	dry = 0.0;
}


CEffect::~CEffect(void)
{
}

void CEffect::Process(double* frame) {
	double* dry_Frame = new double[2];
	double* wet_Frame = new double[2];
	dry_Frame[0] = frame[0];
	wet_Frame[0] = frame[0];
	dry_Frame[1] = frame[1];
	wet_Frame[1] = frame[1];
	ProcessWet(wet_Frame);
	frame[0] = dry * dry_Frame[0] + wet * wet_Frame[0];
	frame[1] = dry * dry_Frame[1] + dry * wet_Frame[1];
	delete dry_Frame;
	delete wet_Frame;
}