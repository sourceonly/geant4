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
// $Id: G4CircularCurve.cc,v 1.6 2001/07/11 09:59:43 gunter Exp $
// GEANT4 tag $Name: geant4-04-01-patch-01 $
//
// ----------------------------------------------------------------------
// GEANT 4 class source file
//
// G4CircularCurve.cc
//
// ----------------------------------------------------------------------

#include "G4CircularCurve.hh"
#include "G4Ellipse.hh"

// G4CircularCurve
G4CircularCurve::G4CircularCurve() {}
G4CircularCurve::~G4CircularCurve() {}

G4CircularCurve::G4CircularCurve(const G4CircularCurve& right)
  : radius(right.radius)
{
  pShift    = right.pShift;
  position  = right.position;
  bBox      = right.bBox;
  start     = right.start;
  end       = right.end;
  pStart    = right.pStart;
  pEnd      = right.pEnd;
  pRange    = right.pRange;
  bounded   = right.bounded;
  sameSense = right.sameSense;
}

G4CircularCurve&
G4CircularCurve::operator=(const G4CircularCurve& right)
{
  if (&right == this) return *this;

  radius    = right.radius;
  pShift    = right.pShift;
  position  = right.position;
  bBox      = right.bBox;
  start     = right.start;
  end       = right.end;
  pStart    = right.pStart;
  pEnd      = right.pEnd;
  pRange    = right.pRange;
  bounded   = right.bounded;
  sameSense = right.sameSense;

  return *this;
}

//////////////////////////////////////////////////////////////////////////////

void G4CircularCurve::InitBounded() 
{  
  // the bbox must include the start and endpoints as well as the
  // extreme points if they lie on the curve
  bBox.Init(GetStart(), GetEnd());
  
  // the parameter values
  // belonging to the points with an extreme x, y and z coordinate
  for (G4int i=0; i<3; i++) 
  {
    G4double u = atan2(position.GetPY()(i), position.GetPX()(i));
    
    if (IsPOn(u)) 
      bBox.Extend(GetPoint(u));
    
    if (IsPOn(u+pi)) 
      bBox.Extend(GetPoint(u+pi));
  }
}

//////////////////////////////////////////////////////////////////////////////

G4Curve* G4CircularCurve::Project(const G4Transform3D& tr)
{
  G4Ellipse e;
  e.Init(position, radius, radius);
  e.SetBounds(GetPStart(), GetPEnd());
 
  return e.Project(tr);
}

//////////////////////////////////////////////////////////////////////////////

G4bool G4CircularCurve::Tangent(G4CurvePoint& cp, G4Vector3D& v)
{
  // The tangent is computed from the 3D point representation
  // for all conics. An alternaive implementation (based on
  // the parametric point) might be worthwhile adding
  // for efficiency.
  
  const G4Axis2Placement3D& pos= *(GetPosition());
  G4Point3D p= pos.GetToPlacementCoordinates() * cp.GetPoint();
  
  v= -p.y()*pos.GetPX() + p.x()*pos.GetPY();
  return true;
}

G4double G4CircularCurve::GetPMax() const
{
  return twopi;
}

G4Point3D G4CircularCurve::GetPoint(G4double param) const
{
  return G4Point3D( position.GetLocation()+radius*
    ( cos(param)*position.GetPX() + sin(param)*position.GetPY() ) );
}

G4double G4CircularCurve::GetPPoint(const G4Point3D& pt) const
{
  G4Point3D ptLocal= position.GetToPlacementCoordinates()*pt;
  G4double angle= atan2(ptLocal.y(), ptLocal.x());
  return (angle<0)? angle+twopi: angle;
}

////////////////////////////////////////////////////////////////////////////

/*
#include "G4CurveRayIntersection.hh"

void G4CircularCurve::IntersectRay2D(const G4Ray& ray,
				     G4CurveRayIntersection& is)
{
  G4Exception("G4CircularCurve is always 3D!");
  exit(1);
}
*/

G4int G4CircularCurve::IntersectRay2D(const G4Ray& ray)
{
  G4Exception("G4CircularCurve is always 3D!");
  return 0;
}