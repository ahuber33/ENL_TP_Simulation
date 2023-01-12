TCanvas* c;
TPad* pad1;
TPad* pad2;
TPad* pad3;
TPad* pad4;
TH2F* f;
TH2F* Ref_xy;
TH2F* Ref_Ex;
TH2F* Ref_Ey;
TH2F* h_xy;
TH2F* h_Ex;
TH2F* h_Ey;
TF1*fit;
TF1* fit_y = new TF1("fit_y", "gaus", -3, 3);
float out[2];


void Create_Pad_Canvas(const char* Canvasname)
{
  gStyle->SetOptTitle(kFALSE);
  c = new TCanvas(Canvasname, Canvasname, 0, 10, 1000, 1000);
  c->SetWindowPosition(600, 0);
  pad1 = new TPad("pad1", "", 0.0, 0.51, 0.49, 1);
  pad2 = new TPad("pad2", "", 0.51, 0.51, 1, 1);
  pad3 = new TPad("pad3", "", 0.0, 0., 0.49, 0.49);
  pad4 = new TPad("pad4", "", 0.51, 0., 1, 0.49);
  pad1->Draw();
  pad2->Draw();
  pad3->Draw();
  pad4->Draw();		      
}


TH2F* histo_PosXY(const char* filename, const char* name)
{
  cout << " Begin of " << name << endl;
  TFile* file = new TFile(filename);
  float x=0;
  float y=0;
  TTree *Tree = (TTree*)file->Get("TP");
  Tree->SetBranchAddress("PositionX", &x);
  Tree->SetBranchAddress("PositionY", &y);
  const int Entries = Tree->GetEntries();

  f = new TH2F(name, name, 600, -20, 40, 200, -10, 10);

  for (int i=0; i<Entries; i++)
  {
    Tree->GetEntry(i);
    f->Fill(x, y); 
  }

  cout << " End of " << name << endl;

  return f;
  
}



TH2F* histo_EstartPosX(const char* filename, const char* name)
{
  cout << " Begin of " << name << endl;
  TFile* file = new TFile(filename);
  float x=0;
  float y=0;
  TTree *Tree = (TTree*)file->Get("TP");
  Tree->SetBranchAddress("PositionX", &x);
  Tree->SetBranchAddress("E_start", &y);
  const int Entries = Tree->GetEntries();

  f = new TH2F(name, name, 600, -20, 40, 120, 0, 12000);

  for (int i=0; i<Entries; i++)
  {
    Tree->GetEntry(i);
    f->Fill(x, y); 
  }

  cout << " End of " << name << endl;

  return f;
  
}



TH2F* histo_EstartPosY(const char* filename, const char* name)
{
  cout << " Begin of " << name << endl;
  TFile* file = new TFile(filename);
  float x=0;
  float y=0;
  TTree *Tree = (TTree*)file->Get("TP");
  Tree->SetBranchAddress("PositionY", &x);
  Tree->SetBranchAddress("E_start", &y);
  const int Entries = Tree->GetEntries();

  f = new TH2F(name, name, 200, -10, 10, 120, 0, 12000);

  for (int i=0; i<Entries; i++)
  {
    Tree->GetEntry(i);
    f->Fill(x, y); 
  }

  cout << " End of " << name << endl;

  return f;
  
}


TGraphErrors* Graph_Y(TH2F* f, int bin_start, int bin_end)
{
  cout << " Begin of Graph" << endl;
  int n=0;
  float X[120], Y[120], eX[120], eY[120];
  TH1D* proj = new TH1D("proj", "proj", 120, 0, 12000);
  proj->Reset();
  
  for (int i=bin_start; i<=bin_end; i++)
    {
      //cout << "i = " << i << endl;
      f->ProjectionX("proj", i, i, "");
      proj->Fit(fit_y, "RQ");
      X[n] = i*100;
      eX[n] = 100;
      Y[n] = fit_y->GetParameter(1);
      eY[n] = fit_y->GetParameter(2);
      proj->Reset();
      n++;
    }
  
  TGraphErrors* g = new TGraphErrors(n , X, Y, eX, eY);

  proj->Delete();
  
  cout << " End of Graph" << endl;

  return g;

}



void Calcul_Deviation_and_Draw(const char* filename, const char* name)
{
  Create_Pad_Canvas(name);
  pad1->cd();
  Ref_xy = histo_PosXY("Configuration_PAUL_TCC_7.5cm_x_0_y_0_0.1rad.root", "PosXY_1");
  h_xy = histo_PosXY(filename, "PosXY_2");
  Ref_xy->Draw("");
  h_xy->SetMarkerColor(kRed);
  h_xy->Draw("same");
  TLatex *l1 = new TLatex(-10, 8, "Reference (0 ; 0)");
  l1->Draw();
  l1->SetTextSize(0.05);
  l1->SetTextColor(kBlack);
  TLatex *l2 = new TLatex(-10, 6, name);
  l2->Draw();
  l2->SetTextSize(0.05);
  l2->SetTextColor(kRed);

  
  pad2->cd();
  Ref_Ex = histo_EstartPosX("Configuration_PAUL_TCC_7.5cm_x_0_y_0_0.1rad.root", "Estart:PosX_1");
  h_Ex = histo_EstartPosX(filename, "Estart:PosX_2");
  h_Ex->SetMarkerColor(kRed);
  Ref_Ex->Draw("");
  h_Ex->Draw("same");
  TLatex *l3 = new TLatex(4, 7000, "Reference (0 ; 0)");
  l3->Draw();
  l3->SetTextSize(0.05);
  l3->SetTextColor(kBlack);
  TLatex *l4 = new TLatex(4, 5000, name);
  l4->Draw();
  l4->SetTextSize(0.05);
  l4->SetTextColor(kRed);
  
  pad3->cd();
  Ref_Ey = histo_EstartPosY("Configuration_PAUL_TCC_7.5cm_x_0_y_0_0.1rad.root", "Estart:PosY_1");
  h_Ey = histo_EstartPosY(filename, "Estart:PosY_2");
  h_Ey->SetMarkerColor(kRed);
  Ref_Ey->Draw("");
  h_Ey->Draw("same");
  TLatex *l5 = new TLatex(-8, 11500, "Reference (0 ; 0)");
  l5->Draw();
  l5->SetTextSize(0.05);
  l5->SetTextColor(kBlack);
  TLatex *l6 = new TLatex(-8, 10500, name);
  l6->Draw();
  l6->SetTextSize(0.05);
  l6->SetTextColor(kRed);

  pad4->cd();
  TMultiGraph* mg = new TMultiGraph();
  TGraphErrors* test = Graph_Y(Ref_Ey, 11, 100);
  test->SetLineColor(kBlack);
  test->SetFillColor(kBlack);
  test->SetFillStyle(3001);
  TGraphErrors* test1 = Graph_Y(h_Ey, 11, 100);
  test1->SetLineColor(kRed);
  test1->SetFillColor(kRed);
  test1->SetFillStyle(3002);
  mg->Add(test);
  mg->Add(test1);
  mg->Draw("AL3");

  float a,b,c,d = 0;
  float da,db,dc,dd = 0;
  float n=1;
  for (int i=0; i<test->GetN(); i++)
    {
      a+= test->GetPointY(i);
      da+= test->GetErrorY(i);
      b+= test1->GetPointY(i);
      db+= test1->GetErrorY(i);
      c = abs(a-b)/n;
      dc = abs(da+db)/n;
      cout << " Diff = " << c << " +- " << dc << endl;
      n++;
    }


  out[2] = {c, dc};
  

  
}
