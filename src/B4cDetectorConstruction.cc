 /// Compton And Two photon Spectrometer (CATS)
 /// Summer 2022 Vincent Bruening, Mount Allision University Physics, supervised by Dr. David Hornidge
 /// Modified exampleB4c 

#include "B4cDetectorConstruction.hh"
#include "B4cCalorimeterSD.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4RotationMatrix.hh"
#include "G4SubtractionSolid.hh"
#include "G4MultiUnion.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4SDManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


G4ThreadLocal 
G4GlobalMagFieldMessenger* B4cDetectorConstruction::fMagFieldMessenger = 0; 


B4cDetectorConstruction::B4cDetectorConstruction()
 : G4VUserDetectorConstruction(),
   fCheckOverlaps(true),
   fNofLayers(-1)
{
}


B4cDetectorConstruction::~B4cDetectorConstruction()
{ 
}  


G4VPhysicalVolume* B4cDetectorConstruction::Construct()
{
  // Define materials 
  DefineMaterials();
  
  // Define volumes
  return DefineVolumes();
}


void B4cDetectorConstruction::DefineMaterials()
{ 
  // Lead material defined using NIST Manager
  auto nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_Pb");
  nistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  nistManager->FindOrBuildMaterial("G4_AIR");
  nistManager->FindOrBuildMaterial("G4_LITHIUM_CARBONATE");
  nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//Main Construction starts here
G4VPhysicalVolume* B4cDetectorConstruction::DefineVolumes()
{
  // Get material
  auto defaultMaterial = G4Material::GetMaterial("G4_AIR");
  auto boxMaterial = G4Material::GetMaterial("G4_Pb");
  //auto gapMaterial = G4Material::GetMaterial("liquidArgon");
  auto coreMaterial = G4Material::GetMaterial("G4_SODIUM_IODIDE");
  auto ringMaterial = G4Material::GetMaterial("G4_LITHIUM_CARBONATE");
  auto scintMaterial = G4Material::GetMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    
   //     
  // World
  //
  auto worldS 
    = new G4Box("World",           // its name
                 300*cm, 300*cm, 300*cm); // its size
                         
  auto worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 defaultMaterial,  // its material
                 "World");         // its name
                                   
  auto worldPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 worldLV,          // its logical volume                         
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  
  G4double z = 31.75*cm;//31.75
  G4double w = 40.75*cm;
  G4ThreeVector pos1 = G4ThreeVector(0, 0, 150*cm);//Use this to change location of CATS

 //CATS Core
 G4Tubs* Core =
    new G4Tubs("Core", 0*cm, 13.35*cm, z, 0.*deg, 360.*deg);

 G4LogicalVolume* logicCore =
    new G4LogicalVolume(Core,
                        coreMaterial,
                        "Core");

  new G4PVPlacement(0,
                    pos1,
                    logicCore,
                    "Core",
                    worldLV,
                    false,
                    1,
                    fCheckOverlaps);

   //Segmented Annulus
  G4Tubs* AnnulusPiece1 =
    new G4Tubs("AnnulusPiece1", 13.35*cm, 24.15*cm, z, 0.*deg, 60*deg);
  G4LogicalVolume *logicAnnulusPiece1 =
    new G4LogicalVolume(AnnulusPiece1, coreMaterial, "AnnulusPiece1");
   new G4PVPlacement(0, pos1, logicAnnulusPiece1, "AnnulusPiece1", worldLV, false, 2, fCheckOverlaps);

   G4Tubs* AnnulusPiece2 =
     new G4Tubs("AnnulusPiece2", 13.35*cm, 24.15*cm, z, 60.*deg, 60*deg);
   G4LogicalVolume *logicAnnulusPiece2 =
    new G4LogicalVolume(AnnulusPiece2, coreMaterial, "AnnulusPiece2");
   new G4PVPlacement(0, pos1, logicAnnulusPiece2, "AnnulusPiece2", worldLV, false, 3, fCheckOverlaps);

   G4Tubs* AnnulusPiece3 =
    new G4Tubs("AnnulusPiece3", 13.35*cm, 24.15*cm, z, 120.*deg, 60*deg);
  G4LogicalVolume *logicAnnulusPiece3 =
    new G4LogicalVolume(AnnulusPiece3, coreMaterial, "AnnulusPiece3");
   new G4PVPlacement(0, pos1, logicAnnulusPiece3, "AnnulusPiece3", worldLV, false, 4, fCheckOverlaps);

  G4Tubs* AnnulusPiece4 =
    new G4Tubs("AnnulusPiece4", 13.35*cm, 24.15*cm, z, 180.*deg, 60*deg);
  G4LogicalVolume *logicAnnulusPiece4 =
    new G4LogicalVolume(AnnulusPiece4, coreMaterial, "AnnulusPiece4");
   new G4PVPlacement(0, pos1, logicAnnulusPiece4, "AnnulusPiece4", worldLV, false, 5, fCheckOverlaps);

   G4Tubs* AnnulusPiece5 =
    new G4Tubs("AnnulusPiece5", 13.35*cm, 24.15*cm, z, 240.*deg, 60*deg);
  G4LogicalVolume *logicAnnulusPiece5 =
    new G4LogicalVolume(AnnulusPiece5, coreMaterial, "AnnulusPiece5");
   new G4PVPlacement(0, pos1, logicAnnulusPiece5, "AnnulusPiece5", worldLV, false, 6, fCheckOverlaps);

   G4Tubs* AnnulusPiece6 =
    new G4Tubs("AnnulusPiece6", 13.35*cm, 24.15*cm, z, 300.*deg, 60*deg);
  G4LogicalVolume *logicAnnulusPiece6 =
    new G4LogicalVolume(AnnulusPiece6, coreMaterial, "AnnulusPiece6");
   new G4PVPlacement(0, pos1, logicAnnulusPiece6, "AnnulusPiece6", worldLV, false, 7, fCheckOverlaps);


  //Lithium Carbonate Layer for Insulation
  G4Tubs* Ring =
	 new G4Tubs("Ring", 24.15*cm, 25.15*cm, z, 0, 360*deg);
 	G4LogicalVolume *logicRing =
	new G4LogicalVolume(Ring, ringMaterial, "Ring");
	new G4PVPlacement(0, pos1, logicRing, "Ring", worldLV, false, 8, fCheckOverlaps);

//Scintillators to veto Cosmic Rays
G4Tubs *Scint1 = new G4Tubs("Scint1", 25.15*cm, 35.15*cm, w, 0, 72*deg);
G4LogicalVolume *logicScint1 = 
	new G4LogicalVolume(Scint1, scintMaterial, "Scint1");
	new G4PVPlacement(0, pos1, logicScint1, "Scint1", worldLV, false, 9, fCheckOverlaps);

G4Tubs *Scint2 = new G4Tubs("Scint2", 25.15*cm, 35.15*cm, w, 72*deg, 72*deg);
G4LogicalVolume *logicScint2 =
        new G4LogicalVolume(Scint2, scintMaterial, "Scint2");
        new G4PVPlacement(0, pos1, logicScint2, "Scint2", worldLV, false, 10, fCheckOverlaps);

G4Tubs *Scint3 = new G4Tubs("Scint3", 25.15*cm, 35.15*cm, w, 144*deg, 72*deg);
G4LogicalVolume *logicScint3 =
        new G4LogicalVolume(Scint3, scintMaterial, "Scint3");
        new G4PVPlacement(0, pos1, logicScint3, "Scint3", worldLV, false, 11, fCheckOverlaps);

G4Tubs *Scint4 = new G4Tubs("Scint4", 25.15*cm, 35.15*cm, w, 216*deg, 72*deg);
G4LogicalVolume *logicScint4 =
        new G4LogicalVolume(Scint4, scintMaterial, "Scint4");
        new G4PVPlacement(0, pos1, logicScint4, "Scint4", worldLV, false, 12, fCheckOverlaps);

G4Tubs *Scint5 = new G4Tubs("Scint5", 25.15*cm, 35.15*cm, w, 288*deg, 72*deg);
G4LogicalVolume *logicScint5 =
        new G4LogicalVolume(Scint5, scintMaterial, "Scint5");
        new G4PVPlacement(0, pos1, logicScint5, "Scint5", worldLV, false, 13, fCheckOverlaps);
//previous 5 form an annulus, 6th scintillator goes on the back

G4Tubs *Scint6 = new G4Tubs("Scint6", 0*cm, 35*cm, 4.7*cm, 0*deg, 360*deg);
G4LogicalVolume *logicScint6 =
	new G4LogicalVolume(Scint6, scintMaterial, "Scint6");
	new G4PVPlacement(0, G4ThreeVector(0,0,205.45*cm), logicScint6, "Scint6", worldLV, false, 14, fCheckOverlaps);//186.45


//Set colours
auto CATScolour = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
CATScolour->SetVisibility(true);
logicCore->SetVisAttributes(CATScolour);
logicAnnulusPiece1->SetVisAttributes(CATScolour);
logicAnnulusPiece2->SetVisAttributes(CATScolour);
logicAnnulusPiece3->SetVisAttributes(CATScolour);
logicAnnulusPiece4->SetVisAttributes(CATScolour);
logicAnnulusPiece5->SetVisAttributes(CATScolour);
logicAnnulusPiece6->SetVisAttributes(CATScolour);
logicRing->SetVisAttributes(CATScolour);
logicScint1->SetVisAttributes(CATScolour);
logicScint2->SetVisAttributes(CATScolour);
logicScint3->SetVisAttributes(CATScolour);
logicScint4->SetVisAttributes(CATScolour);
logicScint5->SetVisAttributes(CATScolour);
logicScint6->SetVisAttributes(CATScolour);


//Next, we make the collimator

G4double Leadx = 351.5*mm;
G4double Longy = 50*mm;
G4double Longzz = 650.5*mm;

//Two of the Long Components
G4Box *LongBit1 = new G4Box("LongBit1", Leadx+111*mm, Longy, Longzz);
G4Box *LongBit2 = new G4Box("LongBit2", Leadx+111*mm, Longy, Longzz);

G4Box* OtherLongBit1 = new G4Box("OtherLongBit1", Longy, Leadx+10*mm, Longzz);
G4Box* OtherLongBit2 = new G4Box("OtherLongBit2", Longy, Leadx+10*mm, Longzz);


G4Box* EndBit = new G4Box("EndBit", Leadx+110*mm, Leadx+105*mm, Longy);

//subtraction solid here!
G4Box* FrontBit = new G4Box("FrontBit", 460.5*mm, 460*mm, 105*mm);
G4Tubs* FrontBitHole = new G4Tubs("FrontBitHole", 0*cm, 6.9*cm, 105.1*mm, 0*deg, 360*deg); //had to make the hole slightly longer than the box- otherwise you could not see the hole on both sides of the front bit

G4SubtractionSolid *subtraction = new G4SubtractionSolid("subtraction", FrontBit, FrontBitHole);


//endbit transform
G4ThreeVector EndDisplacement = G4ThreeVector(0,0,66.15*cm);//adding 5cm to z so no overlap with back scintillator
G4RotationMatrix none = G4RotationMatrix(); //for no rotation
G4Transform3D EndBitTransform = G4Transform3D(none, EndDisplacement);


G4double Placement = 401.5*mm;
G4double LongBitZ= -1.3*cm;

//LongBit1 transform
G4ThreeVector HighLongBit1 = G4ThreeVector(0,Placement+1*cm,LongBitZ);
G4Transform3D LongBit1Transform = G4Transform3D(none, HighLongBit1);

//LongBit2 transform
G4ThreeVector LowLongBit2 = G4ThreeVector(0,-Placement,LongBitZ);
G4Transform3D LongBit2Transform = G4Transform3D(none, LowLongBit2);

//OtherLongBit1 transform
G4ThreeVector OLB1Displacement = G4ThreeVector(Placement+1*cm,0,LongBitZ);
G4Transform3D OLB1Transform = G4Transform3D(none, OLB1Displacement);

//OtherLongBit2 transform
G4ThreeVector OLB2Displacement = G4ThreeVector(-Placement-1*cm,0,LongBitZ);
G4Transform3D OLB2Transform = G4Transform3D(none, OLB2Displacement);
//front
G4ThreeVector FrontDisplacement = G4ThreeVector(1*mm,5*mm,-695.5*mm);
G4Transform3D FrontBitTransform = G4Transform3D(none, FrontDisplacement);

G4MultiUnion* LeadBox = new G4MultiUnion("LeadBox");

LeadBox->AddNode(*EndBit, EndBitTransform);
LeadBox->AddNode(*LongBit1, LongBit1Transform);
LeadBox->AddNode(*LongBit2, LongBit2Transform);
LeadBox->AddNode(*OtherLongBit1, OLB1Transform);
LeadBox->AddNode(*OtherLongBit2, OLB2Transform);
LeadBox->AddNode(*subtraction, FrontBitTransform);

LeadBox->Voxelize();

G4LogicalVolume *LeadBoxLogic = new G4LogicalVolume(LeadBox, boxMaterial, "LeadLogic");
				new G4PVPlacement(0, pos1, LeadBoxLogic, "PLeadBox", worldLV, 16, true, fCheckOverlaps);//add fCheckOverLaps


//Colour collimator
auto LeadBoxVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0));
LeadBoxVisAtt->SetVisibility(true);
LeadBoxLogic->SetVisAttributes(LeadBoxVisAtt);

				
//Now we make the plastic veto for charged particles

