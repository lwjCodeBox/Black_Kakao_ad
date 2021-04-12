﻿
// Black_Kakao_ad.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "Black_Kakao_ad.h"
#include "Black_Kakao_adDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBlackKakaoadApp

BEGIN_MESSAGE_MAP(CBlackKakaoadApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CBlackKakaoadApp 생성

CBlackKakaoadApp::CBlackKakaoadApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CBlackKakaoadApp 개체입니다.

CBlackKakaoadApp theApp;


// CBlackKakaoadApp 초기화

BOOL CBlackKakaoadApp::InitInstance()
{
	CWinApp::InitInstance();

	CBlackKakaoadDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}