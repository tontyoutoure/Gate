#include "GateSourceTurbo.hh"
#include "GateSourceTurboMessenger.hh"
#include <G4Event.hh>
#include <G4Exception.hh>
#include <G4ExceptionSeverity.hh>
#include <G4PrimaryVertex.hh>
#include <G4ThreeVector.hh>
#include <G4Vector3D.hh>
#include <cmath>
G4int GateSourceTurbo::GeneratePrimaries(G4Event *event) {
  if (event)
    GateMessage("Beam", 2,
                "Generating particle " << event->GetEventID() << Gateendl);

  G4int numVertices = 0;

  SetParticleTime(m_time);
  GeneratePrimaryVertex(event);
  numVertices++;

  // if (event) {
  //   for (int i = 0; i < event->GetPrimaryVertex(0)->GetNumberOfParticle();
  //        i++) {
  //     G4PrimaryParticle *p = event->GetPrimaryVertex(0)->GetPrimary(i);
  //     GateMessage("Beam", 3,
  //                 "(" << event->GetEventID() << ") "
  //                     << p->GetG4code()->GetParticleName()
  //                     << " pos=" << event->GetPrimaryVertex(0)->GetPosition()
  //                     << " weight=" << p->GetWeight()
  //                     << " energy=" << G4BestUnit(mEnergy, "Energy")
  //                     << " mom=" << p->GetMomentum()
  //                     << " ptime=" << G4BestUnit(p->GetProperTime(), "Time")
  //                     << " atime=" << G4BestUnit(GetTime(), "Time") <<
  //                     ")\n");
  //   }
  // }

  // if (event) {
  //   printf("time %e ns\n", GetTime());
  // }

  // G4cout<<"Generate primaries\n";
  return numVertices;
}

GateSourceTurbo::GateSourceTurbo(G4String name) : GateVSource(name) {
  m_sourceMessenger = new GateSourceTurboMessenger(this);
}
G4bool GateSourceTurbo::CheckPosDirValid(const G4ThreeVector &pos,
                                         const G4ThreeVector &dir) const {
  // compare theta with cos2, to avoid complex calculation
  //   G4double cot2theta = std::copysign(1.0, dir.z()) * dir.z() * dir.z() /
  //                        (dir.x() * dir.x() + dir.y() * dir.y());

  G4double cot2theta_dinominator = (dir.x() * dir.x() + dir.y() * dir.y());
  G4double cot2theta_numerator =
      std::copysign(1.0, dir.z()) * dir.z() * dir.z();

  G4double x1 = mPth1.x() - pos.x();
  G4double y1 = mPth1.y() - pos.y();
  G4double z1 = mPth1.z() - pos.z();

  //   G4double cot2theta1 = std::copysign(1.0, z1) * z1 * z1 / (x1 * x1 + y1 *
  //   y1);
  G4double cot2theta1_dinominator = (x1 * x1 + y1 * y1);
  G4double cot2theta1_numerator = std::copysign(1.0, z1) * z1 * z1;
  G4double x2 = mPth2.x() - pos.x();
  G4double y2 = mPth2.y() - pos.y();
  G4double z2 = mPth2.z() - pos.z();
  //   G4double cot2theta2 = std::copysign(1.0, z2) * z2 * z2 / (x2 * x2 + y2 *
  //   y2);
  G4double cot2theta2_dinominator = (x2 * x2 + y2 * y2);
  G4double cot2theta2_numerator = std::copysign(1.0, z2) * z2 * z2;
  //   G4bool theta_valid = (cot2theta1 > cot2theta) && (cot2theta >
  //   cot2theta2);
  G4bool theta_valid = (cot2theta1_numerator * cot2theta_dinominator >
                        cot2theta_numerator * cot2theta1_dinominator) &&
                       (cot2theta_numerator * cot2theta_dinominator >
                        cot2theta2_numerator * cot2theta_dinominator);

  // sum of angles between dir and two source-edge vector should be less than
  // pi, aka whehter sine is positive. Denominator, which are magnitude of
  // vectors, are ignored, since they do not affect the sign

  x1 = mPphi1.x() - pos.x();
  y1 = mPphi1.y() - pos.y();
  x2 = mPphi2.x() - pos.x();
  y2 = mPphi2.y() - pos.y();

  G4double cross1 = x1 * dir.y() - y1 * dir.x();
  G4double dot1 = x1 * dir.x() + y1 * dir.y();
  G4double cross2 = dir.x() * y2 - dir.y() * x2;
  G4double dot2 = x2 * dir.x() + y2 * dir.y();
  G4bool phi_valid = (cross1 * dot2 + cross2 * dot1) > 0;

  // TBD

  return theta_valid && phi_valid;
}
void GateSourceTurbo::SetPhiTheta(const G4ThreeVector &pos) const {
  // compare theta with cos2, to avoid complex calculation
  //   G4double cot2theta = std::copysign(1.0, dir.z()) * dir.z() * dir.z() /
  //                        (dir.x() * dir.x() + dir.y() * dir.y());

  G4Vector3D v_theta1 = mPth1 - pos;
  G4Vector3D v_theta2 = mPth2 - pos;
  G4double theta1 = v_theta1.theta();
  G4double theta2 = v_theta2.theta();
  m_angSPS->SetMinTheta(M_PI-theta1);
  m_angSPS->SetMaxTheta(M_PI-theta2);
  G4Vector3D v_phi1 = mPphi1 - pos;
  G4Vector3D v_phi2 = mPphi2 - pos;
  G4double phi1 = v_phi1.phi();
  G4double phi2 = v_phi2.phi();
  m_angSPS->SetMinPhi(M_PI+phi1);
  m_angSPS->SetMaxPhi(M_PI+phi2);
}

