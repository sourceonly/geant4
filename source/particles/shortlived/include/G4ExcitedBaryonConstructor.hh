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
//
// $Id: G4ExcitedBaryonConstructor.hh,v 1.5 2001/07/11 10:02:05 gunter Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
// 
// --------------------------------------------------------------
//	GEANT 4 class implementation file 
//
//      History: first implementation, based on object model of
//      10 oct 1998  H.Kurashige
// ---------------------------------------------------------------
#ifndef G4ExcitedBaryonConstructor_h
#define G4ExcitedBaryonConstructor_h 1

#include "globals.hh"
#include "G4ios.hh"
class     G4DecayTable;

class G4ExcitedBaryonConstructor
{
  //This class is a utility class for construction 
  //short lived particles

  public:
    G4ExcitedBaryonConstructor(G4int nStates = 0, G4int isoSpin=0);
    virtual  ~G4ExcitedBaryonConstructor();
  
  public:
    virtual  void Construct(G4int indexOfState = -1);
 
  protected:
    virtual  void ConstructParticle(G4int indexOfState);
    virtual  void ConstructAntiParticle(G4int indexOfState);
    
    
    virtual  G4double GetCharge(G4int iIsoSpin3);
    virtual  G4int    GetEncoding(G4int iIsoSpin3, G4int idxState);

  protected:
    G4int NumberOfStates;
    G4int iIsoSpin;

    const G4String type;
    const G4int    iConjugation;
    const G4int    iGParity;
    const G4int    leptonNumber;
    const G4int    baryonNumber;

    // following methods are pure virtual
    // thes methods should be implemented in derived classes
    virtual  G4bool   Exist( G4int ) = 0;
    virtual  G4int    GetQuarkContents(G4int, G4int)=0;
    virtual  G4String GetName(G4int, G4int )=0;
    virtual  G4String GetMultipletName(G4int)=0;
    virtual  G4double GetMass( G4int )=0;
    virtual  G4double GetWidth( G4int )=0;
    virtual  G4int    GetiSpin( G4int )=0;
    virtual  G4int    GetiParity( G4int )=0;
    virtual  G4int    GetEncodingOffset( G4int )=0;
    virtual  G4DecayTable* CreateDecayTable(const G4String&,
					    G4int , G4int, G4bool)=0;
};

#endif











