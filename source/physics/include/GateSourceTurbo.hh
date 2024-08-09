#pragma once
#include "GateVSource.hh"
#include <G4Point3D.hh>
#include <G4String.hh>
#include <G4ThreeVector.hh>

/*
author: LiKun (likun@dotuai.com)
source only generated particles that fulfill the following conditions:

Given four points in space, pth1, pth2, pphi1, pphi2
then elevation angle of the particle, theta from the source point, should
between the elevation angles of source point seeing of pth1 and pth2. Also the
azimuthal angle of the particle, phi from the source point, should between the
azimuthal angles of source point seeing pphi1 and pphi2.




*/

class GateSourceTurbo : public GateVSource {
public:
  GateSourceTurbo(G4String name);
  ~GateSourceTurbo() { G4cout << "GateSourceTurbo destructs" << G4endl; };

  G4int GeneratePrimaries(G4Event *event) override;
  void GeneratePrimaryVertex(G4Event *event) override;

  // should be reimplemented
  G4double GetNextTime(G4double timeStart) override;
  void SetA1(G4double a) { a1 = a; };
  void SetA2(G4double a) { a2 = a; };
  void SetB1(G4double b) { b1 = b; };
  void SetB2(G4double b) { b2 = b; };
  void SetPlaneDistance(G4double distance) { plane_distance = distance; };
  void SetPlanePhi(G4double phi) { plane_phi = phi; sin_plane_phi = sin(phi); cos_plane_phi = cos(phi); };



  void SetActRatio(G4int samplingCount);

private:
  void SetPhiTheta(const G4ThreeVector &pos) const;
  G4double GetSolidAngle(const G4ThreeVector &pos) const;
  G4bool CheckPosDirValid(const G4ThreeVector &pos,
                          const G4ThreeVector &dir) const;
  G4double m_ActRatio = 1;
  G4double plane_distance{NAN};
  G4double plane_phi{NAN};
  G4double sin_plane_phi{NAN}, cos_plane_phi{NAN};
  G4double a1{NAN}, a2{NAN}, b1{NAN}, b2{NAN};

  // G4ThreeVector mPth1;
  // G4ThreeVector mPth2;
  // G4ThreeVector mPphi1;
  // G4ThreeVector mPphi2;
};