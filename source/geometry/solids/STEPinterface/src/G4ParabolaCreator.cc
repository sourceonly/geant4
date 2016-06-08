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
// $Id: G4ParabolaCreator.cc,v 1.3 2001/07/11 10:00:11 gunter Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
// 
// ----------------------------------------------------------------------
// Class G4ParabolaCreator
//
// Authors: J.Sulkimo, P.Urban.
// Revisions by: L.Broglia, G.Cosmo.
//
// History:
//   18-Nov-1999: First step of re-engineering - G.Cosmo
// ----------------------------------------------------------------------

#include "G4ParabolaCreator.hh"
#include "G4GeometryTable.hh"

G4ParabolaCreator G4ParabolaCreator::csc;

G4ParabolaCreator::G4ParabolaCreator()
{
  G4GeometryTable::RegisterObject(this);
}

G4ParabolaCreator::~G4ParabolaCreator() {}

void G4ParabolaCreator::CreateG4Geometry(STEPentity& Ent)
{
  G4double focal_dist;
  
  // L. Broglia
  // G4Placement* place;
  G4Axis2Placement3D* place;

  Ent.ResetAttributes();
  STEPattribute* Attr = Ent.NextAttribute();
  while(Attr->NonRefType() == STRING_TYPE ||
	Attr->NonRefType() == sdaiSTRING )
    Attr = Ent.NextAttribute();	

  // Get the placement
    STEPentity* TmpEnt= *Attr->ptr.c;
  void *tmp =G4GeometryTable::CreateObject(*TmpEnt);

  // L. Broglia
  // place = (G4Placement*)tmp;
  place = (G4Axis2Placement3D*)tmp;
  
  // get semi axises
  Attr = Ent.NextAttribute();
  focal_dist = *Attr->ptr.r;

}

void G4ParabolaCreator::CreateSTEPGeometry(void* G4obj)
{
}