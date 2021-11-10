#pragma once
#include "CEffect.h"
#include <vector>
#include "resource.h"


class CCitcuarEffect :
	public CEffect
{
	public:
		CCitcuarEffect(void);
		virtual ~CCitcuarEffect(void);
	protected:
		std::vector<double> inList;
		std::vector<double> outList;
		int wrloc;
};
