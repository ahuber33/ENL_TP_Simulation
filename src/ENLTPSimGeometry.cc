//// ENLTPSimGeometry.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLTPSimGeometry.hh"
#include "ENLTPSimRunAction.hh"
#include "ENLTPSimMaterials.hh"
#include "ENLTPSimSteppingAction.hh"
#include "Geometry.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4UnitsTable.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4Box.hh"
#include "G4Orb.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4SDManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4MaterialTable.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4RunManager.hh"
#include "G4Transform3D.hh"
#include "G4SurfaceProperty.hh"
#include "globals.hh"
#include <fstream>
#include <iostream>
#include "G4PVParameterised.hh"
#include "G4PVReplica.hh"
#include "G4SubtractionSolid.hh"
#include "G4AssemblyVolume.hh"

#include "G4ElectroMagneticField.hh"
#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4EquationOfMotion.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4ChordFinder.hh"
#include "G4UniformElectricField.hh"
#include "G4EqMagElectricField.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4MagIntegratorDriver.hh"

#include "G4ExplicitEuler.hh"
#include "G4ImplicitEuler.hh"
#include "G4SimpleRunge.hh"
#include "G4SimpleHeum.hh"
#include "G4ClassicalRK4.hh"
#include "G4HelixExplicitEuler.hh"
#include "G4HelixImplicitEuler.hh"
#include "G4HelixSimpleRunge.hh"
#include "G4CashKarpRKF45.hh"
#include "G4RKG3_Stepper.hh"
#include "G4ConstRK4.hh"
#include "G4NystromRK4.hh"
#include "G4HelixMixedStepper.hh"
#include "G4ExactHelixStepper.hh"
#include "G4InterpolationDriver.hh"
#include "G4IntegrationDriver.hh"
#include "G4VIntegrationDriver.hh"
#include "G4BFieldIntegrationDriver.hh"
#include <G4HelixHeum.hh>

// Newest steppers - from Release 10.3-beta (June 2013)
#include "G4BogackiShampine23.hh"
#include "G4BogackiShampine45.hh"
#include "G4DormandPrince745.hh"
#include "G4DormandPrinceRK56.hh"
#include "G4DormandPrinceRK78.hh"
#include "G4TsitourasRK45.hh"


using namespace CLHEP;

const G4String ENLTPSimGeometry::path_bin = "../bin/";
const G4String ENLTPSimGeometry::path = "../simulation_input_files/";

// Constructor
ENLTPSimGeometry::ENLTPSimGeometry(){}

// Destructor
ENLTPSimGeometry::~ENLTPSimGeometry()
{
}

