#include "stdafx.h"

#include "DataWrapper.h"

namespace EmguCvEllipseDetector {
	/*
	* This class implements a ellipse .NET wrapper of YAED (Yet Another Ellipse Detector)
	*/
	Ellipse::Ellipse() : _xc(0), _yc(0), _a(0), _b(0), _rad(0)
	{}

	Ellipse::Ellipse(float xc, float yc, float a, float b, float rad) : _xc(xc), _yc(yc), _a(a), _b(b), _rad(rad)
	{}
}