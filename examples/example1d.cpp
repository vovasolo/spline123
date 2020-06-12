#include "TH1.h"
#include "TF1.h"
#include "TGraph.h"
#include "TRandom3.h"
#include "TCanvas.h"
#include "TApplication.h"

#include "bspline123d.h"
#include "bsfit123.h"
#include "json11.hpp"

#include <cmath>
#include <vector>
#include <string>

TRandom3 rndgen;

class MyGraph
{
public:
    MyGraph(int x_min, int x_max) : xmin(x_min), xmax(x_max)
    {
        f = new TF1("f",[&](double*x, double *p){ return bs->Eval(x[0]); }, xmin, xmax, 0);
    }

    void SetTitle(const char *title) {this->title = std::string(title);}
    void SetBS(Bspline1d *bs) {this->bs = bs;}
    void SetFunc(TF1 *func) {g = func;}
    void SetNoise(double noise) {this->noise = noise;}
    std::vector <double> &GetX() {return x;}
    std::vector <double> &GetY() {return y;}
    void MkData(int npts)
    {
        x.clear();
        y.clear();
        double step = (xmax-xmin)/npts;
        for (int i=0; i<npts; i++) {
            double xx = xmin+ (i + 0.5)*step;
            x.push_back(xx);
            y.push_back(g->Eval(xx) + noise*(rndgen.Rndm()-0.5));
        }
    }
    void Draw()
    {
        gr = new TGraph(x.size(), &x[0], &y[0]);
        gr->SetTitle(title.c_str());
        gr->Draw("A*");
        g->Draw("same");
        f->SetLineColor(4);
        f->Draw("same");
    }

    double xmin;
    double xmax;
    double noise = 0.;
    Bspline1d *bs;
    TF1 *f = nullptr;
    TF1 *g = nullptr;
    TGraph *gr = nullptr;
    std::vector <double> x, y;
    std::string title;
};

int main(int argc, char* argv[])
{
    TApplication theApp("App",&argc, argv);
    TCanvas c1("c1", "Test", 800, 600);
    c1.Divide(2,2);

// part 1
    c1.cd(1);
    TF1 *fb1 = new TF1("fb1","gaus(0)+expo(3)",0,100);
    fb1->SetParameters(1, 47, 7, 1, -0.025);
    MyGraph graph1(0, 100);
    graph1.SetTitle("Simple fit");
    graph1.SetFunc(fb1);
    graph1.SetNoise(0.0);
    graph1.MkData(40);

    BSfit1D F1(0, 100, 15);
    Bspline1d *bs1 = F1.FitAndMakeSpline(graph1.GetX(), graph1.GetY());
    graph1.SetBS(bs1);
    graph1.Draw();

// part 2
    c1.cd(2);
    TF1 *fb2 = new TF1("fb2","gaus(0)+expo(3)",0,100);
    fb2->SetParameters(0, 47, 7, 1, -0.025);

    MyGraph graph2(0, 100);
    graph2.SetTitle("Simple fit with noise");
    graph2.SetFunc(fb2);
    graph2.SetNoise(0.2);
    graph2.MkData(100);

    BSfit1D F2(0, 100, 15);
    Bspline1d *bs2 = F2.FitAndMakeSpline(graph2.GetX(), graph2.GetY());
    graph2.SetBS(bs2);
    graph2.Draw();

// part 3
    c1.cd(3);
    TF1 *fb3 = new TF1("fb2","gaus(0)", 0, 100);
    fb3->SetParameters(2, 0, 15);

    MyGraph graph3(0, 100);
    graph3.SetTitle("Constrained fit: non-increasing");
    graph3.SetFunc(fb3);
    graph3.SetNoise(0.4);
    graph3.MkData(30);

    ConstrainedFit1D F3(0, 100, 10);
    F3.ForceNonNegative();
    F3.ForceNonIncreasing();
    F3.FixDrvLeft(0.);
    Bspline1d *bs3 = F3.FitAndMakeSpline(graph3.GetX(), graph3.GetY());
    graph3.SetBS(bs3);
    graph3.Draw();

// part 4

    c1.cd(4);
    TF1 *fb4 = new TF1("fb2","gaus(0)+expo(3)",0,100);
    fb4->SetParameters(1.5, 47, 12, -1000, -0.025);

    MyGraph graph4(0, 100);
    graph4.SetTitle("Constrained fit: limited between 0 and 1.5");
    graph4.SetFunc(fb4);
    graph4.SetNoise(0.4);
    graph4.MkData(100);

    ConstrainedFit1D F4(0, 100, 15);
    F4.SetMinimum(0);
    F4.SetMaximum(1.5);
    Bspline1d *bs4 = F4.FitAndMakeSpline(graph4.GetX(), graph4.GetY());
    graph4.SetBS(bs4);
    graph4.Draw();

#ifdef crap
    std::string json = bs->GetJsonString();
	std::cout << json << std::endl;
	
	std::string err;
	Bspline1d *bs_copy = new Bspline1d(json11::Json::parse(json, err));
	std::cout << std::endl << bs_copy->GetJsonString() << std::endl;
	
	TGraph *gr0 = new TGraph(x.size(), &x[0], &y[0]);
	gr0->Draw("A*");

	fb2->Draw("same");

	TF1 *bsfunc = new TF1("myfunc",myfunction,0,100,0);
	bsfunc->SetLineColor(4);
	bsfunc->Draw("same");
#endif
    theApp.Run();
    return 0;
}
