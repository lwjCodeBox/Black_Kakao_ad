
// Black_Kakao_adDlg.h: 헤더 파일
//

#pragma once
#include "Thread/Multi_Thread.h"

// CBlackKakaoadDlg 대화 상자
class CBlackKakaoadDlg : public CDialogEx
{
// 생성입니다.
private:
	HWND hwnd_KakaoMain, hwnd_KakaoLogin, hwnd_KakaoAd, hwnd_KakaoChildWnd;
	RECT m_Kakao_Rect;

public:
	TDataPtr dataPtr;

private:
	void Print_console(char *p_strMsg, int a_num);
	void Print_console(char *p_strMsg);
	
	void Thread_Allstop();

	// 트레이 아이콘을 추가, 삭제 그리고 변경하는 함수
	void TrayStateSetup(int a_command, const wchar_t *ap_tip_str, int a_icon_id);

public:
	HWND *Get_hwnd_KakaoMain() { return &hwnd_KakaoMain; }
	HWND *Get_hwnd_KakaoChildWnd() { return &hwnd_KakaoChildWnd; }
	RECT *Get_m_Kakao_Rect() { return &m_Kakao_Rect; }

public:
	CBlackKakaoadDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BLACK_KAKAO_AD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedAutoRunBtn();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedAutoUndoBtn();		
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedConsole();

protected:
	afx_msg LRESULT On27001(WPARAM wParam, LPARAM lParam);	
	afx_msg LRESULT OnTrayMessage(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};
