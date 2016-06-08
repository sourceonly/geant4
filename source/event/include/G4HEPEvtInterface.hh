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
// $Id: G4HEPEvtInterface.hh,v 1.6 2001/07/11 09:58:48 gunter Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//

#ifndef G4HEPEvtInterface_h
#define G4HEPEvtInterface_h 1

#include "g4std/fstream"
#include "g4std/vector"
#include "globals.hh"
#include "G4VPrimaryGenerator.hh"
#include "G4HEPEvtParticle.hh"

class G4PrimaryVertex;
class G4Event;

// class description:
//
//  This is a concrete class of G4VPrimaryGenerator.
//  This class object reads an ASCII file which contains particles generated
// by a physics generator which supports /HEPEVT/ common block.
// 
//  The format of ASCII file must be equivalent to the follwing sample fortran
// code.
//***********************************************************
//      SUBROUTINE HEP2G4
//*
//* Output /HEPEVT/ event structure to G4HEPEvtInterface
//*
//***********************************************************
//      PARAMETER (NMXHEP=2000)
//      COMMON/HEPEVT/NEVHEP,NHEP,ISTHEP(NMXHEP),IDHEP(NMXHEP),
//     >JMOHEP(2,NMXHEP),JDAHEP(2,NMXHEP),PHEP(5,NMXHEP),VHEP(4,NMXHEP)
//      DOUBLE PRECISION PHEP,VHEP
//*
//      WRITE(6,*) NHEP
//      DO IHEP=1,NHEP
//       WRITE(6,10) 
//     >  ISTHEP(IHEP),IDHEP(IHEP),JDAHEP(1,IHEP),JDAHEP(2,IHEP),
//     >  PHEP(1,IHEP),PHEP(2,IHEP),PHEP(3,IHEP),PHEP(5,IHEP)
//10    FORMAT(4I5,4(1X,D15.8))
//      ENDDO
//*
//      RETURN
//      END
//
//  The position and time of the primary interaction must be set by the corresponding
// set methods of G4VPrimaryGenerator base class, otherwise zero will be set.
//

class G4HEPEvtInterface:public G4VPrimaryGenerator
{
  public: // with description
    G4HEPEvtInterface(char* evfile);
    G4HEPEvtInterface(G4String evfile);
    // Constructors, "evfile" is the file name (with directory path).
  
  public:
    ~G4HEPEvtInterface();

    void GeneratePrimaryVertex(G4Event* evt);

  private:
    G4String fileName;
    G4std::ifstream inputFile;
    G4std::vector<G4HEPEvtParticle*> HPlist;
};

#endif
