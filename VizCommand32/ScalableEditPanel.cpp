// ヘッダのインクルード
// 独自のヘッダ
#include "ScalableEditPanel.h"	// CScalableEditPanel

// コンストラクタCScalableEditPanel
CScalableEditPanel::CScalableEditPanel() : CUserControl(){

	// メンバ変数の初期化.
	m_pScalableEdit = NULL;	// m_pScalableEditをNULLで初期化.
	m_nId = 0;	// m_nIdを0で初期化.

}

// デストラクタ~CScalableEditPanel
CScalableEditPanel::~CScalableEditPanel(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CScalableEditPanel::RegisterClass(HINSTANCE hInstance){

	// ウィンドウクラスの登録.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(WHITE_BRUSH));	// CUserControl::RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
BOOL CScalableEditPanel::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackgroundを指定.
	return CUserControl::RegisterClass(hInstance, _T("CScalableEditPanel"), hbrBackground);	// CUserControl::RegisterClassで登録.

}

// ウィンドウ作成関数Create.
BOOL CScalableEditPanel::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウの作成.
	m_nId = hMenu;	// m_nIdにhMenuを格納.
	BOOL bRet = CUserControl::Create(_T("CScalableEditPanel"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, m_nId, hInstance);	// CWindow::Createで作成.

	// 成功.
	if (bRet){	// bRetがTRUE.

		// 子スカラブルエディットコントロールの生成.
		m_pScalableEdit = new CScalableEdit();	// CScalableEditオブジェクトを生成し, ポインタをm_pScalableEditに格納.
		BOOL bRet2 = m_pScalableEdit->Create(_T(""), ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, m_x, m_y, m_iClientAreaWidth, m_iClientAreaHeight, m_hWnd, m_nId + 100, hInstance);	// m_pScalableEdit->Createで子スカラブルエディットコントロール生成.
		if (bRet2){	// bRet2がTRUE.
			// リサイズ.
			MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_pScalableEdit->m_iHeight, TRUE);	// MoveWindowでm_pScalableEdit->m_iHeightの高さにリサイズ.
		}

	}

	// 戻り値を返す.
	return bRet;	// bRetを返す.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CScalableEditPanel::Destroy(){

	// スカラブルエディットコントロールの破棄.
	if (m_pScalableEdit != NULL){	// m_pScalableEditがNULLでなければ.
		m_pScalableEdit->Destroy();	// m_pScalableEdit->Destroyで破棄.
		delete m_pScalableEdit;	// deleteでm_pScalableEditを解放.
		m_pScalableEdit = NULL;	// m_pScalableEditにNULLをセット.
	}

	// 親ウィンドウのDestroyを呼ぶ.
	CUserControl::Destroy();	// CUserControl::Destroyを呼ぶ.

}

// ウィンドウの作成が開始された時.
int CScalableEditPanel::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// 親のOnCreateを呼ぶ.
	return CUserControl::OnCreate(hwnd, lpCreateStruct);	// CUserControl::OnCreateを呼ぶ.

}

// ウィンドウのサイズが変更された時.
void CScalableEditPanel::OnSize(UINT nType, int cx, int cy){

	// 親のOnSizeを呼ぶ.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSizeを呼ぶ.

	// UM_SIZECHILDで子ウィンドウのサイズに合わせる.
	WPARAM wParam;	// WPARAM型wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAMでwParamをセット.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessageでUM_SIZECHILDを送信.

}

// 子から親へウィンドウサイズ変更の要求が発生した時.
void CScalableEditPanel::OnSizeChild(WPARAM wParam, LPARAM lParam){

	// サイズ取り出し.
	int iWidth = LOWORD(wParam);	// LOWORDはiWidth.
	int iHeight = HIWORD(wParam);	// HIWORDはiHeight.

	// サイズセット.
	m_iWidth = iWidth;	// m_iWidthにiWidthをセット.
	m_iHeight = iHeight;	// m_iHeightにiHeightをセット.

	// 自身のウィンドウサイズ変更.
	MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_iHeight, TRUE);	// MoveWindowで子ウィンドウのサイズに合わせる.

}