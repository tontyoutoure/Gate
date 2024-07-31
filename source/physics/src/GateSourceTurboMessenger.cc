#include "GateSourceTurboMessenger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "GateSourceTurbo.hh"

GateSourceTurboMessenger::GateSourceTurboMessenger(GateSourceTurbo *source)
    : GateVSourceMessenger(source), mSource(source) {

  G4String cmdName;
  //   cmdName = GetDirectoryName()+"setMinBremEnergy";
  //   setMinBremEnergyCmd = new G4UIcmdWithADoubleAndUnit(cmdName,this);
  //   setMinBremEnergyCmd->SetGuidance("Set the minimum energy of the
  //   bremsstrahlung generated.");
  //   setMinBremEnergyCmd->SetParameterName("min_energy", false);

  cmdName = GetDirectoryName() + "edgePointTheta1";
  edgePointTheta1Cmd = new G4UIcmdWith3VectorAndUnit(cmdName, this);
  edgePointTheta1Cmd->SetGuidance("Set the elevation edge point 1.");
  edgePointTheta1Cmd->SetParameterName("x", "y", "z", false);

  cmdName = GetDirectoryName() + "edgePointTheta2";
  edgePointTheta2Cmd = new G4UIcmdWith3VectorAndUnit(cmdName, this);
  edgePointTheta2Cmd->SetGuidance("Set the elevation edge point 2.");
  edgePointTheta2Cmd->SetParameterName("x", "y", "z", false);

  cmdName = GetDirectoryName() + "edgePointPhi1";
  edgePointPhi1Cmd = new G4UIcmdWith3VectorAndUnit(cmdName, this);
  edgePointPhi1Cmd->SetGuidance("Set the azimuthal edge point 1.");
  edgePointPhi1Cmd->SetParameterName("x", "y", "z", false);

  cmdName = GetDirectoryName() + "edgePointPhi2";
  edgePointPhi2Cmd = new G4UIcmdWith3VectorAndUnit(cmdName, this);
  edgePointPhi2Cmd->SetGuidance("Set the azimuthal edge point 2.");
  edgePointPhi2Cmd->SetParameterName("x", "y", "z", false);

  cmdName = GetDirectoryName() + "SetActRatio";
  SetActRatioCmd = new G4UIcmdWithAnInteger(cmdName, this);
  SetActRatioCmd->SetGuidance("Set the activity ratio with a sampling count.");
  SetActRatioCmd->SetParameterName("samplingCount", true, false);
  SetActRatioCmd->SetDefaultValue(10000000);
}

GateSourceTurboMessenger::~GateSourceTurboMessenger() {
  delete edgePointTheta1Cmd;
  delete edgePointTheta2Cmd;
  delete edgePointPhi1Cmd;
  delete edgePointPhi2Cmd;
  delete SetActRatioCmd;
}

void GateSourceTurboMessenger::SetNewValue(G4UIcommand *command,
                                           G4String newValue) {
  GateVSourceMessenger::SetNewValue(command, newValue);
  if (command == edgePointTheta1Cmd) {
    mSource->SetEdgePointTheta1(
        edgePointTheta1Cmd->GetNew3VectorValue(newValue));
  } else if (command == edgePointTheta2Cmd) {
    mSource->SetEdgePointTheta2(
        edgePointTheta2Cmd->GetNew3VectorValue(newValue));
  } else if (command == edgePointPhi1Cmd) {
    mSource->SetEdgePointPhi1(edgePointPhi1Cmd->GetNew3VectorValue(newValue));
  } else if (command == edgePointPhi2Cmd) {
    mSource->SetEdgePointPhi2(edgePointPhi2Cmd->GetNew3VectorValue(newValue));
  } else if (command == SetActRatioCmd) {
    mSource->SetActRatio(SetActRatioCmd->GetNewIntValue(newValue));
  }
}