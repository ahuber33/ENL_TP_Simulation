#include "EMField.hh"
#include "G4Exp.hh"
#include "G4SystemOfUnits.hh"
#include "BMap.hh"

EMField::EMField()
{}

  void EMField::GetFieldValue(const double point[4], double *Bfield ) const
  {

    // Magnetic field
    Bfield[0] = 0;
    Bfield[1] = 0;
    Bfield[2] = 0;

    // Electric field
    Bfield[3] = 0;
    Bfield[4] = 0;
    Bfield[5] = 0;

    G4double x = point[0];
    G4double y = point[1];
    G4double z = point[2];

    bool trigger =true;


    // CHAMP CONSTANT !!!!!!!

    // Définition du domaine d'applications
    if(x <-25.4 || x > 25.4) trigger = false;
    if(y <-7.55 || y > 7.55) trigger = false;
    //if(z <-200 || z > 199.5) trigger = false;
    if(z <-25.4 || z > 25.4) trigger = false;

    float By = 0;

    //if (trigger ==true) By = BMap::GetInstance()->Interpolate(x,y,z);
    if (trigger ==true) By = -0.6;


    Bfield[1] = By*tesla;

    //G4cout << "Position (" << x << "; " << y << "; " << z << ")" << " => B = " << By << G4endl;

  }
