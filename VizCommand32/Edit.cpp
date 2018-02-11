// ヘッダのインクルード
// 独自のヘッダ
#include "Edit.h"	// CEdit

// コンストラクタCEdit
CEdit::CEdit() : CCustomControl(){

}

// デストラクタ~CEdit
CEdit::~CEdit(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CEdit::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)

	// ウィンドウクラス名が"Edit"なカスタムコントロールを作成.
	return CCustomControl::Create(_T("Edit"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, (HMENU)hMenu, hInstance);	// CCustomControl::Createでエディットコントロールを作成.

}

// ウィンドウの作成が開始された時.
int CEdit::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// UM_SIZECHILDで子ウィンドウのサイズに合わせる.
	WPARAM wParam;	// WPARAM型wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAMでwParamをセット.
	SendMessage(GetParent(hwnd), UM_SIZECHILD, wParam, (LPARAM)hwnd);	// SendMessageでUM_SIZECHILDを送信.

	// 常にウィンドウ作成に成功するものとする.
	return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

}

// ウィンドウのサイズが変更された時.
void CEdit::OnSize(UINT nType, int cx, int cy){

	// 親クラスのOnSize.
	CCustomControl::OnSize(nType, cx, cy);	// CCustomControl::OnSizeを呼ぶ.

	// UM_SIZECHILDで子ウィンドウのサイズに合わせる.
	WPARAM wParam;	// WPARAM型wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAMでwParamをセット.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessageでUM_SIZECHILDを送信.

}