#pragma once

#include "G4UImessenger.hh"
#include "GateMessenger.hh"
#include "GateVSourceMessenger.hh"
#include "globals.hh"
#include <G4Colour.hh>
#include <G4Vector3D.hh>
#include <G4Polyline.hh>

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
class G4UIcmdWithAString;
class G4VGraphicsScene;
class G4ModelingParameters;
// class GateUIcmdWithADoubleWithUnitAndInteger;

#include "GateUIcmdWithAVector.hh"
class GateSourceTurbo;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class GateSourceTurboMessenger : public GateVSourceMessenger {
  void ViusalizeWindow(G4String newValue) const;
public:
  GateSourceTurboMessenger(GateSourceTurbo *source);
  ~GateSourceTurboMessenger();

  void SetNewValue(G4UIcommand *, G4String);

protected:
  GateSourceTurbo *mSource;
  G4UIcommand *VisualizeWindowCmd;
  G4UIcmdWithADoubleAndUnit *SetPlaneDistanceCmd;
  G4UIcmdWithADoubleAndUnit *SetPlanePhiCmd;
  G4UIcmdWithADoubleAndUnit *SetA1Cmd;
  G4UIcmdWithADoubleAndUnit *SetA2Cmd;
  G4UIcmdWithADoubleAndUnit *SetB1Cmd;
  G4UIcmdWithADoubleAndUnit *SetB2Cmd;
  G4UIcmdWithAnInteger *InitializeCmd;
  G4UIcmdWithADouble *SetActRatioCmd;
  G4UIcmdWithADouble *SetMaxSolidAngleCmd;
  G4UIcmdWithAString *loadVoxelizedPhantomCmd;
  G4UIcmdWith3VectorAndUnit* setPhantomPositionCmd;
  struct Window
  {
    Window(const G4Vector3D& pos1, const G4Vector3D& pos2, const G4Vector3D& pos3, const G4Vector3D& pos4, G4Colour colour, G4double width);
    void operator()(G4VGraphicsScene&, const G4ModelingParameters*);
    G4Polyline fPolyline;
    G4Colour fColour;
    G4double fWidth;
  };

};
