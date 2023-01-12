#include"Deviation_Pierre.hh"

void Deviation_Pierre()
{

  float Dev_0_1[2] = Calcul_Deviation_and_Draw("Configuration_PAUL_TCC_7.5cm_x_0_y_0.1mm_0.1rad.root", "Deviation (0 ; 0.1) mm");
  float te[2] = Dev_Calcul_Deviation_and_Draw("Configuration_PAUL_TCC_7.5cm_x_0_y_0.2mm_0.1rad.root", "Deviation (0 ; 0.2) mm");
  float t[2] = Calcul_Deviation_and_Draw("Configuration_PAUL_TCC_7.5cm_x_0.2_y_0.2mm_0.1rad.root", "Deviation (0.2 ; 0.2) mm");
  
}
