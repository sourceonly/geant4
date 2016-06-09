//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
// $Id: G4ComptonScattering52.cc,v 1.1 2005/05/04 16:16:12 vnivanch Exp $
// GEANT4 tag $Name: geant4-07-01 $
//
// 
//------------ G4ComptonScattering52 physics process -----------------------------
//                   by Michel Maire, April 1996
//
// 28-05-96, DoIt() small change in ElecDirection, by M.Maire
// 10-06-96, simplification in ComputeMicroscopicCrossSection(), by M.Maire
// 21-06-96, SetCuts implementation, M.Maire
// 13-09-96, small changes in DoIt for better efficiency. Thanks to P.Urban
// 06-01-97, crossection table + meanfreepath table, M.Maire
// 05-03-97, new Physics scheme, M.Maire
// 28-03-97, protection in BuildPhysicsTable, M.Maire
// 07-04-98, remove 'tracking cut' of the scattered gamma, MMa
// 04-06-98, in DoIt, secondary production condition:
//                                     range>std::min(threshold,safety)
// 13-08-98, new methods SetBining()  PrintInfo()
// 15-12-98, cross section=0 below 10 keV
// 28-05-01, V.Ivanchenko minor changes to provide ANSI -wall compilation
// 13-07-01, DoIt: suppression of production cut for the electron (mma)
// 03-08-01, new methods Store/Retrieve PhysicsTable (mma)
// 06-08-01, BuildThePhysicsTable() called from constructor (mma)
// 17-09-01, migration of Materials to pure STL (mma)
// 20-09-01, DoIt: fminimalEnergy = 1*eV (mma)
// 01-10-01, come back to BuildPhysicsTable(const G4ParticleDefinition&)
// 17-04-02, LowestEnergyLimit = 1*keV     
// 26-05-04, cross section parametrization improved for low energy :
//           Egamma <~ 15 keV (Laszlo) 
// 08-11-04, Remove Store/Retrieve tables (V.Ivanchenko)
// 04-05-05, Add 52 to class name (V.Ivanchenko)
// -----------------------------------------------------------------------------

#include "G4ComptonScattering52.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicsTableHelper.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

using namespace std;

G4ComptonScattering52::G4ComptonScattering52(const G4String& processName,
    G4ProcessType type):G4VDiscreteProcess (processName, type),
    theCrossSectionTable(NULL),
    theMeanFreePathTable(NULL),
    LowestEnergyLimit (  1*keV),
    HighestEnergyLimit(100*GeV),
    NumbBinTable(80),
    fminimalEnergy(1*eV)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
// destructor
 
