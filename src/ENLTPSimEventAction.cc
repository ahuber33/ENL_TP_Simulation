/// ENLTPSimEventAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2017 (C) Projet BADGE - CARMELEC -P2R

#include "G4SteppingManager.hh"
#include "ENLTPSimSteppingAction.hh"
#include "G4Run.hh"
#include "ENLTPSimEventAction.hh"
#include "G4RunManager.hh"
#include "ENLTPSimRunAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include <fstream>
#include <iostream>
#include "G4PrimaryVertex.hh"
#include <math.h>
#include "TRandom3.h"
#include "TGraph.h"

using namespace CLHEP;

ENLTPSimEventAction::ENLTPSimEventAction(char* suff):suffixe(suff){}

ENLTPSimEventAction::~ENLTPSimEventAction(){}


// Initialize all counters and set up the event branches for
// filling histograms with ROOT
void ENLTPSimEventAction::BeginOfEventAction(const G4Event* evt){

  StatsOptical.IncidentE = 0;
  StatsOptical.DepositZnS = 0;
  StatsOptical.DepositSc = 0;
  StatsOptical.ScintillationZnS = 0;
  StatsOptical.CerenkovZnS = 0;
  StatsOptical.ScintillationSc = 0;
  StatsOptical.CerenkovSc = 0;
  StatsOptical.Absorbed = 0;
  StatsOptical.BulkAbsZnS = 0;
  StatsOptical.BulkAbsSc = 0;
  StatsOptical.Escaped = 0;
  StatsOptical.Failed = 0;
  //StatsOptical.WLS = 0;
  StatsOptical.Detected = 0;
  StatsOptical.PositionX.clear();
  StatsOptical.PositionY.clear();
  StatsOptical.PositionZ.clear();
  StatsOptical.MomentumX.clear();
  StatsOptical.MomentumY.clear();
  StatsOptical.MomentumZ.clear();
  StatsOptical.BirthLambda.clear();
  StatsOptical.Time.clear();
  StatsOptical.Energy_pe.clear();
  StatsOptical.Rayleigh.clear();
  StatsOptical.Total_Reflections.clear();
  StatsOptical.Wrap_Reflections.clear();
  StatsOptical.TotalLength.clear();

  StatsTP.ParticuleID=0;
  StatsTP.E_start=0;
  StatsTP.E_dep=0;
  StatsTP.Charge=0;
  StatsTP.PositionX =0;
  StatsTP.PositionY =0;
  StatsTP.PositionZ =0;
  StatsTP.Time =0;
  StatsTP.TotalLength =0;
  StatsTP.InteractionDepth =0;

}


