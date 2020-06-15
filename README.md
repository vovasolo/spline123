# spline123
C++ library (with Python bindings) for fitting data with cubic splines in 1, 2 and 3 dimensions

The provided data are fit with piecewise cubic (bi-cubic or tri-cubic for higher dimensions) polynomials (splines), guaranteed to have smooth first and continuous second derivatives. The splines stored as a linear combination of uniform cubic B-splines (UCBS) or their tensor products in 2D and 3D, with coefficients obtained by linear least squares.

## Features
* Simple but powerful interface
* Fast, both for fitting and evaluation
* Unconstrained fit by linear least squares
* Constrained fit by quadratic programming:
  * Minimum and/or maximum limits, including non-negative option
  * Monotonically rising or falling
  * Fixed value and/or derivative at the endpoints
* Direct and binned fitting options
* Smart treatment of missing data
* Import from and export to JSON

## Requirements
* A compiler with C++11 support (tested on GCC 4.8 and several newer versions)
* The only hard library dependence is [Eigen linear algebra library](http://eigen.tuxfamily.org).
* Python support requires also [pybind11 library](https://pybind11.readthedocs.io/en/stable) installed
* The included example depends on [CERN ROOT](https://root.cern.ch) framework

## Compilation
The included Makefile can be used to build shared library ```spline.so```
```
git clone https://github.com/vovasolo/spline123.git
cd spline123
make
```

## Python module
```
make python
```
will create ```spline.so``` with Python bindings. Copy it to one of the folders in the search path for Python modules (```sys.path```), then load with 
```python
import spline
```

## Example
If ROOT is installed, you can build a simple example with 
```
make example
```

## Usage: C++
The basic usage requires only two classes: ```BSfit1D``` for fitting and ```Bspline1d``` for spline evaluation. While internally the library works with arrays of doubles, the preferred way to supply data is in the form of ```std::vector```. Let's start by preparing some data to fit.
```c++
std::vector<double> x, f;
// fill vectors x and f with data
for (double xx = 0.; xx <= 10.; xx+=0.2) {
    x.push_back(xx); 
    f.push_pack(exp(-xx*xx/100.));
}
```
Now create an unconstrained fitting object, perform the fit and retrieve the resulting spline object in one go, and then evaluate the spline, first at one point and then for all points in a vector:
```c++
// prepare fit on the segment [0,10] with a 15-interval spline
BSfit1D F1(0, 10, 15);
// do fit, create and store spline
Bspline1d *bs1 = F1.FitAndMakeSpline(x, f);
// calculate spline at position 4
double spl_4 = bs1->Eval(4);
// calculate spline at all positions from vector x
std::vector<double> spl_x = bs1->Eval(x);
```
### Constrained fit
Introducing one more class: ```ConstrainedFit1D```. As a descendant of ```BSfit1D```, it provides the same fitting and data handling functionality, adding the methods necessary to define the constraints.
```c++
Constrainedfit1D F1(0, 10, 15);
CF1.ForceNonNegative();
CF1.ForceNonIncreasing();
CF1.FixDrvLeft(0);
Bspline1d *bs1 = CF1.FitAndMakeSpline(x, f);
```
### Binned fit
When there is a lot of data points, the time required for fitting can become inconveniently long. The solution is to collect the data points into bins along x (y,z), then take average for each bin and fit this average.
```c++
BSfit1D BF1(0, 10, 15);
BF1.AddData(x,f);
BF1.AddData(x2,f2); // optional
BF1.BinnedFit();
Bspline1d *bs1 = BF1.MakeSpline();
```
AddData can be repeated several times with new data: the results will be accumulating in the internal storage
### Input/output
The spline parameters and coefficients can be exported (as JSON) into ```std::string```. The exact copy of the original spline object can be recreated by suppluing the exported string to ```Bspline1d``` constructor:
```c++
std::string jsontext = bs1->GetJsonString();
Bspline1d *bs2 = new Bspline1d(jsontext);
std::cout << bs1->Eval(4) << "==" << bs2->Eval(4) << std::endl;
```
 