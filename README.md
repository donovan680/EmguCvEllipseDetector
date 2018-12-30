# EmguCvEllipseDetector
.Net library which is compatible with EmguCV for ellipse detection based on the algorithm of very fast ellipse detector, codename: YAED (Yet Another Ellipse Detector).
This library is modified based on [EllipseDetectorLib](https://github.com/glani/EllipseDetectorLib)

#### Third party libraries

It uses:

* [Emgu CV](https://github.com/emgucv/emgucv)

* [Open Source Computer Vision Library](https://github.com/opencv/opencv) 

for image reading and processing.

#### The main advantage

Real-time ellipse detection is an important yet challenging task, since the estimation of the five parameters of an ellipse requires heavy computation.

A new efficient ellipse detection method (Y. Xie and Q. Ji) has remained ineffective and inappropriate for realtime processing.

This library is suitable in programs which require an approximate ellipse detection and have to do this in realtime. 

#### Projects
There are two projects:

* [EmguCvEllipseDetector](EmguCvEllipseDetector/): the main C++/CLI .Net library. In other words this is the wrapper.

* [TestCSharp](TestCSharp/): the example written in C# which uses EmguCvEllipseDetector library.

#### Build and deploy
This library has been written in Microsoft Visual Studio 2017. Files *.csproj contain configurations for platforms x64 with both Debug and Release modes.
For successfull build [OpenCV](https://github.com/opencv/opencv) and [EmguCV](https://www.nuget.org/packages/EMGU.CV/) have to be installed. In addition environment variable OPENCV_DIR where opencv is installed should be set. To run the test program, opencv_world***.dll needs to be manually copied to the bin directory. 

#### Features and Capabilities
Here are just a few examples of what EllipseDetectorLib can do:
* [Samples](test-data/): A dozen files shows the initial and result images.

#### What is YAED (Yet Another Ellipse Detector)?

##### According to the comments in the code:
--------------------------------------------------------------
This code is intended for academic use only.
You are free to use and modify the code, at your own risk.

If you use this code, or find it useful, please refer to the paper:

Michele Fornaciari, Andrea Prati, Rita Cucchiara,
A fast and effective ellipse detector for embedded vision applications
Pattern Recognition, Volume 47, Issue 11, November 2014, Pages 3693-3708, ISSN 0031-3203,
http://dx.doi.org/10.1016/j.patcog.2014.05.012
http://www.sciencedirect.com/science/article/pii/S0031320314001976


The comments in the code refer to the abovementioned paper.
If you need further details about the code or the algorithm, please contact me at:

michele.fornaciari@unimore.it

last update: 23/12/2014

--------------------------------------------------------------
