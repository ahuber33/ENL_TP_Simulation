/// ENLTPSimSteppingAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLTPSimSteppingAction.hh"
#include "G4DynamicParticle.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4ProcessManager.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4OpticalPhoton.hh"
#include "ENLTPSimRunAction.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "ENLTPSimEventAction.hh"
#include <iostream>
#include <fstream>
#include "G4Material.hh"
#include "G4Trajectory.hh"
#include "ENLTPSimTrackInformation.hh"
#include "ENLTPSimGeometry.hh"
#include "G4StepPoint.hh"
#include "TRandom3.h"
#include "TF1.h"
#include "G4EmConfigurator.hh"
#include "G4IonFluctuations.hh"
#include "G4UniversalFluctuation.hh"
#include "G4ionIonisation.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4LossTableManager.hh"
#include "G4BraggIonGasModel.hh"
#include "G4BetheBlochIonGasModel.hh"



using namespace CLHEP;

const G4String ENLTPSimSteppingAction::path = "../simulation_input_files/";

ENLTPSimSteppingAction::ENLTPSimSteppingAction()
{}

  ENLTPSimSteppingAction::~ENLTPSimSteppingAction(){}
  void ENLTPSimSteppingAction::UserSteppingAction(const G4Step *aStep){


    //###################################
    // Déclaration of functions/variables
    //###################################
    G4Track* theTrack = aStep->GetTrack();
    ENLTPSimTrackInformation *trackInformation = (ENLTPSimTrackInformation*)theTrack->GetUserInformation();
    G4String partname = aStep->GetTrack()->GetDefinition()->GetParticleName();
    G4int partID = aStep->GetTrack()->GetDefinition()->GetPDGEncoding();
    ENLTPSimRunAction *runac = (ENLTPSimRunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());
    G4EventManager *evtman = G4EventManager::GetEventManager();
    ENLTPSimEventAction *evtac = (ENLTPSimEventAction*)evtman->GetUserEventAction();
    ENLTPSimTrackInformation* info = (ENLTPSimTrackInformation*)(aStep->GetTrack()->GetUserInformation());
    G4String endproc = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4int Parent_ID = aStep->GetTrack()->GetParentID();
    G4int StepNo = aStep->GetTrack()->GetCurrentStepNumber();

    G4double x = aStep->GetTrack()->GetPosition().x();
    G4double y = aStep->GetTrack()->GetPosition().y();
    G4double z = aStep->GetTrack()->GetPosition().z();
    G4double px = aStep->GetPostStepPoint()->GetMomentum().x();
    G4double py = aStep->GetPostStepPoint()->GetMomentum().y();
    G4double pz = aStep->GetPostStepPoint()->GetMomentum().z();
    G4double r = sqrt(x*x + y*y);
    //G4double my_dist_after = aStep->GetTrack()->GetTrackLength()/mm;



    //#######################################################################
    //#######################################################################
    //##########################START OPTICAL PART###########################
    //#######################################################################
    //#######################################################################

    if(0){                       //set to 1 to ignore generated photons
      if(theTrack->GetDefinition()->GetParticleName()=="opticalphoton")
      theTrack->SetTrackStatus(fStopAndKill);
    }

    //The following lines are for debugging purposes
    if(partname == "opticalphoton" && aStep->GetTrack()->GetUserInformation() ==0) G4cout << "WARNING! No user info attached to photon" << G4endl;

    G4OpBoundaryProcessStatus boundaryStatus=Undefined;
    static G4OpBoundaryProcess* boundary=NULL;

    //find the boundary process only once
    if(!boundary)
    {
      G4ProcessManager* pm = aStep->GetTrack()->GetDefinition()->GetProcessManager();
      G4int nprocesses = pm->GetProcessListLength();
      G4ProcessVector* pv = pm->GetProcessList();
      G4int i;
      for( i = 0; i < nprocesses; i++){
        if((*pv)[i]->GetProcessName()=="OpBoundary")
        {
          boundary = (G4OpBoundaryProcess*)(*pv)[i];
          break;
        }
      }
    }


    if(partname =="opticalphoton")
    { //ALL the code in relation with Optical needs to be here !!!!
      boundaryStatus = boundary->GetStatus();
      //G4cout << "BirthLambda = " << info->GetBirthLambda() << G4endl;
      //G4cout << "Time =" << aStep->GetPostStepPoint()->GetGlobalTime()/ns << G4endl;

      if(endproc == "OpAbsorption")
      {
        if(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "ZnS") {evtac->CountBulkAbsZnS();}
        if(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "Scintillator") {evtac->CountBulkAbsSc();}
        //G4cout << "Photon BulkAbsorbed" << G4endl;
        //G4cout << "N bulk abs Sc = " << evtac->GetBulkAbsSc() << G4endl;
        //G4cout << "N bulk abs ZnS = " << evtac->GetBulkAbsZnS() << G4endl;
      }


      if(endproc == "OpRayleigh")
      {
        ((ENLTPSimTrackInformation*)(aStep->GetTrack()->GetUserInformation()))->CountRayleighScattering();
        //G4cout << "Rayleigh scattering" << G4endl;
        //G4cout << "Number of scattering = " << ((ENLOpticalSimTrackInformation*) (aStep->GetTrack()->GetUserInformation()))->GetRayleigh() << G4endl;
      }

      // If WLS -> Use this !!!
      /*
      else if (endproc == "OpWLS")
      {
      evtac->CountWLS();
      my_dist_after = my_dist_after + aStep->GetTrack()->GetTrackLength()/mm;
      //G4cout << "Count WLS true = " << info->GetWLSCount() << G4endl;
      //G4cout << "Distance d = " << d << G4endl;

      //{
      if (info->GetWLSCount() == 0)
      {
      Length_Track = aStep->GetTrack()->GetTrackLength()/mm;
      //G4cout << "Count WLS = " << info->GetWLSCount() << G4endl;
    }

    if (info->GetWLSCount() > 0)
    {
    Length_Track += aStep->GetTrack()->GetTrackLength()/mm;
    //G4cout << "Count WLS = " << info->GetWLSCount() << G4endl;
  }
  //G4cout << "Track Length = " << aStep->GetTrack()->GetTrackLength()/mm << G4endl;
  //G4cout << "Total Length Track (for different OpWLS) = " << Total_Length_Track << G4endl;
}
*/

else if(partname == "opticalphoton" && endproc != "Transportation" && endproc != "OpAbsorption")
G4cout << endproc << G4endl;


if(aStep->GetPostStepPoint()->GetStepStatus()==fGeomBoundary){

  switch(boundaryStatus){
    case Detection:
    {
      evtac->CountDetected();
      evtac->FillPhotonPositionX(x);
      evtac->FillPhotonPositionY(y);
      evtac->FillPhotonPositionZ(z);
      evtac->FillPhotonMomentumX(px);
      evtac->FillPhotonMomentumY(py);
      evtac->FillPhotonMomentumZ(pz);
      evtac->FillBirthLambda(info->GetBirthLambda());
      evtac->FillPhotonTime(aStep->GetPostStepPoint()->GetGlobalTime()/ns);
      evtac->FillEnergype(aStep->GetTotalEnergyDeposit()/eV);
      evtac->FillRayleigh(((ENLTPSimTrackInformation*) (aStep->GetTrack()->GetUserInformation()))->GetRayleigh());
      evtac->FillTotalReflections(((ENLTPSimTrackInformation*) (aStep->GetTrack()->GetUserInformation()))->GetTotalInternalReflections());
      evtac->FillWrapReflecions(((ENLTPSimTrackInformation*)(aStep->GetTrack()->GetUserInformation()))->GetReflections());
      evtac->FillPhotonTotalLength(aStep->GetTrack()->GetTrackLength()/mm);
      //G4cout << "Photon detecté" << G4endl;
      //G4cout << "N detecté = " << evtac->GetDetected() << G4endl;

      break;
      case Absorption:    // used to get the number TRANSMITTED!!

      if (theTrack->GetNextVolume()->GetName()=="Photocathode")
      {
        evtac->CountFailed();
        //G4cout << "Photon failed" << G4endl;
        //G4cout << "N failed = " << evtac->GetFailed() << G4endl;

        //  Note that currently it is not set up to root output...see void CountDetected();
      }
      else{  // if not bulk, transmitted, or detected...it must be surface!
        evtac->CountAbsorbed();
        //G4cout << "Photon surface absorbed" << G4endl;
        //G4cout << "N absorbed = " << evtac->GetAbsorbed() << G4endl;
      }

      break;
      case Undefined: G4cout<<"Undefined Boundary Process!"<<G4endl;
      break;
      case NoRINDEX:
      {
        evtac->CountEscaped();
        //G4cout << "count escaped" << G4endl;
        //G4cout << "N escaped = " << evtac->GetEscaped() << G4endl;
      }
      break;

      // if we have any kind of reflections, count them
      case LambertianReflection:
      case LobeReflection:
      case SpikeReflection:
      {
        ((ENLTPSimTrackInformation*)(aStep->GetTrack()->GetUserInformation()))->CountReflections();
        //G4cout << "Reflection" << G4endl;
        break;}
        case TotalInternalReflection:
        {
          ((ENLTPSimTrackInformation*)(aStep->GetTrack()->GetUserInformation()))->CountTotalInternalReflections();
          //G4cout << "Reflection totale" << G4endl;
          break;
        }
        default:
        break;
      }
    }
  }


  if(partname == "opticalphoton" && aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "Scintillation" && StepNo ==1)
  {
    if(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "ZnS")
    {
      evtac->CountScintillationZnS();
      //G4cout << " Photon Scintillation from ZnS!!!" << G4endl;
    }

    if(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "Scintillator")
    {
      evtac->CountScintillationSc();
      //G4cout << " Photon Scintillation from Sc!!!" << G4endl;
    }
    //G4cout << "n sc = " << evtac->GetCountScintillation() << G4endl;

  }

  if(partname == "opticalphoton" && aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "Cerenkov" && StepNo ==1)
  {
    //G4cout << " Photon Cerenkov !!!" << G4endl;
    if(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "ZnS"){evtac->CountCerenkovZnS();}
    if(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "Scintillator"){evtac->CountCerenkovSc();}
    //G4cout << "n cerenkov = " << evtac->GetCountCerenkov() << G4endl;
    //G4cout << " Birth = " << info->GetBirthLambda() << G4endl;
  }


}

//#######################################################################
//#######################################################################
//############################END OPTICAL PART###########################
//#######################################################################
//#######################################################################



//#######################################################################
//#######################################################################
//###########################START EM INFOS PART#########################
//#######################################################################
//#######################################################################

if (Parent_ID ==0 && StepNo==1)
{
  evtac->SetEstartTP(aStep->GetPreStepPoint()->GetKineticEnergy()/keV);
  evtac->SetIncidentE(aStep->GetPreStepPoint()->GetKineticEnergy()/keV);
  evtac->SetParticuleID(partID);
  evtac->SetCharge(aStep->GetPostStepPoint()->GetCharge());
}


if (((aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "Scintillator") || (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "ZnS"))
&& ((aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() == "Scintillator") || (aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() == "ZnS"))
&& partname != "opticalphoton")
{
  evtac->AddTrackLength(aStep->GetTrack()->GetStepLength()/mm);
  evtac->AddEdepTP(aStep->GetTotalEnergyDeposit()/keV);
}

//Be careful here !!! If Zns in here, put ZnS. If not, put Scintillator !!!!
if(Parent_ID ==0 && aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() == "Scintillator" && evtac->GetTPPositionZ()==0)
{
  evtac->SetTPPositionX(x);
  evtac->SetTPPositionY(y);
  evtac->SetTPPositionZ(z);
  evtac->SetTPTime(aStep->GetPostStepPoint()->GetGlobalTime()/ns);
}

if(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "ZnS" && partname != "opticalphoton") {evtac->AddEdepZnS(aStep->GetTotalEnergyDeposit()/keV);}
if(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "Scintillator" && partname != "opticalphoton") {evtac->AddEdepSc(aStep->GetTotalEnergyDeposit()/keV);}

if(aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() == "PhysicalWorld") {theTrack->SetTrackStatus(fStopAndKill);}


//G4cout << "Charge = " << aStep->GetPostStepPoint()->GetCharge() << G4endl;
//G4cout<< "Charge 2 = " << aStep->GetTrack()->GetDefinition()->GetPDGCharge()<<G4endl;

}
