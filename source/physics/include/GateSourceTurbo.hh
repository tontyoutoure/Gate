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
  void SetEdgePointTheta1(G4ThreeVector point) {
    mPth1 = point;
    m_PointSetFlag |= 0b0001;
  };
  void SetEdgePointTheta2(G4ThreeVector point) {
    mPth2 = point;
    m_PointSetFlag |= 0b0010;
  };
  void SetEdgePointPhi1(G4ThreeVector point) {
    mPphi1 = point;
    m_PointSetFlag |= 0b0100;
  };
  void SetEdgePointPhi2(G4ThreeVector point) {
    mPphi2 = point;
    m_PointSetFlag |= 0b1000;
  };

  void SetActRatio(G4int samplingCount);

private:
  void SetPhiTheta(const G4ThreeVector &pos) const;
  G4double GetSolidAngle(const G4ThreeVector &pos) const;
  G4bool CheckPosDirValid(const G4ThreeVector &pos,
                          const G4ThreeVector &dir) const;
  G4int m_PointSetFlag = 0;
  G4double m_ActRatio = 1;
  G4ThreeVector mPth1;
  G4ThreeVector mPth2;
  G4ThreeVector mPphi1;
  G4ThreeVector mPphi2;
};