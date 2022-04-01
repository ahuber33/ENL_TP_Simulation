/// TPSimMaterials.cc
/// Auteur: Arnaud HUBER <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "TPSimMaterials.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4MaterialPropertyVector.hh"
#include "G4NistManager.hh"
#include <fstream>
#include <iostream>
#include "G4UnitsTable.hh"
#include "G4ThreeVector.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4Scintillation.hh"

using namespace CLHEP;

const G4String TPSimMaterials::path = "../simulation_input_files/";

// Used to set up all material properties.  Some materials
// are left over from previous simulations and may not be
// needed.  Code to read in material properties from file
// is poorly done.  Can improve using vectors.  Careful of
// memory leaks.  Careful of files and how they are read in.

TPSimMaterials::TPSimMaterials(G4String prop_buildfile):bs_glass(0),
polysty(0),
Ti02(0),
coating(0),
scintillator(0),
Vacuum(0),
plastic(0),
mylar(0),
grease(0),
cargille(0),
PMMA(0)


{


	//G4cout << "Test" << G4endl;

	std::ifstream config_prop;
	config_prop.open(prop_buildfile);
	if (!config_prop.is_open())
	G4cout << "Error opening file " << prop_buildfile << G4endl;
	else{
		//G4cout << "Accessing the properties file. " << G4endl;

		while(!config_prop.eof()){
			G4String variable,unit;
			G4double value;

			config_prop >> variable;
			if(!config_prop.good()) break;
			if(variable == "scintIndexconst")
			{
				config_prop>>scintIndexconst;
			}
			if(variable == "scalingfactor_low")
			{
				config_prop>>scalingfactor_low;
			}
			if(variable == "scalingfactor_high")
			{
				config_prop>>scalingfactor_high;
			}
			if(variable == "pop_scalingfactor_low")
			{
				config_prop>>pop_scalingfactor_low;
			}
			if(variable == "pop_scalingfactor_high")
			{
				config_prop>>pop_scalingfactor_high;
			}
			if(variable == "lightyield")
			{
				config_prop>>lightyield;
			}
			if(variable == "lightyieldZnS")
			{
				config_prop>>lightyieldZnS;
			}
			if(variable == "paint_ref_coeff")
			{
				config_prop>>paint_ref_coeff;
			}
			if(variable == "mylar_ref_coeff")
			{
				config_prop>>mylar_ref_coeff;
			}
			else if(variable == "scintAbsorbconst")
			{
				config_prop >> value >> unit;
				scintAbsorbconst = value*G4UnitDefinition::GetValueOf(unit);
			}

		}
	}

	config_prop.close();
	Construct();


}

TPSimMaterials::~TPSimMaterials()
{
	if(scintillator) { delete scintillator; scintillator = 0; }
	if (Vacuum){ delete Vacuum; Vacuum = 0; }
	if (polysty){ delete polysty; polysty = 0; }
	if (coating){ delete coating; coating = 0; }
	if (Ti02){ delete Ti02; Ti02 = 0; }
	if (plastic){ delete plastic; plastic = 0; }
	if (mylar){ delete mylar; mylar = 0; }
	if (grease){ delete grease; grease = 0; }
	if (bs_glass){ delete bs_glass; bs_glass = 0; }
	if (PMMA){ delete PMMA; PMMA = 0;}
}


