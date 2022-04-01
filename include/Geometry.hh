/// Geometry.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

// This class is used to create a plastic Geometry.

#ifndef Geometry_h
#define Geometry_h

#include "G4LogicalVolume.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "CLHEP/Units/SystemOfUnits.h"

class ENLTPSimMaterials;
class Geometry

{
public:

  //constructor, builds from keys specified in buildfile
  Geometry(G4String buildfile);
  ~Geometry();
  //  void Construct();

public:

  // Functions to call this geometry in x_blockGeometry.cc

  G4LogicalVolume *GetScTest();
  G4LogicalVolume *GetEFPlates();
  G4LogicalVolume *GetVolumeEFPlates();
  G4LogicalVolume *GetMFPlates();
  G4LogicalVolume *GetVolumeMFPlates();
  G4LogicalVolume *GetPinhole();
  G4LogicalVolume *GetLaBr3();
  G4LogicalVolume *GetZnS();
  G4LogicalVolume *GetPhotocathode();


  // Functions that can be called to return various scint dimensions

  //****************COMMON********************
  // wrapping
  G4double GetTeflonThickness(){return TeflonThickness;}
  G4double GetAirGapTeflon(){return AirGapTeflon;}
  G4double GetMylarThickness(){return MylarThickness;}
  G4double GetAirGapMylar(){return AirGapMylar;}
  // glue
  G4double GetGlueThickness(){return GlueThickness;}
  // ElectricField Plates
  G4double GetEFValue(){return EF_Value;}
  G4double GetEFDistBetweenPlates(){return EF_Dist_between_plates;}
  G4double GetEFPlatesThickness(){return EF_Thickness_plates;}
  G4double GetEFPlatesLength(){return EF_Length_plates;}
  G4double GetEFPlatesWidth(){return EF_Width_plates;}
  // MagneticField Plates
  G4double GetMFValue(){return MF_Value;}
  G4double GetMFDistBetweenPlates(){return MF_Dist_between_plates;}
  G4double GetMFPlatesThickness(){return MF_Thickness_plates;}
  G4double GetMFPlatesLength(){return MF_Length_plates;}
  G4double GetMFPlatesWidth(){return MF_Width_plates;}
  // Position of Plates
  G4double GetDistBetweenPlates(){return Dist_between_plates;}
  G4double GetEFPlatesDetector(){return Dist_EFPlates_Detector;}
  G4double GetPinholeMFPlates(){return Dist_pinhole_MFPlates;}
  G4double GetTranslationPinhole(){return translation_pinhole;}
  // Position of Detector
  G4double GetScintillatorThickness(){return ScintillatorThickness;}
  G4double GetZnSThickness(){return ZnSThickness;}


private:


  Geometry *theScint;
  ENLTPSimMaterials* scintProp;

  static const G4String path_bin;


  // Materials
  G4Material *Material;

  // Logical Volumes
  G4LogicalVolume *LogicalVolume;

  G4double ScintillatorLength;
  G4double ScintillatorThickness;
  G4double ZnSThickness;
  // Physical Dimensions
  // wrapping
  G4double AirGapTeflon;
  G4double TeflonThickness;
  G4double AirGapMylar;
  G4double MylarThickness;
  // glue
  G4double GlueThickness;

  //ElectricField Plates
  G4double EF_Value;
  G4double EF_Dist_between_plates;
  G4double EF_Thickness_plates;
  G4double EF_Length_plates;
  G4double EF_Width_plates;

  //MagneticField Plates
  G4double MF_Value;
  G4double MF_Dist_between_plates;
  G4double MF_Thickness_plates;
  G4double MF_Length_plates;
  G4double MF_Width_plates;

  //Pinhole
  G4double Pinhole_radius_ext;
  G4double Pinhole_radius_int;
  G4double Pinhole_thickness;

  //Position of Plates
  G4double Dist_between_plates;
  G4double Dist_EFPlates_Detector;
  G4double Dist_pinhole_MFPlates;
  G4double translation_pinhole;


  // Other
  G4VisAttributes *clear;

};
#endif
