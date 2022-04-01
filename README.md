# ENLTPSim for Thomson Parabola Simulation

# INSTRUCTIONS TO USE THE SIMULATION
# - Download the VMWare Geant4.11.0.0 from https://heberge.lp2ib.in2p3.fr/G4VM/index.html
# - Copy all the files from ENL_egn_Simulation folder (https://github.com/ahuber33/ENL_egn_Simulation)
# - Create a build folder in the ENL_egn_Simulation folder and go inside.
# - Use this command : "cmake -DGeant4_DIR=$G4COMP ../" and compile it with make
# - The executable ENLegnSim will be add to your bin folder
# - If you want to have a visualization, launch this command : "./ENLTPSim [name of ROOT file ]". It will generate 1 particle according to the vis.mac with QT and you will have a ROOT file with the name you gave in response located in the Resultats folder.
# - If you want to have statistics without the visualization, use this command : "./ENLTPSim [name of ROOT file] [number of events generated] [name of macro]". Personnaly, I used the vrml.mac but you can create another one. Just to remember that you need to write the name of your macro when you launch the simulation.
# - An ENLTPSim.cfg file is located in bin directory. All the dimensions necessary are in this file to avoid recompilation when you want to change some parameters. If you add some other dimensions, don't forget to add the variables in Geometry.cc.
# - TP Tree contains datas about Energy of the particles (start and deposited) and position of interaction on the detector. Anoterh Tree optical is available if the Optical part is activated.
# - DO NOT HESITATE TO REPORT BUGS OR ANY IDEAS THAT WILL IMPROVE THE SIMULATION !!!!

#commit #1 le 23/02/2022 [TPSim.0.0.0]:
#-Code de base provenant de la version TPSim.0.5.0 avec quelques parties de code nettoyés pour en simplifier la lecture
#-Code Deviation.cc utilisé pour comparer deviation particules avec GEANT4 et par calcul.
