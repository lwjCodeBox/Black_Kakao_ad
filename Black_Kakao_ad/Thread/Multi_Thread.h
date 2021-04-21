#pragma once

/// <Developed by developer Wonjong>
/// * ��Ƽ ������ �ڵ���.
/// * Copyright 2020.11.04 �̿���. All rights reserved.
/// </Developed by developer Wonjong>

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

#include <vector>
#include <wtypes.h>

struct ThreadData
{
	HWND h_wnd;
	HANDLE h_kill_event;
	HANDLE h_thread;
	DWORD thread_id;	
};

struct TDataPtr
{	
	std::vector<void *> pThreadItemDataPtr;		
};
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void *FindThreadPtr(ThreadData *ap_data);

// ���� �迭�� �ִ� ������ ������ ������.
void *GetThreadPtr_2(int a_pos);

DWORD WINAPI SM_Thread_Run(void *ap_data);
DWORD WINAPI SM_Thread_Run2(void *ap_data);
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+