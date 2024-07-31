#pragma once

#include "G4UImessenger.hh"
#include "GateMessenger.hh"
#include "GateVSourceMessenger.hh"
#include "globals.hh"

class GateVSource;

class GateClock;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithoutParameter;
// class GateUIcmdWithADoubleWithUnitAndInteger;

#include "GateUIcmdWithAVector.hh"
class GateSourceTurbo;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class GateSourceTurboMessenger : public GateVSourceMessenger {
public:
  GateSourceTurboMessenger(GateSourceTurbo *source);
  ~GateSourceTurboMessenger();

  void SetNewValue(G4UIcommand *, G4String);

protected:
  GateSourceTurbo *mSource;

  G4UIcmdWith3VectorAndUnit *edgePointTheta1Cmd;
  G4UIcmdWith3VectorAndUnit *edgePointTheta2Cmd;
  G4UIcmdWith3VectorAndUnit *edgePointPhi1Cmd;
  G4UIcmdWith3VectorAndUnit *edgePointPhi2Cmd;
  G4UIcmdWithAnInteger *SetActRatioCmd;
};
