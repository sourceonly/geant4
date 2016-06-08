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
// $Id: G4Fragment.hh,v 1.13 2002/06/07 15:30:55 jwellisc Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
// Hadronic Process: Nuclear De-excitations
// by V. Lara (May 1998)

#ifndef G4Fragment_h
#define G4Fragment_h 1

#include "G4ios.hh"
#include "g4std/iomanip"
#include "g4std/vector"

#include "globals.hh"
#include "G4LorentzVector.hh"
#include "G4ParticleMomentum.hh"
#include "G4ThreeVector.hh"
#include "G4NucleiProperties.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "Randomize.hh"
#include "G4Proton.hh"
#include "G4Neutron.hh"


class G4ParticleDefinition;

class G4Fragment;     // Forward deckaration
typedef G4std::vector<G4Fragment*> G4FragmentVector;

//#define pctest


class G4Fragment 
{
public:

  // ============= CONSTRUCTORS ==================

  // Default constructor
  G4Fragment();

  // Destructor
  ~G4Fragment();

  // Copy constructor
  G4Fragment(const G4Fragment &right);

  // Several constructors

  // A,Z and 4-momentum
  G4Fragment(const G4int A, const G4int Z, const G4LorentzVector aMomentum);

  // 4-momentum and pointer to G4particleDefinition (for gammas)
  G4Fragment(const G4LorentzVector aMomentum, G4ParticleDefinition * aParticleDefinition);

  // ============= OPERATORS ==================
    
  const G4Fragment & operator=(const G4Fragment &right);
  G4bool operator==(const G4Fragment &right) const;
  G4bool operator!=(const G4Fragment &right) const;

  friend G4std::ostream& operator<<(G4std::ostream&, const G4Fragment*);
  friend G4std::ostream& operator<<(G4std::ostream&, const G4Fragment&);

  // ============= METHODS ==================

  inline G4double GetA(void) const;
  void SetA(const G4double value);
  
  G4double GetZ(void) const;
  void SetZ(const G4double value);
  
  G4double GetExcitationEnergy(void) const;
  void SetExcitationEnergy(const G4double value);
  
  const G4LorentzVector GetMomentum(void) const;
  void SetMomentum(const G4LorentzVector value);
  
  const G4ThreeVector GetAngularMomentum(void) const;
  void SetAngularMomentum(const G4ThreeVector value);
  
  G4int GetNumberOfExcitons(void) const;
  //  void SetNumberOfExcitons(const G4int value);
  
  G4int GetNumberOfHoles(void) const;
  void SetNumberOfHoles(const G4int value);
  
  G4int GetNumberOfCharged(void) const;
  void SetNumberOfCharged(const G4int value);

  G4int GetNumberOfParticles(void) const;
  void SetNumberOfParticles(const G4int value);

  inline G4ParticleDefinition * GetParticleDefinition(void) const;
  void SetParticleDefinition(G4ParticleDefinition * aParticleDefinition);

  G4double GetCreationTime(void) const;
  void SetCreationTime(const G4double time);


// Some utility methods

  inline G4double GetGroundStateMass(void) const;
  
  inline G4double GetBindingEnergy(void) const;

#ifdef pctest
  G4String GetCreatorModel() const { return theCreatorModel; }
  void SetCreatorModel(const G4String & aModel) 
  { theCreatorModel = aModel; }
#endif

private:

  G4double CalculateExcitationEnergy(const G4LorentzVector value) const;

  G4ThreeVector IsotropicRandom3Vector(const G4double Magnitude = 1.0) const;
  

  // ============= DATA MEMBERS ==================

  G4double theA;
  
  G4double theZ;
  
  G4double theExcitationEnergy;

  G4LorentzVector theMomentum;
  
  G4ThreeVector theAngularMomentum;
  
  G4int numberOfParticles;
  
  G4int numberOfHoles;
  
  G4int numberOfCharged;


  // Gamma evaporation requeriments

  G4ParticleDefinition * theParticleDefinition;
  
  G4double theCreationTime;

#ifdef pctest
  G4String theCreatorModel;
#endif 
};

// Class G4Fragment 

inline G4double G4Fragment::GetA() const
{
  return theA;
}

inline void G4Fragment::SetA(const G4double value)
{
  theA = value;
}

inline G4double G4Fragment::GetZ()  const
{
  return theZ;
}

inline void G4Fragment::SetZ(const G4double value)
{
  theZ = value;
}

inline G4double G4Fragment::GetExcitationEnergy()  const
{
  // temporary fix for what seems to be
  // a problem with rounding errors for on-shell lorentz-vectors in CLHEP.
  // HPW Apr 1999 @@@@@@@ 
  
  if(abs(theExcitationEnergy)<10*eV) return 0; 
  return theExcitationEnergy;
}

inline void G4Fragment::SetExcitationEnergy(const G4double value)
{
  //   theExcitationEnergy = value;
  G4cout << "Warning: G4Fragment::SetExcitationEnergy() is a dummy method. Please, avoid to use it." << G4endl;
}

inline const G4LorentzVector G4Fragment::GetMomentum()  const
{
  return theMomentum;
}

inline void G4Fragment::SetMomentum(const G4LorentzVector value)
{
  theMomentum = value;
  theExcitationEnergy = CalculateExcitationEnergy(value);
}

inline const G4ThreeVector G4Fragment::GetAngularMomentum()  const
{
  return theAngularMomentum;
}

inline void G4Fragment::SetAngularMomentum(const G4ThreeVector value)
{
  theAngularMomentum = value;
}

inline G4int G4Fragment::GetNumberOfExcitons()  const
{
  return numberOfParticles + numberOfHoles;
}

inline void G4Fragment::SetNumberOfParticles(const G4int value)
{
  numberOfParticles = value;
}

inline G4int G4Fragment::GetNumberOfHoles()  const
{
  return numberOfHoles;
}

inline void G4Fragment::SetNumberOfHoles(const G4int value)
{
  numberOfHoles = value;
}

inline G4int G4Fragment::GetNumberOfCharged()  const
{
  return numberOfCharged;
}

inline void G4Fragment::SetNumberOfCharged(const G4int value)
{
  if (value <= numberOfParticles) numberOfCharged = value;
  else G4Exception("G4Fragment::SetNumberOfCharged: Number of charged particles can't be greater than number of particles");
}

inline G4int G4Fragment::GetNumberOfParticles()  const
{
  return numberOfParticles;
}


inline G4ParticleDefinition * G4Fragment::GetParticleDefinition(void) const
{
  return theParticleDefinition;
}

inline void G4Fragment::SetParticleDefinition(G4ParticleDefinition * aParticleDefinition)
{
  theParticleDefinition = aParticleDefinition;
}


inline G4double G4Fragment::GetCreationTime(void) const 
{
  return theCreationTime;
}

inline void G4Fragment::SetCreationTime(const G4double time)
{
  theCreationTime = time;
}

inline G4double G4Fragment::GetGroundStateMass(void) const
{
	if (theA == 0) return 0.0; // photon
	else return G4ParticleTable::GetParticleTable()->
		    GetIonTable()->GetIonMass(static_cast<G4int>(theZ),static_cast<G4int>(theA));
}
	
inline G4double G4Fragment::GetBindingEnergy(void) const
{
	return -GetGroundStateMass()+(theA-theZ)*G4Neutron::Neutron()->GetPDGMass()
										 + theZ*G4Proton::Proton()->GetPDGMass();
}


#endif