G4double GateSourceTurbo::GetSolidAngle(const G4ThreeVector &pos) const {
  // if (pos.mag2() >= mPth1.mag2() || pos.mag2() >= mPth2.mag2() ||
  //     pos.mag2() >= mPphi1.mag2() || pos.mag2() >= mPphi2.mag2()) {
  //   G4Exception("GateSourceTurbo::GetSolidAngle", "GetSolidAngleError",
  //               FatalException, "source position not inside edge point");
  // }

  G4double phi1 = atan2(mPphi1.y() - pos.y(), mPphi1.x() - pos.x());
  G4double phi2 = atan2(mPphi2.y() - pos.y(), mPphi2.x() - pos.x());
  if (phi2 < phi1) {
    phi2 += 2 * M_PI;
  }
  if (phi2 - phi1 > M_PI) {
    G4Exception("GateSourceTurbo::GetSolidAngle", "GetSolidAngleError",
                FatalException, "edge point error: phi1 larger than phi2");
  }
  G4double costheta1 = (mPth1.z() - pos.z()) / (mPth1 - pos).mag();
  G4double costheta2 = (mPth2.z() - pos.z()) / (mPth2 - pos).mag();
  if (costheta2 < costheta1) {
    G4Exception("GateSourceTurbo::GetSolidAngle", "GetSolidAngleError",
                FatalException, "edge point error: theta1 larger than theta2");
  }
  return (phi2 - phi1) * (costheta2 - costheta1);
}

void GateSourceTurbo::SetActRatio(G4int samplingCount) {
  if ((m_PointSetFlag & 0b1111) != 0b1111) {
    G4Exception("GateSourceTurbo::SetActRatio", "SetActRatioError",
                FatalException, "Not all edge points are set");
  }
  GateVVolume *v = mVolume;
  while (v->GetObjectName() != "world") {

    if (G4RotationMatrix({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}) !=
        v->GetPhysicalVolume(0)->GetObjectRotationValue()) {
      G4Exception("GateSourceTurbo::SetActRatio", "SetActRatioError",
                  FatalException,
                  "Turbo source must not attach to a rotated volume");
    }
    v = v->GetParentVolume();
  }
auto start_time = std::chrono::high_resolution_clock::now();
  G4double act_ratio_all = 0;
   G4ThreeVector pos;
  for (G4int i = 0; i < samplingCount; i++) {
   pos = m_posSPS->GenerateOne();
    act_ratio_all += GetSolidAngle(pos) / 4 / M_PI;
  }
  m_ActRatio = act_ratio_all / samplingCount;
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    G4cout << "Activity Ratio of source " << m_name << " is " << m_ActRatio<< Gateendl;
}

