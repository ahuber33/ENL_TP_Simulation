float deviation_B(float m, float q, float B, float Lb1, float Lb2, float En)
{
  float x;
  float alpha;

  //Definition of parameters
  float c = 3e08;

  //Preliminary calculs
  float mrepos = ((m*c*c)/q)/1000; // en keV
  //cout << "mrepos = " << mrepos << endl;
  float beta = sqrt(1-pow(mrepos/(En+mrepos),2));
  //  cout << "beta = " << beta << endl;

  Lb1 = Lb1*sqrt(1-beta*beta);
  Lb2 = Lb2*sqrt(1-beta*beta);

  float gamma = 1/(sqrt(1-beta*beta));
  //cout << "gamma = " << gamma << endl;

  alpha = q/(m*beta*c);

  x = alpha*gamma*B*((Lb1*Lb1)/2 + Lb1*Lb2) *1000;
  //cout << "x = " << x << " m" << endl;

  return x;
}



void Deviation()
{

  float mp = 1.6726e-27; //kg
  float me = 9.1094e-31; //kg
  float mHe = 4.0026*1.66054e-27;
  float qp = 1.6e-19; //C
  float qe = 1.6e-19; //C
  float pinhole =0.1;
  float B = 0.6; //T
  float E = 0; //V/m
  float Le1 = 0.; //m
  float Le2 = 0.; //m
  float D = 5e-3; //m
  float Lb1 = 0.0508; //m
  float Lb2 = 0.1573; //m
  float E_start = 10000; //keV
  float E_end = 100000; //keV


 
  TFile* file = new TFile("a.root");
  float En,x,y;
  int bin;
  TTree *Tree = (TTree*)file->Get("TP");
  Tree->SetBranchAddress("E_start", &En);
  Tree->SetBranchAddress("PositionX", &x);
  Tree->SetBranchAddress("PositionY", &y);
  float Entries = Tree->GetEntries();
  TH1F* h = new TH1F("histo_B","histo_B", 10000, 0, 100000);
  //TH2F* h = new TH2F("h","h", 1000, 10000, 100000, 4000, 0, 400);


  for (int i=0; i<Entries; i++)
    {
      Tree->GetEntry(i);
      //h->Fill(En,x+20);
      h->SetBinContent(En/10, x+20);
    }


  int n=0;
  TGraph* g_B = new TGraph();
  TGraph* g_err_B = new TGraph();
  
  for (int i=E_start; i<E_end; i+=10)
    {
      x = deviation_B(me, qe, B, Lb1, Lb2, i); 
      g_B->SetPoint(n, i, x);
      g_err_B->SetPoint(n, i, (g_B->Eval(i) - h->Interpolate(i)));

      n++;
    }

  new TCanvas;
  h->Draw("L");
  h->SetLineColor(kRed);
  g_B->Draw("same");
  g_B->SetLineColor(kCyan);
  g_B->SetMarkerColor(kCyan);

  new TCanvas;
  g_err_B->Draw();


  
}
