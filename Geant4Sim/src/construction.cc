#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
	//Definition of the MESSENGERS for changing same important parameters!!!

  	fMessenger = new G4GenericMessenger(this, "/disk/", "Disk Construction");

	fMessenger->DeclareProperty("rhoD", rhoD, "Plastic disk coordinate rho with respect negative z axis, insert negative values [mm]");

	fMessenger->DeclareProperty("alphaD", alphaD, "Plastic disk coordinate alpha with respect positive y axis, insert positive values [deg]");
	
	rhoD = -111.;  //Real experiment: -111.0*mm
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
}





MyDetectorConstruction::~MyDetectorConstruction()
{}






void MyDetectorConstruction::DefineMaterials()
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









void MyDetectorConstruction::Construct2DPET()
{	

	solidScintillator = new G4Tubs("solidScintillator", //name
	 							 		0.*mm, 12.7*mm, //inner and outer radius
											   12.7*mm, //height
									   0*deg, 360*deg); //initial and final angle

	logicScintillator = new G4LogicalVolume(solidScintillator, //solid volume
 														  NaI, //material
										 "logicScintillator"); //name

	//Let's create two identical NaI crystals, 
	//1. the GATE 
	physScintillatorGate = new G4PVPlacement(0, //rotation
 			  G4ThreeVector(0., 0., +198.7*mm), //position coordinates
 							 logicScintillator, //logical volume
 							"physScintillator", //name
 									logicWorld, //logical mother volume
 										 false, //no boolean operator
											33, //copy number = 33
										 true); //check overlaps

	//2. the SPECTROMETER

	G4Rotate3D rotSY(gammaD*deg, G4ThreeVector(0.,1.,0.));
	G4Translate3D tranSZ(G4ThreeVector(0., 0., -198.7*mm));
	G4Transform3D transformSpct = (rotSY)*(tranSZ);

	physScintillatorSpect = new G4PVPlacement(transformSpct, //rotation and position				  
							  logicScintillator, //logical volume
 							 "physScintillator", //name
 									 logicWorld, //logical mother volume
 										  false, //no boolean operator
											 44, //copy number = 44
										  true); //check overlaps
}


//WORLD CONSTRUCTION

G4VPhysicalVolume *MyDetectorConstruction::Construct()
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
	}

	//Make logicScintillator a Sensitive Detector
	ConstructSDandField(); 

	return physWorld;
}




void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector"); //name

    //Tell who are the SensitiveDetectors, i.e. logicScintillator
    if(logicScintillator != NULL)
    {    
		logicScintillator->SetSensitiveDetector(sensDet);
    }
    else
    {
    	G4cout << "ERROR: logiScintillator not defined!" << G4endl;
  	}
}