void GateSourceTurbo::GeneratePrimaryVertex(G4Event *event) {
  G4ThreeVector position = m_posSPS->GenerateOne();
  ChangeParticlePositionRelativeToAttachedVolume(position);
  SetPhiTheta(position);
  G4ThreeVector direction = m_angSPS->GenerateOne();
  G4PrimaryVertex *vertex =
      new G4PrimaryVertex(position, GetParticleTime());

  // Set placement relative to attached volume
  // DD(particle_momentum_direction);

  G4double particle_energy = 0;
  particle_energy = m_eneSPS->GenerateOne(GetParticleDefinition());
  mEnergy = particle_energy; // because particle_energy is private

  G4double mass = GetParticleDefinition()->GetPDGMass();
  G4double energy = particle_energy + mass;
  G4double pmom = std::sqrt(energy * energy - mass * mass);
  G4double px = pmom * direction.x();
  G4double py = pmom * direction.y();
  G4double pz = pmom * direction.z();

  G4PrimaryParticle *particle =
      new G4PrimaryParticle(GetParticleDefinition(), px, py, pz);
  particle->SetMass(mass);
  particle->SetCharge(GetParticleDefinition()->GetPDGCharge());
  particle->SetPolarization(GetParticlePolarization().x(),
                            GetParticlePolarization().y(),
                            GetParticlePolarization().z());

  G4double particle_weight = GetBiasRndm()->GetBiasWeight();
  particle->SetWeight(particle_weight);

  // Add one particle
  vertex->SetPrimary(particle);

  // Verbose
  if (nVerboseLevel > 1) {
    G4cout << "Particle name: " << GetParticleDefinition()->GetParticleName()
           << Gateendl;
    G4cout << "       Energy: " << particle_energy << Gateendl;
    G4cout << "     Position: " << particle_position << Gateendl;
    G4cout << "    Direction: " << direction << Gateendl;
  }
  if (nVerboseLevel > 2) {
    G4cout << "Creating primaries and assigning to vertex\n";
  }

  event->AddPrimaryVertex(vertex);
}

G4double GateSourceTurbo::GetNextTime(G4double timeStart) {

  /* GetVolumeID ??? */

  // returns the proposed time for the next event of this source, sampled from
  // the source time distribution
  G4double aTime = DBL_MAX;

  // if(m_activity==0 && m_timeInterval!=0.)  SetActivity();

  if (m_activity > 0.) {
    // compute the present activity, on the base of the starting activity and
    // the lifetime (if any)
    G4double activityNow = m_activity;
    if (timeStart < m_startTime)
      activityNow = 0.;
    else {
      // Force life time to 0, time is managed by GATE not G4
      GetParticleDefinition()->SetPDGLifeTime(0);
      if (m_forcedUnstableFlag) {
        if (m_forcedLifeTime > 0.) {
          activityNow =
              m_activity * exp(-(timeStart - m_startTime) / m_forcedLifeTime);
        } else {
          G4cout << "[GateVSource::GetNextTime] ERROR: Forced decay with "
                    "negative lifetime: (s) "
                 << m_forcedLifeTime / s << Gateendl;
        }
      } else {
        G4ParticleDefinition *partDef = GetParticleDefinition();
        if (partDef) {
          if (!(partDef->GetPDGStable())) {
            if (nVerboseLevel > 0)
              G4cout << "GateVSource::GetNextTime : unstable particle "
                     << GetParticleDefinition()->GetParticleName()
                     << " from source " << GetName() << Gateendl;
            // activity is constant
            activityNow = m_activity;
          } else if (nVerboseLevel > 1)
            G4cout << "GateVSource::GetNextTime : stable particle "
                   << GetParticleDefinition()->GetParticleName()
                   << " from source " << GetName() << Gateendl;
        } else if (nVerboseLevel > 0)
          G4cout << "GateVSource::GetNextTime : NULL ParticleDefinition for "
                    "source "
                 << GetName() << " assumed stable \n";
      }
    }

    activityNow *= m_ActRatio;

    if (nVerboseLevel > 0)
      G4cout << "GateVSource::GetNextTime : Initial activity (becq) : "
             << m_activity / becquerel << Gateendl
             << "                            At time (s) " << timeStart / s
             << " activity (becq) " << activityNow / becquerel << Gateendl;

    // sampling of the interval distribution
    if (!mEnableRegularActivity) {
      aTime = -log(G4UniformRand()) * (1. / activityNow);
    } else {
      GateError("I should not be here. ");
      // DD(activityNow);
      //         DD(m_activity);
      //         DD(timeStart/s);
      aTime = 1. / activityNow;
    }
  }

  if (nVerboseLevel > 0)
    G4cout << "GateVSource::GetNextTime : next time (s) " << aTime / s
           << Gateendl;

  // Dump(0);
  /*G4cout<< "    CentreCoords       (mm)  : "
               << m_posSPS->GetCentreCoords().x()/mm << " "
               << m_posSPS->GetCentreCoords().y()/mm << " "
               << m_posSPS->GetCentreCoords().z()/mm << Gateendl;*/
  return aTime;
}