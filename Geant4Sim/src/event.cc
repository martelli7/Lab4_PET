#include "event.hh"

MyEventAction::MyEventAction(MyRunAction*)
{
	fEdepGATE = 0.;
	fEdepSPCT = 0.;
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
	fEdepGATE = 0.;
	fEdepSPCT = 0.;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{

	if (fEdepGATE > 0.02 || fEdepSPCT > 0.02) 
	{
    	G4cout << "Total energy deposition in this event in GATE Scint: " << fEdepGATE << " MeV" << G4endl;
    	G4cout << "Total energy deposition in this event in SPCT Scint: " << fEdepSPCT << " MeV" << G4endl;

    	G4AnalysisManager *man = G4AnalysisManager::Instance();

    	man->FillNtupleDColumn(0, 0, fEdepGATE); 
    	man->FillNtupleDColumn(0, 1, fEdepSPCT); 

    	man->AddNtupleRow(0);
	}
}
