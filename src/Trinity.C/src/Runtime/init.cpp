// Graph Engine
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.md file in the project root for full license information.
//
#include "TrinityCommon.h"
#include "Memory/Memory.h"
#include "BackgroundThread/BackgroundThread.h"
#include "Trinity/Diagnostics/LogAutoFlushTask.h"

/* Should only be reached from CLR*/
DLL_EXPORT VOID __stdcall __INIT_TRINITY_C__()
{
#ifdef TRINITY_PLATFORM_WINDOWS
    Memory::LargePageMinimum = GetLargePageMinimum();
#endif
    Memory::GetWorkingSetSize();

#ifndef TRINITY_DISABLE_PREEMPTIVE
    Runtime::ProbeCLRMethodAddresses();
#endif

#ifdef TRINITY_OPTIONAL_PREEMPTIVE
    Runtime::__transition_enabled = true;
#endif

    BackgroundThread::TaskScheduler::Start();
}