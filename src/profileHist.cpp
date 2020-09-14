#include "profileHist.h"

double ProfileHist::GetEntriesTotal() const
{
    double sum = 0.;
    for (int i=0; i<data.size(); i++)
        sum += data[i].GetEntries();
    return sum;
}

bool ProfileHist::Fill(double x, double t)
{
    if (ndim>1) 
        return false; 
    int ix = LocateX(x);
    if (ix>=0 && ix<xdim)
        data[ix].Add(t);
    return true;    
}

bool ProfileHist::Fill(double x, double y, double t)
{
    if (ndim>2) 
        return false;
    int ix = LocateX(x);
    int iy = LocateY(y);
    if (ix>=0 && ix<xdim && iy>=0 && iy<ydim)
        data[ix+iy*xdim].Add(t);
    return true;    
}

bool ProfileHist::Fill(double x, double y, double z, double t)
{
    int ix = LocateX(x);
    int iy = LocateY(y);
    int iz = LocateZ(z);
    if (ix>=0 && ix<xdim && iy>=0 && iy<ydim && iz>=0 && iz<zdim)
        data[ix+(iy+iz*ydim)*xdim].Add(t);
    return true;
}

void ProfileHist::Clear()
{
    for (PHCell cell : data)
        cell.Clear();
}

ProfileHist::ProfileHist(int x_dim, double x_min, double x_max) : xdim(x_dim), xmin(x_min), xmax(x_max)
{
    data.resize(xdim);
    dx = xmax - xmin;
    ndim = 1;
    ydim = zdim = 1;
}

ProfileHist::ProfileHist(int x_dim, double x_min, double x_max, int y_dim, double y_min, double y_max) : 
                        xdim(x_dim), xmin(x_min), xmax(x_max), ydim(y_dim), ymin(y_min), ymax(y_max)
{
    data.resize(xdim*ydim);
    dx = xmax - xmin;
    dy = ymax - ymin;
    ndim = 2;
    zdim = 1;
}

ProfileHist::ProfileHist(int x_dim, double x_min, double x_max, int y_dim, double y_min, double y_max, 
                        int z_dim, double z_min, double z_max) : xdim(x_dim), xmin(x_min), xmax(x_max), 
                        ydim(y_dim), ymin(y_min), ymax(y_max), zdim(z_dim), zmin(z_min), zmax(z_max)
{
    data.resize(xdim*ydim*zdim);
    dx = xmax - xmin;
    dy = ymax - ymin;
    dz = zmax - zmin;
    ndim = 3;
}

std::vector <double> ProfileHist::GetMeans()
{
    int len = GetBinsTotal();
    std::vector <double> tmp;
    tmp.reserve(len);
    for (int i=0; i<len; i++)
        tmp.push_back(GetFlatBinMean(i));
    return tmp;    
}
std::vector <double> ProfileHist::GetXCenters()
{
    int len = GetBinsTotal();
    std::vector <double> tmp;
    tmp.reserve(len);
    for (int i=0; i<len; i++)
        tmp.push_back(GetBinCenterX(Getix(i)));
    return tmp;  
}
std::vector <double> ProfileHist::GetYCenters()
{
    int len = GetBinsTotal();
    std::vector <double> tmp;
    tmp.reserve(len);
    for (int i=0; i<len; i++)
        tmp.push_back(GetBinCenterY(Getiy(i)));
    return tmp;  
}
std::vector <double> ProfileHist::GetZCenters()
{
    int len = GetBinsTotal();
    std::vector <double> tmp;
    tmp.reserve(len);
    for (int i=0; i<len; i++)
        tmp.push_back(GetBinCenterZ(Getiz(i)));
    return tmp;  
}

std::vector <double>  ProfileHist::GetSigmas()
{
    int len = GetBinsTotal();
    std::vector <double> tmp;
    tmp.reserve(len);
    for (int i=0; i<len; i++)
        tmp.push_back(GetFlatBinSigma(i));
    return tmp;
}

std::vector <double>  ProfileHist::GetWeights()
{
    int len = GetBinsTotal();
    std::vector <double> tmp;
    tmp.reserve(len);
    for (int i=0; i<len; i++)
        tmp.push_back(GetFlatBinEntries(i));
    return tmp;
}

