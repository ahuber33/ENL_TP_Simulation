// TPSimGeometry_test.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2017 (C) Projet BADGE - CARMELEC -P2R

#include "TPSimGeometry.hh"
#include "TPSimRunAction.hh"
#include "TPSimMaterials.hh"
#include "TPSimSteppingAction.hh"
#include "GM.hh"
#include "Coupling.hh"
#include "PMT.hh"
#include "GdL.hh"
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

using namespace CLHEP;

const G4String TPSimGeometry::path_bin = "../bin/";
const G4String TPSimGeometry::path = "../simulation_input_files/";

// Constructor
TPSimGeometry::TPSimGeometry(){}

// Destructor
TPSimGeometry::~TPSimGeometry()
{
}

// Main Function: Builds Full block, coupling, and PMT geometries
G4VPhysicalVolume* TPSimGeometry::Construct( ){
  // Initialize scint classes
  scintProp = new TPSimMaterials(path_bin+"Materials.cfg");
  Vacuum = scintProp->GetMaterial("Vacuum");
  VacuumWorld = scintProp->GetMaterial("VacuumWorld");
  Air = scintProp->GetMaterial("Air");
  theScint = new GM(path_bin+"OpticalModule.cfg");


  // ***********************
  // Visualization Colors
  // ***********************
  // Create some colors for visualizations
  invis = new G4VisAttributes( G4Colour(255/255. ,255/255. ,255/255. ));
  invis->SetVisibility(false);

  white = new G4VisAttributes(G4Colour(1,1,1,0.1)); // Sets the color (can be looked up online)
  //white->SetForceWireframe(true); // Sets to wire frame mode for coloring the volume
  white->SetForceSolid(true); // Sets to solid mode for coloring the volume
  white->SetVisibility(true); // Makes color visible in visualization

  gray = new G4VisAttributes(G4Colour(0.5,0.5,0.5,0.5));
  //  gray->SetForceWireframe(true);
   gray->SetForceSolid(true);
  gray->SetVisibility(true);

  gray_bis = new G4VisAttributes(G4Colour(0.5,0.5,0.5,0.25));
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

  orange = new G4VisAttributes(G4Colour(1,0.5,0,0.3));
  //  orange->SetForceWireframe(true);
  orange->SetForceSolid(true);
  orange->SetVisibility(true);

  yellow = new G4VisAttributes(G4Colour(1,1,0,0.19));
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

  cyan = new G4VisAttributes(G4Colour(0,1,1,0.95));
  //  cyan->SetForceWireframe(true);
  cyan->SetForceSolid(true);
  cyan->SetVisibility(true);

  blue = new G4VisAttributes(G4Colour(0,0,1,0.3));
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
  Flip.rotateX(90*deg);
  Flip.rotateY(0*deg);

  //#########################
  // DEFINE GEOMETRY VOLUMES#
  //#########################

  // Create World Volume
  // This is just a big box to place all other logical volumes inside
  G4Box *SolidWorld = new G4Box("SolidWorld", 110*cm, 110*cm, 110*cm );
  LogicalWorld = new G4LogicalVolume(SolidWorld, VacuumWorld,"LogicalWorld",0,0,0);
  LogicalWorld->SetVisAttributes(invis);

  // Place the world volume: center of world at origin (0,0,0)
  PhysicalWorld = new G4PVPlacement(G4Transform3D
				    (DontRotate,G4ThreeVector(0,0,0)),
				    "PhysicalWorld",LogicalWorld,NULL,false,0);



  // Create Holder Volume
  // This is just a big box to count the escaped photons
  //G4Box *s_holder;
  G4Orb *s_holder;
  s_holder = new G4Orb("s_holder",29.9*cm) ;

   LogicalHolder = new G4LogicalVolume(s_holder,Air,"logical_holder",0,0,0); //Replace Air with Vacuum (init)

  // Place the holder volume: center of world at origin (0,0,0)
  PhysicalHolder = new G4PVPlacement(G4Transform3D
				    (DontRotate,G4ThreeVector(0,0,0)),
				    LogicalHolder, "Air",LogicalWorld,false,0);

  LogicalHolder->SetVisAttributes(invis);


  //*********************************
  // Build scint et wrapping volumes*
  //*********************** *********
  //Simply calls functions from Scintillator() class
  LogicalDolphy_GM = theScint->GetDolphy_GM();
  LogicalDolphy_Anode = theScint->GetDolphy_Anode();
  LogicalDolphy_Gaz = theScint->GetDolphy_Gaz();
  LogicalDolphy_Membrane = theScint->GetDolphy_Membrane();
  LogicalDolphy_Bague = theScint->GetDolphy_Bague();
  LogicalDolphy_Ampoule = theScint->GetDolphy_Ampoule();
  LogicalDolphy_Circuit_Imprime = theScint->GetDolphy_Circuit_Imprime();
  LogicalDolphy_Bouton_Poussoir = theScint->GetDolphy_Bouton_Poussoir();
  LogicalDolphy_Buzzer = theScint->GetDolphy_Buzzer();
  LogicalDolphy_CI = theScint->GetDolphy_CI();
  LogicalDolphy_Connecteur = theScint->GetDolphy_Connecteur();
  LogicalDolphy_Ecran = theScint->GetDolphy_Ecran();
  LogicalDolphy_Ecrou = theScint->GetDolphy_Ecrou();
  LogicalDolphy_Transfo = theScint->GetDolphy_Transfo();
  LogicalDolphy_Couvercle_Pile = theScint->GetDolphy_Couvercle_Pile();
  LogicalDolphy_Pile = theScint->GetDolphy_Pile();
  LogicalDolphy_Dessous = theScint->GetDolphy_Dessous();
  LogicalDolphy_Dessus = theScint->GetDolphy_Dessus();
  LogicalDolphy_Fenetre = theScint->GetDolphy_Fenetre();
  LogicalDolphy_Grille = theScint->GetDolphy_Grille();
  LogicalDolphy_Insert1 = theScint->GetDolphy_Insert1();
  LogicalDolphy_Insert2 = theScint->GetDolphy_Insert2();
  LogicalDolphy_Insert3 = theScint->GetDolphy_Insert3();
  LogicalDolphy_Protection_Grille = theScint->GetDolphy_Protection_Grille();
  LogicalDolphy_Protection_Grille_Test = theScint->GetDolphy_Protection_Grille_Test();
  LogicalDolphy_Rondelle_Protection = theScint->GetDolphy_Rondelle_Protection();
  LogicalDolphy_Filtre_H10 = theScint->GetDolphy_Filtre_H10();
  LogicalDolphy_Mousse_GM = theScint->GetDolphy_Mousse_GM();
  LogicalDolphy_Rondelle = theScint->GetDolphy_Rondelle();
  LogicalDolphy_Support_Ressort1 = theScint->GetDolphy_Support_Ressort1();
  LogicalDolphy_Support_Ressort2 = theScint->GetDolphy_Support_Ressort2();
  LogicalDolphy_Vis_1 = theScint->GetDolphy_Vis1();
  LogicalDolphy_Vis_2 = theScint->GetDolphy_Vis2();
  LogicalDolphy_Vis_3 = theScint->GetDolphy_Vis3();
  LogicalDolphy_Vis_4 = theScint->GetDolphy_Vis4();
  LogicalDolphy_Vis_5 = theScint->GetDolphy_Vis5();
  LogicalDolphy_Vis_6 = theScint->GetDolphy_Vis6();
  LogicalDolphy_Vis_7 = theScint->GetDolphy_Vis7();
  LogicalDolphy_Vis_8 = theScint->GetDolphy_Vis8();
  LogicalDolphy_Vis_9 = theScint->GetDolphy_Vis9();
  LogicalDolphy_Vis_10 = theScint->GetDolphy_Vis10();
  LogicalDolphy_Vis_11 = theScint->GetDolphy_Vis11();
  LogicalDolphy_Vis_12 = theScint->GetDolphy_Vis12();

  // Set colors of various block materials
  LogicalDolphy_GM->SetVisAttributes(red);
  LogicalDolphy_Anode->SetVisAttributes(yellow);
  LogicalDolphy_Gaz->SetVisAttributes(green);
  LogicalDolphy_Membrane->SetVisAttributes(black);
  LogicalDolphy_Bague->SetVisAttributes(gray);
  LogicalDolphy_Ampoule->SetVisAttributes(gray);
  LogicalDolphy_Circuit_Imprime->SetVisAttributes(yellow);
  LogicalDolphy_Bouton_Poussoir->SetVisAttributes(orange);
  LogicalDolphy_Buzzer->SetVisAttributes(cyan);
  LogicalDolphy_CI->SetVisAttributes(blue);
  LogicalDolphy_Connecteur->SetVisAttributes(blue);
  LogicalDolphy_Ecran->SetVisAttributes(magenta);
  LogicalDolphy_Ecrou->SetVisAttributes(orange);
  LogicalDolphy_Transfo->SetVisAttributes(orange);
  LogicalDolphy_Couvercle_Pile->SetVisAttributes(gray);
  LogicalDolphy_Pile->SetVisAttributes(red);
  LogicalDolphy_Dessous->SetVisAttributes(gray_bis);
  LogicalDolphy_Dessus->SetVisAttributes(gray_bis);
  LogicalDolphy_Fenetre->SetVisAttributes(blue);
  LogicalDolphy_Grille->SetVisAttributes(yellow);
  LogicalDolphy_Insert1->SetVisAttributes(orange);
  LogicalDolphy_Insert2->SetVisAttributes(orange);
  LogicalDolphy_Insert3->SetVisAttributes(orange);
  LogicalDolphy_Protection_Grille->SetVisAttributes(gray);
  LogicalDolphy_Filtre_H10->SetVisAttributes(gray);
  LogicalDolphy_Protection_Grille_Test->SetVisAttributes(cyan);
  LogicalDolphy_Rondelle_Protection->SetVisAttributes(orange);
  LogicalDolphy_Mousse_GM->SetVisAttributes(blue);
  LogicalDolphy_Rondelle->SetVisAttributes(yellow);
  LogicalDolphy_Support_Ressort1->SetVisAttributes(yellow);
  LogicalDolphy_Support_Ressort2->SetVisAttributes(yellow);
  LogicalDolphy_Vis_1->SetVisAttributes(cyan);
  LogicalDolphy_Vis_2->SetVisAttributes(cyan);
  LogicalDolphy_Vis_3->SetVisAttributes(cyan);
  LogicalDolphy_Vis_4->SetVisAttributes(cyan);
  LogicalDolphy_Vis_5->SetVisAttributes(cyan);
  LogicalDolphy_Vis_6->SetVisAttributes(cyan);
  LogicalDolphy_Vis_7->SetVisAttributes(cyan);
  LogicalDolphy_Vis_8->SetVisAttributes(cyan);
  LogicalDolphy_Vis_9->SetVisAttributes(cyan);
  LogicalDolphy_Vis_10->SetVisAttributes(cyan);
  LogicalDolphy_Vis_11->SetVisAttributes(cyan);
  LogicalDolphy_Vis_12->SetVisAttributes(cyan);

  //############################
  // DEFINE GEOMETRY PLACEMENTS#
  //############################

  #ifndef disable_gdml


  PhysicalDolphy_GM = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_GM,"GM_LND",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Gaz = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.645*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Gaz,"GM_Gaz",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Anode = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Anode,"GM_Anode",
  				    LogicalDolphy_Gaz,false,0);



  PhysicalDolphy_Membrane = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Membrane,"GM_Membrane",
  				    LogicalHolder,false,0);



  PhysicalDolphy_Bague = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Bague,"GM_Bague",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Ampoule = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Ampoule,"GM_Ampoule",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Circuit_Imprime = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Circuit_Imprime,"Circuit_Imprime",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Bouton_Poussoir = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Bouton_Poussoir,"Bouton_Poussoir",
  				    LogicalHolder,false,0);



  PhysicalDolphy_Buzzer = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Buzzer,"Buzzer",
  				    LogicalHolder,false,0);


  PhysicalDolphy_CI = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_CI,"CI",
  				    LogicalHolder,false,0);

  PhysicalDolphy_Connecteur = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Connecteur,"Connecteur",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Ecran = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Ecran,"Ecran",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Ecrou = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Ecrou,"Ecrou",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Transfo = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Transfo,"Transfo",
  				    LogicalHolder,false,0);



  PhysicalDolphy_Couvercle_Pile = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Couvercle_Pile,"Couvercle_Pile",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Pile = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Pile,"Pile",
  				    LogicalHolder,false,0);

  PhysicalDolphy_Dessous = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Dessous,"Dessous",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Dessus = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Dessus,"Dessus",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Fenetre = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Fenetre,"Fenetre",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Grille = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Grille,"Grille",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Insert1 = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Insert1,"Insert1",
  				    LogicalHolder,false,0);

  PhysicalDolphy_Insert2 = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Insert2,"Insert2",
  				    LogicalHolder,false,0);

  PhysicalDolphy_Insert3 = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Insert3,"Insert3",
  				    LogicalHolder,false,0);


  // PhysicalDolphy_Protection_Grille = new G4PVPlacement(G4Transform3D
  // 				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  // 				    LogicalDolphy_Protection_Grille,"Protection_Grille",
  // 				    LogicalHolder,false,0);


  PhysicalDolphy_Protection_Grille_Test = new G4PVPlacement(G4Transform3D
  				    (Flip,G4ThreeVector(0*mm,9.25*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Protection_Grille_Test,"Protection_Grille",
  				    LogicalHolder,false,0);



  // PhysicalDolphy_Filtre_H10 = new G4PVPlacement(G4Transform3D
  // 				    (DontRotate,G4ThreeVector(0*mm,0*mm,0.*mm)), // Set at origin as basis of everything else
  // 				    LogicalDolphy_Filtre_H10,"Filtre_H10",
  // 				    LogicalHolder,false,0);



  PhysicalDolphy_Rondelle_Protection = new G4PVPlacement(G4Transform3D
  				    (Flip,G4ThreeVector(0*mm,9.25*mm,0.*mm)), // 10.75 pour 4mm Nylon; 10.25 pour 3mm Nylon;
  				    LogicalDolphy_Rondelle_Protection,"Rondelle_Protection",
  				    LogicalHolder,false,0);



  PhysicalDolphy_Mousse_GM = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Mousse_GM,"Mousse_GM",
  				    LogicalHolder,false,0);



  PhysicalDolphy_Rondelle = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Rondelle,"Rondelle",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Support_Ressort1 = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Support_Ressort1,"Support_Ressort1",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Support_Ressort2 = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Support_Ressort2,"Support_Ressort2",
  				    LogicalHolder,false,0);





  PhysicalDolphy_Vis_1 = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Vis_1,"Vis_1",
  				    LogicalHolder,false,0);



  PhysicalDolphy_Vis_2 = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Vis_2,"Vis_2",
  				    LogicalHolder,false,0);



  PhysicalDolphy_Vis_3 = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Vis_3,"Vis_3",
  				    LogicalHolder,false,0);



  PhysicalDolphy_Vis_4 = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Vis_4,"Vis_4",
  				    LogicalHolder,false,0);



  PhysicalDolphy_Vis_5 = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Vis_5,"Vis_5",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Vis_6 = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Vis_6,"Vis_6",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Vis_7 = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Vis_7,"Vis_7",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Vis_8 = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Vis_8,"Vis_8",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Vis_9 = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Vis_9,"Vis_9",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Vis_10 = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Vis_10,"Vis_10",
  				    LogicalHolder,false,0);



  PhysicalDolphy_Vis_11 = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Vis_11,"Vis_11",
  				    LogicalHolder,false,0);


  PhysicalDolphy_Vis_12 = new G4PVPlacement(G4Transform3D
  				    (DontRotate,G4ThreeVector(0*mm,0.*mm,0.*mm)), // Set at origin as basis of everything else
  				    LogicalDolphy_Vis_12,"Vis_12",
  				    LogicalHolder,false,0);






#else

#endif





  // Returns world with everything in it and all properties set
  return PhysicalWorld;
}
