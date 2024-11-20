
// ImageDialogAppDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ImageDialogApp.h"
#include "ImageDialogAppDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageDialogAppDlg 대화 상자



CImageDialogAppDlg::CImageDialogAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGEDIALOGAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageDialogAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImageDialogAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CImageDialogAppDlg::OnBnClickedButtonDraw)
	ON_BN_CLICKED(IDC_BUTTON_ACTION, &CImageDialogAppDlg::OnBnClickedButtonAction)
	ON_BN_CLICKED(IDC_BUTTON_MAKEUI, &CImageDialogAppDlg::OnBnClickedButtonMakeui)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CImageDialogAppDlg::OnBnClickedButtonOpen)
END_MESSAGE_MAP()


// CImageDialogAppDlg 메시지 처리기

BOOL CImageDialogAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.	
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	isMakeUIButtonTapped = false;
	nCenterX = 80;
	nCenterY = 80;


	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CImageDialogAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CImageDialogAppDlg::OnPaint()
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
HCURSOR CImageDialogAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CImageDialogAppDlg::OnBnClickedButtonMakeui()
{
	isMakeUIButtonTapped = true;

	// m_Image에 데이터가 남아있다면
	if (m_Image != NULL) {
		// 우선 먼저 제거한다. 
		m_Image.Destroy();
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	// Image를 생성 
	// nHeight를 -로 지정한 이유는 Top-Down 방식으로 Image를 생성하기 때문.
	m_Image.Create(nWidth, -nHeight, nBpp);

	// 색상 팔레트 설정
	if (nBpp == 8) {
		// 256개의 색상 정보를 저장하는 배열 
		static RGBQUAD rgb[256];

		for (int i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
			m_Image.SetColorTable(0, 256, rgb);
		}
	}

	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	// memset을 사용할 때는 Top-Down 방식으로 Image를 생성해야 하므로 
	// nHeight를 미리 -로 지정하고 시작하는 것이 좋다.
	memset(fm, 0xff, nWidth * nHeight);

	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			//fm[j * nPitch + i] = (i % 0xff);
			fm[j * nPitch + i] = (0xff);
		}
	}

	// Load한 후, 현재 대화 상자의 디바이스 컨텍스트를 얻어온다. 이를 통해 화면에 그릴 수 있다.
	CClientDC dc(this);

	// 대화 상자에 Image를 그린다.
	m_Image.Draw(dc, 0, 0);
}

void CImageDialogAppDlg::OnBnClickedButtonDraw()
{
	if (isMakeUIButtonTapped) {
		DrawCircle();
		UpdateDisplay();
	}
}


void CImageDialogAppDlg::OnBnClickedButtonAction()
{
	if (isMakeUIButtonTapped) {
		// Action 버튼 클릭 횟수 증가
		actionCount++;

		// 중심 좌표 업데이트 (x += 25, y += 20)
		/*static int nCenterX = 80;
		static int nCenterY = 80;*/

		nCenterX += 35;
		nCenterY += 30;

		// 랜덤한 반지름 생성 (10 ~ 50)
		int nRadius = rand() % 41 + 10; // 10 이상 50 이하의 랜덤 값

		int nGray = 80; // 원의 색상 (그레이스케일 값)

		// Image 정보 가져오기
		int nWidth = m_Image.GetWidth();
		int nHeight = m_Image.GetHeight();
		int nPitch = m_Image.GetPitch();

		unsigned char* fm = (unsigned char*)m_Image.GetBits();

		// **기존 이미지 초기화 (흰색으로 채우기)**
		memset(fm, 255, abs(nPitch) * nHeight);

		// 새 원 그리기
		for (int j = nCenterY - nRadius; j <= nCenterY + nRadius; j++) {
			for (int i = nCenterX - nRadius; i <= nCenterX + nRadius; i++) {
				int dx = i - nCenterX;
				int dy = j - nCenterY;

				if (dx * dx + dy * dy <= nRadius * nRadius) {
					if (j >= 0 && j < nHeight && i >= 0 && i < nWidth) {
						fm[j * nPitch + i] = nGray; // 회색 원
					}
				}
			}
		}

		// 업데이트된 이미지를 다시 화면에 그리기
		UpdateDisplay();

		// 파일 이름 설정 및 저장
		CString fileName;
		fileName.Format(_T("c:\\Image\\save%d.bmp"), actionCount);
		m_Image.Save(fileName);

		// 정보 출력
		CString info;
		info.Format(_T("Circle 위치: (%d, %d), 반지름: %d\n저장 파일: %s"),
			nCenterX, nCenterY, nRadius, fileName);
		AfxMessageBox(info);
	}
}

void CImageDialogAppDlg::DrawCircle()
{
	// 중심 좌표
	int nCenterX = 80;
	int nCenterY = 80;

	// 랜덤한 반지름 생성 (10 ~ 50)
	// 변칙적인 크기를 만들기 위해 rand() 값 사용
	int nRadius = rand() % 41 + 10; // 10 이상 50 이하의 랜덤 값

	int nGray = 80; // 원의 색상 (그레이스케일 값)

	// Image의 정보를 가져오기
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	int nPitch = m_Image.GetPitch();

	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	// **기존 이미지 초기화 (흰색으로 채우기)**
	memset(fm, 255, abs(nPitch) * nHeight);

	// 원의 사각형 범위 내 픽셀 처리
	for (int j = nCenterY - nRadius; j <= nCenterY + nRadius; j++) {
		for (int i = nCenterX - nRadius; i <= nCenterX + nRadius; i++) {
			// (i, j)가 원의 내부에 있는지 확인
			int dx = i - nCenterX;
			int dy = j - nCenterY;

			if (dx * dx + dy * dy <= nRadius * nRadius) {
				// 픽셀 데이터 설정 (범위를 벗어나지 않도록 확인)
				if (j >= 0 && j < nHeight && i >= 0 && i < nWidth) {
					fm[j * nPitch + i] = nGray;
				}
			}
		}
	}
}

void CImageDialogAppDlg::UpdateDisplay()
{
	// 화면에 이미지 다시 그리기
	CClientDC dc(this);
	m_Image.Draw(dc, 0, 0);
}

#include <string>
#include <vector>

using namespace std;
void CImageDialogAppDlg::OnBnClickedButtonOpen()
{
	if (isMakeUIButtonTapped) {

		CFileDialog fileDlg(TRUE, _T("bmp"), NULL, OFN_FILEMUSTEXIST,
			_T("Image Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"));
		if (fileDlg.DoModal() == IDOK)
		{
			CString filePath = fileDlg.GetPathName();

			// 이미지 로드
			if (!m_Image.IsNull()) {
				m_Image.Destroy(); // 기존 이미지 초기화
			}

			HRESULT hr = m_Image.Load(filePath);
			if (FAILED(hr)) {
				AfxMessageBox(_T("이미지 파일을 불러오지 못했습니다."));
				return;
			}

			// 이미지 출력
			CClientDC dc(this);
			m_Image.Draw(dc, 0, 0);

			// 중심 좌표 계산
			int centerX = m_Image.GetWidth() / 2;
			int centerY = m_Image.GetHeight() / 2;

			nCenterX = 80;
			nCenterY = 80;

			isMakeUIButtonTapped = false;
		}

	}
}
