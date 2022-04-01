/// ENLTPSimRunAction.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLTPSimRunAction_h
#define ENLTPSimRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "TROOT.h"
#include "TTree.h"
#include "ENLTPSimEventAction.hh"
#include <TFile.h>
#include <vector>

class G4Run;

class ENLTPSimRunAction : public G4UserRunAction
{

public:
  ENLTPSimRunAction(char*);
  ~ENLTPSimRunAction();

public:
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

  //adds the photon fates from an event to the run tree
  void UpdateStatisticsOptical(RunTallyOptical);
  void UpdateStatisticsTP(RunTallyTP);



private:
  G4String suffixe;
  G4int NumPMTs;
  G4int NumFibers;
  RunTallyOptical StatsOptical;
  RunTallyTP StatsTP;
  TFile *f;
  TTree *Tree_Optical;
  TTree *Tree_TP;
  TBranch *RunBranch;
  time_t start;

};

#endif
