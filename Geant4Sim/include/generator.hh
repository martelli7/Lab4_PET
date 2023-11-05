#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4Geantino.hh"
#include "G4IonTable.hh"

#include "G4GenericMessenger.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
    public:
    	MyPrimaryGenerator();
    	~MyPrimaryGenerator();
		
		//This method is invoked from RunManager() during the loop. It generates the particle primary vertex
    	virtual void GeneratePrimaries(G4Event*);
	
    private:
        G4ParticleGun *fParticleGun;

		G4GenericMessenger *fMessenger;

		G4double rhoS, alphaS;
};

#endif
