// ヘッダのインクルード
// 独自のヘッダ
#include "StaticPanel.h"	// CStaticPanel

// コンストラクタCStaticPanel
CStaticPanel::CStaticPanel() : CUserControl(){

	// メンバ変数の初期化.
	m_pStatic = NULL;	// m_pStaticをNULLで初期化.
	m_nId = 0;	// m_nIdを0で初期化.
	m_hbrBackground = NULL;	// m_hbrBackgroundをNULLで初期化.
	m_hFont = NULL;	// m_hFontをNULLで初期化.

}

// デストラクタ~CStaticPanel
CStaticPanel::~CStaticPanel(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CStaticPanel::RegisterClass(HINSTANCE hInstance){

	// ウィンドウクラスの登録.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(WHITE_BRUSH));	// CUserControl::RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
BOOL CStaticPanel::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackgroundを指定.
	return CUserControl::RegisterClass(hInstance, _T("CStaticPanel"), hbrBackground);	// CUserControl::RegisterClassで登録.

}

// ウィンドウ作成関数Create.
BOOL CStaticPanel::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウの作成.
	m_nId = hMenu;	// m_nIdにhMenuを格納.
	BOOL bRet = CUserControl::Create(_T("CStaticPanel"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, m_nId, hInstance);	// CWindow::Createで作成.

	// 濃緑ブラシ作成.
	m_hbrBackground = CreateSolidBrush(RGB(0x0, 0x7f, 0x0));	// CreateSolidBrushで濃緑ブラシを作成し, m_hbrBackgroundに格納.

	// フォントの生成.
	m_hFont = CreateFont(32, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("ＭＳ 明朝"));	// CreateFontで"ＭＳ 明朝"フォントのGDIオブジェクトを新規に作成し, hFontに格納.(設定はデフォルトのものにしておく.)

	// Createの戻り値を返す.
	return bRet;	// bRetを返す.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CStaticPanel::Destroy(){

	// フォントの破棄.
	if (m_hFont != NULL){	// m_hFontがNULLでない時.
		DeleteObject(m_hFont);	// DeleteObjectで削除.
		m_hFont = NULL;	// m_hFontにNULLをセット.
	}

	// ブラシの破棄.
	if (m_hbrBackground != NULL){	// m_hbrBackgroundがNULLでない時.
		DeleteObject(m_hbrBackground);	// DeleteObjectで削除.
		m_hbrBackground = NULL;	// m_hbrBackgroundにNULLをセット.
	}

	// スタティックコントロールの破棄.
	if (m_pStatic != NULL){	// m_pStaticがNULLでなければ.
		m_pStatic->Destroy();	// m_pStatic->Destroyで破棄.
		delete m_pStatic;	// deleteでm_pStaticを解放.
		m_pStatic = NULL;	// m_pStaticにNULLをセット.
	}

	// 親ウィンドウのDestroyを呼ぶ.
	CUserControl::Destroy();	// CUserControl::Destroyを呼ぶ.

}

// ウィンドウの作成が開始された時.
int CStaticPanel::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// 子エスタティックコントロールの生成.
	m_pStatic = new CStatic();	// CStaticオブジェクトを生成し, ポインタをm_pStaticに格納.
	m_pStatic->Create(_T(""), SS_REALSIZECONTROL | SS_CENTER, m_x, m_y, m_iClientAreaWidth, m_iClientAreaHeight, hwnd, m_nId + 100, lpCreateStruct->hInstance);	// m_pStatic->Createで子スタティックコントロール生成.

	// 親のOnCreateを呼ぶ.
	return CUserControl::OnCreate(hwnd, lpCreateStruct);	// CUserControl::OnCreateを呼ぶ.

}

// ウィンドウのサイズが変更された時.
void CStaticPanel::OnSize(UINT nType, int cx, int cy){

	// 親のOnSizeを呼ぶ.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSizeを呼ぶ.

	// 子スタティックコントロールのリサイズ.
	if (m_pStatic != NULL){	// m_pStaticがNULLでない時.
		MoveWindow(m_pStatic->m_hWnd, m_pStatic->m_x, m_pStatic->m_y, cx, cy, TRUE);	// MoveWindowでリサイズ.
	}

}

// 子スタティックコントロールの描画時.
HBRUSH CStaticPanel::OnCtlColorStatic(HDC hDC, HWND hStatic){

	// 背景を濃緑, テキストを白にする.
	SetBkColor(hDC, RGB(0x0, 0x7f, 0x0));	// 背景は濃緑.
	SetTextColor(hDC, RGB(0xff, 0xff, 0xff));	// テキストは白.
	SendMessage(m_pStatic->m_hWnd, WM_SETFONT, (WPARAM)m_hFont, MAKELPARAM(FALSE, 0));	// WM_SETFONTでフォントをセット.
	return m_hbrBackground;	// m_hbrBackgroundを返す.

}