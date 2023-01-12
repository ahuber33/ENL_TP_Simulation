#include <iostream>
#include <string>
#include <fstream>
#include "Calcul_deviation.hh"

using namespace std;

float deviation_B(float m, float B, float Le1, float Le2, float Lb1, float Lb2, float En)
{
  float x;
  double alpha;
  //  float D = Le1+Le2+Lb1+Lb2;
  float D = Lb1+Lb2;

  //Definition of parameters
  float c = 2.99792e08;
  float q = 1.602e-19;

  //Preliminary calculs
  float mrepos = ((m*c*c)/q)/1000; // en keV
  cout << "mrepos = " << mrepos << endl;
  double beta = sqrt(1-pow(mrepos/(En+mrepos),2));
  double gamma = 1/(sqrt(1-beta*beta));
  cout << "beta = " << beta << endl;
  cout << "gamma = " << gamma << endl;

  alpha = q/(gamma*m*beta*c);

  x = alpha*B*((Lb1*Lb1)/2 + Lb1*Lb2)*1000;
  //x = alpha*B*((Lb1*Lb1)/2)*1000;
  cout << "Deviation B = " << x << " mm" << endl;

  return x;
}

float deviation_E(float m, float E, float Le1, float Le2, float Lb1, float Lb2, float En)
{
  float x;
  float alpha;
  //float D = Le1+Le2+Lb1+Lb2;
  float D = Lb1+Lb2;

  //Definition of parameters
  float c = 2.99792e08;
  float q = 1.602e-19;

  //Preliminary calculs
  float mrepos = ((m*c*c)/q)/1000; // en keV
  //cout << "mrepos = " << mrepos << endl;
  float beta = sqrt(1-pow(mrepos/(En+mrepos),2));
  double gamma = 1/(sqrt(1-beta*beta));
  //  cout << "beta = " << beta << endl;

  //  cout << "D = " << D << endl;
  //if(beta>0.01){D = sqrt(D*D*(1-beta*beta));}
  //  cout << "D new = " << D << endl;

  alpha = q/(gamma*m*beta*c);

  x = alpha*alpha*E*(m/q)*((Le1*Le1)/2 + Le1*Le2) *1000;

  cout << "Deviation E = " << x << " m" << endl;

  return x;
}

void Calcul_deviation()
{
  float x;

  //Definition of parameters
  float me = 9.1094e-31; //kg
  float mp = 1.672e-27;

  //Defintion of variables
  float B = 0.6; //Tesla
  float E = 0.E6; // V/m
  float Le1 = 0.;
  float Le2 =0.;
  float Lb1 = 0.0508;
  float Lb2 = 0.;
  float D=0.25;
  float E_start = 5000; //keV
  float E_end = 100000; //keV


  // TFile* file = new TFile("a.root");
  // float a,c,d;
  // TTree *Tree = (TTree*)file->Get("TP");
  // float Entries = Tree->GetEntries();
  // // TH1F* histo_E = new TH1F("histo_B","histo_B", 10001, 0, 10000);
  //TH1F* histo_B = new TH1F("histo_B","histo_B", 10001, 0, 10000);
  TH2F* h = Deviation("a.root");
  TH2F* gg = Deviation("champ_reel_fuite.root");
  //ofstream fichier("champ_infini_largeur.txt");

  // for (int i=0; i<Entries; i++)
  //   {
  //     Tree->GetEntry(i);
  //     a = Tree->GetLeaf("E_start")->GetValue();
  //     c = Tree->GetLeaf("PositionX")->GetValue();
  // //     d = Tree->GetLeaf("PositionY")->GetValue();
  //     h->Fill(c-15.4,a/1000);
  // //     histo_B->SetBinContent(a, c);
  // //     histo_E->SetBinContent(a, d);
  //     // if(a >2000)
  //     // 	{
  //     // 	  fichier << a/1000 << "\t" <<  c << endl;
  //     // 	}

  //   }

  //file->Close();
  //  file->Delete();

  int n=0;
  TGraph* g_E = new TGraph();
  TGraph* g_B = new TGraph();
  TGraph* g = new TGraph();
  TGraph* g_err_E = new TGraph();
  TGraph* g_err_B = new TGraph();
  float Dist[20] = {180.1, 114.7, 89.72, 74.33, 63.46, 55.19, 48.61, 43.26, 38.84, 35.13, 32, 29.32, 27.03, 25.06, 23.33, 21.82, 20.49, 19.3, 18.25, 17.3};
  float Energie[20] = {1., 6, 11, 16, 21, 26, 31, 36, 41, 46, 51, 56, 61, 66, 71, 76, 81, 86, 91, 96};

  TGraph* GPT = new TGraph(20, Dist, Energie);


  for (float i=E_start; i<E_end; i+=1000)
    {
      cout << "E = " << i << endl;
      x = deviation_B(me, B, Le1, Le2, Lb1, Lb2, i);
      g_B->SetPoint(n, x, i/1000);


      //g_err_B->SetPoint(n, i, (g_B->Eval(i) - histo_B->Interpolate(i)));

      x = deviation_E(me, E, Le1, Le2, Lb1, Lb2, i);
      g_E->SetPoint(n, i, x);
      //      g_err_E->SetPoint(n, i, (g_E->Eval(i) - histo_E->Interpolate(i)));
      n++;
    }

  //cout << deviation_E(mp, E, D, 200) << endl;


  new TCanvas;
  //histo_E->Draw("L");
  //histo_E->SetLineColor(kRed);
  h->Draw("");
  gg->Draw("same");
  gg->SetMarkerColor(kRed);
  GPT->Draw("same");
  GPT->SetLineColor(kBlue);
  // g_B->Draw("same");
  // g_B->SetLineColor(kCyan);
  // g_B->SetMarkerColor(kCyan);








}
