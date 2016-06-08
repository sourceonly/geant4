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
// $Id: G4VLevelDensityParameter.cc,v 1.5 2001/08/01 17:05:37 hpw Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
// Hadronic Process: Nuclear De-excitations
// by V. Lara (Oct 1998)
//


#include "G4VLevelDensityParameter.hh"


G4VLevelDensityParameter::
G4VLevelDensityParameter(const G4VLevelDensityParameter &right)
{
    G4Exception("G4VLevelDensityParameter::copy_constructor meant to not be accessable");
}




const G4VLevelDensityParameter & G4VLevelDensityParameter::
operator=(const G4VLevelDensityParameter &right)
{
    G4Exception("G4VLevelDensityParameter::operator= meant to not be accessable");
    return *this;
}


G4bool G4VLevelDensityParameter::
operator==(const G4VLevelDensityParameter &right) const
{
    return false;
}

G4bool G4VLevelDensityParameter::
operator!=(const G4VLevelDensityParameter &right) const
{
    return true;
}




