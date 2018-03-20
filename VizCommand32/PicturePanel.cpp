// ヘッダのインクルード
// 独自のヘッダ
#include "PicturePanel.h"	// CPicturePanel

// コンストラクタCPicturePanel
CPicturePanel::CPicturePanel() : CUserControl(){

	// メンバ変数の初期化.
	m_pPicture = NULL;	// m_pPictureをNULLで初期化.
	m_nId = 0;	// m_nIdを0で初期化.

}

// デストラクタ~CPicturePanel
CPicturePanel::~CPicturePanel(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CPicturePanel::RegisterClass(HINSTANCE hInstance){

	// ウィンドウクラスの登録.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(WHITE_BRUSH));	// CUserControl::RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
BOOL CPicturePanel::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackgroundを指定.
	return CUserControl::RegisterClass(hInstance, _T("CPicturePanel"), hbrBackground);	// CUserControl::RegisterClassで登録.

}

// ウィンドウ作成関数Create.
BOOL CPicturePanel::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウの作成.
	m_nId = hMenu;	// m_nIdにhMenuを格納.
	return CUserControl::Create(_T("CPicturePanel"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, m_nId, hInstance);	// CWindow::Createで作成.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CPicturePanel::Destroy(){

	// ピクチャーコントロールの破棄.
	if (m_pPicture != NULL){	// m_pPictureがNULLでなければ.
		m_pPicture->Destroy();	// m_pPicture->Destroyで破棄.
		delete m_pPicture;	// deleteでm_pPictureを解放.
		m_pPicture = NULL;	// m_pPictureにNULLをセット.
	}

	// 親ウィンドウのDestroyを呼ぶ.
	CUserControl::Destroy();	// CUserControl::Destroyを呼ぶ.

}

// ウィンドウの作成が開始された時.
int CPicturePanel::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// 子ピクチャーコントロールの生成.
	m_pPicture = new CPicture();	// CPictureオブジェクトを生成し, ポインタをm_pPictureに格納.
	m_pPicture->Create(_T(""), 0, m_x, m_y, m_iClientAreaWidth, m_iClientAreaHeight, hwnd, m_nId + 100, lpCreateStruct->hInstance);	// m_pPicture->Createで子ピクチャーコントロール生成.

	// 親のOnCreateを呼ぶ.
	return CUserControl::OnCreate(hwnd, lpCreateStruct);	// CUserControl::OnCreateを呼ぶ.

}

// ウィンドウのサイズが変更された時.
void CPicturePanel::OnSize(UINT nType, int cx, int cy){

	// 親のOnSizeを呼ぶ.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSizeを呼ぶ.

	// 子ピクチャーコントロールのリサイズ.
	if (m_pPicture != NULL){	// m_pPictureがNULLでない時.
		MoveWindow(m_pPicture->m_hWnd, m_pPicture->m_x, m_pPicture->m_y, cx, cy, TRUE);	// MoveWindowでリサイズ.
	}

}