G4ComptonScattering52::~G4ComptonScattering52()
{
   if (theCrossSectionTable) {
      theCrossSectionTable->clearAndDestroy();
      delete theCrossSectionTable;
   }

   if (theMeanFreePathTable) {
      theMeanFreePathTable->clearAndDestroy();
      delete theMeanFreePathTable;
   }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool G4ComptonScattering52::IsApplicable( const G4ParticleDefinition& particle)
{
   return ( &particle == G4Gamma::Gamma() ); 
}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4ComptonScattering52::SetPhysicsTableBining(
                                   G4double lowE, G4double highE, G4int nBins)
{
  LowestEnergyLimit = lowE; HighestEnergyLimit = highE; NumbBinTable = nBins;
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void G4ComptonScattering52::BuildPhysicsTable(const G4ParticleDefinition&)
// Build cross section and mean free path tables
{
   G4double LowEdgeEnergy, Value;
   G4PhysicsLogVector* ptrVector;

// Build cross section per atom tables for the Compton Scattering process

   if (theCrossSectionTable) {
       theCrossSectionTable->clearAndDestroy(); delete theCrossSectionTable;}

   theCrossSectionTable = new G4PhysicsTable(G4Element::GetNumberOfElements());
   const G4ElementTable* theElementTable = G4Element::GetElementTable();
   G4double AtomicNumber;
   size_t J;

   for ( J=0 ; J < G4Element::GetNumberOfElements(); J++ )
       {
        //create physics vector then fill it ....
        ptrVector = new G4PhysicsLogVector(LowestEnergyLimit,HighestEnergyLimit,
                                           NumbBinTable );
        AtomicNumber = (*theElementTable)[J]->GetZ();

        for ( G4int i = 0 ; i < NumbBinTable ; i++ )
           {
             LowEdgeEnergy = ptrVector->GetLowEdgeEnergy(i);
             Value = ComputeCrossSectionPerAtom(LowEdgeEnergy, AtomicNumber);
             ptrVector->PutValue(i,Value);
           }

        theCrossSectionTable->insertAt( J , ptrVector ) ;

      }

// Build mean free path table for the Compton Scattering process

   if (theMeanFreePathTable) {
       theMeanFreePathTable->clearAndDestroy(); delete theMeanFreePathTable;}
 
   theMeanFreePathTable= new G4PhysicsTable(G4Material::GetNumberOfMaterials());
   const G4MaterialTable* theMaterialTable = G4Material::GetMaterialTable();
   G4Material* material;

   for ( J=0 ; J < G4Material::GetNumberOfMaterials(); J++ )  
       { 
        //create physics vector then fill it ....
        ptrVector = new G4PhysicsLogVector(LowestEnergyLimit,HighestEnergyLimit,
                                           NumbBinTable ) ;
        material = (*theMaterialTable)[J];

        for ( G4int i = 0 ; i < NumbBinTable ; i++ )      
           {
             LowEdgeEnergy = ptrVector->GetLowEdgeEnergy( i ) ;
             Value = ComputeMeanFreePath( LowEdgeEnergy, material);  
             ptrVector->PutValue( i , Value ) ;
           }

        theMeanFreePathTable->insertAt( J , ptrVector ) ;
      }

    PrintInfoDefinition();  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double G4ComptonScattering52::ComputeCrossSectionPerAtom
                              (G4double GammaEnergy, G4double Z)
 
// Calculates the cross section per atom in GEANT4 internal units.
// A parametrized formula from L. Urban is used to estimate
// the total cross section.
// It gives a good description of the data from 10 keV to 100/Z GeV.
// lower limit 1 keV now with a correction for low energy 
 
{
 G4double CrossSection = 0.0 ;
 if ( Z < 1. )                     return CrossSection;
 if ( GammaEnergy < 1.*keV       ) return CrossSection;
 if ( GammaEnergy > (100.*GeV/Z) ) return CrossSection;

 static const G4double a = 20.0 , b = 230.0 , c = 440.0;
  
 static const G4double
 d1= 2.7965e-1*barn, d2=-1.8300e-1*barn, d3= 6.7527   *barn, d4=-1.9798e+1*barn,
 e1= 1.9756e-5*barn, e2=-1.0205e-2*barn, e3=-7.3913e-2*barn, e4= 2.7079e-2*barn,
 f1=-3.9178e-7*barn, f2= 6.8241e-5*barn, f3= 6.0480e-5*barn, f4= 3.0274e-4*barn;
     
 G4double p1Z = Z*(d1 + e1*Z + f1*Z*Z), p2Z = Z*(d2 + e2*Z + f2*Z*Z),
          p3Z = Z*(d3 + e3*Z + f3*Z*Z), p4Z = Z*(d4 + e4*Z + f4*Z*Z);

 G4double T0 = 15*keV; if (Z == 1.) T0 = 40*keV; 

 G4double X = max(GammaEnergy, T0) / electron_mass_c2;
 CrossSection = p1Z*log(1.+2*X)/X
                + (p2Z + p3Z*X + p4Z*X*X)/(1. + a*X + b*X*X + c*X*X*X);
		
 //  modification for low energy. (special case for Hydrogen)
 if (GammaEnergy < T0) {
   G4double dT0 = 1.*keV;
   X = (T0+dT0) / electron_mass_c2 ;
   G4double sigma = p1Z*log(1.+2*X)/X
                    + (p2Z + p3Z*X + p4Z*X*X)/(1. + a*X + b*X*X + c*X*X*X);
   G4double c1 = -T0*(sigma-CrossSection)/(CrossSection*dT0);             
   G4double c2 = 0.150; if (Z > 1.) c2 = 0.375-0.0556*log(Z);
   G4double  y = log(GammaEnergy/T0);
   CrossSection *= exp(-y*(c1+c2*y));          
   }

 return CrossSection;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double G4ComptonScattering52::ComputeMeanFreePath(G4double GammaEnergy,
                                                         G4Material* aMaterial)

// returns the gamma mean free path in GEANT4 internal units

{
  const G4ElementVector* theElementVector = aMaterial->GetElementVector() ;
  const G4double* NbOfAtomsPerVolume = aMaterial->GetVecNbOfAtomsPerVolume();

  G4double SIGMA = 0.;

  for ( size_t elm=0 ; elm < aMaterial->GetNumberOfElements() ; elm++ )
      {
        SIGMA += NbOfAtomsPerVolume[elm] * 
                 ComputeCrossSectionPerAtom(GammaEnergy,
                                            (*theElementVector)[elm]->GetZ());
      }       
  return SIGMA > DBL_MIN ? 1./SIGMA : DBL_MAX;
}

 //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double G4ComptonScattering52::GetCrossSectionPerAtom(
                                 G4DynamicParticle* aDynamicGamma,
                                 G4Element*         anElement)
 
// gives the microscopic total cross section in GEANT4 internal units

{
   G4double crossSection;
   G4double GammaEnergy = aDynamicGamma->GetKineticEnergy();
   G4bool isOutRange ;
   if (GammaEnergy < LowestEnergyLimit || GammaEnergy > HighestEnergyLimit)
      crossSection = 0.;
   else
      crossSection = (*theCrossSectionTable)(anElement->GetIndex())->
                                       GetValue(GammaEnergy, isOutRange);

   return crossSection;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4double G4ComptonScattering52::GetMeanFreePath(const G4Track& aTrack,
                                              G4double,
                                              G4ForceCondition*)

// returns the gamma mean free path in GEANT4 internal units

{
   const G4DynamicParticle* aDynamicGamma = aTrack.GetDynamicParticle();
   G4double GammaEnergy = aDynamicGamma->GetKineticEnergy();
   G4Material* aMaterial = aTrack.GetMaterial();

   G4double MeanFreePath;
   G4bool isOutRange;

   if (GammaEnergy > HighestEnergyLimit || GammaEnergy < LowestEnergyLimit)
     MeanFreePath = DBL_MAX;
   else
     MeanFreePath = (*theMeanFreePathTable)(aMaterial->GetIndex())->
                                       GetValue(GammaEnergy, isOutRange);
   return MeanFreePath;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VParticleChange* G4ComptonScattering52::PostStepDoIt(const G4Track& aTrack,
                                                     const G4Step&  aStep)
//
// The scattered gamma energy is sampled according to Klein - Nishina formula.
// The random number techniques of Butcher & Messel are used 
// (Nuc Phys 20(1960),15).
// GEANT4 internal units
//
// Note : Effects due to binding of atomic electrons are negliged.
 
{
   aParticleChange.Initialize(aTrack);

   const G4DynamicParticle* aDynamicGamma = aTrack.GetDynamicParticle();
   G4double GammaEnergy0 = aDynamicGamma->GetKineticEnergy();
   G4double E0_m = GammaEnergy0 / electron_mass_c2 ;

   G4ParticleMomentum GammaDirection0 = aDynamicGamma->GetMomentumDirection();

   //
   // sample the energy rate of the scattered gamma 
   //

   G4double epsilon, epsilonsq, onecost, sint2, greject ;

   G4double epsilon0 = 1./(1. + 2*E0_m) , epsilon0sq = epsilon0*epsilon0;
   G4double alpha1   = - log(epsilon0)  , alpha2 = 0.5*(1.- epsilon0sq);

   do {
       if ( alpha1/(alpha1+alpha2) > G4UniformRand() )
            { epsilon   = exp(-alpha1*G4UniformRand());   // epsilon0**r
              epsilonsq = epsilon*epsilon; }
       else {
             epsilonsq = epsilon0sq + (1.- epsilon0sq)*G4UniformRand();
             epsilon   = sqrt(epsilonsq);
       };
       onecost = (1.- epsilon)/(epsilon*E0_m);
       sint2   = onecost*(2.-onecost);
       greject = 1. - epsilon*sint2/(1.+ epsilonsq);
   } while (greject < G4UniformRand());
 
   //
   // scattered gamma angles. ( Z - axis along the parent gamma)
   //

   G4double cosTeta = 1. - onecost , sinTeta = sqrt (sint2);
   G4double Phi     = twopi * G4UniformRand();
   G4double dirx = sinTeta*cos(Phi), diry = sinTeta*sin(Phi), dirz = cosTeta;

   //
   // update G4VParticleChange for the scattered gamma
   //
   
   G4ThreeVector GammaDirection1 ( dirx,diry,dirz );
   GammaDirection1.rotateUz(GammaDirection0);
   aParticleChange.ProposeMomentumDirection( GammaDirection1 );
   G4double GammaEnergy1 = epsilon*GammaEnergy0;
   G4double localEnergyDeposit = 0.;
   
   if (GammaEnergy1 > fminimalEnergy)
     {
       aParticleChange.ProposeEnergy( GammaEnergy1 );
     }
   else
     {
       localEnergyDeposit += GammaEnergy1;    
       aParticleChange.ProposeEnergy(0.) ;
       aParticleChange.ProposeTrackStatus(fStopAndKill);
     }
       
   //
   // kinematic of the scattered electron
   //

   G4double ElecKineEnergy = GammaEnergy0 - GammaEnergy1;

    if (ElecKineEnergy > fminimalEnergy)	
      {
        G4double ElecMomentum = sqrt(ElecKineEnergy*
	                            (ElecKineEnergy+2.*electron_mass_c2));
        G4ThreeVector ElecDirection (
        (GammaEnergy0*GammaDirection0 - GammaEnergy1*GammaDirection1)
	*(1./ElecMomentum) );

        // create G4DynamicParticle object for the electron.
        G4DynamicParticle* aElectron= new G4DynamicParticle(
	                   G4Electron::Electron(),ElecDirection,ElecKineEnergy);

        aParticleChange.SetNumberOfSecondaries(1);
        aParticleChange.AddSecondary( aElectron );
      }
    else
      {
        aParticleChange.SetNumberOfSecondaries(0);
	localEnergyDeposit += ElecKineEnergy;
      }
    aParticleChange.ProposeLocalEnergyDeposit (localEnergyDeposit);

   //  Reset NbOfInteractionLengthLeft and return aParticleChange
   return G4VDiscreteProcess::PostStepDoIt( aTrack, aStep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool G4ComptonScattering52::StorePhysicsTable(const G4ParticleDefinition* particle,
				              const G4String& directory,
				                    G4bool          ascii)
{
  G4String filename;

  // store cross section table
  filename = GetPhysicsTableFileName(particle,directory,"CrossSection",ascii);
  if ( !theCrossSectionTable->StorePhysicsTable(filename, ascii) ){
    G4cout << " FAIL theCrossSectionTable->StorePhysicsTable in " << filename
           << G4endl;
    return false;
  }

  // store mean free path table
  filename = GetPhysicsTableFileName(particle,directory,"MeanFreePath",ascii);
  if ( !theMeanFreePathTable->StorePhysicsTable(filename, ascii) ){
    G4cout << " FAIL theMeanFreePathTable->StorePhysicsTable in " << filename
           << G4endl;
    return false;
  }

  G4cout << GetProcessName() << " for " << particle->GetParticleName()
         << ": Success to store the PhysicsTables in "
         << directory << G4endl;
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
G4bool G4ComptonScattering52::RetrievePhysicsTable(const G4ParticleDefinition* particle,
					         const G4String& directory,
				                 G4bool          ascii)
{
  // delete theCrossSectionTable and theMeanFreePathTable
  if (theCrossSectionTable != 0) {
    theCrossSectionTable->clearAndDestroy();
    delete theCrossSectionTable;
  }
  if (theMeanFreePathTable != 0) {
    theMeanFreePathTable->clearAndDestroy();
    delete theMeanFreePathTable;
  }

  G4String filename;

  // retreive cross section table
  filename = GetPhysicsTableFileName(particle,directory,"CrossSection",ascii);
  theCrossSectionTable = new G4PhysicsTable(G4Element::GetNumberOfElements());
  if ( !G4PhysicsTableHelper::RetrievePhysicsTable(filename, ascii) ){
    G4cout << " FAIL theCrossSectionTable->RetrievePhysicsTable in " << filename
           << G4endl;
    return false;
  }

  // retreive mean free path table
  filename = GetPhysicsTableFileName(particle,directory,"MeanFreePath",ascii);
  theMeanFreePathTable = new G4PhysicsTable(G4Material::GetNumberOfMaterials());
  if ( !G4PhysicsTableHelper::RetrievePhysicsTable(filename, ascii) ){
    G4cout << " FAIL theMeanFreePathTable->RetrievePhysicsTable in " << filename
           << G4endl;
    return false;
  }

  G4cout << GetProcessName() << " for " << particle->GetParticleName()
         << ": Success to retrieve the PhysicsTables from "
         << directory << G4endl;
  return true;
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4ComptonScattering52::PrintInfoDefinition()
{
  G4String comments = "Total cross sections from a parametrisation. ";
           comments += "Good description from 10 KeV to (100/Z) GeV. \n";
           comments += "       Scattered gamma energy according Klein-Nishina.";
                     
  G4cout << G4endl << GetProcessName() << ":  " << comments
         << "\n        PhysicsTables from "
	           << G4BestUnit(LowestEnergyLimit,"Energy")
         << " to " << G4BestUnit(HighestEnergyLimit,"Energy") 
         << " in " << NumbBinTable << " bins. \n";
}         

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......