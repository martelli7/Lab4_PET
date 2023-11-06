#include "run.hh"

MyRunAction::MyRunAction()
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	//Creation of an Ntuple where storing datas
  	man->CreateNtuple("EnergyDeposition", "Energy deposition");
  	man->CreateNtupleDColumn("fEdepGATE");
  	man->CreateNtupleDColumn("fEdepSPCT");
  	man->FinishNtuple(0);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{	
	//Creation of a root file for each run 
	G4AnalysisManager *man = G4AnalysisManager::Instance();
  	G4int runID = run->GetRunID();

  	std::stringstream strRunID;
  	strRunID << runID;

  	man->OpenFile("output"+strRunID.str()+".root");
}

void MyRunAction::EndOfRunAction(const G4Run*)
{	
    	G4AnalysisManager *man = G4AnalysisManager::Instance();

    	man->Write();
    	man->CloseFile();
}
