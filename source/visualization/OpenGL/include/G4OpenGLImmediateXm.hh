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
// $Id: G4OpenGLImmediateXm.hh,v 1.6 2001/07/11 10:08:49 gunter Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
// 
// Andrew Walkden  10th February 1997
// OpenGL graphics system factory.

#if defined (G4VIS_BUILD_OPENGLXM_DRIVER) || defined (G4VIS_USE_OPENGLXM)

#ifndef G4OPENGLIMMEDIATEXM_HH
#define G4OPENGLIMMEDIATEXM_HH

#include "G4VGraphicsSystem.hh"

class G4OpenGLImmediateXm: public G4VGraphicsSystem {
public:
  G4OpenGLImmediateXm ();
  virtual ~G4OpenGLImmediateXm ();
  G4VSceneHandler* CreateSceneHandler (const G4String& name = "");
  G4VViewer*  CreateViewer  (G4VSceneHandler&, const G4String& name = "");
};

#endif

#endif