G4Box* Veto = new G4Box("Veto", 7*cm, 7*cm, 2.5*mm);
G4LogicalVolume *VetoLogic = new G4LogicalVolume(Veto, scintMaterial, "VetoLogic");
			     new G4PVPlacement(0, G4ThreeVector(0,5*mm, 693.5*mm), VetoLogic, "PVeto", worldLV, 17, true, fCheckOverlaps);
//873.5
auto VetoVisAtt= new G4VisAttributes(G4Colour(1.0,0.0,0.0));
VetoVisAtt->SetVisibility(true);
VetoLogic->SetVisAttributes(VetoVisAtt);


			     
G4Cons* LeadCone = new G4Cons("LeadCone", 138*mm, 260*mm, 187*mm, 260*mm, 73*mm, 0*deg, 360*deg);
G4LogicalVolume *LeadConeLogic = new G4LogicalVolume(LeadCone, boxMaterial, "LeadConeLogic");
                                 new G4PVPlacement(0, G4ThreeVector(0,0,1019.5*mm), LeadConeLogic, "PLeadCone", worldLV, 15, true, fCheckOverlaps);//G4ThreeVector(0,0,-390.5*mm), 1227.5, 1182.5
//1109.5	
 
auto LeadConeVisAtt= new G4VisAttributes(G4Colour(1.0,0.0,1.0));
LeadConeVisAtt->SetVisibility(true);
LeadConeLogic->SetVisAttributes(LeadConeVisAtt);				
				                                        
  // Visualization attributes
  //
  worldLV->SetVisAttributes (G4VisAttributes::GetInvisible());

  return worldPV;
}
//Main Construct ends here!
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cDetectorConstruction::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

  // 
  // Sensitive detectors
  //
  auto coreSD 
    = new B4cCalorimeterSD("CoreSD", "CoreHitsCollection", 1);
  G4SDManager::GetSDMpointer()->AddNewDetector(coreSD);		// consider making all of these the same sensitive detector, should increase mean energy of core
  SetSensitiveDetector("Core",coreSD);

  auto annuluspiece1SD
    = new B4cCalorimeterSD("AnnulusPiece1SD", "AnnulusPiece1HitsCollection", 1);
  G4SDManager::GetSDMpointer()->AddNewDetector(annuluspiece1SD);
  SetSensitiveDetector("AnnulusPiece1",annuluspiece1SD);

  auto annuluspiece2SD 
    = new B4cCalorimeterSD("AnnulusPiece2SD", "AnnulusPiece2HitsCollection", 1);
  G4SDManager::GetSDMpointer()->AddNewDetector(annuluspiece2SD);
  SetSensitiveDetector("AnnulusPiece2",annuluspiece2SD);

  auto annuluspiece3SD
    = new B4cCalorimeterSD("AnnulusPiece3SD", "AnnulusPiece3HitsCollection", 1);
  G4SDManager::GetSDMpointer()->AddNewDetector(annuluspiece3SD);
  SetSensitiveDetector("AnnulusPiece3",annuluspiece3SD);

  auto annuluspiece4SD
    = new B4cCalorimeterSD("AnnulusPiece4SD", "AnnulusPiece4HitsCollection", 1);
  G4SDManager::GetSDMpointer()->AddNewDetector(annuluspiece4SD);
  SetSensitiveDetector("AnnulusPiece4",annuluspiece4SD);

  auto annuluspiece5SD
    = new B4cCalorimeterSD("AnnulusPiece5SD", "AnnulusPiece5HitsCollection", 1);
  G4SDManager::GetSDMpointer()->AddNewDetector(annuluspiece5SD);
  SetSensitiveDetector("AnnulusPiece5",annuluspiece5SD);

  auto annuluspiece6SD
    = new B4cCalorimeterSD("AnnulusPiece6SD", "AnnulusPiece6HitsCollection", 1);
  G4SDManager::GetSDMpointer()->AddNewDetector(annuluspiece6SD);
  SetSensitiveDetector("AnnulusPiece6",annuluspiece6SD);


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
