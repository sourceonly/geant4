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
// $Id: G4Sort.hh,v 1.4 2001/07/11 09:59:38 gunter Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
// ----------------------------------------------------------------------
//
// Global functions for sorting and swaping arrays of various
// kinds of numbers.

// Author:  Alan Breakstone
// ----------------------------------------------------------------------
#ifndef __SORT_H
#define __SORT_H

#include "globals.hh"

void sort_double( G4double [], G4int, G4int );

void swap_double( G4double [], G4int, G4int );

#endif