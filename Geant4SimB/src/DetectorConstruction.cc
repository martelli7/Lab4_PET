//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B3/B3a/src/DetectorConstruction.cc
/// \brief Implementation of the B3::DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

namespace B3
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
{
	//Definition of the MESSENGERS for changing same important parameters!!!

  	fMessenger = new G4GenericMessenger(this, "/disk/", "Disk Construction");

	fMessenger->DeclareProperty("rhoD", rhoD, "Plastic disk coordinate rho with respect negative z axis, insert negative values [mm]");

	fMessenger->DeclareProperty("alphaD", alphaD, "Plastic disk coordinate alpha with respect positive y axis, insert positive values [deg]");
	
	rhoD = 0.;  //Real experiment: -111.0*mm
	alphaD = 0.; //Real experiment: 225.0*deg (rest rotating plate)

	fMessenger1 = new G4GenericMessenger(this, "/detector/", "Spectrometer Construction");

	fMessenger1->DeclareProperty("gammaD", gammaD, "Spectrometer coordinate gamma with respect positive y axis, insert positive values [deg]");
	
	gammaD = 0.; //Real experiment: between -30 deg and + 30 deg

	//Let's call DefineMaterials() method
	DefineMaterials();

	//Let's define the world volume half values
	xWorld = 2*m;
	yWorld = 2*m;
	zWorld = 2*m;

	//Define detector type
	is2DPET = true;

	DefineMaterials();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
  	//Let's use NIST database to define the world/detector materials!
	G4NistManager *nist = G4NistManager::Instance();
	
	//Firstly, let's made our World of Air
	worldMat = nist->FindOrBuildMaterial("G4_AIR");

	//Selected Momentum for 200nm and 900nm
	G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2}; 

	//Reflective index of the World (air), in function of the selected wavelenght
	G4double rindexWorld[2] = {1.0, 1.0}; 

	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX",energy,rindexWorld,2);
	worldMat->SetMaterialPropertiesTable(mptWorld);
	    		      
	//Now let's define the plastic encapsulating the source 
	auto Carbon = nist->FindOrBuildElement("C");
	auto Oxygen = nist->FindOrBuildElement("O");
	auto Hydrogen = nist->FindOrBuildElement("H"); 

	PMMA = new G4Material("PMMA", 1.18*g/cm3, 3, kStateSolid); 
	PMMA->AddElement(Carbon, 5); 
	PMMA->AddElement(Oxygen, 2); 
	PMMA->AddElement(Hydrogen, 8); 


	//In conclusion, the definition of Sodium Iodide for Scintillator
	auto Sodium = nist->FindOrBuildElement("Na");
	auto Iodine = nist->FindOrBuildElement("I");

	NaI = new G4Material("NaI", 3.67*g/cm3, 2); //Formula, density, number of elements
	NaI->AddElement(Sodium, 1);
	NaI->AddElement(Iodine, 1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void DetectorConstruction::Construct2DPET()
{	

	solidScintillator = new G4Tubs("solidScintillator", //name
	 				0.*mm, 12.7*mm, //inner and outer radius
					12.7*mm, //height
					0*deg, 360*deg); //initial and final angle

	logicScintillatorGATE = new G4LogicalVolume(solidScintillator, //solid volume
 							NaI, //material
							"logicScintillatorGATE"); //name

	logicScintillatorSPCT = new G4LogicalVolume(solidScintillator, //solid volume
 							NaI, //material
							"logicScintillatorSPCT"); //name

	//Let's create two identical NaI crystals, 
	//1. the GATE 
	physScintillatorGATE = new G4PVPlacement(0, //rotation
 			  			G4ThreeVector(0., 0., +198.7*mm), //position coordinates
 						logicScintillatorGATE, //logical volume
 						"physScintillatorGATE", //name
 						logicWorld, //logical mother volume
 						false, //no boolean operator
						33, //copy number = 33
						true); //check overlaps

	//2. the SPECTROMETER

	G4Rotate3D rotSY(gammaD*deg, G4ThreeVector(0.,1.,0.));
	G4Translate3D tranSZ(G4ThreeVector(0., 0., -198.7*mm));
	G4Transform3D transformSpct = (rotSY)*(tranSZ);

	physScintillatorSPCT = new G4PVPlacement(transformSpct, //rotation and position				  
						logicScintillatorSPCT, //logical volume
 						"physScintillatorSPCT", //name
 						logicWorld, //logical mother volume
 						false, //no boolean operator
						44, //copy number = 44
						true); //check overlaps
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......




G4VPhysicalVolume* DetectorConstruction::Construct()
{
	//Define the World volume
	solidWorld = new G4Box("solidWorld", //name
				xWorld,yWorld,zWorld); //dimensions x/2, y/2, z/2

	logicWorld = new G4LogicalVolume(solidWorld, //solid volume
 					worldMat, //material
					"logicWorld"); //name

	physWorld = new G4PVPlacement(0, //rotation
 		  			G4ThreeVector(0., 0., 0.), //position coordinates
 					logicWorld, //logical volume
 					"physWorld", //name
 					0, //logical mother volume
 					false, //no boolean operator
					13, //copy number = 13
					true); //check overlaps
	 
	  
	//Let's create the source plastic capsule 
	solidSource = new G4Tubs("solidSource", //name
				0*mm, 1*cm, //inner and outer radius
				2*mm, //height
				0*deg, 360*deg); //initial and final angle

	logicSource = new G4LogicalVolume(solidSource, //solid volume
					PMMA, //material
					"logicSource"); //name

	logicSource->SetVisAttributes(G4VisAttributes(G4Colour(1, 0, 0))); //let's display it in red
	
	G4Rotate3D rotY(alphaD*deg, G4ThreeVector(0.,1.,0.));
	G4Translate3D tranZ(G4ThreeVector(0., 0., rhoD*mm));
	G4Transform3D transformDisk = (rotY)*(tranZ);
	
	physSource = new G4PVPlacement(transformDisk, //rotation and position coordinates
					logicSource, //logical volume
		                	"physSource", //name
					logicWorld, //logical mother volume
					false, //no boolean operator 
					11, //copy number = 11
					true); //check overlaps

	//Call constructor of the detector
	if(is2DPET) 
	{
		Construct2DPET();
		G4cout << "Gamma angle = " << gammaD << G4endl;
	} 
  

  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
  	G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

  	// declare crystal as a MultiFunctionalDetector scorer
  	// NB: "crystal" is not the name of the physical volumes!!!
  	auto cryst = new G4MultiFunctionalDetector("crystal");
 	G4SDManager::GetSDMpointer()->AddNewDetector(cryst);
  	G4VPrimitiveScorer* primitiv1 = new G4PSEnergyDeposit("edep");
  	cryst->RegisterPrimitive(primitiv1);
	logicScintillatorGATE->SetSensitiveDetector(cryst);
	logicScintillatorSPCT->SetSensitiveDetector(cryst);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}

