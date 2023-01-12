#ifndef BMAP_HH
#define BMAP_HH

#include "TFile.h"
#include "TROOT.h"
#include "TH2F.h"
#include "TH3F.h"
class BMap
{
private:
  BMap() {
    //TFile *file = new TFile("/home/local1/Optical_Simulation_Arnaud/simulation_input_files/Scan.root");
    TFile *file = new TFile("/mnt/hgfs/shared/Simulations/ENL_TP_Simulation/simulation_input_files/BMap.root", "READ");
    //Map = (TH2F*) file->Get("Scan");
    Map = (TH3F*) file->Get("zzz");
    gROOT->cd() ;
  }

  ~BMap();

  TH3F *Map;

public:
  static BMap *Instance;

  static BMap *GetInstance() {
    if (Instance == NULL) Instance = new BMap;
    return Instance;}

  //double Interpolate(double x, double y) {
  //return Map->Interpolate(x, y);}

  double Interpolate(double x, double y, double z) {
  return Map->Interpolate(x, y, z);}

  // double Interpolate(double x, double y, double z) {
  //   int binX = ((x+150)/5) +1;
  //   int binY = ((y+150)/5) +1;
  //   int binZ = ((z)/5) +1;

  //   return Map->GetBinContent(binX, binY, binZ);}


};


BMap *BMap::Instance = NULL;


#endif
