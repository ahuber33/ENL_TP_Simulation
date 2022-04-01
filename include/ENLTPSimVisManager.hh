/// ENLTPSimVisManager.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLTPSimVisManager_h
#define ENLTPSimVisManager_h 1

#include "G4VisManager.hh"


class ENLTPSimVisManager: public G4VisManager {

public:

  ENLTPSimVisManager ();

private:

  void RegisterGraphicsSystems ();

};

#endif
