
// Black_Kakao_adDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Black_Kakao_ad.h"
#include "Black_Kakao_adDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBlackKakaoadDlg 대화 상자



CBlackKakaoadDlg::CBlackKakaoadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BLACK_KAKAO_AD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TRAY_ICON); //IDR_MAINFRAME
}

void CBlackKakaoadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBlackKakaoadDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CBlackKakaoadDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_AUTO_RUN_BTN, &CBlackKakaoadDlg::OnBnClickedAutoRunBtn)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_AUTO_UNDO_BTN, &CBlackKakaoadDlg::OnBnClickedAutoUndoBtn)	
	ON_BN_CLICKED(IDC_CONSOLE, &CBlackKakaoadDlg::OnBnClickedConsole)
	ON_MESSAGE(27001, &CBlackKakaoadDlg::On27001)		
	ON_MESSAGE(26001, &CBlackKakaoadDlg::OnTrayMessage)
END_MESSAGE_MAP()


// CBlackKakaoadDlg 메시지 처리기

BOOL CBlackKakaoadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
	
	// 닫기 버튼 비활성화.
	GetDlgItem(IDCANCEL)->ShowWindow(false);

	// 트레이 아이콘을 추가한다.
	TrayStateSetup(NIM_ADD, L"카카오톡 광과 제거~", IDI_TRAY_ICON);	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CBlackKakaoadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CBlackKakaoadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBlackKakaoadDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// 트레이 아이콘을 제거한다.
	TrayStateSetup(NIM_DELETE, L"", IDI_TRAY_ICON);

	// 모든 스레드 종료.
	Thread_Allstop();	
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CBlackKakaoadDlg::OnBnClickedOk()
{
#if 0 // 원본
	hwnd_KakaoMain = ::FindWindow(NULL, L"카카오톡");
	hwnd_KakaoAd = ::FindWindowEx(hwnd_KakaoMain, NULL, L"EVA_Window", NULL);
	hwnd_KakaoChildWnd = ::FindWindowEx(hwnd_KakaoMain, NULL, L"EVA_ChildWindow", NULL);

	//if (IDYES == MessageBox(L"광고삭제", L"Title", MB_ICONQUESTION | MB_YESNO)) {
		RECT Rect;
		::GetWindowRect(hwnd_KakaoMain, &Rect);
		::SetWindowPos(hwnd_KakaoAd, NULL, NULL, NULL, NULL, NULL, SWP_NOACTIVATE);
		::SetWindowPos(hwnd_KakaoChildWnd, HWND_BOTTOM, NULL, NULL, (Rect.right - Rect.left - 2), (Rect.bottom - Rect.top - 33), SWP_NOMOVE);

		//this->close();
		CDialogEx::OnOK();
	//}
#else
	// https://jungpaeng.tistory.com/10
	hwnd_KakaoMain = ::FindWindow(NULL, L"카카오톡");

	hwnd_KakaoAd = ::FindWindowEx(hwnd_KakaoMain, NULL, L"EVA_Window", NULL);
	hwnd_KakaoChildWnd = ::FindWindowEx(hwnd_KakaoMain, NULL, L"EVA_ChildWindow", NULL);

	// 광고 삭제 하는 부분.
	if (IDYES == MessageBox(L"광고삭제", L"카카오톡 광고 삭제", MB_ICONQUESTION | MB_YESNO)) {
		
		RECT Rect;
		::GetWindowRect(hwnd_KakaoMain, &Rect);
		::SendMessage(hwnd_KakaoAd, WM_CLOSE, NULL, NULL);
		::SetWindowPos(hwnd_KakaoChildWnd, HWND_BOTTOM, NULL, NULL, (Rect.right - Rect.left - 2), (Rect.bottom - Rect.top - 33), SWP_NOMOVE);		
	}
	
	ThreadData *p = new ThreadData;
	p->h_wnd = m_hWnd;
	dataPtr.pThreadItemDataPtr.push_back(p);

	p->h_kill_event = CreateEvent(NULL, 1, 0, NULL); // 스레드를 위한 이벤트 큐 생성.
	p->h_thread = CreateThread(NULL, 0x80000, SM_Thread_Run, p, 10, &p->thread_id); // 스레드 생성.

	GetDlgItem(IDOK)->EnableWindow(FALSE);
	SetFocus();
	//CDialogEx::OnOK();

#endif
} 
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

