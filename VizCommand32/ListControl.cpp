// ヘッダのインクルード
// 独自のヘッダ
#include "ListControl.h"	// CListControl

// コンストラクタCListControl
CListControl::CListControl() : CCustomControl(){

}

// デストラクタ~CListControl
CListControl::~CListControl(){

}

// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CListControl::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウクラス名が"SysListView32"なカスタムコントロールを作成.
	return CCustomControl::Create(_T("SysListView32"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, (HMENU)hMenu, hInstance);	// CCustomControl::Createでリストコントロールを作成.

}

// ウィンドウの作成が開始された時.
int CListControl::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// UM_SIZECHILDで子ウィンドウのサイズに合わせる.
	WPARAM wParam;	// WPARAM型wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAMでwParamをセット.
	SendMessage(GetParent(hwnd), UM_SIZECHILD, wParam, (LPARAM)hwnd);	// SendMessageでUM_SIZECHILDを送信.

	// 常にウィンドウ作成に成功するものとする.
	return CCustomControl::OnCreate(hwnd, lpCreateStruct);	// CCustomControl::OnCreateを呼ぶ.

}

// ウィンドウのサイズが変更された時.
void CListControl::OnSize(UINT nType, int cx, int cy){

	// 親クラスのOnSize.
	CCustomControl::OnSize(nType, cx, cy);	// CCustomControl::OnSizeを呼ぶ.

	// UM_SIZECHILDで子ウィンドウのサイズに合わせる.
	WPARAM wParam;	// WPARAM型wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAMでwParamをセット.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessageでUM_SIZECHILDを送信.

}