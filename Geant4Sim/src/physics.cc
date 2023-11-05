#include "physics.hh"
#include "G4EmStandardPhysics_option4.hh"

MyPhysicsList::MyPhysicsList()
{   
    //Definition of the experiment physics
    RegisterPhysics (new G4EmStandardPhysics_option4()); //EM interactions
    RegisterPhysics (new G4OpticalPhysics()); //Optical physics
    RegisterPhysics (new G4DecayPhysics()); //Decay physics
    RegisterPhysics (new G4RadioactiveDecayPhysics()); //Radioactive physics
}

MyPhysicsList::~MyPhysicsList()
{}