// Get the number of stored trajectories and calculate the statistics
void ENLTPSimEventAction::EndOfEventAction(const G4Event* evt){
  //G4int event_id = evt->GetEventID();

  ENLTPSimRunAction *runac = (ENLTPSimRunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());

  G4double Absfrac = 0;
  G4double BulkfracZnS = 0;
  G4double BulkfracSc = 0;
  G4double Escfrac = 0;
  G4double Failfrac = 0;
  //G4double WLSfrac = 0;
  //G4double Catfrac = 0;
  G4double efficiency = 0;
  G4int GeneratedSc = StatsOptical.ScintillationSc + StatsOptical.CerenkovSc;
  G4int GeneratedZnS = StatsOptical.ScintillationZnS + StatsOptical.CerenkovZnS;
  G4int Generated = GeneratedSc + GeneratedZnS;
  G4int Scintillation = StatsOptical.ScintillationSc + StatsOptical.ScintillationZnS;
  G4int Cerenkov = StatsOptical.CerenkovSc + StatsOptical.CerenkovZnS;
  G4float Deposit = StatsOptical.DepositSc +  StatsOptical.DepositZnS;


  if (Scintillation >0)
  {
    efficiency = 100*(1.0*StatsOptical.Detected)/(1.0*Generated);
    Absfrac = 100*(1.0*StatsOptical.Absorbed)/(1.0*Generated);
    BulkfracZnS = 100*(1.0*StatsOptical.BulkAbsZnS)/(1.0*Generated);
    BulkfracSc = 100*(1.0*StatsOptical.BulkAbsSc)/(1.0*Generated);
    Escfrac = 100*(1.0*StatsOptical.Escaped)/(1.0*Generated);
    Failfrac = 100*(1.0*StatsOptical.Failed)/(1.0*Generated);
    //WLSfrac = 100*(1.0*StatsOptical.WLS)/(1.0*Generated);
    //Catfrac = 100 * (cpt_photons_lost/(1.0*Detected));
    efficiency = 100 * (StatsOptical.Detected/(1.0*Generated));

    // Output the results
    // G4cout  << "\n\nRun " << G4RunManager::GetRunManager()->GetCurrentRun()->GetRunID() <<  " >>> Event " << evt->GetEventID() << G4endl;
    // G4cout << "Incident Energy:                             " << StatsOptical.IncidentE << " keV " << G4endl;
    // G4cout << "Energy Deposited TOTAL:                      " << Deposit   << " keV " << G4endl;
    // G4cout << "     in ZnS:                                 " << StatsOptical.DepositZnS   << " keV " << G4endl;
    // G4cout << "     in EJ-212:                              " << StatsOptical.DepositSc   << " keV " << G4endl;
    // G4cout << "Photons Generated in ZnS:                    " << GeneratedZnS     << G4endl;
    // G4cout << "     from Scintillation :                    " << StatsOptical.ScintillationZnS << "   (" << (float(StatsOptical.ScintillationZnS))/(float(GeneratedZnS))*100 << " %)"     << G4endl;
    // G4cout << "     from Cerenkov :                         " << StatsOptical.CerenkovZnS     << "    (" << (float(StatsOptical.CerenkovZnS))/(float(GeneratedZnS))*100 << " %)"     << G4endl;
    // G4cout << "Photons Generated in EJ-212:                 " << GeneratedSc     << G4endl;
    // G4cout << "     from Scintillation :                    " << StatsOptical.ScintillationSc << "   (" << (float(StatsOptical.ScintillationSc))/(float(GeneratedSc))*100 << " %)"     << G4endl;
    // G4cout << "     from Cerenkov :                         " << StatsOptical.CerenkovSc     << "    (" << (float(StatsOptical.CerenkovSc))/(float(GeneratedSc))*100 << " %)"     << G4endl;
    // G4cout << "TOTAL Photons Generated:                     " << Generated      << G4endl;
    // G4cout << "     from Scintillation :                    " << Scintillation << "   (" << (float(Scintillation))/(float(Generated))*100 << " %)"     << G4endl;
    // G4cout << "     from Cerenkov :                         " << Cerenkov     << "    (" << (float(Cerenkov))/(float(Generated))*100 << " %)"     << G4endl;
    //
    // G4cout << "Photons Surface Absorbed  :                  " << StatsOptical.Absorbed      << "        " << Absfrac << " % " << G4endl;
    // G4cout << "Photons Bulk Absorbed in ZnS :               " << StatsOptical.BulkAbsZnS       << "        " << BulkfracZnS << " % " << G4endl;
    // G4cout << "Photons Bulk Absorbed in EJ-212 :            " << StatsOptical.BulkAbsSc       << "        " << BulkfracSc << " % " << G4endl;
    // G4cout << "Photons Escaped:                             " << StatsOptical.Escaped       << "        " << Escfrac << " % " << G4endl;
    // G4cout << "Photons only Transmitted to Photocathode:    " << StatsOptical.Failed        << "        " << Failfrac << " % " << G4endl;
    // G4cout << "Photons Collected in PMT (QE):               " << StatsOptical.Detected      << "        " << efficiency << " % " << G4endl;
    // G4cout << "Total Photons Considered:                    " << StatsOptical.Absorbed + StatsOptical.BulkAbsZnS + StatsOptical.BulkAbsSc + StatsOptical.Escaped + StatsOptical.Failed + StatsOptical.Detected  << "        " << Absfrac + BulkfracZnS + BulkfracSc + Escfrac + Failfrac + efficiency << " % " << G4endl;
    // //G4cout << "Photons WL Shifted:                          " << StatsOptical.WLS           << "        " << WLSfrac << " % " << G4endl;
    // G4cout << ""  <<  G4endl;
    // G4cout << ""  <<  G4endl;

  }

if(Deposit>0)
{
  runac->UpdateStatisticsOptical(StatsOptical);
  runac->UpdateStatisticsTP(StatsTP);
}


}
