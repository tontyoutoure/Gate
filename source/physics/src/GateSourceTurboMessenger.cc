#include "GateSourceTurboMessenger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "GateSourceTurbo.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

GateSourceTurboMessenger::GateSourceTurboMessenger(GateSourceTurbo *source)
    : GateVSourceMessenger(source), mSource(source) {

  G4String cmdName;
  //   cmdName = GetDirectoryName()+"setMinBremEnergy";
  //   setMinBremEnergyCmd = new G4UIcmdWithADoubleAndUnit(cmdName,this);
  //   setMinBremEnergyCmd->SetGuidance("Set the minimum energy of the
  //   bremsstrahlung generated.");
  //   setMinBremEnergyCmd->SetParameterName("min_energy", false);
  cmdName = GetDirectoryName() + "setPlaneDistance";
  SetPlaneDistanceCmd = new G4UIcmdWithADoubleAndUnit(cmdName, this);
  SetPlaneDistanceCmd->SetGuidance("Set the distance of the target plane to system center.");
  SetPlaneDistanceCmd->SetParameterName("distance", false);

  cmdName = GetDirectoryName() + "setPlanePhi";
  SetPlanePhiCmd = new G4UIcmdWithADoubleAndUnit(cmdName, this);
  SetPlanePhiCmd->SetGuidance("Set the azimuthal angle of the target plane.");
  SetPlanePhiCmd->SetParameterName("phi", false);

  cmdName = GetDirectoryName() + "setA1";
  SetA1Cmd = new G4UIcmdWithADoubleAndUnit(cmdName, this);
  SetA1Cmd->SetGuidance("Set the left edge of the opening, relative to closet point to system center on the target plane.");
  SetA1Cmd->SetParameterName("a1", false);

  cmdName = GetDirectoryName() + "setA2";
  SetA2Cmd = new G4UIcmdWithADoubleAndUnit(cmdName, this);
  SetA2Cmd->SetGuidance("Set the right edge of the opening, relative to closet point to system center on the target plane.");
  SetA2Cmd->SetParameterName("a2", false);

  cmdName = GetDirectoryName() + "setB1";
  SetB1Cmd = new G4UIcmdWithADoubleAndUnit(cmdName, this);
  SetB1Cmd->SetGuidance("Set bottom edge of the opening, relative to closet point to system center on the target plane.");
  SetB1Cmd->SetParameterName("b1", false);

  cmdName = GetDirectoryName() + "setB2";
  SetB2Cmd = new G4UIcmdWithADoubleAndUnit(cmdName, this);
  SetB2Cmd->SetGuidance("Set top edge of the opening, relative to closet point to system center on the target plane.");
  SetB2Cmd->SetParameterName("b2", false);
  
  cmdName = GetDirectoryName() + "setActRatio";
  SetActRatioCmd = new G4UIcmdWithAnInteger(cmdName, this);
  SetActRatioCmd->SetGuidance("Set the activity ratio with a sampling count.");
  SetActRatioCmd->SetParameterName("samplingCount", true, false);
  SetActRatioCmd->SetDefaultValue(10000000);
}

GateSourceTurboMessenger::~GateSourceTurboMessenger() {
  delete SetPlaneDistanceCmd;
  delete SetPlanePhiCmd;
  delete SetA1Cmd;
  delete SetA2Cmd;
  delete SetB1Cmd;
  delete SetB2Cmd;
  delete SetActRatioCmd;
}

void GateSourceTurboMessenger::SetNewValue(G4UIcommand *command,
                                           G4String newValue) {
  GateVSourceMessenger::SetNewValue(command, newValue);
  if (command == SetPlaneDistanceCmd) {
    mSource->SetPlaneDistance(SetPlaneDistanceCmd->GetNewDoubleValue(newValue));
  } else if (command == SetPlanePhiCmd) {
    mSource->SetPlanePhi(SetPlanePhiCmd->GetNewDoubleValue(newValue));
  } else if (command == SetA1Cmd) {
    mSource->SetA1(SetA1Cmd->GetNewDoubleValue(newValue));
  } else if (command == SetA2Cmd) {
    mSource->SetA2(SetA2Cmd->GetNewDoubleValue(newValue));
  } else if (command == SetB1Cmd) {
    mSource->SetB1(SetB1Cmd->GetNewDoubleValue(newValue));
  } else if (command == SetB2Cmd) {
    mSource->SetB2(SetB2Cmd->GetNewDoubleValue(newValue));
  } else if (command == SetActRatioCmd) {
    mSource->SetActRatio(SetActRatioCmd->GetNewIntValue(newValue));
  }
}