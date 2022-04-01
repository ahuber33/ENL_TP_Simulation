/// ENLTPSimEventAction.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLTPSimEventAction_h
#define ENLTPSimEventAction_h 1
#include "G4ParticleGun.hh"
#include "G4UserEventAction.hh"
#include "TH1F.h"
#include "TROOT.h"
#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"
#include "TCanvas.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include <vector>
#include "TVector.h"

class G4Event;


//This struct carries statistics OPTICAL part
struct RunTallyOptical {
  float  IncidentE;
  float  DepositZnS;
  float  DepositSc;
  int    ScintillationZnS;
  int    CerenkovZnS;
  int    ScintillationSc;
  int    CerenkovSc;
  int    BulkAbsZnS;
  int    BulkAbsSc;
  int    Absorbed;
  int    Escaped;
  int    Failed;
  //int    WLS;
  int    Detected;
  std::vector<float>PositionX;
  std::vector<float>PositionY;
  std::vector<float>PositionZ;
  std::vector<float>MomentumX;
  std::vector<float>MomentumY;
  std::vector<float>MomentumZ;
  std::vector<float>BirthLambda;
  std::vector<float>Time;
  std::vector<float>Energy_pe;
  std::vector<float>Rayleigh;
  std::vector<float>Total_Reflections;
  std::vector<float>Wrap_Reflections;
  std::vector<float>TotalLength;

  inline int operator ==(const RunTallyOptical& right) const
  {return (this==&right);}
};

struct RunTallyTP {
  int ParticuleID;
  float E_start;
  float E_dep;
  float Charge;
  float PositionX;
  float PositionY;
  float PositionZ;
  float Time;
  float TotalLength;
  float InteractionDepth;


  inline int operator ==(const RunTallyTP& right) const
  {return (this==&right);}
};


class ENLTPSimEventAction : public G4UserEventAction
{
public:
  ENLTPSimEventAction(char*);
  ~ENLTPSimEventAction();

public:
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);

  //Functions for Optical Tree
  void SetIncidentE(G4double ince){StatsOptical.IncidentE=ince;}
  void AddEdepSc(G4float edep){StatsOptical.DepositSc+=edep;}
  void AddEdepZnS(G4float edep){StatsOptical.DepositZnS+=edep;}
  void CountCerenkovZnS(){StatsOptical.CerenkovZnS++;}
  void CountCerenkovSc(){StatsOptical.CerenkovSc++;}
  void CountScintillationZnS(){StatsOptical.ScintillationZnS++;}
  void CountScintillationSc(){StatsOptical.ScintillationSc++;}
  void CountDetected(){StatsOptical.Detected++;}
  int GetDetected(){return StatsOptical.Detected;}
  //void CountWLS(){StatsOptical.WLS++;}
  void CountAbsorbed(){StatsOptical.Absorbed++;}
  int GetAbsorbed(){return StatsOptical.Absorbed;}
  void CountBulkAbsSc(){StatsOptical.BulkAbsSc++;}
  int GetBulkAbsSc(){return StatsOptical.BulkAbsSc;}
  void CountBulkAbsZnS(){StatsOptical.BulkAbsZnS++;}
  int GetBulkAbsZnS(){return StatsOptical.BulkAbsZnS;}
  void CountEscaped(){StatsOptical.Escaped++;}
  int GetEscaped(){return StatsOptical.Escaped;}
  void CountFailed(){StatsOptical.Failed++;}
  int GetFailed(){return StatsOptical.Failed;}
  void FillPhotonPositionX(G4float e){StatsOptical.PositionX.push_back(e);}
  void FillPhotonPositionY(G4float e){StatsOptical.PositionY.push_back(e);}
  void FillPhotonPositionZ(G4float e){StatsOptical.PositionZ.push_back(e);}
  void FillPhotonMomentumX(G4float e){StatsOptical.MomentumX.push_back(e);}
  void FillPhotonMomentumY(G4float e){StatsOptical.MomentumY.push_back(e);}
  void FillPhotonMomentumZ(G4float e){StatsOptical.MomentumZ.push_back(e);}
  void FillBirthLambda(G4float e){StatsOptical.BirthLambda.push_back(e);}
  void FillPhotonTime(G4float e){StatsOptical.Time.push_back(e);}
  void FillEnergype(G4float e){StatsOptical.Energy_pe.push_back(e);}
  void FillRayleigh(G4float e){StatsOptical.Rayleigh.push_back(e);}
  void FillTotalReflections(G4float e){StatsOptical.Total_Reflections.push_back(e);}
  void FillWrapReflecions(G4float e){StatsOptical.Wrap_Reflections.push_back(e);}
  void FillPhotonTotalLength(G4float e){StatsOptical.TotalLength.push_back(e);}

  //Functions for TP Tree
  void SetParticuleID(G4double a){StatsTP.ParticuleID =a;}
  float GetParticuleID(){return StatsTP.ParticuleID;}
  void SetEstartTP(G4double d){StatsTP.E_start+=d;}
  float GetEstartTP(){return StatsTP.E_start;}
  void AddEdepTP(G4double d){StatsTP.E_dep+=d;}
  float GetEdepTP(){return StatsTP.E_dep;}
  void SetCharge(G4double a){StatsTP.Charge =a;}
  float GetCharge(){return StatsTP.Charge;}
  void SetTPPositionX(G4double d){StatsTP.PositionX=d;}
  float GetTPPositionX(){return StatsTP.PositionX;}
  void SetTPPositionY(G4double d){StatsTP.PositionY=d;}
  float GetTPPositionY(){return StatsTP.PositionY;}
  void SetTPPositionZ(G4double d){StatsTP.PositionZ=d;}
  float GetTPPositionZ(){return StatsTP.PositionZ;}
  void SetTPTime(G4double d){StatsTP.Time=d;}
  float GetTPTime(){return StatsTP.Time;}
  void AddTrackLength(G4double d){StatsTP.TotalLength+=d;}
  float GetTotalTrackLength(){return StatsTP.TotalLength;}
  void SetInteractionDepthTP(G4double d){StatsTP.InteractionDepth+=d;}
  float GetInteractionDepthTP(){return StatsTP.InteractionDepth;}


private:

  TTree *EventTree;
  TBranch *EventBranch;
  RunTallyOptical StatsOptical;
  RunTallyTP StatsTP;
  G4String suffixe;





};


#endif
