int Compteur(string file)
{
  TFile* f = new TFile(file.c_str());

  float E_dep=0;
  //float Compteur=0;

  TTree *Tree = (TTree*)f->Get("Tree_sphere");
  Tree->SetBranchAddress("E_dep_Electron", &E_dep);

  int Entries = Tree->GetEntries();
  //cout << "Entries = " << Entries << endl;

  cout << "Compteur[" << file<< "] = " << Entries << endl;

  return Entries;

}


TGraphErrors *Reponse_Relative(string path)
{
  float DED = 100.;

  string Chemin = path + string("Cs137_100µSv.root");
  float Cpt = Compteur(Chemin);
  float Cs137 = Cpt / DED;
  cout << "Sensibilité [Cs137] = " << Cs137 << " cps/µSv/h" << endl;
  float E_Cs137 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));


  string Chemin = path + string("Co60_100µSv.root");
  Cpt = Compteur(Chemin);
  float Co60 = Cpt / DED;
  float E_Co60 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));


  string Chemin = path + string("N-300_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_300 = Cpt / DED;
  float E_N_300 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-250_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_250 = Cpt / DED;
  float E_N_250 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-200_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_200 = Cpt / DED;
  float E_N_200 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-150_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_150 = Cpt / DED;
  float E_N_150 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-120_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_120 = Cpt / DED;
  float E_N_120 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-100_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_100 = Cpt / DED;
  float E_N_100 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-80_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_80 = Cpt / DED;
  float E_N_80 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-60_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_60 = Cpt / DED;
  float E_N_60 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-40_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_40 = Cpt / DED;
  float E_N_40 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-30_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_30 = Cpt / DED;
  float E_N_30 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-25_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_25 = Cpt / DED;
  float E_N_25 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-20_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_20 = Cpt / DED;
  float E_N_20 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-15_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_15 = Cpt / DED;
  float E_N_15 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));




  float Rep_rel_Co60 = Co60 / Cs137;
  float E_Rep_rel_Co60 = sqrt(pow(E_Co60/Cs137, 2) + pow((E_Co60*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_Cs137 = Cs137 / Cs137;
  float E_Rep_rel_Cs137 = sqrt(pow(E_Cs137/Cs137, 2) + pow((E_Cs137*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N300 = N_300 / Cs137;
  float E_Rep_rel_N300 = sqrt(pow(E_N_300/Cs137, 2) + pow((E_N_300*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N250 = N_250 / Cs137;
  float E_Rep_rel_N250 = sqrt(pow(E_N_250/Cs137, 2) + pow((E_N_250*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N200 = N_200 / Cs137;
  float E_Rep_rel_N200 = sqrt(pow(E_N_200/Cs137, 2) + pow((E_N_200*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N150 = N_150 / Cs137;
  float E_Rep_rel_N150 = sqrt(pow(E_N_150/Cs137, 2) + pow((E_N_150*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N120 = N_120 / Cs137;
  float E_Rep_rel_N120 = sqrt(pow(E_N_120/Cs137, 2) + pow((E_N_120*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N100 = N_100 / Cs137;
  float E_Rep_rel_N100 = sqrt(pow(E_N_100/Cs137, 2) + pow((E_N_100*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N80 = N_80 / Cs137;
  float E_Rep_rel_N80 = sqrt(pow(E_N_80/Cs137, 2) + pow((E_N_80*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N60 = N_60 / Cs137;
  float E_Rep_rel_N60 = sqrt(pow(E_N_60/Cs137, 2) + pow((E_N_60*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N40 = N_40 / Cs137;
  float E_Rep_rel_N40 = sqrt(pow(E_N_40/Cs137, 2) + pow((E_N_40*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N30 = N_30 / Cs137;
  float E_Rep_rel_N30 = sqrt(pow(E_N_30/Cs137, 2) + pow((E_N_30*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N25 = N_25 / Cs137;
  float E_Rep_rel_N25 = sqrt(pow(E_N_25/Cs137, 2) + pow((E_N_25*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N20 = N_20 / Cs137;
  float E_Rep_rel_N20 = sqrt(pow(E_N_20/Cs137, 2) + pow((E_N_20*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N15 = N_15 / Cs137;
  float E_Rep_rel_N15 = sqrt(pow(E_N_15/Cs137, 2) + pow((E_N_15*E_Cs137)/(Cs137*Cs137), 2));



  float E[15] = {12, 16, 20, 24, 33, 48, 65, 83, 100, 118, 164, 208, 250, 662, 1250};
  float Err_E[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


  float Rep_relative[15] = {Rep_rel_N15, Rep_rel_N20, Rep_rel_N25, Rep_rel_N30, Rep_rel_N40, Rep_rel_N60, Rep_rel_N80, Rep_rel_N100, Rep_rel_N120, Rep_rel_N150, Rep_rel_N200, Rep_rel_N250, Rep_rel_N300, Rep_rel_Cs137, Rep_rel_Co60};

  float E_Rep_relative[15] = {E_Rep_rel_N15, E_Rep_rel_N20, E_Rep_rel_N25, E_Rep_rel_N30, E_Rep_rel_N40, E_Rep_rel_N60, E_Rep_rel_N80, E_Rep_rel_N100, E_Rep_rel_N120, E_Rep_rel_N150, E_Rep_rel_N200, E_Rep_rel_N250, E_Rep_rel_N300, E_Rep_rel_Cs137, E_Rep_rel_Co60};



  TGraphErrors *g = new TGraphErrors (15, E, Rep_relative, Err_E, E_Rep_relative);

  return g;

    
}



TGraphErrors *Reponse_Relative_new(string path)
{
  float DED = 100.;

  string Chemin = path + string("Cs137_1000µSv.root");
  float Cpt = Compteur(Chemin);
  float Cs137 = Cpt / 1000;
  cout << "Sensibilité [Cs137] = " << Cs137 << " cps/µSv/h" << endl;
  float E_Cs137 = sqrt( (pow(sqrt(Cpt)/1000, 2)) + pow((Cpt*0.05*1000)/(1000*1000), 2));


  string Chemin = path + string("Co60_100µSv.root");
  Cpt = Compteur(Chemin);
  float Co60 = Cpt / DED;
  float E_Co60 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));


  string Chemin = path + string("N-300_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_300 = Cpt / DED;
  float E_N_300 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-250_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_250 = Cpt / DED;
  float E_N_250 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-200_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_200 = Cpt / DED;
  float E_N_200 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-150_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_150 = Cpt / DED;
  float E_N_150 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-120_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_120 = Cpt / DED;
  float E_N_120 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-100_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_100 = Cpt / DED;
  float E_N_100 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-80_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_80 = Cpt / DED;
  float E_N_80 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-60_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_60 = Cpt / DED;
  float E_N_60 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-40_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_40 = Cpt / DED;
  float E_N_40 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-30_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_30 = Cpt / DED;
  float E_N_30 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-25_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_25 = Cpt / DED;
  float E_N_25 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-20_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_20 = Cpt / DED;
  float E_N_20 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-15_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_15 = Cpt / DED;
  float E_N_15 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));




  float Rep_rel_Co60 = Co60 / Cs137;
  float E_Rep_rel_Co60 = sqrt(pow(E_Co60/Cs137, 2) + pow((E_Co60*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_Cs137 = Cs137 / Cs137;
  float E_Rep_rel_Cs137 = sqrt(pow(E_Cs137/Cs137, 2) + pow((E_Cs137*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N300 = N_300 / Cs137;
  float E_Rep_rel_N300 = sqrt(pow(E_N_300/Cs137, 2) + pow((E_N_300*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N250 = N_250 / Cs137;
  float E_Rep_rel_N250 = sqrt(pow(E_N_250/Cs137, 2) + pow((E_N_250*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N200 = N_200 / Cs137;
  float E_Rep_rel_N200 = sqrt(pow(E_N_200/Cs137, 2) + pow((E_N_200*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N150 = N_150 / Cs137;
  float E_Rep_rel_N150 = sqrt(pow(E_N_150/Cs137, 2) + pow((E_N_150*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N120 = N_120 / Cs137;
  float E_Rep_rel_N120 = sqrt(pow(E_N_120/Cs137, 2) + pow((E_N_120*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N100 = N_100 / Cs137;
  float E_Rep_rel_N100 = sqrt(pow(E_N_100/Cs137, 2) + pow((E_N_100*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N80 = N_80 / Cs137;
  float E_Rep_rel_N80 = sqrt(pow(E_N_80/Cs137, 2) + pow((E_N_80*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N60 = N_60 / Cs137;
  float E_Rep_rel_N60 = sqrt(pow(E_N_60/Cs137, 2) + pow((E_N_60*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N40 = N_40 / Cs137;
  float E_Rep_rel_N40 = sqrt(pow(E_N_40/Cs137, 2) + pow((E_N_40*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N30 = N_30 / Cs137;
  float E_Rep_rel_N30 = sqrt(pow(E_N_30/Cs137, 2) + pow((E_N_30*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N25 = N_25 / Cs137;
  float E_Rep_rel_N25 = sqrt(pow(E_N_25/Cs137, 2) + pow((E_N_25*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N20 = N_20 / Cs137;
  float E_Rep_rel_N20 = sqrt(pow(E_N_20/Cs137, 2) + pow((E_N_20*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N15 = N_15 / Cs137;
  float E_Rep_rel_N15 = sqrt(pow(E_N_15/Cs137, 2) + pow((E_N_15*E_Cs137)/(Cs137*Cs137), 2));



  float E[15] = {12, 16, 20, 24, 33, 48, 65, 83, 100, 118, 164, 208, 250, 662, 1250};
  float Err_E[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


  float Rep_relative[15] = {Rep_rel_N15, Rep_rel_N20, Rep_rel_N25, Rep_rel_N30, Rep_rel_N40, Rep_rel_N60, Rep_rel_N80, Rep_rel_N100, Rep_rel_N120, Rep_rel_N150, Rep_rel_N200, Rep_rel_N250, Rep_rel_N300, Rep_rel_Cs137, Rep_rel_Co60};

  float E_Rep_relative[15] = {E_Rep_rel_N15, E_Rep_rel_N20, E_Rep_rel_N25, E_Rep_rel_N30, E_Rep_rel_N40, E_Rep_rel_N60, E_Rep_rel_N80, E_Rep_rel_N100, E_Rep_rel_N120, E_Rep_rel_N150, E_Rep_rel_N200, E_Rep_rel_N250, E_Rep_rel_N300, E_Rep_rel_Cs137, E_Rep_rel_Co60};



  TGraphErrors *g = new TGraphErrors (15, E, Rep_relative, Err_E, E_Rep_relative);

  return g;

    
}




TGraphErrors *Reponse_Relative_short(string path)
{
  float DED = 100.;

  string Chemin = path + string("Cs137_1000µSv.root");
  float Cpt = Compteur(Chemin);
  float Cs137 = Cpt / 1000;
  cout << "Sensibilité [Cs137] = " << Cs137 << " cps/µSv/h" << endl;
  float E_Cs137 = sqrt( (pow(sqrt(Cpt)/1000, 2)) + pow((Cpt*0.05*1000)/(1000*1000), 2));


  string Chemin = path + string("Co60_100µSv.root");
  Cpt = Compteur(Chemin);
  float Co60 = Cpt / DED;
  float E_Co60 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));


  string Chemin = path + string("N-300_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_300 = Cpt / DED;
  float E_N_300 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-250_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_250 = Cpt / DED;
  float E_N_250 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-200_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_200 = Cpt / DED;
  float E_N_200 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-150_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_150 = Cpt / DED;
  float E_N_150 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-120_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_120 = Cpt / DED;
  float E_N_120 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-100_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_100 = Cpt / DED;
  float E_N_100 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-80_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_80 = Cpt / DED;
  float E_N_80 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-60_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_60 = Cpt / DED;
  float E_N_60 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));

  string Chemin = path + string("N-40_100µSv.root");
  Cpt = Compteur(Chemin);
  float N_40 = Cpt / DED;
  float E_N_40 = sqrt( (pow(sqrt(Cpt)/DED, 2)) + pow((Cpt*0.05*DED)/(DED*DED), 2));





  float Rep_rel_Co60 = Co60 / Cs137;
  float E_Rep_rel_Co60 = sqrt(pow(E_Co60/Cs137, 2) + pow((E_Co60*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_Cs137 = Cs137 / Cs137;
  float E_Rep_rel_Cs137 = sqrt(pow(E_Cs137/Cs137, 2) + pow((E_Cs137*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N300 = N_300 / Cs137;
  float E_Rep_rel_N300 = sqrt(pow(E_N_300/Cs137, 2) + pow((E_N_300*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N250 = N_250 / Cs137;
  float E_Rep_rel_N250 = sqrt(pow(E_N_250/Cs137, 2) + pow((E_N_250*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N200 = N_200 / Cs137;
  float E_Rep_rel_N200 = sqrt(pow(E_N_200/Cs137, 2) + pow((E_N_200*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N150 = N_150 / Cs137;
  float E_Rep_rel_N150 = sqrt(pow(E_N_150/Cs137, 2) + pow((E_N_150*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N120 = N_120 / Cs137;
  float E_Rep_rel_N120 = sqrt(pow(E_N_120/Cs137, 2) + pow((E_N_120*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N100 = N_100 / Cs137;
  float E_Rep_rel_N100 = sqrt(pow(E_N_100/Cs137, 2) + pow((E_N_100*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N80 = N_80 / Cs137;
  float E_Rep_rel_N80 = sqrt(pow(E_N_80/Cs137, 2) + pow((E_N_80*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N60 = N_60 / Cs137;
  float E_Rep_rel_N60 = sqrt(pow(E_N_60/Cs137, 2) + pow((E_N_60*E_Cs137)/(Cs137*Cs137), 2));

  float Rep_rel_N40 = N_40 / Cs137;
  float E_Rep_rel_N40 = sqrt(pow(E_N_40/Cs137, 2) + pow((E_N_40*E_Cs137)/(Cs137*Cs137), 2));




  float E[11] = {33, 48, 65, 83, 100, 118, 164, 208, 250, 662, 1250};
  float Err_E[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


  float Rep_relative[11] = {Rep_rel_N40, Rep_rel_N60, Rep_rel_N80, Rep_rel_N100, Rep_rel_N120, Rep_rel_N150, Rep_rel_N200, Rep_rel_N250, Rep_rel_N300, Rep_rel_Cs137, Rep_rel_Co60};

  float E_Rep_relative[11] = {E_Rep_rel_N40, E_Rep_rel_N60, E_Rep_rel_N80, E_Rep_rel_N100, E_Rep_rel_N120, E_Rep_rel_N150, E_Rep_rel_N200, E_Rep_rel_N250, E_Rep_rel_N300, E_Rep_rel_Cs137, E_Rep_rel_Co60};



  TGraphErrors *g = new TGraphErrors (11, E, Rep_relative, Err_E, E_Rep_relative);

  return g;

    
}




