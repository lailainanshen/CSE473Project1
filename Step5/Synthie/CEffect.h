#pragma once
class CEffect
{
public:
	CEffect(void);
	virtual ~CEffect(void);
	void Process(double* frame);
private:
	double wet;
	double dry;
	virtual void ProcessWet(double* frame) = 0;
	void setWetLevel(double wval) { if (wval >= 0.0 && wval <= 1.0) { wet = wval; } }
	double getWetLevel() { return wet; }
	void setDryLevel(double dval) { if (dval >= 0.0 && dval <= 1.0) { dry = dval; } }
	double getDryLevel() { return dry; }
};

