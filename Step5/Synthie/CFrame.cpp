#include "stdafx.h"
#include "CFrame.h"

CFrame::CFrame()
{
	m_frame[0] = 0;
	m_frame[1] = 0;
}

CFrame::~CFrame(void)
{
}

void CFrame::setFrame(double* frame_In) {
	m_frame[0] = frame_In[0];
	m_frame[1] = frame_In[1];
}