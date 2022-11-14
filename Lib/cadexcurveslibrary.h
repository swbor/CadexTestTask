#ifndef CADEXCURVESLIBRARY_H
#define CADEXCURVESLIBRARY_H

#include "CadexCurvesLibrary_global.h"

#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

enum CurveTypes{CircleType = 0, ElipseType, HelixType};

struct CADEXCURVESLIBRARY_EXPORT Point3D{
    double x{},y{},z{};
    Point3D()=default;
    Point3D(double X,double Y, double Z):x(X),y(Y),z(Z){};
    void Print(){cout<<"("<<x<<" ,"<<y<<" ,"<<z<<" ) ";}
    virtual ~Point3D()=default;
};

struct CADEXCURVESLIBRARY_EXPORT Vector3D:public Point3D{
    Vector3D() = default;
    Vector3D(double X,double Y, double Z):Point3D(X,Y,Z){};
    ~Vector3D()=default;
};

class CADEXCURVESLIBRARY_EXPORT Curves
{
protected:
    Point3D c{};
public:
    Curves()=default;
    Curves(Point3D C):c(C){};
    Curves(double x, double y, double z):c(x,y,z){};
    void setCenter(const Point3D &С){c = С;};
    void setCenter(double X,double Y, double Z){c.x = X;c.y = Y;c.z = Z;}
    Point3D getCenter(){return c;};
    virtual Point3D calcPoint(double t) = 0;
    virtual Vector3D calcVector(double t) = 0;
    virtual CurveTypes getType() = 0;
    virtual ~Curves()=default;
};

class CADEXCURVESLIBRARY_EXPORT Circle:public Curves
{
    double radi{};
public:
    Circle()=default;
    Circle(Point3D C,double Radi):Curves(C),radi(Radi){};
    void setRadi(double Radi){radi = Radi;}
    double getRadi(){return radi;}
    Point3D calcPoint(double t);
    Vector3D calcVector(double t);
    CurveTypes getType(){return CurveTypes::CircleType;}
    ~Circle()=default;
};

class CADEXCURVESLIBRARY_EXPORT Elipse:public Curves
{
    double radi_a{};
    double radi_b{};
public:
    Elipse()=default;
    Elipse(Point3D C,double Radi_a, double Radi_b):Curves(C),radi_a(Radi_a), radi_b(Radi_b){};
    void setRadiA(double RadiA){radi_a = RadiA;}
    void setRadiB(double RadiB){radi_b = RadiB;}
    double getRadiA(){return radi_a;}
    double getRadiB(){return radi_b;}
    Point3D calcPoint(double t);
    Vector3D calcVector(double t);
    CurveTypes getType(){return CurveTypes::ElipseType;}
    ~Elipse()=default;
};

class CADEXCURVESLIBRARY_EXPORT Helix:public Curves
{
    double radi{};
    double step{};
public:
    Helix()=default;
    Helix(Point3D C,double Radi, double Step):Curves(C),radi(Radi), step(Step){};
    void setRadi(double Radi){radi = Radi;}
    void setStep(double Step){step = Step;}
    double getRadi(){return radi;}
    double getStep(){return step;}
    Point3D calcPoint(double t);
    Vector3D calcVector(double t);
    CurveTypes getType(){return CurveTypes::HelixType;}
    ~Helix()=default;
};

#endif // CADEXCURVESLIBRARY_H
