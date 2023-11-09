#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

#include "G4AnalysisManager.hh"

#include "run.hh"

class MyEventAction : public G4UserEventAction
{
  public:
    MyEventAction(MyRunAction*);
    ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    inline void AddEdepGATE(G4double edep) 
    { 
      fEdepGATE += edep; 
    }
    inline void AddEdepSPCT(G4double edep) 
    { 
      fEdepSPCT += edep; 
    }

  private:
    G4double fEdepGATE;
    G4double fEdepSPCT;

};

#endif
