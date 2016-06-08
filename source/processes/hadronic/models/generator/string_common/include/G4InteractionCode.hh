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
// $Id: G4InteractionCode.hh,v 1.4 2001/08/01 17:08:58 hpw Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
#ifndef G4InteractionCode_h
#define G4InteractionCode_h 1


class G4InteractionCode
{

  public:
    G4InteractionCode(G4String & aCode);

    void SetCode(G4String & aCode);
    G4String GetCode();

  private:

    G4String theCode;
};

inline void G4InteractionCode::SetCode(G4String & aCode)
{
  theCode = aCode;
}

inline G4String G4InteractionCode::GetCode()
{
  return theCode;
}

#endif