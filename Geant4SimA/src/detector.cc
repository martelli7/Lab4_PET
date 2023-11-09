#include "detector.hh"
#include "G4RunManager.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
}


MySensitiveDetector::~MySensitiveDetector()
{}


G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{	
	G4double edep = aStep->GetTotalEnergyDeposit();

	//Access to the particle track
	G4Track *track = aStep->GetTrack(); 
	G4int trkID = track->GetTrackID();

	//Here we access touchable variables
	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

	G4int copyNo = touchable->GetVolume()->GetCopyNo(); //Returns CopyNumber of the hitted volume
	
	if (copyNo == 33 || copyNo == 44)
	{
    	//Access UserEventAction to sum the deposited energy
    	MyEventAction* evAction = (MyEventAction*)G4RunManager::GetRunManager()->GetUserEventAction(); 

    		if (copyNo == 33) 
		{
        		evAction->AddEdepGATE(edep);  
    		}
    		else if (copyNo == 44) 
		{
	      		evAction->AddEdepSPCT(edep); 
    		}
	}

	return true;
}
