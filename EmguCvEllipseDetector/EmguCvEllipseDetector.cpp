#include "stdafx.h"

#include "EmguCvEllipseDetector.h"

namespace EmguCvEllipseDetector {

	EllipseDetector::EllipseDetector()
		: _szPreProcessingGaussKernelSize(System::Drawing::Size(5, 5)), _dPreProcessingGaussSigma(1.0),
		_iThLength(16), _fThObb(3.0f), _fThPos(1.0f), _iNs(16), _fTaoCenters(0.05f),
		_fDistanceToEllipseContour(0.1f), _fMinScore(0.7f), _fMinReliability(0.5f),
		_lstEllipses(nullptr), _etExecutionTime(nullptr) {}

	EllipseDetector::EllipseDetector(System::Drawing::Size szPreProcessingGaussKernelSize, double dPreProcessingGaussSigma,
		int iThLength, float fThObb, float fThPos, int iNs, float fTaoCenters,
		float fDistanceToEllipseContour, float fMinScore, float fMinReliability)
		: _szPreProcessingGaussKernelSize(szPreProcessingGaussKernelSize), _dPreProcessingGaussSigma(dPreProcessingGaussSigma),
		_iThLength(iThLength), _fThObb(fThObb), _fThPos(fThPos), _iNs(iNs), _fTaoCenters(fTaoCenters),
		_fDistanceToEllipseContour(fDistanceToEllipseContour), _fMinScore(fMinScore), _fMinReliability(fMinReliability),
		_lstEllipses(nullptr), _etExecutionTime(nullptr) {}

	EllipseDetector::~EllipseDetector(void) {}

	EllipseDetector::!EllipseDetector() {
		if (_lstEllipses != nullptr) { delete _lstEllipses; }
		if (_etExecutionTime != nullptr) { delete _etExecutionTime; }

		//Release managed resources
		GC::Collect();
	}

	void EllipseDetector::Detect(Emgu::CV::Mat ^inputMat, [Runtime::InteropServices::Out] System::Collections::Generic::List<Ellipse^>^ %ellipses)
	{
		if (_lstEllipses == nullptr) {
			_lstEllipses = gcnew System::Collections::Generic::List<Ellipse^>();
		}
		else {
			_lstEllipses->Clear();
		}

		if (inputMat->NumberOfChannels != 1) {
			throw gcnew System::Exception("The channel of input mat should be 1!");
		}
		if (inputMat->Depth != Emgu::CV::CvEnum::DepthType::Cv8U) {
			throw gcnew System::Exception("The depth type of input mat should be Cv8U!");
		}

		int width = inputMat->Width;
		int height = inputMat->Height;

		cli::array<System::Byte>^ inputMatData = gcnew cli::array<System::Byte>(width*height);
		inputMat->CopyTo(inputMatData);
		pin_ptr<System::Byte> p = &inputMatData[0];
		unsigned char* pby = p;
		unsigned char* inputCvMatData = reinterpret_cast<unsigned char*>(pby);
		cv::Mat1b* inputCvMat = new cv::Mat1b(inputMat->Rows, inputMat->Cols, inputCvMatData);

		float fMaxCenterDistance = sqrt(float(width*width + height * height)) * _fTaoCenters;
		cv::Size cvszPreProcessingGaussKernelSize = cv::Size(_szPreProcessingGaussKernelSize.Width, _szPreProcessingGaussKernelSize.Height);

		Yaed::CEllipseDetectorYaed yaed;
		yaed.SetParameters(cvszPreProcessingGaussKernelSize,
			this->_dPreProcessingGaussSigma,
			this->_fThPos,
			fMaxCenterDistance,
			this->_iThLength,
			this->_fThObb,
			this->_fDistanceToEllipseContour,
			this->_fMinScore,
			this->_fMinReliability,
			this->_iNs
		);


		// Detect
		std::vector<Yaed::Ellipse> ellipsesYaed;
		yaed.Detect(*inputCvMat, ellipsesYaed);

		vector<double> times = yaed.GetTimes();

		int sz_ell = int(ellipsesYaed.size());
		//int n = (iTopN == 0) ? sz_ell : min(iTopN, sz_ell);
		for (int i = 0; i < sz_ell; ++i)
		{
			Yaed::Ellipse& e = ellipsesYaed[i];
			_lstEllipses->Add(gcnew Ellipse(e._xc, e._yc, e._a, e._b, e._rad));
		}
		ellipses = _lstEllipses;

		if (_etExecutionTime != nullptr)
		{
			delete _etExecutionTime;
		}

		_etExecutionTime = gcnew ExecutionTime(times[0], times[1], times[2], times[3], times[4], times[5], yaed.GetExecTime());
		delete inputCvMat;
	}
}