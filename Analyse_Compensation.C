#include "Analyse_Compensation.hh"

void Analyse_Compensation()
{
  float E[15] = {12, 16, 20, 24, 33, 48, 65, 83, 100, 118, 164, 208, 250, 662, 1250};

  float Rep_relative[15] = {0.49, 0.591, 1.045, 0.902, 0.935, 0.947, 1.044, 1.269, 1.369, 1.316, 1.073, 0.932, 0.862, 1.00, 1.251};

  TGraph *SCK_Cen = new TGraph (15, E, Rep_relative);


  string Path = "/p2r301b/Arnaud/Dolphy_Beta/Resultats/DOLPHY_Beta_Config_SCK-Cen/Dolphy_Beta_anode_Config_SCK-Cen_fenetre_normale_";
  //string Path2 = "/p2r301b/Arnaud/Dolphy_Beta/Resultats/Dolphy_Beta_anode_Config_SCK-Cen_Test_";
  //string Path2 = "/p2r301b/Arnaud/Dolphy_Beta/Resultats/DOLPHY_Beta_SnSb_1.5cm_Nylon_1.5cm_rayon_1.4cm/Dolphy_Beta_";
  //string Path2 = "/p2r301b/Arnaud/Dolphy_Beta/Resultats/DOLPHY_Beta_SnSb_1.5cm_Nylon_1.5cm_rayon_1.6cm/Dolphy_Beta_";
  //string Path2 = "/p2r301b/Arnaud/Dolphy_Beta/Resultats/DOLPHY_Beta_SnSb_1.5cm_Nylon_1.5cm_rayon_1.5cm/Dolphy_Beta_";
  string Path2 = "/p2r301b/Arnaud/Dolphy_Beta/Resultats/DOLPHY_Beta_PbSb_1.5cm_Nylon_1.5cm_rayon_1.5cm/Dolphy_Beta_";

  TGraphErrors *Simu = Reponse_Relative(Path);  
  //TGraphErrors *Simu2 = Reponse_Relative_new(Path2);  
  TGraphErrors *Simu2 = Reponse_Relative_short(Path2);  
  float E_norme[2] = {0, 1300};
  float Norme_sup[2] = {1.67, 1.67};
  float Norme_low[2] = {0.71, 0.71};
  TGraph *Borne_sup = new TGraph(2, E_norme, Norme_sup);
  TGraph *Borne_low = new TGraph(2, E_norme, Norme_low);

  TCanvas* c1 = new TCanvas("Simu only","Simu only");
  Simu->Draw();
  Simu->SetLineColor(kBlue);
  Simu->SetLineWidth(2);
  Simu2->Draw("same");
  Simu2->SetLineColor(kCyan);
  Simu2->SetLineWidth(2);
  Borne_sup->Draw("same");
  Borne_low->Draw("same");
  Borne_sup->SetLineColor(kRed);
  Borne_low->SetLineColor(kRed);
  Simu->GetYaxis()->SetRangeUser(0.01, 2);
  Borne_sup->SetLineWidth(2);
  Borne_low->SetLineWidth(2);
  SCK_Cen->Draw("same");
  SCK_Cen->SetLineColor(kOrange);
  SCK_Cen->SetLineWidth(3);
  TLegend *leg2 = new TLegend(0.72,0.65,0.9,0.9);
  leg2->AddEntry(SCK_Cen,"Exp. SCK-Cen","lp");
  leg2->AddEntry(Simu,"Simu. SCK-Cen","lp");
  leg2->AddEntry(Simu2,"Nouv. compensation (1.5cm SnSb)","lp");
  leg2->Draw();



  // TCanvas* c2 = new TCanvas("Influence_Seuil AmBe", "Influence_Seuil AmBe");
  // c2->SetLogx();
  // c2->SetLogy();
  // Seuil_1_AmBe->Draw();
  // Seuil_1_AmBe->SetLineColor(kBlack);
  // Seuil_1_AmBe->SetLineWidth(2);
  // Seuil_1_AmBe->GetXaxis()->SetLimits(pow(10, -8), 20);
  // Seuil_1_AmBe->GetYaxis()->SetRangeUser(0.01, 100);
  // Seuil_2_AmBe->Draw("same");
  // Seuil_2_AmBe->SetLineColor(kBlue);
  // Seuil_2_AmBe->SetLineWidth(2);
  // Seuil_3_AmBe->Draw("same");
  // Seuil_3_AmBe->SetLineColor(kRed);
  // Seuil_3_AmBe->SetLineWidth(2);
  // Borne_sup->Draw("same");
  // Borne_sup->SetLineColor(kCyan);
  // Borne_sup->SetLineWidth(3);
  // Borne_low->Draw("same");
  // Borne_low->SetLineColor(kCyan);
  // Borne_low->SetLineWidth(3);

  // TLegend *leg2 = new TLegend(0.72,0.65,0.9,0.9);
  // leg2->AddEntry(Seuil_1_AmBe,"Seuil 100 keV","lp");
  // leg2->AddEntry(Seuil_2_AmBe,"Seuil 500 keV","lp");
  // leg2->AddEntry(Seuil_3_AmBe,"Seuil 800 keV","lp");
  // leg2->Draw();


}
