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
// * authors in the GEANT4 collaboration.                             *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: G4StopDummyDeexcitation.cc,v 1.7 2001/10/04 20:00:43 hpw Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
// -------------------------------------------------------------------
//      GEANT 4 class file --- Copyright CERN 1998
//      CERN Geneva Switzerland
//
//
//      File name:     G4StopDummyDeexcitation
//
//      Author:        Maria Grazia Pia (pia@genova.infn.it)
// 
//      Creation date: 8 May 1998
//
//      Modifications: 
// -------------------------------------------------------------------

#include "G4ios.hh"

#include "G4StopDummyDeexcitation.hh"

#include "globals.hh"
#include "G4DynamicParticleVector.hh"
#include "G4ThreeVector.hh"

// Constructor

G4StopDummyDeexcitation::G4StopDummyDeexcitation()
  
{}


// Destructor

G4StopDummyDeexcitation::~G4StopDummyDeexcitation()
{
}

G4ReactionProductVector* G4StopDummyDeexcitation::BreakUp(G4double A, G4double Z, 
							 G4double excitation, 
							 const G4ThreeVector& p)
{
  return 0;
}


