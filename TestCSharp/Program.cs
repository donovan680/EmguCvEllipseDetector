﻿using System;
using System.IO;
using System.Drawing;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Emgu.CV;
using Emgu.CV.CvEnum;
using EmguCvEllipseDetector;

namespace TestCSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            string path = Path.Combine(typeof(Program).Assembly.CodeBase.Replace("file:///", "").Replace("/", "\\"), "..");
            string fileName = args.Length > 0 ? args[0] : string.Empty;
            if (!string.IsNullOrEmpty(fileName))
            {
                var inputMat = CvInvoke.Imread(fileName);
                var grayMat = new Mat();
                CvInvoke.CvtColor(inputMat, grayMat, ColorConversion.Bgr2Gray);
                EllipseDetector detector = new EllipseDetector();
                detector.Detect(grayMat, out var ellipses);

                using (var bitmap = new Bitmap(fileName))
                using (Graphics graphics = Graphics.FromImage(bitmap))
                {
                    Brush aBrushCenter = Brushes.Blue;

                    int i = 0;
                    foreach (var result in ellipses)
                    {
                        var aBrush = i % 2 == 0 ? Brushes.Red : Brushes.Green;
                        graphics.FillRectangle(aBrushCenter, result.Center.X, result.Center.Y, 5, 5);
                        for (double angle = 0.0f; angle < Math.PI * 2; angle += 0.01f)
                        {
                            var v2X = result.MajorSemiAxisLengthA * Math.Cos(angle);
                            var v2Y = result.MinorSemiAxisLengthB * Math.Sin(angle);
                            var vx = v2X * Math.Cos(result.OrientationAngleInRadian) - v2Y * Math.Sin(result.OrientationAngleInRadian) + result.Center.X;
                            var vy = v2Y * Math.Cos(result.OrientationAngleInRadian) + v2X * Math.Sin(result.OrientationAngleInRadian) + result.Center.Y;

                            var points2 = new[] { new PointF(), new PointF() };
                            points2[0].X = (float)vx;
                            points2[0].Y = (float)vy;
                            points2[1].X = (float)vx;
                            points2[1].Y = (float)vy;
                            graphics.FillRectangle(aBrush, points2[0].X, points2[0].Y, 3, 3);
                        }

                        i++;
                    }
                    var fi = new FileInfo(fileName);

                    bitmap.Save(Path.Combine(path, "output" + fi.Name), bitmap.RawFormat);
                    Console.WriteLine("--------------------------------");
                    Console.WriteLine("Execution Time: ");
                    var times = detector.ExecTime;

                    Console.WriteLine("Edge Detection: \t{0}", times.EdgeDetection);
                    Console.WriteLine("Pre processing: \t{0}", times.PreProcessing);
                    Console.WriteLine("Grouping:       \t{0}", times.Grouping);
                    Console.WriteLine("Estimation:     \t{0}", times.Estimation);
                    Console.WriteLine("Validation:     \t{0}", times.Validation);
                    Console.WriteLine("Clustering:     \t{0}", times.Clustering);
                    Console.WriteLine("--------------------------------");
                    Console.WriteLine("Total:	         \t{0}", times.Total);
                    Console.WriteLine("--------------------------------");

                    Console.ReadKey();
                }
            }

        }
    }
}
