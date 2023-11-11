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
/// \file B3/B3a/include/DetectorConstruction.hh
/// \brief Definition of the B3::DetectorConstruction class

#ifndef B3DetectorConstruction_h
#define B3DetectorConstruction_h 1

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
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

namespace B3
{

/// Detector construction class to define materials and geometry.
///
/// Crystals are positioned in Ring, with an appropriate rotation matrix.
/// Several copies of Ring are placed in the full detector.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public: 
    DetectorConstruction();
    ~DetectorConstruction() override = default;

  public:
    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;

  private:

	G4Box *solidWorld;
	G4Tubs *solidScintillator, *solidSource;
	G4LogicalVolume *logicWorld, *logicScintillatorGATE, *logicScintillatorSPCT,  *logicSource;
	G4VPhysicalVolume *physWorld, *physSource, *physScintillatorGATE, *physScintillatorSPCT;

	G4Material *worldMat, *NaI, *PMMA;	

    void DefineMaterials();

	//This method is invoked inside the virtual method Construct()
	void Construct2DPET();

    G4bool fCheckOverlaps = true;
	
	G4GenericMessenger *fMessenger, *fMessenger1;  

	G4double xWorld, yWorld, zWorld;
	G4double rhoD, alphaD, gammaD;

	G4bool is2DPET;

	
};

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

