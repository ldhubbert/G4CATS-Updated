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
/// \file B4cEventAction.cc
/// \brief Implementation of the B4cEventAction class

#include "B4cEventAction.hh"
#include "B4cCalorimeterSD.hh"
#include "B4cCalorHit.hh"
#include "B4Analysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cEventAction::B4cEventAction()
 : G4UserEventAction(),
   fCoreHCID(-1),
   fAnn1HCID(-1),
   fAnn2HCID(-1),
   fAnn3HCID(-1),
   fAnn4HCID(-1),
   fAnn5HCID(-1),
   fAnn6HCID(-1)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cEventAction::~B4cEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cCalorHitsCollection* 
B4cEventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const

{
  B4cCalorHitsCollection* hitsCollection 
    = static_cast<B4cCalorHitsCollection*>(
        event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("B4cEventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }         

  return hitsCollection;
}    


void B4cEventAction::PrintEventStatistics(
                              G4double coreEdep, G4double coreTrackLength,
			      G4double ann2Edep,
			      G4double ann3Edep,
			      G4double ann4Edep,
			      G4double ann5Edep,
			      G4double ann6Edep,
                              G4double ann1Edep, G4double ann1TrackLength) const
{
  // print event statistics
  G4cout
     << "   Core: total energy: " 
     << std::setw(1) << G4BestUnit(coreEdep, "Energy")
     << "       total track length: " 
     << std::setw(1) << G4BestUnit(coreTrackLength, "Length")
     << G4endl
     << "        Annulus Piece 1: total energy: " 
     << std::setw(2) << G4BestUnit(ann1Edep, "Energy")
     << "       total track length: " 
     << std::setw(2) << G4BestUnit(ann1TrackLength, "Length")
     << "        Annulus Piece 2: total energy: "
     << std::setw(3) << G4BestUnit(ann2Edep, "Energy")
     << "        Annulus Piece 3: total energy: "
     << std::setw(4) << G4BestUnit(ann3Edep, "Energy")
     << "        Annulus Piece 4: total energy: "
     << std::setw(5) << G4BestUnit(ann4Edep, "Energy")     
     << "        Annulus Piece 5: total energy: "
     << std::setw(6) << G4BestUnit(ann5Edep, "Energy")     
     << "        Annulus Piece 6: total energy: "
     << std::setw(7) << G4BestUnit(ann6Edep, "Energy")
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cEventAction::BeginOfEventAction(const G4Event* /*event*/)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cEventAction::EndOfEventAction(const G4Event* event)
{  
  // Get hits collections IDs (only once)
  if ( fCoreHCID == -1 ) {
    fCoreHCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("CoreHitsCollection");
    fAnn1HCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("AnnulusPiece1HitsCollection");//was: CoreHitsCollection
    fAnn2HCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("AnnulusPiece2HitsCollection");
    fAnn3HCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("AnnulusPiece3HitsCollection"); 
    fAnn4HCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("AnnulusPiece4HitsCollection");
    fAnn5HCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("AnnulusPiece5HitsCollection");
    fAnn6HCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("AnnulusPiece6HitsCollection");
  }

  // Get hits collections
  auto CoreHC = GetHitsCollection(fCoreHCID, event);
  auto Ann1HC = GetHitsCollection(fAnn1HCID, event);
  auto Ann2HC = GetHitsCollection(fAnn2HCID, event);
  auto Ann3HC = GetHitsCollection(fAnn3HCID, event);
  auto Ann4HC = GetHitsCollection(fAnn4HCID, event);
  auto Ann5HC = GetHitsCollection(fAnn5HCID, event);
  auto Ann6HC = GetHitsCollection(fAnn6HCID, event);
  // Get hit with total values
  auto CoreHit = (*CoreHC)[CoreHC->entries()-1];
  auto Ann1Hit = (*Ann1HC)[Ann1HC->entries()-1];
  auto Ann2Hit = (*Ann2HC)[Ann2HC->entries()-1];
  auto Ann3Hit = (*Ann3HC)[Ann3HC->entries()-1];
  auto Ann4Hit = (*Ann4HC)[Ann4HC->entries()-1];
  auto Ann5Hit = (*Ann5HC)[Ann5HC->entries()-1];
  auto Ann6Hit = (*Ann6HC)[Ann6HC->entries()-1];
  // Print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    G4cout << "---> End of event: " << eventID << G4endl;     

    PrintEventStatistics(
      CoreHit->GetEdep(), CoreHit->GetTrackLength(),
      Ann2Hit->GetEdep(),
      Ann3Hit->GetEdep(),
      Ann4Hit->GetEdep(),
      Ann5Hit->GetEdep(),
      Ann6Hit->GetEdep(),
      Ann1Hit->GetEdep(), Ann1Hit->GetTrackLength());
 
      }  
  
  // Fill histograms, ntuple
  //

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
 
  // fill histograms
  analysisManager->FillH1(0, CoreHit->GetEdep());
  analysisManager->FillH1(1, Ann1Hit->GetEdep());
  analysisManager->FillH1(2, CoreHit->GetTrackLength());
  analysisManager->FillH1(3, Ann1Hit->GetTrackLength());

  analysisManager->FillH1(4, Ann2Hit->GetEdep());
  analysisManager->FillH1(5, Ann3Hit->GetEdep());
  analysisManager->FillH1(6, Ann4Hit->GetEdep());
  analysisManager->FillH1(7, Ann5Hit->GetEdep());
  analysisManager->FillH1(8, Ann6Hit->GetEdep());
  
  // fill ntuple
  analysisManager->FillNtupleDColumn(0, CoreHit->GetEdep());
  analysisManager->FillNtupleDColumn(1, Ann1Hit->GetEdep());
  analysisManager->FillNtupleDColumn(2, CoreHit->GetTrackLength());
  analysisManager->FillNtupleDColumn(3, Ann1Hit->GetTrackLength());
  
  analysisManager->FillNtupleDColumn(4, Ann2Hit->GetEdep());
  analysisManager->FillNtupleDColumn(5, Ann3Hit->GetEdep());
  analysisManager->FillNtupleDColumn(6, Ann4Hit->GetEdep());
  analysisManager->FillNtupleDColumn(7, Ann5Hit->GetEdep());
  analysisManager->FillNtupleDColumn(8, Ann6Hit->GetEdep());
  
  analysisManager->AddNtupleRow();  
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
