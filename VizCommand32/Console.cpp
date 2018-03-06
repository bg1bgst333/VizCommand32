// ヘッダのインクルード
// 独自のヘッダ
#include "Console.h"	// CConsole

// コンストラクタCConsole
CConsole::CConsole() : CScalableEditPanel(){

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CConsole::RegisterClass(HINSTANCE hInstance){

	// ウィンドウクラスの登録.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(WHITE_BRUSH));	// CUserControl::RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
BOOL CConsole::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackgroundを指定.
	return CUserControl::RegisterClass(hInstance, _T("CConsole"), hbrBackground);	// CUserControl::RegisterClassで登録.

}

// ウィンドウ作成関数Create.
BOOL CConsole::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウの作成.
	m_nId = hMenu;	// m_nIdにhMenuを格納.
	BOOL bRet = CUserControl::Create(_T("CConsole"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, m_nId, hInstance);	// CWindow::Createで作成.

	// 成功.
	if (bRet){	// bRetがTRUE.

		// 子コンソールコアの生成.
		m_pScalableEdit = new CConsoleCore();	// CConsoleCoreオブジェクトを生成し, ポインタをm_pScalableEditに格納.
		BOOL bRet2 = m_pScalableEdit->Create(_T(""), 0, m_x, m_y, m_iClientAreaWidth, m_iClientAreaHeight, m_hWnd, m_nId + 100, hInstance);	// m_pScalableEdit->Createで子スカラブルエディットコントロール生成.
		if (bRet2){	// bRet2がTRUE.
			// リサイズ.
			MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_pScalableEdit->m_iHeight, TRUE);	// MoveWindowでm_pScalableEdit->m_iHeightの高さにリサイズ.
		}

	}

	// 戻り値を返す.
	return bRet;	// bRetを返す.

}

// ウィンドウのサイズが変更された時.
void CConsole::OnSize(UINT nType, int cx, int cy){

	// 親のOnSizeを呼ぶ.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSizeを呼ぶ.

	// 子コンソールコアのリサイズ.
	if (m_pScalableEdit != NULL){	// NULLでなければ.
		MoveWindow(m_pScalableEdit->m_hWnd, m_pScalableEdit->m_x, m_pScalableEdit->m_y, cx, cy, TRUE);	// MoveWindowで子コンソールコアをリサイズ.
	}

	// UM_SIZECHILDで子ウィンドウのサイズに合わせる.
	WPARAM wParam;	// WPARAM型wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAMでwParamをセット.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessageでUM_SIZECHILDを送信.

}