// ヘッダのインクルード
// 独自のヘッダ
#include "FileListControlPanel.h"	// CFileListControlPanel
#include <commctrl.h>	// コモンコントロール

// コンストラクタCFileListControlPanel
CFileListControlPanel::CFileListControlPanel() : CListControlPanel(){

	// メンバの初期化.
	m_tstrPath = _T("");	// m_tstrPathに""をセット.

}

// デストラクタ~CFileListControlPanel
CFileListControlPanel::~CFileListControlPanel(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CFileListControlPanel::RegisterClass(HINSTANCE hInstance){

	// ウィンドウクラスの登録.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(WHITE_BRUSH));	// CUserControl::RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
BOOL CFileListControlPanel::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackgroundを指定.
	return CUserControl::RegisterClass(hInstance, _T("CFileListControlPanel"), hbrBackground);	// CUserControl::RegisterClassで登録.

}

// ウィンドウ作成関数Create.
BOOL CFileListControlPanel::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウの作成.
	m_nId = hMenu;	// m_nIdにhMenuを格納.
	return CUserControl::Create(_T("CFileListControlPanel"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, m_nId, hInstance);	// CWindow::Createで作成.

}

// ファイルの探索ScanFile.
void CFileListControlPanel::ScanFile(tstring tstrPath){

	// メンバにセット.
	m_tstrPath = tstrPath;	// m_tstrPathにtstrPathをセット.

	// ファイルのスキャン.
	((CFileListControl *)m_pListControl)->ScanFile(tstrPath);	// ((CFileListControl *)m_pListControl)->ScanFileでtstrPathのファイルをスキャン.

}

// ウィンドウの作成が開始された時.
int CFileListControlPanel::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// 親のOnCreateを呼ぶ.
	int iRet = CUserControl::OnCreate(hwnd, lpCreateStruct);	// CUserControl::OnCreateを呼ぶ.

	// 子リストコントロールの生成.
	m_pListControl = new CFileListControl();	// CFileListControlオブジェクトを生成し, ポインタをm_pListControlに格納.
	m_pListControl->Create(_T(""), LVS_ICON, m_x, m_y, m_iClientAreaWidth, m_iClientAreaHeight, hwnd, m_nId + 100, lpCreateStruct->hInstance);	// m_pListControl->Createで子リストコントロール生成.

	// 初回更新タイマーをセット.
	SetTimer(hwnd, 2, 100, NULL);	// SetTimerで更新タイマーをセット.(100ミリ秒==0.1秒)

	// iRetを返す.
	return iRet;	// iRetを返す.

}

// タイマーイベントが発生した時.
void CFileListControlPanel::OnTimer(UINT_PTR nIDEvent){

	// タイマーを終了.
	KillTimer(m_hWnd, 2);	// 初回更新タイマーを終了.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CFileListControlPanel::Destroy(){

	// リストコントロールを削除.
	if (m_pListControl != NULL){	// m_pListControlがNULLでない時.
		m_pListControl->Destroy();	// m_pListControl->Destroyで終了処理.
		delete m_pListControl;	// deleteでm_pListControlを解放.
		m_pListControl = NULL;	// m_pListControlにNULLをセット.
	}

	// 親クラスのDestroyを呼ぶ.
	CListControlPanel::Destroy();	// CListControlPanel::Destroyを呼ぶ.

}