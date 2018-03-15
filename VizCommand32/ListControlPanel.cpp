// ヘッダのインクルード
// 独自のヘッダ
#include "ListControlPanel.h"	// CListControlPanel
#include <commctrl.h>	// コモンコントロール

// コンストラクタCListControlPanel
CListControlPanel::CListControlPanel() : CUserControl(){

	// メンバ変数の初期化.
	m_pListControl = NULL;	// m_pListControlをNULLで初期化.
	m_nId = 0;	// m_nIdを0で初期化.

}

// デストラクタ~CListControlPanel
CListControlPanel::~CListControlPanel(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CListControlPanel::RegisterClass(HINSTANCE hInstance){

	// ウィンドウクラスの登録.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(WHITE_BRUSH));	// CUserControl::RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
BOOL CListControlPanel::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackgroundを指定.
	return CUserControl::RegisterClass(hInstance, _T("CListControlPanel"), hbrBackground);	// CUserControl::RegisterClassで登録.

}

// ウィンドウ作成関数Create.
BOOL CListControlPanel::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウの作成.
	m_nId = hMenu;	// m_nIdにhMenuを格納.
	return CUserControl::Create(_T("CListControlPanel"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, m_nId, hInstance);	// CWindow::Createで作成.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CListControlPanel::Destroy(){

	// リストコントロールの破棄.
	if (m_pListControl != NULL){	// m_pListControlがNULLでなければ.
		m_pListControl->Destroy();	// m_pListControl->Destroyで破棄.
		delete m_pListControl;	// deleteでm_pListControlを解放.
		m_pListControl = NULL;	// m_pListControlにNULLをセット.
	}

	// 親ウィンドウのDestroyを呼ぶ.
	CUserControl::Destroy();	// CUserControl::Destroyを呼ぶ.

}

// ウィンドウの作成が開始された時.
int CListControlPanel::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// 子リストコントロールの生成.
	m_pListControl = new CListControl();	// CListControlオブジェクトを生成し, ポインタをm_pListControlに格納.
	m_pListControl->Create(_T(""), LVS_ICON, m_x, m_y, m_iClientAreaWidth, m_iClientAreaHeight, hwnd, m_nId + 100, lpCreateStruct->hInstance);	// m_pListControl->Createで子リストコントロール生成.

	// 親のOnCreateを呼ぶ.
	return CUserControl::OnCreate(hwnd, lpCreateStruct);	// CUserControl::OnCreateを呼ぶ.

}

// ウィンドウのサイズが変更された時.
void CListControlPanel::OnSize(UINT nType, int cx, int cy){

	// 親のOnSizeを呼ぶ.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSizeを呼ぶ.

	// 子リストコントロールのリサイズ.
	if (m_pListControl != NULL){	// m_pListControlがNULLでない時.
		MoveWindow(m_pListControl->m_hWnd, m_pListControl->m_x, m_pListControl->m_y, cx, cy, TRUE);	// MoveWindowでリサイズ.
	}

	// UM_SIZECHILDで子ウィンドウのサイズに合わせる.
	WPARAM wParam;	// WPARAM型wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAMでwParamをセット.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessageでUM_SIZECHILDを送信.

}

// 子から親へウィンドウサイズ変更の要求が発生した時.
void CListControlPanel::OnSizeChild(WPARAM wParam, LPARAM lParam){

	// サイズ取り出し.
	int iWidth = LOWORD(wParam);	// LOWORDはiWidth.
	int iHeight = HIWORD(wParam);	// HIWORDはiHeight.

	// サイズセット.
	m_iWidth = iWidth;	// m_iWidthにiWidthをセット.
	m_iHeight = iHeight;	// m_iHeightにiHeightをセット.

	// 自身のウィンドウサイズ変更.
	MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_iHeight, TRUE);	// MoveWindowで子ウィンドウのサイズに合わせる.

}