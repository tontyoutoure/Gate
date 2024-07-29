

#ifndef GateCoincidenceMultiplesKiller_h
#define GateCoincidenceMultiplesKiller_h 1

#include "globals.hh"
#include <iostream>
#include <vector>
#include "G4ThreeVector.hh"
#include "GateVDigitizerModule.hh"
#include "GateCoincidenceDigi.hh"
#include "GateClockDependent.hh"
#include "GateCrystalSD.hh"

#include "globals.hh"
#include "GateVPulseProcessor.hh"
#include "GateObjectStore.hh"

#include "GateCoincidenceDigitizer.hh"
#include "GateCoincidenceMultiplesKillerMessenger.hh"

class GateCoincidenceMultiplesKillerMessenger;


class GateCoincidenceMultiplesKiller : public GateVDigitizerModule
{
public:



  //! Destructor
  virtual ~GateCoincidenceMultiplesKiller() ;

  //! Constructs  attached to a GateDigitizer
  GateCoincidenceMultiplesKiller(GateCoincidenceDigitizer *digitizer, G4String name);


public:
  void Digitize() override;

  virtual void DescribeMyself(size_t indent);

protected:


private:
  GateCoincidenceMultiplesKillerMessenger *m_messenger;    //!< Messenger
  GateCoincidenceDigi* m_outputDigi;

  GateCoincidenceDigiCollection* m_OutputDigiCollection;

  GateCoincidenceDigitizer* m_digitizer;
  G4int nVerboseLevel;




};


#endif
