// ヘッダのインクルード
// 独自のヘッダ
#include "EditPanel.h"	// CEditPanel

// コンストラクタCEditPanel
CEditPanel::CEditPanel() : CUserControl(){

	// メンバ変数の初期化.
	m_pEdit = NULL;	// m_pEditをNULLで初期化.
	m_nId = 0;	// m_nIdを0で初期化.

}

// デストラクタ~CEditPanel
CEditPanel::~CEditPanel(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CEditPanel::RegisterClass(HINSTANCE hInstance){

	// ウィンドウクラスの登録.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(WHITE_BRUSH));	// CUserControl::RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
BOOL CEditPanel::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackgroundを指定.
	return CUserControl::RegisterClass(hInstance, _T("CEditPanel"), hbrBackground);	// CUserControl::RegisterClassで登録.

}

// ウィンドウ作成関数Create.
BOOL CEditPanel::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウの作成.
	m_nId = hMenu;	// m_nIdにhMenuを格納.
	return CUserControl::Create(_T("CEditPanel"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, m_nId, hInstance);	// CWindow::Createで作成.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CEditPanel::Destroy(){

	// エディットコントロールの破棄.
	if (m_pEdit != NULL){	// m_pEditがNULLでなければ.
		m_pEdit->Destroy();	// m_pEdit->Destroyで破棄.
		delete m_pEdit;	// deleteでm_pEditを解放.
		m_pEdit = NULL;	// m_pEditにNULLをセット.
	}

	// 親ウィンドウのDestroyを呼ぶ.
	CUserControl::Destroy();	// CUserControl::Destroyを呼ぶ.

}

// ウィンドウの作成が開始された時.
int CEditPanel::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// 子エディットコントロールの生成.
	m_pEdit = new CEdit();	// CEditオブジェクトを生成し, ポインタをm_pEditに格納.
	m_pEdit->Create(_T(""), ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, m_x, m_y, m_iClientAreaWidth, m_iClientAreaHeight, hwnd, m_nId + 100, lpCreateStruct->hInstance);	// m_pEdit->Createで子エディットコントロール生成.

	// 親のOnCreateを呼ぶ.
	return CUserControl::OnCreate(hwnd, lpCreateStruct);	// CUserControl::OnCreateを呼ぶ.

}

// ウィンドウのサイズが変更された時.
void CEditPanel::OnSize(UINT nType, int cx, int cy){

	// 親のOnSizeを呼ぶ.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSizeを呼ぶ.

	// 子エディットコントロールのリサイズ.
	if (m_pEdit != NULL){	// m_pEditがNULLでない時.
		MoveWindow(m_pEdit->m_hWnd, m_pEdit->m_x, m_pEdit->m_y, cx, cy, TRUE);	// MoveWindowでリサイズ.
	}

}