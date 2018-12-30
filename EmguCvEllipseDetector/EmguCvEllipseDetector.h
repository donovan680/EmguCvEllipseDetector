#pragma once

#include "opencv2/opencv.hpp"

#include "DataWrapper.h"
#include "EllipseDetectorYaed.h"


using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;
using namespace Emgu::CV;
using namespace cv;

namespace EmguCvEllipseDetector {
	public ref class EllipseDetector
	{
	protected:
		!EllipseDetector();

	public:
		EllipseDetector(void);
		EllipseDetector(System::Drawing::Size szPreProcessingGaussKernelSize, double dPreProcessingGaussSigma,
			int iThLength, float fThObb, float fThPos, int iNs, float fTaoCenters,
			float fDistanceToEllipseContour, float fMinScore, float fMinReliability);
		~EllipseDetector(void);

		void Detect(Emgu::CV::Mat ^inputMat, [Runtime::InteropServices::Out] System::Collections::Generic::List<Ellipse^>^ %ellipses);

		void SetParameters(System::Drawing::Size szPreProcessingGaussKernelSize, double dPreProcessingGaussSigma,
			int iThLength, float fThObb, float fThPos, int iNs, float fTaoCenters,
			float fDistanceToEllipseContour, float fMinScore, float fMinReliability) {
			_szPreProcessingGaussKernelSize = szPreProcessingGaussKernelSize;
			_dPreProcessingGaussSigma = dPreProcessingGaussSigma;
			_iThLength = iThLength;
			_fThObb = fThObb;
			_fThPos = fThPos;
			_iNs = iNs;
			_fTaoCenters = fTaoCenters;
			_fDistanceToEllipseContour = fDistanceToEllipseContour;
			_fMinScore = fMinScore;
			_fMinReliability = fMinReliability;
		}

		property System::Drawing::Size PreProcessingGaussKernelSize {
			System::Drawing::Size get() { return _szPreProcessingGaussKernelSize; }
			void set(System::Drawing::Size value) { _szPreProcessingGaussKernelSize = value; }
		}

		property double PreProcessingGaussSigma {
			double get() { return _dPreProcessingGaussSigma; }
			void set(double value) { _dPreProcessingGaussSigma = value; }
		}

		property int ThLength {
			int get() { return _iThLength; }
			void set(int value) { _iThLength = value; }
		}

		property float ThObb {
			float get() { return _fThObb; }
			void set(float value) { _fThObb = value; }
		}

		property float ThPos {
			float get() { return _fThPos; }
			void set(float value) { _fThPos = value; }
		}

		property int Ns {
			int get() { return _iNs; }
			void set(int value) { _iNs = value; }
		}

		property float TaoCenters {
			float get() { return _fTaoCenters; }
			void set(float value) { _fTaoCenters = value; }
		}

		property float DistanceToEllipseContour {
			float get() { return _fDistanceToEllipseContour; }
			void set(float value) { _fDistanceToEllipseContour = value; }
		}

		property float MinScore {
			float get() { return _fMinScore; }
			void set(float value) { _fMinScore = value; }
		}

		property float MinReliability {
			float get() { return _fMinReliability; }
			void set(float value) { _fMinReliability = value; }
		}

		property ExecutionTime^ ExecTime {
			ExecutionTime^ get() { return _etExecutionTime; }
		}

	private:
		System::Collections::Generic::List<Ellipse^> ^_lstEllipses;
		ExecutionTime ^_etExecutionTime;

		// Preprocessing
		System::Drawing::Size _szPreProcessingGaussKernelSize;
		double _dPreProcessingGaussSigma;
		// 3.1.2 Arc detection
		int _iThLength;
		float _fThObb;
		// 3.2.1 Arc selection
		float _fThPos;
		int _iNs;
		//3.2.2 Center estimation
		float _fTaoCenters;
		//3.3.1 Validation
		float _fDistanceToEllipseContour;
		float _fMinScore;
		// Not included in paper, refer to code comments
		float _fMinReliability;
	};
}
