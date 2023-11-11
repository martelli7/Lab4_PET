#include "generator.hh"
#include "G4Gamma.hh"
#include "Randomize.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "G4Event.hh"
#include "G4Transform3D.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{	
	fMessenger2 = new G4GenericMessenger(this, "/source/", "Generator Construction");

	fMessenger2->DeclareProperty("rhoS", rhoS, "Na22 source coordinate rho with respect negative z axis, insert negative values [mm]");

	fMessenger2->DeclareProperty("alphaS", alphaS, "Na22 source coordinate alpha with respect positive y axis, insert positive values [deg]");
	
	rhoS = 0.;  //Real experiment: -111.0*mm
	alphaS = 0.; //Real experiment: 225.0*deg (rest rotating plate)
	
	fParticleGun = new G4ParticleGun(1); //Number of particle
    
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("geantino");
    //geantino is a "placeholder" particle
    //if not overwritten by a particular particle, it will get the nucleus defined later

    G4ThreeVector pos(0.,0.,0.);//Particle position
    G4ThreeVector mom(0.,0.,0.);//Particle momentum
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(0.*GeV);
    fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

//Particle definition
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();

	if(particle == G4Geantino::Geantino())
	{
		G4int Z = 11;
	    G4int A = 22;
			
		G4double charge = 0.*eplus;
		G4double energy = 0.*keV;	
			
		G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);	

		G4PrimaryVertex* vertex = new G4PrimaryVertex(G4ThreeVector(rhoS*cos(alphaS*deg)*mm, //x
							  						0, //y
							 rhoS*sin(alphaS*deg)*mm), //z
												   0); //t

		auto Na22 = new G4PrimaryParticle(ion); 

		Na22->SetMomentumDirection(G4ThreeVector(0,0,0));
		Na22->SetTotalEnergy(0.);
	    vertex->SetPrimary(Na22); 
					
	    anEvent->AddPrimaryVertex(vertex); 
	}
}
