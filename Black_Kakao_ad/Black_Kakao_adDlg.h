
// Black_Kakao_adDlg.h: 헤더 파일
//

#pragma once


// CBlackKakaoadDlg 대화 상자
class CBlackKakaoadDlg : public CDialogEx
{
// 생성입니다.
private:
	HWND hwnd_KakaoMain, hwnd_KakaoLogin, hwnd_KakaoAd, hwnd_KakaoChildWnd;
	RECT m_Kakao_Rect;
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
};
