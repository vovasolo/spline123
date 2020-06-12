#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "bspline123d.h"
#include "bsfit123.h"

namespace py = pybind11;

PYBIND11_MODULE(spline, m) {
    py::class_<Bspline1d>(m, "Bspline1d")
        .def(py::init<double, double, int>())
        .def(py::init<std::string &>())
        .def("Eval", (std::vector <double> (Bspline1d::*)(std::vector <double> &) const) &Bspline1d::Eval)
        .def("Eval", (double (Bspline1d::*)(double) const) &Bspline1d::Eval)
        .def("EvalDrv", (std::vector <double> (Bspline1d::*)(std::vector <double> &) const) &Bspline1d::EvalDrv)
        .def("EvalDrv", (double (Bspline1d::*)(double) const) &Bspline1d::EvalDrv)
        .def("GetCoef", (std::vector<double> (Bspline1d::*)() const) &Bspline1d::GetCoef)
        .def("GetCoef", (double (Bspline1d::*)(int i) const) &Bspline1d::GetCoef)
        .def("SetCoef", (bool (Bspline1d::*)(std::vector <double> &)) &Bspline1d::SetCoef)
        .def("GetJsonString", (std::string (Bspline1d::*)() const) &Bspline1d::GetJsonString)
        .def("Basis", (double (Bspline1d::*)(double x, int n) const) &Bspline1d::Basis)
        .def("Basis", (std::vector <double> (Bspline1d::*) (std::vector <double> &vx, int n) const) &Bspline1d::Basis)
        .def("BasisDrv", (double (Bspline1d::*)(double x, int n) const) &Bspline1d::BasisDrv)
        .def("BasisDrv", (std::vector <double> (Bspline1d::*) (std::vector <double> &vx, int n) const) &Bspline1d::BasisDrv)
        ;

    py::class_<Bspline2d>(m, "Bspline2d")
        .def(py::init<double, double, int, double, double, int>())
        .def(py::init<std::string &>())
        .def("Eval", (std::vector <double> (Bspline2d::*)(std::vector <double> &, std::vector <double> &) const) &Bspline2d::Eval)
        .def("Eval", (double (Bspline2d::*)(double, double) const) &Bspline2d::Eval)
        .def("EvalDrvX", (std::vector <double> (Bspline2d::*)(std::vector <double> &, std::vector <double> &) const) &Bspline2d::EvalDrvX)
        .def("EvalDrvX", (double (Bspline2d::*)(double, double) const) &Bspline2d::EvalDrvX)
        .def("EvalDrvY", (std::vector <double> (Bspline2d::*)(std::vector <double> &, std::vector <double> &) const) &Bspline2d::EvalDrvY)
        .def("EvalDrvY", (double (Bspline2d::*)(double, double) const) &Bspline2d::EvalDrvY)
        .def("GetCoef", (std::vector<double> (Bspline2d::*)() const) &Bspline2d::GetCoef)
        .def("GetCoef", (double (Bspline2d::*)(int i) const) &Bspline2d::GetCoef)
        .def("SetCoef", (bool (Bspline2d::*)(std::vector <double> &)) &Bspline2d::SetCoef)
        .def("GetJsonString", (std::string (Bspline2d::*)() const) &Bspline2d::GetJsonString)
        .def("Basis", (double (Bspline2d::*)(double, double, int, int) const) &Bspline2d::Basis)
        .def("Basis", (std::vector <double> (Bspline2d::*) (std::vector <double> &, std::vector <double> &, int, int) const) &Bspline2d::Basis)
        .def("BasisDrvX", (double (Bspline2d::*)(double, double, int, int) const) &Bspline2d::BasisDrvX)
        .def("BasisDrvX", (std::vector <double> (Bspline2d::*) (std::vector <double> &, std::vector <double> &, int, int) const) &Bspline2d::BasisDrvX)
        .def("BasisDrvY", (double (Bspline2d::*)(double, double, int, int) const) &Bspline2d::BasisDrvY)
        .def("BasisDrvY", (std::vector <double> (Bspline2d::*) (std::vector <double> &, std::vector <double> &, int, int) const) &Bspline2d::BasisDrvY)
        ;

    py::class_<BSfit1D>(m, "BSfit1D")
        .def(py::init<double, double, int>())
    	.def(py::init<Bspline1d*>())
        .def("AddData", (void (BSfit1D::*)(std::vector <double> &, std::vector <double> &)) &BSfit1D::AddData)
        .def("SetBinning", &BSfit1D::SetBinning)
        .def("SetBinningAuto", &BSfit1D::SetBinningAuto)
    	.def("Fit", (bool (BSfit1D::*)(std::vector <double> &, std::vector <double> &)) &BSfit1D::Fit)
        .def("BinnedFit", &BSfit1D::BinnedFit)
        .def("GetCoef", &BSfit1D::GetCoef)
        .def("MakeSpline", &BSfit1D::MakeSpline)
        .def("FitAndMakeSpline", &BSfit1D::FitAndMakeSpline)
        ;      

    py::class_<Constraints1D>(m, "Constraints1D")
        .def("ForceNonIncreasing", &Constraints1D::ForceNonIncreasing)
        .def("ForceNonDecreasing", &Constraints1D::ForceNonDecreasing)
        .def("FixAt", &Constraints1D::FixAt)
        .def("FixDrvAt", &Constraints1D::FixDrvAt)
        .def("FixLeft", &Constraints1D::FixLeft)
        .def("FixDrvLeft", &Constraints1D::FixDrvLeft)
        .def("FixRight", &Constraints1D::FixRight)
        .def("FixDrvRight", &Constraints1D::FixDrvRight)       
        ;
    
    py::class_<ConstrainedFit1D>(m, "ConstrainedFit1D")
        .def(py::init<double, double, int>())
        .def("Constraints", &ConstrainedFit1D::Constraints)
        .def("FitAndMakeSpline", &ConstrainedFit1D::FitAndMakeSpline)
        ;

    py::class_<BSfit2D>(m, "BSfit2D")
    	.def(py::init<Bspline2d*>())
    	.def("Fit", (bool (BSfit2D::*)(std::vector <double> &, std::vector <double> &, std::vector <double> &)) &BSfit2D::Fit);        
}

