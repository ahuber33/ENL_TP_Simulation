/// TPSimVisManager.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr> 
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef TPSimVisManager_h
#define TPSimVisManager_h 1

#include "G4VisManager.hh"


class TPSimVisManager: public G4VisManager {

public:

  TPSimVisManager ();

private:

  void RegisterGraphicsSystems ();

};

#endif
