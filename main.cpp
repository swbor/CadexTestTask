#include <iostream>
#include "Lib/cadexcurveslibrary.h"
#include <algorithm>
#include "omp.h"

#define N 100
#define MaxDoubleRand 100

using namespace std;

double fRand(double fMin = 0, double fMax = MaxDoubleRand)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}


int main()
{
    cout<<"All "<<N<<" curves:\n\n";
    vector<Curves*> curves(N);
    srand(time(NULL));
    Curves* newCurve;
    for (int i = 0; i<N; i++)
    {
        switch (rand()%3)
        {
            case CurveTypes::CircleType://circle
                newCurve = new Circle(Point3D(fRand(),fRand(),fRand()),fRand());
                break;
            case CurveTypes::ElipseType://elipse
                newCurve = new Elipse(Point3D(fRand(),fRand(),fRand()),fRand(),fRand());
                break;
            case CurveTypes::HelixType://helix
                newCurve = new Helix(Point3D(fRand(),fRand(),fRand()),fRand(),fRand());
        }
        curves[i] = newCurve;
    }
    double t = M_PI/4;
    Point3D p;
    Vector3D v;
    for (auto c:curves)
    {
        switch(c->getType())
        {
        case CurveTypes::CircleType://circle
            cout<<"Circle: ";
            break;
        case CurveTypes::ElipseType://elipse
            cout<<"Elipse: ";
            break;
        case CurveTypes::HelixType://helix
            cout<<"Helix: ";
        }
        p = c->calcPoint(t);
        v = c->calcVector(t);
        cout<<"Point = ";
        p.Print();
        cout<<"Vector = ";
        v.Print();
        cout<<"\n";
    }
    vector<Circle*> secondContainer;
    cout<<"\nSecond container before sorting:\n";
    Circle* cp;
    for (auto c:curves)
    {
        if (c->getType()==CurveTypes::CircleType)
        {
            cp = (Circle*)c;
            secondContainer.push_back(cp);
            cout << "Circle; Center Point = ";
            cp->getCenter().Print();
            cout << "radi = " << cp->getRadi() << "\n";
        }
    }
    cout<<"\nSecond container after sorting:\n";
    sort(secondContainer.begin(), secondContainer.end(), [&](Circle* t1,Circle* t2) {
        return t1->getRadi() < t2->getRadi();
    });
    for (auto c:secondContainer)
    {
        cout << "Circle; Center Point = ";
        c->getCenter().Print();
        cout << "radi = " << c->getRadi() << "\n";
    }
    double radii_sum = 0.0;
    #pragma omp parallel for
    for (auto c:secondContainer)
    {
        radii_sum += c->getRadi();
    }
    cout<<"Sum of radii = "<<radii_sum<<endl;
    return 0;
}