LRESULT CBlackKakaoadDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{	
	/*if (hwnd_KakaoMain != NULL) {				
		::GetWindowRect(hwnd_KakaoMain, &m_Kakao_Rect);
		::SetWindowPos(hwnd_KakaoChildWnd, HWND_BOTTOM, NULL, NULL, (m_Kakao_Rect.right - m_Kakao_Rect.left - 2), (m_Kakao_Rect.bottom - m_Kakao_Rect.top - 33), SWP_NOMOVE);
	}*/

	// https://blog.naver.com/tipsware/221124184150
	// 'X 버튼'을 누른 경우에 발생하는 메시지. 
	if (message == WM_CLOSE) {
		//int check = MessageBox(L"창 숨기기??", L"다이얼로그 창 숨김??", MB_ICONQUESTION | MB_OKCANCEL);
		//if (IDCANCEL == check) return 0;

		// 최소화후 숨겨야 화면에 나타나지 않음!
		ShowWindow(SW_SHOWMINIMIZED);
		PostMessage(WM_SHOWWINDOW, FALSE, SW_OTHERUNZOOM);

		return 0;
	}	
	else if (message == WM_DESTROY) {
		int num;
		num = 10;
	}
			
	return CDialogEx::WindowProc(message, wParam, lParam);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

BOOL CBlackKakaoadDlg::PreTranslateMessage(MSG *pMsg)
{	
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_ESCAPE) {
			ShowWindow(SW_SHOWMINIMIZED);
			PostMessage(WM_SHOWWINDOW, FALSE, SW_OTHERUNZOOM);
			
			return true;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CBlackKakaoadDlg::OnBnClickedAutoRunBtn()
{	
	//https://3001ssw.tistory.com/51
	HKEY hkey;

	// 해당 경로의 레지스트리를 open 한다.
	LONG reg = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0L, KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hkey);	

	// 레지스트리를 성공적으로 open 하였다면 ERROR_SUCCESS값이 reg에 저장된다.
	if (ERROR_SUCCESS == reg) {
#if 0 // .exe 파일을 레지스트리에 등록함.
		// 실행 파일이 있는 경로를 얻어옴.
		wchar_t chFilePath[MAX_PATH];
		ZeroMemory(chFilePath, sizeof(chFilePath));

		GetModuleFileName(NULL, chFilePath, 256);		
		rsize_t wcs_len = wcslen(chFilePath) * 2;
		
		wchar_t regiValue[MAX_PATH];
		ZeroMemory(regiValue, sizeof(regiValue));
		_tcscpy_s(regiValue, wcs_len, chFilePath);

		// 레지스트리의 run 항목에 자동 실행될 프로그램의 경로를 저장한다.
		reg = ::RegSetValueEx(hkey, L"Black_Kakao_ad", 0, REG_SZ, (LPBYTE)regiValue, wcs_len + 1);
	
#else // .bat 파일을 레지스트리에 등록함.
		// 실행 파일이 있는 경로를 얻어옴.
		wchar_t dir[MAX_PATH];
		ZeroMemory(dir, sizeof(dir));

		//GetCurrentDirectory(MAX_PATH, dir);
		GetModuleFileName(NULL, dir, 256);
		PathRemoveFileSpec(dir);
		wchar_t *bat = L"\\black_ad.bat";
		wcscat(dir, bat);
		rsize_t wcs_len = wcslen(dir) * 2;
		
		wchar_t regiValue[MAX_PATH];
		ZeroMemory(regiValue, sizeof(regiValue));
		_tcscpy_s(regiValue, wcs_len, dir);

		// 레지스트리의 run 항목에 자동 실행될 프로그램의 경로를 저장한다.
		reg = ::RegSetValueEx(hkey, L"Black_Kakao_ad", 0, REG_SZ, (LPBYTE)regiValue, wcs_len);
#endif

		if (reg == ERROR_SUCCESS) MessageBox(L"등록 성공");
		else MessageBox(L"등록 실패");

		// 오픈한 키를 닫는다.
		RegCloseKey(hkey);
	}

	else MessageBox(L"not open");
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CBlackKakaoadDlg::OnBnClickedAutoUndoBtn()
{
	HKEY hkey;

	// 해당 경로의 레지스트리를 open 한다.
	LONG reg = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0L, KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hkey);	

	// 레지스트리를 성공적으로 open 하였다면 ERROR_SUCCESS값이 reg 에 저장된다.
	if (ERROR_SUCCESS == reg) {

		reg = RegDeleteValue(hkey, L"Black_Kakao_ad");

		if (reg == ERROR_SUCCESS) MessageBox(L"삭제 성공");
		else MessageBox(L"삭제 실패");

		// 오픈한 키를 닫는다.
		RegCloseKey(hkey);
	}
	else MessageBox(L"not open");
		
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CBlackKakaoadDlg::OnBnClickedConsole()
{
	if (AllocConsole()) {
		// 콘솔창 타이틀 설정.
		SetConsoleTitle(L"open console mode");

		// 콘솔창 X버튼 비활성화.
		::EnableMenuItem(::GetSystemMenu(::GetConsoleWindow(), FALSE), SC_CLOSE, MF_DISABLED);
		::DrawMenuBar(::GetConsoleWindow());

		Print_console("+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
		Print_console("      Open Console\n");
		Print_console("+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
		Print_console("\n\n");
	}
	else {
		FreeConsole();
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CBlackKakaoadDlg::Print_console(char *p_strMsg, int a_num)
{
	// 표준 출력 핸들 얻음
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	char strMsg[200];
	sprintf(strMsg, "%d %s", a_num, p_strMsg);

	// 출력
	WriteFile(hConsole, strMsg, strlen(strMsg), NULL, NULL);
}

void CBlackKakaoadDlg::Print_console(char *p_strMsg)
{
	// 표준 출력 핸들 얻음
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	DWORD dwByte(0);
	// 출력할 문자열
	//char *strMsg = NULL;
	char strMsg[200];
	sprintf(strMsg, "%s", p_strMsg);

	// 출력
	WriteFile(hConsole, strMsg, strlen(strMsg), &dwByte, NULL);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

// lParam >> 어떤 스레드가 종료되었는지를 알 수 있는 스레드 정보를 담고 있다.
afx_msg LRESULT CBlackKakaoadDlg::On27001(WPARAM wParam, LPARAM lParam)
{	
	ThreadData *p = (ThreadData *)lParam;

	for (int i = 0; i < (int)dataPtr.pThreadItemDataPtr.size(); i++) {
		if (FindThreadPtr(p)) {
			CloseHandle(p->h_kill_event); // 스레드가 종료되었기 때문에 스레드 이벤트 종료시킴.

			// wParam == 0의 의미는 스스로 죽은 경우. (이 코드에서는 스스로 죽지 않는다. 이사님 코드 참고) 
			if (wParam == 0)
				delete p;
			else
				p->h_thread = NULL;

			break;
		}
		else {
			Print_console("Do not find Thread Data!!\n");			
		}
	}

	return 0;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CBlackKakaoadDlg::Thread_Allstop()
{
	ThreadData *p;
	int count = dataPtr.pThreadItemDataPtr.size();
	for (int i = 0; i < count; i++) {
		p = (ThreadData *)GetThreadPtr_2(i);
		SetEvent(p->h_kill_event);
	}
	
	Print_console("Shut down the working threads.  ", count);

	MSG msg;
	while (0 < count) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == 27001) {
				count--;
				msg.wParam = 0;
			}
			TranslateMessage(&msg);
			// DispatchMessage()함수를 통해서 27001 메시지를 처리하게 된다.
			// (On27001(WPARAM wParam, LPARAM lParam) 이 함수로 빠짐.)
			DispatchMessage(&msg);
		}
	}
	
	std::vector<void *>().swap(dataPtr.pThreadItemDataPtr); // 임의 백터와 교환을 한다.
	
	Print_console("*****Thread All Stop Finish!!!*****\n", 99);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

// 트레이 아이콘을 추가, 삭제 그리고 변경하는 함수
void CBlackKakaoadDlg::TrayStateSetup(int a_command, const wchar_t *ap_tip_str, int a_icon_id)
{
	NOTIFYICONDATA taskbar_notify_data;
	
	// 트레이 아이콘의 설명글을 업데이트 한다.
	wcscpy_s(taskbar_notify_data.szTip, 128, ap_tip_str);

	// 트레이 아이콘의 상태를 업데이트 한다.
	switch (a_command) {
	case NIM_ADD:
		taskbar_notify_data.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
		break;
	case NIM_DELETE:
		taskbar_notify_data.uFlags = 0;
		break;
	case NIM_MODIFY:
		taskbar_notify_data.uFlags = NIF_TIP | NIF_ICON;
		break;
	}

	taskbar_notify_data.uID = (UINT)a_icon_id; //(UINT)IDR_MAINFRAME;
	taskbar_notify_data.cbSize = sizeof(NOTIFYICONDATA);
	taskbar_notify_data.hWnd = this->m_hWnd;
	taskbar_notify_data.uCallbackMessage = 26001;
	taskbar_notify_data.hIcon = AfxGetApp()->LoadIcon(a_icon_id);
	
	// 트레이 아이콘에 정보를 적용한다.
	Shell_NotifyIcon(a_command, &taskbar_notify_data);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//// 트레이 아이콘의 툴팁을 변경한다.
//void CExamMFCDlg::OnBnClickedTipModifyBtn()
//{
//	CString str;
//	// 사용자가 에디트 컨트롤에 추가한 문자열을 얻는다.
//	GetDlgItemText(IDC_TIP_STR_EDIT, str);
//	// 얻은 문자열로 트레이 아이콘의 툴팁을 변경한다.
//	TrayStateSetup(NIM_MODIFY, str, IDI_TRAY_ICON);
//}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

// OnTrayMessage() is On26001 of Custome Message Handler
afx_msg LRESULT CBlackKakaoadDlg::OnTrayMessage(WPARAM wParam, LPARAM lParam)
{	
	if (lParam == WM_RBUTTONUP) {		
		CMenu menu;

		menu.CreatePopupMenu();  // 팝업 메뉴를 생성한다.		

		menu.AppendMenu(MF_STRING, 20000, L"종료");

		CString str;
		// 5개의 메뉴 항목을 추가한다.
		for (int i = 1; i < 3; i++) {
			str.Format(L"%d번 메뉴 항목", i);
			// 각 항목을 선택하면 WM_COMMAND메시지가 발생하고 각 ID는
			// wParam 항목의 하위 16비트에 저장되어 있다.
			menu.AppendMenu(MF_STRING, 20000 + i, str);
		}

		CPoint pos;
		GetCursorPos(&pos);  // 화면 상에 마우스 좌표를 얻는다!

		// 지정한 위치에 팝업메뉴를 출력한다.
		menu.TrackPopupMenu(TPM_LEFTALIGN, pos.x, pos.y, this);
		
		// 생성된 팝업 메뉴를 삭제한다.
		menu.DestroyMenu();

		/*
		CPoint ptMouse;
		::GetCursorPos(&ptMouse);
		CMenu menu;
		menu.LoadMenu(IDR_TRAY);
		CMenu *pMenu = menu.GetSubMenu(0); // 활성화 할 메뉴 지정
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, ptMouse.x, ptMouse.y, AfxGetMainWnd());
		*/
	}	
	else if (lParam == WM_LBUTTONDBLCLK) {		
		// 다이얼로그 다시 활성화.
		ShowWindow(SW_RESTORE);
				
		// 다이얼로그 최상위로 올리기.
		SetForegroundWindow();
	}	

	return 0;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

BOOL CBlackKakaoadDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (wParam >= 20000 && wParam < 20003) {  //팝업 메뉴에서 항목이 선택된 경우!
		if (20000 == wParam) {			
			// 프로그램 종료
			PostQuitMessage(0); // DestroyWindow();			
		}
		else {
			CString str;
			str.Format(L"%d번 메뉴 항목이 선택되었습니다!!", wParam - 20000);
			AfxMessageBox(str);
		}
	}

	return CDialogEx::OnCommand(wParam, lParam);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+