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
// $Id: G4ProcessVector.hh,v 1.8 2001/09/19 10:54:47 kurasige Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
// 
// ------------------------------------------------------------
//	GEANT 4 class header file 
//
// Class Description
//  This class is a container for pointers to physics process objects.
// ------------------------------------------------------------

#ifndef G4ProcessVector_h
#define G4ProcessVector_h 1

#include "globals.hh"
#include "G4ios.hh"
#include "g4std/vector"

class G4VProcess;

class G4ProcessVector 
{
  public:
    //  Constructors
    G4ProcessVector(size_t dummy=0);
    G4ProcessVector(const G4ProcessVector &);

    //  Destructor.
    virtual ~G4ProcessVector();

    //assignment operator
    G4ProcessVector & operator=(G4ProcessVector &right);
 
    // equal operator
    G4bool operator==(const G4ProcessVector &right) const;

  public: // With Description
    // Returns the number of items
    G4int entries() const;
    G4int length() const;
    G4int size() const;
    
    // Returns the position of the element
    G4int index(G4VProcess* aProcess) const;
 
    // Returns "true" if the element exists
    G4bool contains(G4VProcess* aProcess) const;

    // Insert an element
    G4bool insert(G4VProcess* aProcess);

    // Insert an element at i-th position
    G4bool insertAt(G4int i, G4VProcess* aProcess);
    
    // Remove and returns the i-th element
    G4VProcess* removeAt(G4int i);

    // Remove and returns the last element
    G4VProcess* removeLast();
    
    // Clear the collection by removing all items
    void clear();
    
    // returns const reference to the i-th item
    G4VProcess* const& operator[](G4int i) const;
    G4VProcess* const& operator()(G4int i) const;

    // returns  reference to the i-th item
    G4VProcess* & operator[](G4int i);
    G4VProcess* & operator()(G4int i);

  protected:
    // Use STL Vector 
    typedef G4std::vector<G4VProcess*> G4ProcVector;

    G4ProcVector * pProcVector;
};

#include "G4ProcessVector.icc"

#endif
















