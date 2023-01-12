#include <iostream>
#include <string>
#include <fstream>

void MapFieldCreation()
{
ifstream file("../simulation_input_files/Bmap_test.txt");

float a,b;

TH1F *zg = new TH1F("z","z", 798, -200, 199.5);
TH2F *xz = new TH2F("xz","xz", 512, -25.6, 25.6, 798, -200, 199.5);
TGraph2D *test = new TGraph2D(408000);
TH3F *zzz = new TH3F("zzz","zzz", 513, -25.6, 25.6, 157, -7.75, 7.75, 800, -200, 199.5);

int n=0;
float x, y, z =0;
for (int i =0; i < 800; i++)
{
  file >> a >> b;
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  for (int j =0; j<513; j++)
  {
    for (int k=0; k<157; k++)
    {
      zzz->SetBinContent(j, k, i, b);
      x = -25.4 +0.1*j;
      z = -200 +0.5*i;
      //cout << " z = " << z << endl;
      xz->SetBinContent(j, i, b);
      //test->SetPoint(n, x, z, b);
      n++;
    }
  }
}


xz->Draw("colz");
//new TCanvas;
//test->Draw("surf1");
//zzz->Draw("BOX2Z");

cout << zzz->Interpolate(0, 0, 100) << endl;

TFile *filename = new TFile("BMap.root", "recreate");
zzz->Write();
filename->Close();
}