void TPSimMaterials::Construct()
{

	G4double R = 8.3144621; //(en J/K/mole => Constante gaz parfait)
	G4double T = 273.15; //en K

	//***********************
	// Define the Elements  *
	//***********************

	elementH = new G4Element( "Hydrogen", "H", 1, 1.00794*g/mole );
	elementC = new G4Element( "Carbon", "C", 6, 12.011*g/mole );
	elementCl = new G4Element( "Chlore", "Cl", 17, 35.453*g/mole );
	elementO = new G4Element( "Oxygen", "O", 8, 15.9994*g/mole );
	elementF = new G4Element ("Fluor", "F", 9., 18.9984032*g/mole);
	elementTi = new G4Element( "Titanium","Ti", 22, 47.88*g/mole);
	elementSi = new G4Element("Silicon","Si",14,28.0855*g/mole);
	elementB = new G4Element("Boron","B",5,10.811*g/mole);
	elementNa = new G4Element("Sodium","Na",11,22.989770*g/mole);
	elementAl = new G4Element("Aluminum","Al",13,26.981538*g/mole);
	elementFe = new G4Element ("Fer", "Fe", 26., 55.845*g/mole);
	elementNi = new G4Element ("Nickel", "Nickel", 28., 58.6939*g/mole);
	elementCr = new G4Element ("Chrome", "Chrome", 24., 51.9961*g/mole);
	elementMn = new G4Element ("Manganese", "Manganese", 25., 54.938044*g/mole);
	elementCu = new G4Element ("Cuivre", "Cuivre", 29., 63.546*g/mole);
	elementSn = new G4Element ("Etain", "Etain", 50., 118.71*g/mole);
	elementSb = new G4Element ("Antimoine", "Antimoine", 51., 121.760*g/mole);
	elementMg = new G4Element ("Magnesium", "Magnesium", 12., 24.305*g/mole);
	elementZn = new G4Element ("Zinc", "Zinc", 30., 65.38*g/mole);
	elementK = new G4Element ("Potassium", "Potassium", 19., 39.0983*g/mole);
	elementN = new G4Element ("Nitrogen", "N", 7., 14.01*g/mole);
	elementPb = new G4Element ("Plomb", "Plomb", 82., 207.2*g/mole);
	elementLa = new G4Element ("Lanthane", "Lanthane", 57., 138.90547*g/mole);
	elementBr = new G4Element ("Brome", "Brome", 35., 79.904*g/mole);
	elementS = new G4Element ("Soufre", "Soufre", 16., 32.065*g/mole);
	// G4Isotope* N14 = new G4Isotope("N14", 7, 14);
	// elementN = new G4Element("Azote", "Azote", 1);
	// elementN->AddIsotope(N14, 100.*perCent);


	//***********************
	// Build Materials      *
	//***********************

	// DiAzote
	G4double M_mole_N2 = 2*14; //en g/mole
	G4double Pression = 100000; //(en Pa => 1 bar = 100 000 Pa)
	N2 = new G4Material("Diazote", ((Pression * M_mole_N2)/(R*T))*g/m3, 1, kStateGas, T, (Pression*0.00000986923*atmosphere));
	N2->AddElement(elementN,2);

	//#######################################################################################################################################
	//#######################################################################################################################################

	H2O = new G4Material("Eau", 1.000*g/cm3, 2);
	H2O->AddElement(elementH, 2);
	H2O->AddElement(elementO, 1);

	//#######################################################################################################################################
	//#######################################################################################################################################

	Polypropylene = new G4Material("Polypropylene", 0.900*g/cm3, 2);
	Polypropylene->AddElement(elementC, 3);
	Polypropylene->AddElement(elementH, 6);

	//#######################################################################################################################################
	//#######################################################################################################################################

	Neoprene = new G4Material("Neoprene", 1.23*g/cm3, 3);
	Neoprene->AddElement(elementC, 4);
	Neoprene->AddElement(elementH, 5);
	Neoprene->AddElement(elementCl, 1);

	//#######################################################################################################################################
	//#######################################################################################################################################

	Papier = new G4Material("Papier", 1.2*g/cm3, 3);
	Papier->AddElement(elementC, 6);
	Papier->AddElement(elementH, 10);
	Papier->AddElement(elementO, 5);

	//#######################################################################################################################################
	//#######################################################################################################################################

	mylar = new G4Material("mylar", 1.40*g/cm3, 3);
	mylar->AddElement(elementH, 4);
	mylar->AddElement(elementC, 5);
	mylar->AddElement(elementO, 2);

	//#######################################################################################################################################
	//#######################################################################################################################################

	//Teflon
	teflon = new G4Material("teflon", 0.40*g/cm3, 4);
	teflon->AddElement(elementH, 6);
	teflon->AddElement(elementC, 2);
	teflon->AddElement(elementO, 1);
	teflon->AddElement(elementSi, 1);

	//#######################################################################################################################################
	//#######################################################################################################################################

	Alu = new G4Material("Alu", 2.6989*g/cm3, 1, kStateSolid);
	Alu->AddElement(elementAl, 1);

	//#######################################################################################################################################
	//#######################################################################################################################################

	Plomb_Antimoine = new G4Material("Plomb_Antimoine"  , 11.04*g/cm3, 2);
	Plomb_Antimoine->AddElement(elementPb, 0.96);
	Plomb_Antimoine->AddElement(elementSb, 0.04);

	//#######################################################################################################################################
	//#######################################################################################################################################

	plastic = new G4Material("plastic", 1.3*g/cm3, 2,	kStateSolid, 273.15*kelvin,	1.0*atmosphere );
	plastic->AddElement( elementH, 0.498 );
	plastic->AddElement( elementC, 0.502 );

	//#######################################################################################################################################
	//#######################################################################################################################################

	Nylon = new G4Material("Nylon", 1.4*g/cm3, 4);
	Nylon->AddElement( elementH, 22 );
	Nylon->AddElement( elementC, 12 );
	Nylon->AddElement( elementN, 2 );
	Nylon->AddElement( elementO, 2 );

	//#######################################################################################################################################
	//#######################################################################################################################################

	Compensation = new G4Material("Compensation", 7.25*g/cm3, 2);
	Compensation->AddElement(elementSn,0.95);
	Compensation->AddElement(elementSb,0.05);

	//#######################################################################################################################################
	//#######################################################################################################################################

	Kapton = new G4Material("Kapton", 1.413*g/cm3, 4);
	Kapton->AddElement(elementO,5);
	Kapton->AddElement(elementC,22);
	Kapton->AddElement(elementN,2);
	Kapton->AddElement(elementH,10);

	//#######################################################################################################################################
	//#######################################################################################################################################

	Acier = new G4Material("Acier", 7.86*g/cm3, 2);
	Acier->AddElement(elementFe, 0.99);
	Acier->AddElement(elementC, 0.01);

	//#######################################################################################################################################
	//#######################################################################################################################################

	Inox = new G4Material("Inox",8.06*g/cm3, 6);
	Inox->AddElement(elementC, 0.001);
	Inox->AddElement(elementSi, 0.007);
	Inox->AddElement(elementCr, 0.18);
	Inox->AddElement(elementMn, 0.01);
	Inox->AddElement(elementFe, 0.712);
	Inox->AddElement(elementNi, 0.09);

	//#######################################################################################################################################
	//#######################################################################################################################################

	Air = new G4Material("Air"  , 1.290*mg/cm3, 2);
	Air->AddElement(elementN, 0.7);
	Air->AddElement(elementO, 0.3);

	//#######################################################################################################################################
	//#######################################################################################################################################

	Fer = new G4Material("Fer"  , 7.87*g/cm3, 1);
	Fer->AddElement(elementFe, 1);

	//#######################################################################################################################################
	//#######################################################################################################################################

	Carbon = new G4Material("Carbon"  , 3.5*g/cm3, 1);
	Carbon->AddElement(elementC, 1);

	//#######################################################################################################################################
	//#######################################################################################################################################

	Cuivre = new G4Material("Cuivre"  , 8.96*g/cm3, 1);
	Cuivre->AddElement(elementCu, 1);

	//#######################################################################################################################################
	//#######################################################################################################################################

	mousse = new G4Material("mousse", 40*kg/m3, 4);
	mousse->AddElement(elementH, 6);
	mousse->AddElement(elementC, 2);
	mousse->AddElement(elementO, 1);
	mousse->AddElement(elementSi, 1);

	//#######################################################################################################################################
	//#######################################################################################################################################

	Mica = new G4Material("Mica", 1.75*g/cm3, 7);
	Mica->AddElement(elementO, 24);
	Mica->AddElement(elementH, 4);
	Mica->AddElement(elementAl, 2);
	Mica->AddElement(elementSi, 6);
	Mica->AddElement(elementMg, 6);
	Mica->AddElement(elementFe, 6);
	Mica->AddElement(elementK, 2);

	//#######################################################################################################################################
	//#######################################################################################################################################

	scintillator = new G4Material("scintillator",
	1.032*g/cm3, //1.053
	2,
	kStateSolid,
	273.15*kelvin,
	1.0*atmosphere );

	scintMPT = new G4MaterialPropertiesTable();

	scintillator->AddElement( elementH, 10);
	//scintillator->AddElement( elementH, 0.5 );
	scintillator->AddElement( elementC, 9);
	//scintillator->AddElement( elementC, 0.5 );

	G4double varabsorblength;
	G4double indexvalue;

	// Read primary emission spectrum

	std::ifstream ReadScint;

	G4String Scint_file = path+"EJ-212.cfg";
	std::vector<G4double> Sc_Emission_Energy;
	std::vector<G4double> Sc_Emission_Ratio;

	ReadScint.open(Scint_file);
	if(ReadScint.is_open()){
		while(!ReadScint.eof()){
			G4String filler;
			ReadScint >> pWavelength >> filler >> ratio;
			//G4cout << "Wavelength = " << 1240./pWavelength << " & emission = "<< ratio << G4endl;
			Sc_Emission_Energy.push_back((1240./pWavelength)*eV);         //convert wavelength to eV
			Sc_Emission_Ratio.push_back(ratio);
		}
	}
	else
	{
		G4cout << "Error opening file: " << Scint_file << G4endl;
	}
	ReadScint.close();

	// // Read primary bulk absorption

	std::ifstream Readabsorb;
	G4String Readabsorblength = path+"PSTBulkAbsorb_reverse.cfg";
	std::vector<G4double> Sc_Absorption_Energy;
	std::vector<G4double> Sc_Absorption_Long;

	Readabsorb.open(Readabsorblength);
	if (Readabsorb.is_open()){
		while(!Readabsorb.eof()){
			G4String filler;
			Readabsorb >> pWavelength >> filler >> varabsorblength;
			//G4cout << "Wavelength = " << pWavelength << " & absorption = "<< varabsorblength << G4endl;
			Sc_Absorption_Energy.push_back((1240./pWavelength)*eV);
			Sc_Absorption_Long.push_back(1.*varabsorblength*m);
		}
	}
	else

	G4cout << "Error opening file: "<< Readabsorblength << G4endl;

	Readabsorb.close();


	// Read WLS absorption
	//
	// wlsAbEntries = 0;
	// std::ifstream ReadWLSa;
	// G4String WLSabsorb = path+"UPS923.cfg";
	//
	// ReadWLSa.open(WLSabsorb);
	// if (ReadWLSa.is_open()){
	//  while(!ReadWLSa.eof()){
	// 	 G4String filler;
	// 	 ReadWLSa>>pWavelength>>filler>>wlsabsorblength;
	// 	 wlsEnergy[wlsAbEntries] = (1240/pWavelength)*eV;
	//
	//
	// 	 if (wlsAbEntries < 200){
	// wlsAbsorb[wlsAbEntries] = wlsabsorblength*m;
	// 	 }
	// 	 else{
	// wlsAbsorb[wlsAbEntries] = wlsabsorblength*m;
	// 	 }
	//
	// 	 wlsAbEntries++;
	//  }
	// }
	// else
	//  {
	// 	 G4cout << "Error opening file: " << WLSabsorb << G4endl;
	//  }
	//
	// ReadWLSa.close();


	// Read WLS emission
	// wlsEmEntries = 0;
	// std::ifstream ReadWLSe;
	// G4String WLSemit = path+"full_popop_emission.cfg";
	// ReadWLSe.open(WLSemit);
	// if(ReadWLSe.is_open()){
	//  while(!ReadWLSe.eof()){
	// 	 G4String filler;
	// 	 ReadWLSe >> pWavelength >> filler >> wlsEmit[wlsEmEntries];
	// 	 wlsEnergy[wlsEmEntries] = (1240/pWavelength)*eV;
	// 	 wlsEmEntries++;
	//  }
	// }
	// else
	//  G4cout << "Error opening file: " << WLSemit << G4endl;
	// ReadWLSe.close();

	// Read scintillator refractive index

	std::ifstream Read_ref_index;
	//G4String ref_index_emit = path+"PST_ref_index.dat";
	G4String ref_index_emit = path+"PS_index_geant_reverse.cfg";
	std::vector<G4double> Sc_Index_Energy;
	std::vector<G4double> Sc_Index_Value;

	Read_ref_index.open(ref_index_emit);
	if(Read_ref_index.is_open()){
		while(!Read_ref_index.eof()){
			G4String filler;
			Read_ref_index >> pWavelength >> filler >> indexvalue;
			//ref_index_value[ref_index_Entries]=1.59;
			Sc_Index_Energy.push_back((1240/pWavelength)*eV);
			//Sc_Index_Value.push_back(indexvalue);
			Sc_Index_Value.push_back(1.59);
		}
	}
	else
	G4cout << "Error opening file: " << ref_index_emit << G4endl;
	Read_ref_index.close();


	// Now apply the properties table

	// scintMPT->AddProperty("WLSCOMPONENT",wlsEnergy,wlsEmit,wlsEmEntries);
	// scintMPT->AddProperty("WLSABSLENGTH",wlsEnergy,wlsAbsorb,wlsAbEntries);   // the WLS absorption spectrum
	// scintMPT->AddConstProperty("WLSTIMECONSTANT",12*ns);
	scintMPT->AddProperty("RINDEX",Sc_Index_Energy, Sc_Index_Value);

	scintMPT->AddProperty("ABSLENGTH", Sc_Absorption_Energy, Sc_Absorption_Long);    // the bulk absorption spectrum
	scintMPT->AddProperty("SCINTILLATIONCOMPONENT1", Sc_Emission_Energy, Sc_Emission_Ratio);
	//scintMPT->AddProperty("SCINTILLATIONCOMPONENT1",scintEnergy,scintEmit,scintEntries);
	//scintMPT->AddProperty("SCINTILLATIONCOMPONENT2",scintEnergy,scintEmit,scintEntries);  // if slow component


	//G4double efficiency = 1.0;
	//scintMPT->AddConstProperty("EFFICIENCY",efficiency);

	scintMPT->AddConstProperty("SCINTILLATIONYIELD",lightyield/MeV);
	//scintMPT->AddConstProperty("ALPHASCINTILLATIONYIELD",0.01*lightyield/MeV);
	G4double scintRes = 1;
	scintMPT->AddConstProperty("RESOLUTIONSCALE",scintRes);
	G4double scintFastconst = 2.1*ns;
	scintMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1",scintFastconst);
	G4double scintSlowconst = 10*ns;
	scintMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT2",scintSlowconst); //if slow component
	scintMPT->AddConstProperty("SCINTILLATIONYIELD1",1.0);
	scintMPT->AddConstProperty("SCINTILLATIONYIELD2",0.0);

	scintillator->SetMaterialPropertiesTable(scintMPT);
	//scintillator->GetIonisation()->SetBirksConstant(0.0872*mm/MeV); //0.126->base; 0.0872->article BiPO
	//scintillator->GetIonisation()->SetBirksConstant(0.25*mm/MeV); // Choisi pour validation modÃ¨le avec LY 11737!!!
	//scintillator->GetIonisation()->SetBirksConstant(0.22*mm/MeV);
	//scintillator->GetIonisation()->SetBirksConstant(0.01*mm/MeV); // TEST ELECTRONS !!! => Maxime


	//#######################################################################################################################################
	//#######################################################################################################################################


	//Vacuum *************************************************************

	// Be careful of this vacuum definition.  This is only used to define
	// a refractive index so that the detector boundaries are defined.

	Vacuum = new G4Material ("Vacuum", //"Vacuum"   => SIMU OPTIQUE BASE
	1.0,  //1.0
	1.01*g/mole,  //1.01*g/mole
	universe_mean_density,   //universe_mean_density
	kStateGas,   //kStateGas
	3.e-18*pascal, //3.e-18*pascal
	2.73*kelvin);  //2.73*kelvin

	G4double y;
	std::vector<G4double> Vacuum_Energy;
	std::vector<G4double> Vacuum_Absorption_Long;
	std::vector<G4double> Vacuum_Index_Value;
	G4double vacAbsorbconst = 10000*m;

	std::ifstream ReadVac;
	G4String Vac = path+"EJ-212.cfg";  // simply index filler values...not EJ-212 values
	ReadVac.open(Vac);
	if(ReadVac.is_open()){
		while(!ReadVac.eof()){
			G4String filler;
			ReadVac >> pWavelength >> filler >> y;
			Vacuum_Energy.push_back((1240/pWavelength)*eV); //convert wavelength to eV
			Vacuum_Absorption_Long.push_back(vacAbsorbconst);
			Vacuum_Index_Value.push_back(1.0);
			//    G4cout<<vacEntries<<" "<<vacEnergy[vacEntries]<<" "<<vacIndex[vacEntries]<<G4endl;
		}
	}
	else
	G4cout << "Error opening file: " << Vac << G4endl;
	ReadVac.close();

	vacMPT = new G4MaterialPropertiesTable();
	//vacMPT->AddProperty("RINDEX", Vacuum_Energy, Vacuum_Index_Value);
	vacMPT->AddProperty("RINDEX", "Air");
	vacMPT->AddProperty("ABSLENGTH", Vacuum_Energy, Vacuum_Absorption_Long);
	Air->SetMaterialPropertiesTable(vacMPT);
	Vacuum->SetMaterialPropertiesTable(vacMPT);

	//Fake Vacuum *************************************************************

	VacuumWorld = new G4Material ("VacuumWorld",
	1.0,
	1.01*g/mole,
	universe_mean_density,
	kStateGas,
	3.e-18*pascal,
	2.73*kelvin);


	//#######################################################################################################################################
	//#######################################################################################################################################

	//GLASS PMT
	// Silicon Dioxide
	SiO2 = new G4Material("SiO2",2.6*g/cm3,2,kStateSolid);
	SiO2->AddElement(elementO,2);
	SiO2->AddElement(elementSi,1);

	// DiBoron TriOxide
	B2O3 = new G4Material("B2O3",2.46*g/cm3,2,kStateSolid);
	B2O3->AddElement(elementB,2);
	B2O3->AddElement(elementO,3);

	// DiSodium Monoxide
	Na2O = new G4Material("Na2O",2.27*g/cm3,2,kStateSolid);
	Na2O->AddElement(elementNa,2);
	Na2O->AddElement(elementO,1);

	// Aluminum Peroxide
	Al2O3 = new G4Material("Al2O3",3.97*g/cm3,2,kStateSolid);
	Al2O3->AddElement(elementAl,2);
	Al2O3->AddElement(elementO,3);

	bs_glass = new G4Material("bs_glass",
	2.23*g/cm3,
	4,
	kStateSolid,
	273.15*kelvin,
	1.0*atmosphere );

	bs_glassMPT = new G4MaterialPropertiesTable();

	bs_glass->AddMaterial(SiO2, 0.81);
	bs_glass->AddMaterial(B2O3, 0.13);
	bs_glass->AddMaterial(Na2O, 0.04);
	bs_glass->AddMaterial(Al2O3, 0.02);

	G4double glassabsorblength;

	std::ifstream ReadGlassBulk;
	G4String GlassBulk = path+"Borosilicate_GlassBulkAbsorb_reverse.cfg";
	ReadGlassBulk.open(GlassBulk);
	ReadGlassBulk.clear();
	std::vector<G4double> PM_Energy;
	std::vector<G4double> PM_Absorption_Long;
	if(ReadGlassBulk.is_open()){
		while(!ReadGlassBulk.eof()){
			G4String filler;
			ReadGlassBulk >> pWavelength >> filler >> glassabsorblength;
			PM_Energy.push_back((1240/pWavelength)*eV);
			PM_Absorption_Long.push_back(glassabsorblength*m);
			//   G4cout << "Energy = " << glassEnergy[glassEntries]
			//<< "    BulkAbsorb = " << glassbulkAbsorb[glassEntries] << G4endl;
		}
	}
	else
	G4cout << "Error opening file: " << GlassBulk << G4endl;

	ReadGlassBulk.close();


	std::ifstream ReadGlassIndex;
	G4String GlassIndexFile = path+"BSG_ref_index_reverse.dat";
	G4double bsgindexvalue;
	std::vector<G4double> PM_Index_Energy;
	std::vector<G4double> PM_Index_Value;
	ReadGlassIndex.open(GlassIndexFile);
	ReadGlassIndex.clear();
	if(ReadGlassIndex.is_open()){
		while(!ReadGlassIndex.eof()){
			G4String filler;
			ReadGlassIndex >> pWavelength >> filler >> bsgindexvalue;
			PM_Index_Energy.push_back((1240/pWavelength)*eV);
			PM_Index_Value.push_back(bsgindexvalue);
			//      G4cout << " Energy = " << bsgindexEnergy[bsgindexEntries] << "    Index = " << bsgindexvalue[bsgindexEntries] << G4endl;
		}
	}

	else
	G4cout << "Error opening file: " << GlassIndexFile << G4endl;

	ReadGlassIndex.close();

	bs_glassMPT->AddProperty("ABSLENGTH",PM_Energy, PM_Absorption_Long);
	//  bs_glassMPT->AddProperty("RINDEX",glassEnergy,bsgindexvalue,glassEntries);
	bs_glassMPT->AddProperty("RINDEX",PM_Index_Energy, PM_Index_Value);
	bs_glass->SetMaterialPropertiesTable(bs_glassMPT);


	//#######################################################################################################################################
	//#######################################################################################################################################

	//Cargille**************************************************************

	cargille = new G4Material("cargille",
	0.99*g/cm3,
	4,
	kStateSolid,
	273.15*kelvin,
	1.0*atmosphere );

	cargille->AddElement( elementH, 6 );
	cargille->AddElement( elementC, 2 );
	cargille->AddElement( elementO, 1 );
	cargille->AddElement( elementSi, 1 );


	G4double cargille_absorblength;
	G4double cargilleIndexconst = 1.406;//1.49 1.406 RTV

	std::ifstream ReadCargille_Bulk;
	G4String Cargille_Bulk = path+"CargilleBulkAbsorb_reverse.cfg";
	std::vector<G4double> Glue_Energy;
	std::vector<G4double> Glue_Index_Value;
	std::vector<G4double> Glue_Absorption_Long;
	ReadCargille_Bulk.open(Cargille_Bulk);
	if(ReadCargille_Bulk.is_open()){
		while(!ReadCargille_Bulk.eof()){
			G4String filler;
			ReadCargille_Bulk>>pWavelength>>filler>>cargille_absorblength;
			Glue_Energy.push_back((1240./pWavelength)*eV);
			Glue_Absorption_Long.push_back(cargille_absorblength*m);
			Glue_Index_Value.push_back(cargilleIndexconst);
		}
	}
	else
	G4cout << "Error opening file: " << Cargille_Bulk << G4endl;
	ReadCargille_Bulk.close();


	// std::ifstream Read_cargille_ref_index;
	// G4String cargille_ref_index_emit = path+"Cargille_ref_index.dat";
	// Read_cargille_ref_index.open(cargille_ref_index_emit);
	// if(Read_cargille_ref_index.is_open()){
	// 	while(!Read_cargille_ref_index.eof()){
	// 		G4String filler;
	// 		Read_cargille_ref_index >> pWavelength >> filler >> ref_index_value[cargille_ref_index_Entries];
	// 		ref_index_Energy[cargille_ref_index_Entries] = (1240/pWavelength)*eV;
	// 		cargille_ref_index_Entries++;
	// 	}
	// }
	// else
	// 	G4cout << "Error opening file: " << cargille_ref_index_emit << G4endl;
	// Read_cargille_ref_index.close();

	cargilleMPT = new G4MaterialPropertiesTable();
	cargilleMPT->AddProperty("RINDEX", Glue_Energy, Glue_Index_Value);
	//cargilleMPT->AddProperty("RINDEX",ref_index_Energy,ref_index_value,cargille_ref_index_Entries);
	cargilleMPT->AddProperty("ABSLENGTH",Glue_Energy, Glue_Absorption_Long);
	cargille->SetMaterialPropertiesTable(cargilleMPT);


	//#######################################################################################################################################
	//#######################################################################################################################################


	// Start of definition LaBr3 scintillation
	LaBr3 = new G4Material("LaBr3", 5.08*g/cm3, 2);
	LaBr3->AddElement(elementLa, 1);
	LaBr3->AddElement(elementBr, 3);

	LaBr3MPT = new G4MaterialPropertiesTable();

	// Read primary emission spectrum

	std::ifstream ReadLaBr3;

	G4String LaBr3_file = path+"LaBr3_emission_spectrum_reverse.cfg";
	std::vector<G4double> LaBr3_Emission_Energy;
	std::vector<G4double> LaBr3_Emission_Ratio;

	ReadLaBr3.open(LaBr3_file);
	if(ReadLaBr3.is_open()){
		while(!ReadLaBr3.eof()){
			G4String filler;
			ReadLaBr3 >> pWavelength >> filler >> ratio;
			//G4cout << "Wavelength = " << 1240./pWavelength << " & emission = "<< ratio << G4endl;
			LaBr3_Emission_Energy.push_back((1240./pWavelength)*eV);         //convert wavelength to eV
			LaBr3_Emission_Ratio.push_back(ratio);
		}
	}
	else
	{
		G4cout << "Error opening file: " << LaBr3_file << G4endl;
	}
	ReadLaBr3.close();

	// Read primary bulk absorption

	std::ifstream LaBr3Readabsorb;
	G4String LaBr3Readabsorblength = path+"LaBr3_absorption_reverse.cfg";
	std::vector<G4double> LaBr3_Absorption_Energy;
	std::vector<G4double> LaBr3_Absorption_Long;

	LaBr3Readabsorb.open(LaBr3Readabsorblength);
	if (LaBr3Readabsorb.is_open()){
		while(!LaBr3Readabsorb.eof()){
			G4String filler;
			LaBr3Readabsorb >> pWavelength >> filler >> varabsorblength;
			//G4cout << "Wavelength = " << pWavelength << " & absorption = "<< varabsorblength << G4endl;
			LaBr3_Absorption_Energy.push_back((1240./pWavelength)*eV);
			LaBr3_Absorption_Long.push_back(1.*varabsorblength*mm);
		}
	}
	else

	G4cout << "Error opening file: "<< LaBr3Readabsorblength << G4endl;

	LaBr3Readabsorb.close();



	// Read primary Rayleigh scattering
	std::ifstream LaBr3Readscatt;
	G4String LaBr3Readscattering = path+"LaBr3_scattering_reverse.cfg";
	std::vector<G4double> LaBr3_Scattering_Energy;
	std::vector<G4double> LaBr3_Scattering_Long;

	LaBr3Readscatt.open(LaBr3Readscattering);
	if (LaBr3Readscatt.is_open()){
		while(!LaBr3Readscatt.eof()){
			G4String filler;
			LaBr3Readscatt >> pWavelength >> filler >> varabsorblength;
			//G4cout << "Wavelength = " << pWavelength << " & absorption = "<< varabsorblength << G4endl;
			LaBr3_Scattering_Energy.push_back((1240./pWavelength)*eV);
			LaBr3_Scattering_Long.push_back(1.*varabsorblength*mm);
		}
	}
	else

	G4cout << "Error opening file: "<< LaBr3Readscattering << G4endl;

	LaBr3Readscatt.close();



	std::ifstream LaBr3Read_ref_index;
	//G4String ref_index_emit = path+"PST_ref_index.dat";
	G4String LaBr3ref_index_emit = path+"LaBr3_index_reverse.cfg";
	std::vector<G4double> LaBr3_Index_Energy;
	std::vector<G4double> LaBr3_Index_Value;

	LaBr3Read_ref_index.open(LaBr3ref_index_emit);
	if(LaBr3Read_ref_index.is_open()){
		while(!LaBr3Read_ref_index.eof()){
			G4String filler;
			LaBr3Read_ref_index >> pWavelength >> filler >> indexvalue;
			//ref_index_value[ref_index_Entries]=1.59;
			LaBr3_Index_Energy.push_back((1240/pWavelength)*eV);
			//LaBr3_Index_Value.push_back(indexvalue);
			LaBr3_Index_Value.push_back(1.9);
		}
	}
	else
	G4cout << "Error opening file: " << LaBr3ref_index_emit << G4endl;
	LaBr3Read_ref_index.close();


	// Now apply the properties table
	LaBr3MPT->AddProperty("RINDEX", LaBr3_Index_Energy, LaBr3_Index_Value);
	LaBr3MPT->AddProperty("ABSLENGTH", LaBr3_Absorption_Energy, LaBr3_Absorption_Long);    // the bulk absorption spectrum
	LaBr3MPT->AddProperty("RAYLEIGH", LaBr3_Scattering_Energy, LaBr3_Scattering_Long);    // the bulk absorption spectrum
	LaBr3MPT->AddProperty("SCINTILLATIONCOMPONENT1", LaBr3_Emission_Energy, LaBr3_Emission_Ratio);
	//scintMPT->AddProperty("SCINTILLATIONCOMPONENT2",scintEnergy,scintEmit,scintEntries);  // if slow component

	//G4double efficiency = 1.0;
	//LaBr3MPT->AddConstProperty("EFFICIENCY",efficiency);

	LaBr3MPT->AddConstProperty("SCINTILLATIONYIELD",lightyield/MeV);
	//LaBr3MPT->AddConstProperty("ALPHASCINTILLATIONYIELD",0.01*lightyield/MeV);
	G4double LaBr3Res = 1;
	LaBr3MPT->AddConstProperty("RESOLUTIONSCALE",LaBr3Res);
	G4double LaBr3Fastconst = 16*ns;
	LaBr3MPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1",LaBr3Fastconst);
	G4double LaBr3Slowconst = 66*ns;
	LaBr3MPT->AddConstProperty("SCINTILLATIONTIMECONSTANT2",LaBr3Slowconst); //if slow component
	LaBr3MPT->AddConstProperty("SCINTILLATIONYIELD1",1.0);
	LaBr3MPT->AddConstProperty("SCINTILLATIONYIELD2",0.0);

	LaBr3->SetMaterialPropertiesTable(LaBr3MPT);
	LaBr3->GetIonisation()->SetBirksConstant(0.03*mm/MeV); //0.126->base; 0.0872->article BiPO

	//#######################################################################################################################################
	//#######################################################################################################################################

	//PMMA
	PMMA = new G4Material("PMMA",  1.19*g/cm3, 3, kStateSolid, 273.15*kelvin, 1.0*atmosphere );
	PMMA->AddElement( elementH, 0.532 );
	PMMA->AddElement( elementC, 0.336 );
	PMMA->AddElement( elementO, 0.132 );

	std::ifstream Read_PMMA_ref_index;
	G4String PMMA_ref_index_emit = path+"PMMA_ref_index_geant_reverse.dat";
	G4double PMMA_absorblength;
	G4double PMMAIndex;
	std::vector<G4double> PMMA_Energy_index;
	std::vector<G4double> PMMA_Index_Value;
	std::vector<G4double> PMMA_Energy_abs;
	std::vector<G4double> PMMA_Absorption_Long;
	Read_PMMA_ref_index.open(PMMA_ref_index_emit);
	if(Read_PMMA_ref_index.is_open()){
		while(!Read_PMMA_ref_index.eof()){
			G4String filler;
			Read_PMMA_ref_index >> pWavelength >> filler >> PMMAIndex;
			PMMA_Energy_index.push_back((1240/pWavelength)*eV);
			PMMA_Index_Value.push_back(PMMAIndex);
		}
	}
	else
	G4cout << "Error opening file: " << PMMA_ref_index_emit << G4endl;
	Read_PMMA_ref_index.close();

	std::ifstream Read_pmma_Bulk;
	G4String PMMA_bulk = path+"PMMABulkAbsorb_reverse.dat";

	//  Read_pmma_Bulk.open(pmma_Bulk);
	Read_pmma_Bulk.open(PMMA_bulk);

	if(Read_pmma_Bulk.is_open()){
		while(!Read_pmma_Bulk.eof()){
			G4String filler;
			Read_pmma_Bulk >> pWavelength >> filler >> PMMA_absorblength;
			PMMA_Energy_abs.push_back((1240/pWavelength)*eV);
			PMMA_Absorption_Long.push_back(PMMA_absorblength*m);
			//      G4cout<<pmmaEntries<<" "<<pmmaEnergy[pmmaEntries]<<" "<<cladIndex1[pmmaEntries]<<G4endl;

		}
	}
	else
	//    G4cout << "Error opening file: " << Bulk << G4endl;
	G4cout << "Error opening file: " << "PMMABulkAbsorb.dat" << G4endl;

	Read_pmma_Bulk.close();

	//PMMA
	PMMAMPT = new G4MaterialPropertiesTable();
	PMMAMPT->AddProperty("ABSLENGTH", PMMA_Energy_abs, PMMA_Absorption_Long);
	PMMAMPT->AddProperty("RINDEX", PMMA_Energy_index, PMMA_Index_Value);
	PMMA->SetMaterialPropertiesTable(PMMAMPT);

	//#######################################################################################################################################
	//#######################################################################################################################################


	// Start of definition ZnS scintillation
	ZnS = new G4Material("ZnS", 4.1*g/cm3, 2);
	ZnS->AddElement(elementZn, 1);
	ZnS->AddElement(elementS, 1);

	ZnSMPT = new G4MaterialPropertiesTable();

	// Read primary emission spectrum

	std::ifstream ReadZnS;

	G4String ZnS_file = path+"ZnS_spectrum.dat";
	std::vector<G4double> ZnS_Emission_Energy;
	std::vector<G4double> ZnS_Emission_Ratio;

	ReadZnS.open(ZnS_file);
	if(ReadZnS.is_open()){
		while(!ReadZnS.eof()){
			G4String filler;
			ReadZnS >> pWavelength >> filler >> ratio;
			//G4cout << "Wavelength = " << 1240./pWavelength << " & emission = "<< ratio << G4endl;
			ZnS_Emission_Energy.push_back((1240./pWavelength)*eV);         //convert wavelength to eV
			ZnS_Emission_Ratio.push_back(ratio);
		}
	}
	else
	{
		G4cout << "Error opening file: " << ZnS_file << G4endl;
	}
	ReadZnS.close();

	// Read primary bulk absorption

	std::ifstream ZnSReadabsorb;
	G4String ZnSReadabsorblength = path+"LaBr3_absorption_reverse.cfg";
	std::vector<G4double> ZnS_Absorption_Energy;
	std::vector<G4double> ZnS_Absorption_Long;

	ZnSReadabsorb.open(ZnSReadabsorblength);
	if (ZnSReadabsorb.is_open()){
		while(!ZnSReadabsorb.eof()){
			G4String filler;
			ZnSReadabsorb >> pWavelength >> filler >> varabsorblength;
			//G4cout << "Wavelength = " << pWavelength << " & absorption = "<< varabsorblength << G4endl;
			ZnS_Absorption_Energy.push_back((1240./pWavelength)*eV);
			ZnS_Absorption_Long.push_back(0.65*mm);
		}
	}
	else

	G4cout << "Error opening file: "<< ZnSReadabsorblength << G4endl;

	ZnSReadabsorb.close();



	std::ifstream ZnSRead_ref_index;
	//G4String ref_index_emit = path+"PST_ref_index.dat";
	G4String ZnSref_index_emit = path+"ZnS_index_reverse.cfg";
	std::vector<G4double> ZnS_Index_Energy;
	std::vector<G4double> ZnS_Index_Value;

	ZnSRead_ref_index.open(ZnSref_index_emit);
	if(ZnSRead_ref_index.is_open()){
		while(!ZnSRead_ref_index.eof()){
			G4String filler;
			ZnSRead_ref_index >> pWavelength >> filler >> indexvalue;
			//ref_index_value[ref_index_Entries]=1.59;
			ZnS_Index_Energy.push_back((1240/pWavelength)*eV);
			ZnS_Index_Value.push_back(indexvalue);
			//ZnS_Index_Value.push_back(1.36);
		}
	}
	else
	G4cout << "Error opening file: " << ZnSref_index_emit << G4endl;
	ZnSRead_ref_index.close();


	// Now apply the properties table
	ZnSMPT->AddProperty("RINDEX", ZnS_Index_Energy, ZnS_Index_Value);
	ZnSMPT->AddProperty("ABSLENGTH", ZnS_Absorption_Energy, ZnS_Absorption_Long);    // the bulk absorption spectrum
	ZnSMPT->AddProperty("SCINTILLATIONCOMPONENT1", ZnS_Emission_Energy, ZnS_Emission_Ratio);
	//scintMPT->AddProperty("SCINTILLATIONCOMPONENT2",scintEnergy,scintEmit,scintEntries);  // if slow component

	//G4double efficiency = 1.0;
	//LaBr3MPT->AddConstProperty("EFFICIENCY",efficiency);

	ZnSMPT->AddConstProperty("SCINTILLATIONYIELD", lightyieldZnS/MeV);
	//LaBr3MPT->AddConstProperty("ALPHASCINTILLATIONYIELD",0.01*lightyield/MeV);
	G4double ZnSRes = 1;
	ZnSMPT->AddConstProperty("RESOLUTIONSCALE", ZnSRes);
	G4double ZnSFastconst = 200*ns;
	ZnSMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT1",ZnSFastconst);
	G4double ZnSSlowconst = 1000*ns;
	ZnSMPT->AddConstProperty("SCINTILLATIONTIMECONSTANT2", ZnSSlowconst); //if slow component
	ZnSMPT->AddConstProperty("SCINTILLATIONYIELD1",1.0);
	ZnSMPT->AddConstProperty("SCINTILLATIONYIELD2",0.0);

	ZnS->SetMaterialPropertiesTable(ZnSMPT);
	//ZnS->GetIonisation()->SetBirksConstant(0.03*mm/MeV); //0.126->base; 0.0872->article BiPO






}

G4Material* TPSimMaterials::GetMaterial(G4String material)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(material);
	return pttoMaterial;
}