// Main Function: Builds Full block, coupling, and PMT geometries
G4VPhysicalVolume* ENLTPSimGeometry::Construct( ){
  // Initialize scint classes
  scintProp = new ENLTPSimMaterials(path_bin+"Materials.cfg");
  Vacuum = scintProp->GetMaterial("Vacuum");
  VacuumWorld = scintProp->GetMaterial("VacuumWorld");
  Air = scintProp->GetMaterial("Air");
  Alu = scintProp->GetMaterial("Alu");
  theScint = new Geometry(path_bin+"ENLTPSim.cfg");


  // ***********************
  // Visualization Colors
  // ***********************
  // Create some colors for visualizations
  invis = new G4VisAttributes( G4Colour(255/255. ,255/255. ,255/255. ));
  invis->SetVisibility(false);

  white = new G4VisAttributes(G4Colour(1,1,1,1.)); // Sets the color (can be looked up online)
  //white->SetForceWireframe(true); // Sets to wire frame mode for coloring the volume
  white->SetForceSolid(true); // Sets to solid mode for coloring the volume
  white->SetVisibility(true); // Makes color visible in visualization

  gray = new G4VisAttributes(G4Colour(0.5,0.5,0.5,0.5));
  //  gray->SetForceWireframe(true);
  gray->SetForceSolid(true);
  gray->SetVisibility(true);

  gray_bis = new G4VisAttributes(G4Colour(0.5,0.5,0.5,0.05));
  //  gray->SetForceWireframe(true);
  gray_bis->SetForceSolid(true);
  gray_bis->SetVisibility(true);

  black = new G4VisAttributes(G4Colour(0,0,0,0.7));
  //  black->SetForceWireframe(true);
  black->SetForceSolid(true);
  black->SetVisibility(true);


  black_bis = new G4VisAttributes(G4Colour(0,0,0,0.4));
  //  black->SetForceWireframe(true);
  black_bis->SetForceSolid(true);
  black_bis->SetVisibility(true);

  red = new G4VisAttributes(G4Colour(1,0,0,0.5));
  //  red->SetForceWireframe(true);
  red->SetForceSolid(true);
  red->SetVisibility(true);


  red_hot = new G4VisAttributes(G4Colour(1,0,0,1));
  //  red->SetForceWireframe(true);
  red_hot->SetForceSolid(true);
  red_hot->SetVisibility(true);

  orange = new G4VisAttributes(G4Colour(1,0.5,0,0.1));
  //  orange->SetForceWireframe(true);
  orange->SetForceSolid(true);
  orange->SetVisibility(true);

  yellow = new G4VisAttributes(G4Colour(1,1,0,0.1));
  //  yellow->SetForceWireframe(true);
  yellow->SetForceSolid(true);
  yellow->SetVisibility(true);

  green = new G4VisAttributes(G4Colour(0,1,0,0.35));
  //  green->SetForceWireframe(true);
  green->SetForceSolid(true);
  green->SetVisibility(true);

  green_hot = new G4VisAttributes(G4Colour(0,1,0,1));
  //  green_hot->SetForceWireframe(true);
  green_hot->SetForceSolid(true);
  green_hot->SetVisibility(true);

  cyan = new G4VisAttributes(G4Colour(0,1,1,0.1));
  //  cyan->SetForceWireframe(true);
  cyan->SetForceSolid(true);
  cyan->SetVisibility(true);

  blue = new G4VisAttributes(G4Colour(0,0,1,0.5));
  //  blue->SetForceWireframe(true);
  blue->SetForceSolid(true);
  blue->SetVisibility(true);

  magenta = new G4VisAttributes(G4Colour(1,0,1,0.85));
  //  magenta->SetForceWireframe(true);
  //magenta->SetForceSolid(true);
  magenta->SetVisibility(true);

  // Define common rotations
  G4RotationMatrix DontRotate;
  DontRotate.rotateX(0.0*deg);
  G4RotationMatrix Flip;
  Flip.rotateZ(0*deg);
  Flip.rotateX(180*deg);
  Flip.rotateY(0*deg);


  // ***********************
  // Various dimensions
  // ***********************
  EF_Value = theScint->GetEFValue();
  EF_Dist_between_plates = theScint->GetDistBetweenPlates();
  EF_Thickness_plates = theScint->GetEFPlatesThickness();
  EF_Length_plates = theScint->GetEFPlatesLength();
  EF_Width_plates = theScint->GetEFPlatesWidth();
  MF_Value = theScint->GetMFValue();
  MF_Dist_between_plates = theScint->GetMFDistBetweenPlates();
  MF_Thickness_plates = theScint->GetMFPlatesThickness();
  MF_Length_plates = theScint->GetMFPlatesLength();
  MF_Width_plates = theScint->GetMFPlatesWidth();
  Dist_between_plates = theScint->GetDistBetweenPlates();
  Dist_EFPlates_Detector = theScint->GetEFPlatesDetector();
  Dist_pinhole_MFPlates = theScint->GetPinholeMFPlates();
  translation_pinhole = theScint->GetTranslationPinhole();
  ScintillatorThickness = theScint->GetScintillatorThickness();
  DetectorThickness = theScint->GetDetectorThickness();
  DetectorTranslation = theScint->GetDetectorTranslation();
  LensThickness = theScint->GetLensThickness();
  LensTranslation = theScint->GetLensTranslation();
  PinholeThickness = theScint->GetPinholeThickness();

  //#########################
  // DEFINE GEOMETRY VOLUMES#
  //#########################

  // Create World Volume
  // This is just a big box to place all other logical volumes inside
  G4Box *SolidWorld = new G4Box("SolidWorld", 1100*cm, 1100*cm, 1100*cm );
  LogicalWorld = new G4LogicalVolume(SolidWorld, VacuumWorld,"LogicalWorld",0,0,0);
  LogicalWorld->SetVisAttributes(invis);

  // Place the world volume: center of world at origin (0,0,0)
  PhysicalWorld = new G4PVPlacement(G4Transform3D(DontRotate,G4ThreeVector(0,0,0)),"World",LogicalWorld,NULL,false,0);


  // Create Holder Volume
  // This is just a big box to count the escaped photons
  G4Box *s_holder = new G4Box("s_holder", 1000*cm, 1000*cm, 1000*cm);

  LogicalHolder = new G4LogicalVolume(s_holder,Vacuum,"logical_holder",0,0,0); //Replace Air with Vacuum (init)


  //*********************************
  // Build scint et wrapping volumes*
  //*********************** *********
  //Simply calls functions from Scintillator() class
  LogicalPinhole = theScint->GetPinhole();
  LogicalEFPlates = theScint->GetEFPlates();
  LogicalVolumeEFPlates = theScint->GetVolumeEFPlates();
  LogicalMFPlates = theScint->GetMFPlates();
  LogicalVolumeMFPlates = theScint->GetVolumeMFPlates();
  LogicalSc = theScint->GetScTest();
  LogicalLens = theScint->GetLens();

  // Set colors of various block materials
  LogicalPinhole->SetVisAttributes(black);
  LogicalEFPlates->SetVisAttributes(red);
  LogicalVolumeEFPlates->SetVisAttributes(gray);
  LogicalMFPlates->SetVisAttributes(blue);
  LogicalVolumeMFPlates->SetVisAttributes(gray);
  LogicalSc->SetVisAttributes(cyan);
  LogicalHolder->SetVisAttributes(invis);
  LogicalLens->SetVisAttributes(gray);

  //***********************
  // Build PMT volumes    *
  //***********************

  // Build the PMT glass structure from PMT class
  LogicalPhotocathode = theScint->GetPhotocathode(); // Call function for PMT glass
  LogicalPhotocathode->SetVisAttributes(orange); // Set photocathode color to orange


  // Define PMT properties
  G4double indexconst = 1.49; // Index currently set to constant for PMT glass
  G4double reflectconst = 0.;
  std::ifstream ReadPMT;
  //G4String PMTfile = path+"QE_ham_GA0124.txt";
  //G4String PMTfile = path+"9102B_ET_reverse.txt";
  G4String PMTfile = path+"ORCA_ENL_reverse.cfg";
  std::vector<G4double> Photocathode_Energy;
  std::vector<G4double> Photocathode_Value;
  std::vector<G4double> Photocathode_Index;
  std::vector<G4double> Photocathode_Reflectivity;
  double wavelength=0.;
  G4double quant_eff;
  ReadPMT.open(PMTfile);
  if (ReadPMT.is_open()){
    while(!ReadPMT.eof()){
      G4String filler;
      ReadPMT >> wavelength >> filler >> quant_eff;
      //PMTdetect[PMTentries] = 0.79*quant_eff*.65;  //0.79 = correction factor to adjust QE to lower value of 34% for R6594 and 0.59 = 25%
      //PMTdetect1[PMTentries] = 1; // Use only if you want %100 QE
      Photocathode_Energy.push_back((1240/wavelength)*eV);
      //Photocathode_Value.push_back(1);  //For the GAxxxx file with good QE and 0.65 for collection efficiency
      Photocathode_Value.push_back(quant_eff*1); //Change 1 if you know ou want to apply a collection efficiency factor !!!
      Photocathode_Index.push_back(indexconst);
      Photocathode_Reflectivity.push_back(reflectconst);
    }
  }
  else
  G4cout << "Error opening file: " << PMTfile << G4endl;
  ReadPMT.close();

  // Define PMT optical boundary surface properties
  OpticalPMT = new G4OpticalSurface("OpticalPMT");
  OpticalPMT->SetModel(glisur);
  OpticalPMT->SetFinish(polished);
  OpticalPMT->SetType(dielectric_metal);

  // Define PMT material properties
  PMT_MPT = new G4MaterialPropertiesTable();
  PMT_MPT->AddProperty("EFFICIENCY",Photocathode_Energy, Photocathode_Value);
  PMT_MPT->AddProperty("REFLECTIVITY",Photocathode_Energy, Photocathode_Reflectivity);
  PMT_MPT->AddProperty("RINDEX", Photocathode_Energy, Photocathode_Index);

  // Geometrical implementation of boundary surface
  OpticalPMT->SetMaterialPropertiesTable(PMT_MPT);
  SSPhotocathode = new G4LogicalSkinSurface("SSVikuiti",LogicalPhotocathode,OpticalPMT);


  //#########################
  // DEFINE EM FIELD PART   #
  //#########################

    G4double fMinStep     = 1*um; // minimal step of 1 mm is default

    // Set accuracy parameters
    G4double deltaChord        = 1*nm; //3.0 mm by default
    G4double epsMax            = 1.0e-16;  // Pure number -- maximum relative integration error
    G4double epsMin            = 1.0e-16;  //
    G4double deltaOneStep      = 0.1*um;
    G4double deltaIntersection = 0.1*um;

  EMField* field = new EMField();


    G4EqMagElectricField* fEquation = new G4EqMagElectricField(field);
    G4MagIntegratorStepper* fStepper = new G4ClassicalRK4 (fEquation, 8);
    //G4MagIntegratorStepper* fStepper = new G4BogackiShampine23 (fEquation, 8);

    G4FieldManager* fFieldMgr =
    G4TransportationManager::GetTransportationManager()->GetFieldManager();

    // Relaxed
    G4MagInt_Driver* fIntgrDriver =
    new G4MagInt_Driver(1*nm,fStepper,fStepper->GetNumberOfVariables() );
    //fIntgrDriver->SetHmin(1);

    G4ChordFinder* fChordFinder = new G4ChordFinder(fIntgrDriver);
    fFieldMgr->SetChordFinder(fChordFinder);
    fChordFinder->SetDeltaChord( deltaChord );
    fFieldMgr->SetDetectorField(field);
    fFieldMgr->SetAccuraciesWithDeltaOneStep(deltaOneStep);
    fFieldMgr->SetMinimumEpsilonStep(epsMin);
    fFieldMgr->SetMaximumEpsilonStep(epsMax);
    fFieldMgr->SetDeltaIntersection(deltaIntersection);
    fFieldMgr->SetDeltaOneStep(0.1 * um);



  //***********************
  // Various Positioning values
  //***********************

  Z_Position_MFPlates = PinholeThickness/2 + Dist_pinhole_MFPlates + MF_Length_plates/2;
  Z_Position_EFPlates = PinholeThickness/2 + Dist_pinhole_MFPlates + MF_Length_plates + Dist_between_plates + EF_Length_plates/2;
  Z_Position_ZnS = PinholeThickness/2 + Dist_pinhole_MFPlates + MF_Length_plates + Dist_between_plates + EF_Length_plates + Dist_EFPlates_Detector + ZnSThickness/2;
  Z_Position_Sc = MF_Length_plates/2 + Dist_EFPlates_Detector + ScintillatorThickness/2;// + Dist_between_plates + EF_Length_plates + Dist_EFPlates_Detector + ZnSThickness + ScintillatorThickness/2;
  Z_Position_Photocathode = PinholeThickness/2 + Dist_pinhole_MFPlates + MF_Length_plates + Dist_between_plates + EF_Length_plates + Dist_EFPlates_Detector + ScintillatorThickness + DetectorThickness/2;
  Z_Position_Lens = PinholeThickness/2 + Dist_pinhole_MFPlates + MF_Length_plates + Dist_between_plates + EF_Length_plates + Dist_EFPlates_Detector + FiberLength + LensTranslation + LensThickness/2;


  //############################
  // DEFINE GEOMETRY PLACEMENTS#
  //############################

  #ifndef disable_gdml

  PhysicalHolder = new G4PVPlacement(G4Transform3D(DontRotate,G4ThreeVector(0, 0, 0)),LogicalHolder, "Vacuum", LogicalWorld,false,0);

  PhysicalPinhole = new G4PVPlacement(G4Transform3D
    (DontRotate,G4ThreeVector(-15.4*mm, 0*mm, -45.4*mm)), // Set at origin as basis of everything else
    LogicalPinhole,"Pinhole",
    LogicalHolder,false,0);

    PhysicalVolumeMFPlates = new G4PVPlacement(G4Transform3D
      (DontRotate,G4ThreeVector(0*mm, 0*mm, 0*mm)), // Set at origin as basis of everything else
      LogicalVolumeMFPlates,"Volume_MF_Plates",
      LogicalHolder,false,0);

      PhysicalMFPlates = new G4PVPlacement(G4Transform3D
        (DontRotate,G4ThreeVector(0*mm, 0, 0)), // Set at origin as basis of everything else
        LogicalMFPlates,"MF_Plates",
        LogicalVolumeMFPlates,false,0);

        // PhysicalVolumeEFPlates = new G4PVPlacement(G4Transform3D
        //   (DontRotate,G4ThreeVector(0*mm,translation_pinhole, Z_Position_EFPlates)), // Set at origin as basis of everything else
        //   LogicalVolumeEFPlates,"Volume_EF_Plates",
        //   LogicalHolder,false,0);
        //
        //   PhysicalEFPlates = new G4PVPlacement(G4Transform3D
        //     (DontRotate,G4ThreeVector(0*mm, 0, 0)), // Set at origin as basis of everything else
        //     LogicalEFPlates,"EF_Plates",
        //     LogicalVolumeEFPlates,false,0);

        PhysicalSc = new G4PVPlacement(G4Transform3D
          (DontRotate,G4ThreeVector(34.6*mm, 17.9*mm, Z_Position_Sc)), // Set at origin as basis of everything else
          LogicalSc,"Scintillator",
          LogicalHolder,false,0);

          // PMT photocathode placement
          // PhysicalPhotocathode = new G4PVPlacement(G4Transform3D
          //   //(DontRotate,G4ThreeVector(FiberWidth/2 + FiberSpace - WidthBunchFibers/2, 0, Z_Position_Photocathode)), //USE THAT FOR TP
          //   (DontRotate,G4ThreeVector(-21, 5, Z_Position_Photocathode)), //USE THAT FOR DEBUG
          //   LogicalPhotocathode,"ORCA",
          //   LogicalHolder,true,0);


          // Lens placement
          // PhysicalLens = new G4PVPlacement(G4Transform3D
          //   (DontRotate,G4ThreeVector(-37.5, -37.5, Z_Position_Lens)), //USE THAT FOR DEBUG
          //   LogicalLens,"Lens",
          //   LogicalHolder,true,0);

          #else

          #endif





          // Returns world with everything in it and all properties set
          return PhysicalWorld;
        }
