#pragma once
#include "AudioNode.h"

class CFrame :
	public CAudioNode
{
public:
	CFrame();
	virtual ~CFrame(void);
	virtual void Start() { }
	virtual bool Generate() { return true; }
	void setFrame(double* frameIn);
};

