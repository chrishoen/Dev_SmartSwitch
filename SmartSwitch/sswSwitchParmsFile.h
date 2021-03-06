#pragma once

/*==============================================================================
Dsp namespace: sixdofs that are measured by a computer vision based system.
Parameters class whose values are read from a command file. 
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineParms.h"
#include "dspSlowThresholderParmsWrapper.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SSW
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class that contains parameter member variables. The values of
// the parameters are set by reading a text file that contains command lines.
// Each command line is of the form "command argument1 argument2 ...".
// 
// The command files are partitioned into different sections and only one
// section can be read at a time to set member variables that are specified
// in it.
//
// The command files are managed by a CmdLineFile object. This opens the 
// file, reads each line in it, parses the line into a CmdLineCmd command 
// object, passes the command object to this object for command execution,
// and then closes the file. 
//
// This class inherits from BaseCmdLineParms, which inherits from 
// BaseCmdLineExec. BaseCmdLineParms provides a method that uses a
// CmdLineFile object to read and process the file. BaseCmdLineExec provides
// an abstract execute(cmd) method to which inheritors provide an overload
// that is called by the CmdLineFile object for each command in the file.
// This execute method then sets a member variables, according to the
// command.
// 
// This class can contain member variables that also inherit from
// BaseCmdLineExec. This provides for command files that have a nested
// structure. If so, then this class is the root.
// 

class SwitchParmsFile : public Ris::BaseCmdLineParms
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   static const int cMaxStringSize = 200;
   static const int cMaxObjects = 8;
   static const int cMaxRafts = 8;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Timer thread period, ms.
   int  mTimerPeriod;

   // Test mode, 1 for thresholder, 2 for classifier.
   int  mTestMode;

   // Initial value.
   float  mInitialValueA;
   float  mInitialValueB;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Slow classifier thresholder parameters.
   Dsp::SlowThresholderParmsWrapper  mThresholderParmsM2Wrapper;
   Dsp::SlowThresholderParmsWrapper  mThresholderParmsM1Wrapper;
   Dsp::SlowThresholderParmsWrapper  mThresholderParmsP1Wrapper;
   Dsp::SlowThresholderParmsWrapper  mThresholderParmsP2Wrapper;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members. These are used int expand.

   // Fuzzy alpha filter sampling period and time constant, seconds.
   float mAlphaFilterTs;
   float mAlphaFilterTc;

   // Fuzzy to crisp threshold.
   float mFuzzyToCrispThreshLo;
   float mFuzzyToCrispThreshHi;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor,
   typedef Ris::BaseCmdLineParms BaseClass;
   SwitchParmsFile();
   void reset();

   // Base class override: Execute a command from the command file to set a 
   // member variable. This is called by the associated command file object
   // for each command in the file.
   void execute(Ris::CmdLineCmd* aCmd) override;

   // Simulate expanded member variables. This is called after the entire
   // section of the command file has been processed.
   void expand() override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Show.
   void show();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance.

#ifdef _SSWSWITCHPARMSFILE_CPP_
   SwitchParmsFile gSwitchParmsFile;
#else
   extern SwitchParmsFile gSwitchParmsFile;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace