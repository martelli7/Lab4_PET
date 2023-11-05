#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"

#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "G4VisAttributes.hh"

#include "detector.hh"

//This class is a derivate class from the class G4VUserDetectorConstruction
class MyDetectorConstruction : public G4VUserDetectorConstruction
{
    public:
		MyDetectorConstruction();
		~MyDetectorConstruction();

		//This method is invoked from RunManager->Initialize(), so for us from macro command /run/initialize. It returns the pointer to the WORLD VOLUME
		virtual G4VPhysicalVolume *Construct();

    private:
		G4Box *solidWorld;
		G4Tubs *solidScintillator, *solidSource;
		G4LogicalVolume *logicWorld, *logicScintillator, *logicSource;
		G4VPhysicalVolume *physWorld, *physSource, *physScintillatorGate, *physScintillatorSpect;

		G4Material *worldMat, *NaI, *PMMA;
		
		//This method is invoked inside MyDetectorConstruction()
		void DefineMaterials();
		
		//This method is invoked inside the virtual method Construct()
		void Construct2DPET();
		
		//This method is invoked from RunManager->Initialize(), so for us from macro command /run/initialize. It returns the pointer to the SENSITIVE VOLUME
		virtual void ConstructSDandField();

		G4GenericMessenger *fMessenger, *fMessenger1;  

		G4double xWorld, yWorld, zWorld;
		G4double rhoD, alphaD, gammaD;

		G4bool is2DPET;
};

#endif
