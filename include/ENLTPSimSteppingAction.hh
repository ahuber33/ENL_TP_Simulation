/// ENLTPSimSteppingAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLTPSimSteppingAction_h
#define ENLTPSimSteppingAction_h

#include "G4UserSteppingAction.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalVolume.hh"
#include "TH2F.h"
#include "TFile.h"

class G4Step;
class G4SteppingManager;
class PMT;

class ENLTPSimSteppingAction : public G4UserSteppingAction
{
public:
  ENLTPSimSteppingAction();
  ~ENLTPSimSteppingAction();
public:
  void UserSteppingAction(const G4Step*);
  int Boundary;
  void Count(){Boundary++;}

  void SetTheta (double e) { NRJ1 = e;};
  double GetTheta() {return NRJ1;}




private:
  static const G4String path;
  int PreviousTrack;
  double NRJ1;
  PMT *R6594;
  G4LogicalVolume *Logical8InchesPMT;
  G4OpticalSurface *OpticalPMT;
  G4LogicalSkinSurface *SSPhotocathode;
  G4MaterialPropertiesTable *PMT_MPT;
  double Length_Track;
  double Total_Length_Track;
  G4double angle_azimutale;


};
#endif
