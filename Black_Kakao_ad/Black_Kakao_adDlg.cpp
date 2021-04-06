
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
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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
END_MESSAGE_MAP()


// CBlackKakaoadDlg 메시지 처리기

BOOL CBlackKakaoadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

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

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CBlackKakaoadDlg::OnBnClickedOk()
{
#if 0 // 원본
	hwnd_KakaoMain = ::FindWindow(NULL, L"카카오톡");
	hwnd_KakaoAd = ::FindWindowEx(hwnd_KakaoMain, NULL, L"EVA_Window", NULL);
	hwnd_KakaoChildWnd = ::FindWindowEx(hwnd_KakaoMain, NULL, L"EVA_ChildWindow", NULL);

	/*QMessageBox MsgBox;

	MsgBox.setInformativeText("Hide KakaoTalk Ad!!\n");

	MsgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

	MsgBox.setDefaultButton(QMessageBox::Ok);*/

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
		//::SetWindowPos(hwnd_KakaoAd, HWND_BOTTOM, NULL, NULL, NULL, NULL, /*SWP_NOACTIVATE*/SWP_NOACTIVATE/*SWP_HIDEWINDOW*/);
		::SendMessage(hwnd_KakaoAd, WM_CLOSE, NULL, NULL);
		::SetWindowPos(hwnd_KakaoChildWnd, HWND_BOTTOM, NULL, NULL, (Rect.right - Rect.left - 2), (Rect.bottom - Rect.top - 33), SWP_NOMOVE);		
	}
	
	//CDialogEx::OnOK();

#endif
} 
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

LRESULT CBlackKakaoadDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{	
	if (hwnd_KakaoMain != NULL) {				
		::GetWindowRect(hwnd_KakaoMain, &m_Kakao_Rect);
		::SetWindowPos(hwnd_KakaoChildWnd, HWND_BOTTOM, NULL, NULL, (m_Kakao_Rect.right - m_Kakao_Rect.left - 2), (m_Kakao_Rect.bottom - m_Kakao_Rect.top - 33), SWP_NOMOVE);
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CBlackKakaoadDlg::OnBnClickedAutoRunBtn()
{
	HKEY hkey;

	// 해당 경로의 레지스트리를 open 한다.
	LONG reg = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0L, KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hkey);
	//LONG reg = RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Kakao", 0L, KEY_ALL_ACCESS, &hkey);

	// 레지스트리를 성공적으로 open 하였다면 ERROR_SUCCESS값이 reg 에 저장된다.
	if (ERROR_SUCCESS == reg) {


		CString sValName = L"VALUENAME";
		CString sVal = _T("Test");
		TCHAR atcvalue[MAX_PATH];
		ZeroMemory(atcvalue, sizeof(atcvalue));
		_tcscpy_s(atcvalue, sVal.GetLength() + 1, sVal.GetBuffer());

		// 레지스트리의 run 항목에 자동 실행될 프로그램의 경로를 저장한다.
		reg = ::RegSetValueEx(hkey, sValName, 0, REG_SZ, (LPBYTE)atcvalue, sValName.GetLength() + 1);

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
	//LONG reg = RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Kakao", 0L, KEY_ALL_ACCESS, &hkey);

	// 레지스트리를 성공적으로 open 하였다면 ERROR_SUCCESS값이 reg 에 저장된다.
	if (ERROR_SUCCESS == reg) {

		reg = RegDeleteValue(hkey, L"VALUENAME");

		if (reg == ERROR_SUCCESS) MessageBox(L"삭제 성공");
		else MessageBox(L"삭제 실패");


		// 오픈한 키를 닫는다.
		RegCloseKey(hkey);
	}
	else MessageBox(L"not open");
		
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+