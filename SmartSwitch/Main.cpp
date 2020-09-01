
#include "stdafx.h"

#include "risThreadsProcess.h"
#include "MainInit.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"

#include "sswTimerThread.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

int main(int argc,char** argv)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Begin program.

   main_initialize(argc, argv);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Launch program threads.

   if (true)
   {
      SSW::gTimerThread = new SSW::TimerThread;
      SSW::gTimerThread->launchThread();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show program threads.

   Ris::Threads::showCurrentThreadInfo();
   if (SSW::gTimerThread)   SSW::gTimerThread->showThreadInfo();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Execute console command line executive, wait for user to exit.

   CmdLineExec* tExec = new CmdLineExec;
   Ris::gCmdLineConsole.execute(tExec);
   delete tExec;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Shutdown program threads.

   if (SSW::gTimerThread)   SSW::gTimerThread->shutdownThread();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Delete program threads.

   if (SSW::gTimerThread)
   {
      delete SSW::gTimerThread;
      SSW::gTimerThread = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // End program.

   main_finalize();
   return 0;
}
