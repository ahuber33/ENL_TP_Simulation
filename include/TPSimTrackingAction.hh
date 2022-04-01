/// TPSimTrackingAction.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef TPSimTrackingAction_h
#define TPSimTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"

class TPSimTrackingAction : public G4UserTrackingAction
{
public:
  TPSimTrackingAction();
  ~TPSimTrackingAction();

  void PreUserTrackingAction(const G4Track*);
  void PostUserTrackingAction(const G4Track*);
};
#endif
