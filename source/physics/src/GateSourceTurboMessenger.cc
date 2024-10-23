#include "GateSourceTurboMessenger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "GateSourceTurbo.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4Polyline.hh"
#include "G4VGraphicsScene.hh"
#include "G4VModel.hh"
#include "G4CallbackModel.hh"
#include <G4Colour.hh>
#include <string>
#include <G4VisManager.hh>
#include "G4UImanager.hh"

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

  cmdName = GetDirectoryName() + "initialize";
  InitializeCmd = new G4UIcmdWithAnInteger(cmdName, this);
  InitializeCmd->SetGuidance("Initialize the source with a given number of samplings.");
  InitializeCmd->SetParameterName("nSamples", false);
  
  cmdName = GetDirectoryName() + "setActRatio";
  SetActRatioCmd = new G4UIcmdWithADouble(cmdName, this);
  SetActRatioCmd->SetGuidance("Set the activity ratio of the source.");
  SetActRatioCmd->SetParameterName("actRatio", false);

  cmdName = GetDirectoryName() +"setMaxSolidAngle";
  SetMaxSolidAngleCmd = new G4UIcmdWithADouble(cmdName, this);
  SetMaxSolidAngleCmd->SetGuidance("Set the maximum solid angle of the source.");
  SetMaxSolidAngleCmd->SetParameterName("maxSolidAngle", false);

  cmdName = GetDirectoryName()+"loadVoxelizedPhantom";
  loadVoxelizedPhantomCmd = new G4UIcmdWithAString(cmdName,this);
  loadVoxelizedPhantomCmd->SetGuidance("Load a voxelized phantom from an image file.");
  loadVoxelizedPhantomCmd->SetParameterName("vox_phantom", false);

  cmdName = GetDirectoryName()+"setVoxelizedPhantomPosition";
  setPhantomPositionCmd = new G4UIcmdWith3VectorAndUnit(cmdName,this);
  setPhantomPositionCmd->SetGuidance("Set the position of the voxelized phantom.");
  setPhantomPositionCmd->SetParameterName("pos_x", "pos_y", "pos_z", false);

  cmdName = GetDirectoryName() + "visualizeWindow";
  VisualizeWindowCmd = new G4UIcommand(cmdName, this);
  VisualizeWindowCmd->SetGuidance("Visualize the output window of the source.");
  G4UIparameter* parameter;
  parameter = new G4UIparameter ("width", 'd', false);
  VisualizeWindowCmd -> SetParameter (parameter);
  parameter = new G4UIparameter ("colour", 's', false);
  VisualizeWindowCmd -> SetParameter (parameter);
}

GateSourceTurboMessenger::~GateSourceTurboMessenger() {
  delete SetPlaneDistanceCmd;
  delete SetPlanePhiCmd;
  delete SetA1Cmd;
  delete SetA2Cmd;
  delete SetB1Cmd;
  delete SetB2Cmd;
  delete SetActRatioCmd;
  delete SetMaxSolidAngleCmd;
  delete InitializeCmd;
  delete loadVoxelizedPhantomCmd;
  delete setPhantomPositionCmd;
  delete VisualizeWindowCmd;
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
    mSource->SetActRatio(SetActRatioCmd->GetNewDoubleValue(newValue));
  }
  else if (command == SetMaxSolidAngleCmd) {
    mSource->SetMaxSolidAngle(SetMaxSolidAngleCmd->GetNewDoubleValue(newValue));
  }
  else if (command == InitializeCmd) 
    mSource->Initialize(InitializeCmd->GetNewIntValue(newValue));
  else if (command == loadVoxelizedPhantomCmd)
    mSource->LoadVoxelizedPhantom(newValue);
  else if (command == setPhantomPositionCmd)
    mSource->SetPhantomPosition(setPhantomPositionCmd->GetNew3VectorValue(newValue));
  else if (command == VisualizeWindowCmd)
    ViusalizeWindow(newValue);
}

GateSourceTurboMessenger::Window::Window(const G4Vector3D& pos1, const G4Vector3D& pos2, const G4Vector3D& pos3, const G4Vector3D& pos4, G4Colour colour, G4double width) {

  fPolyline.push_back(pos1);
  fPolyline.push_back(pos3);
  fPolyline.push_back(pos4);
  fPolyline.push_back(pos2);
  fPolyline.push_back(pos1);
  G4VisAttributes va;
  va.SetLineWidth(width);
  va.SetColour(colour);
  fPolyline.SetVisAttributes(va);

}


void GateSourceTurboMessenger::Window::operator()
  (G4VGraphicsScene &sceneHandler, const G4ModelingParameters *) {
  sceneHandler.BeginPrimitives();
  sceneHandler.AddPrimitive(fPolyline);
  sceneHandler.EndPrimitives();
}

void GateSourceTurboMessenger::ViusalizeWindow(G4String newValue) const {
  G4ThreeVector pos1, pos2, pos3, pos4;
  mSource->GetWindowVertex(pos1, pos2, pos3, pos4);
  // G4cout << "Window vertex 1: " << pos1 << G4endl;
  // G4cout << "Window vertex 2: " << pos2 << G4endl;
  // G4cout << "Window vertex 3: " << pos3 << G4endl;
  // G4cout << "Window vertex 4: " << pos4 << G4endl;
  G4double width = 2;
  G4String colour_str = "red";
  
  std::istringstream is(newValue);
  is >> width >> colour_str;
  G4Colour colour;
  G4Colour::GetColour(colour_str, colour);


  Window * window = new Window(pos1, pos2, pos3, pos4, colour, width);
  G4cout << "viusalize window with" << newValue << G4endl;
  G4VModel* model =
    new G4CallbackModel<GateSourceTurboMessenger::Window>(window);
  model->SetType("Turbo Window");
  model->SetGlobalTag("Turbo Window");
  G4String description = "Turbo Window: ";
  description += "(" + std::to_string(pos1.x()) + " " + std::to_string(pos1.y()) + " " + std::to_string(pos1.z()) + "), ";
  description += "(" + std::to_string(pos2.x()) + " " + std::to_string(pos2.y()) + " " + std::to_string(pos2.z()) + "), ";
  description += "(" + std::to_string(pos3.x()) + " " + std::to_string(pos3.y()) + " " + std::to_string(pos3.z()) + "), ";
  description += "(" + std::to_string(pos4.x()) + " " + std::to_string(pos4.y()) + " " + std::to_string(pos4.z()) + ")";
  model->SetGlobalDescription(description);

  G4VisManager* fpVisManager = G4VisManager::GetInstance();
  G4Scene* pScene = fpVisManager->GetCurrentScene();
  const G4String& currentSceneName = pScene -> GetName ();
  G4bool successful = pScene -> AddRunDurationModel (model, true);
  G4UImanager::GetUIpointer () -> ApplyCommand ("/vis/scene/notifyHandlers");
}