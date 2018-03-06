// ヘッダのインクルード
// 独自のヘッダ
#include "ConsoleCore.h"	// CConsoleCore

// コンストラクタCConsoleCore
CConsoleCore::CConsoleCore() : CScalableEdit(){

	// メンバの初期化.
	m_tstrCommandString = _T("");	// m_tstrCommandStringを""で初期化.

}

// コマンド文字列の取得関数GetCommandString.
tstring CConsoleCore::GetCommandString(){

	// テキストの取得.
	m_tstrCommandString = GetText();	// GetTextで取得した文字列をm_tstrCommandStringに格納.

	// コマンド文字列を返す.
	return m_tstrCommandString;	// m_tstrCommandStringを返す.

}

// キーが押された時.
int CConsoleCore::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){

	// リターンキーが押された時.
	if (nChar == VK_RETURN){	// nCharがVK_RETURNの時.

		// コマンド文字列の取得.
		GetCommandString();	// GetCommandStringでコマンド文字列を取得.
		MessageBox(m_hWnd, m_tstrCommandString.c_str(), _T("VizCommand"), MB_OK);	// MessageBoxでm_tstrCommandStringを表示.

	}

	// 親クラスの既定処理.
	return CScalableEdit::OnKeyDown(nChar, nRepCnt, nFlags);	// CScalableEdit::OnKeyDownを呼ぶ.

}