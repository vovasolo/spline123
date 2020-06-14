# spline123
C++ library (with Python bindings) for fitting data with cubic splines in 1, 2 and 3 dimensions

The provided data are fit with piecewise cubic (bi-cubic or tri-cubic for higher dimensions) polynomials (splines), guaranteed to have smooth first and continuous second derivatives. The splines stored as a linear combination of uniform cubic B-splines (UCBS) or their tensor products in 2D and 3D, with coefficients obtained by linear least squares.

## Features
* Simple but powerful interface
* Fast, both for fitting and evaluation
* Unconstrained fit by linear least squares
* Constrained fit by quadratic programming:
  * Minimum and/or maximum limits, including non-negative option
  * Monotonically rising of falling
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
If CERN ROOT is installed, you can build a simple example with 
```
make example
```

