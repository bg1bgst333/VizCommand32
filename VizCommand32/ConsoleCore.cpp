// ヘッダのインクルード
// 独自のヘッダ
#include "ConsoleCore.h"	// CConsoleCore
#include <shlobj.h>	// シェルオブジェクト

// コンストラクタCConsoleCore
CConsoleCore::CConsoleCore() : CScalableEdit(){

	// メンバの初期化.
	m_tstrCommandString = _T("");	// m_tstrCommandStringを""で初期化.
	m_tstrFormString = GREATER_THAN;	// m_tstrFormStringを">"に初期化.
	m_lStartPos = 0;	// m_lStartPosを0に初期化.
	m_lCurrentPos = 0;	// m_lCurrentPosを0に初期化.

}

// コマンド文字列の取得関数GetCommandString.
tstring CConsoleCore::GetCommandString(){

	// テキストの取得.
	m_tstrCommandString = GetText();	// GetTextで取得した文字列をm_tstrCommandStringに格納.

	// コマンド文字列を返す.
	return m_tstrCommandString;	// m_tstrCommandStringを返す.

}

// ホームフォルダ(CSIDL_PROFILE)のパスを取得.
tstring CConsoleCore::GetProfilePath(HWND hWnd){

	// 配列の初期化.
	TCHAR tszPath[1024] = {0};	// CSIDL_PROFILEなパスを格納する配列tszPathを{0}で初期化.

	// ホームフォルダのパスを取得.
	SHGetSpecialFolderPath(hWnd, tszPath, CSIDL_PROFILE, FALSE);	// SHGetSpecialFolderPathでCSIDL_PROFILEなパスを取得.

	// ホームフォルダのパスをメンバに格納.
	m_tstrProfilePath = tszPath;	// m_tstrProfilePathにtszPathを格納.

	// ホームフォルダのパスを返す.
	return m_tstrProfilePath;	// m_tstrProfilePathを返す.

}

// 入力フォーム文字列の取得.
tstring CConsoleCore::GetInputFormString(){

	// 入力フォーム文字列の生成.
	m_tstrInputFormString = m_tstrCurrentPath + m_tstrFormString;	// 入力フォーム文字列 = 現在のパス + フォーム文字列.

	// 入力フォーム文字列を返す.
	return m_tstrInputFormString;	// m_tstrInputFormStringを返す.

}

// コンソールに文字列を出力.
void CConsoleCore::PutConsole(tstring tstrString){

	// 文字列を追加する.
	SendMessage(m_hWnd, EM_REPLACESEL, 0, (LPARAM)tstrString.c_str());	// EM_REPLACESELでtstrStringを追加する.(本来は置換だが, 0を指定したときは追加(挿入)したことになる.)

	// 入力位置の更新.
	SendMessage(m_hWnd, EM_GETSEL, (WPARAM)&m_lStartPos, NULL);	// EM_GETSELで選択していない場合は開始位置を取得できる.

}

// 入力フォームの出力.
void CConsoleCore::ShowInputForm(){

	// 入力フォーム文字列を出力.
	PutConsole(m_tstrInputFormString);	// PutConsoleでm_tstrInputFormStringを出力.

}

// ウィンドウの作成が開始された時.
int CConsoleCore::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// 親クラスのOnCreateを呼ぶ.
	CScalableEdit::OnCreate(hwnd, lpCreateStruct);	// CScalableEdit::OnCreateを呼ぶ.

	// ホームフォルダの取得.
	GetProfilePath(hwnd);	// GetProfilePathでホームフォルダを取得.

	// 現在のパスをホームフォルダにセット.
	m_tstrCurrentPath = m_tstrProfilePath;	// m_tstrCurrentPathにm_tstrProfilePathをセット.

	// 入力フォーム文字列を取得.
	GetInputFormString();	// GetInputFormStringを取得.

	// 成功.
	return 0;	// 成功なので0を返す.

}

// キーが押された時.
int CConsoleCore::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){

	// リターンキーが押された時.
	if (nChar == VK_RETURN){	// nCharがVK_RETURNの時.

		// コマンド文字列の取得.
		GetCommandString();	// GetCommandStringでコマンド文字列を取得.
		MessageBox(m_hWnd, m_tstrCommandString.c_str(), _T("VizCommand"), MB_OK);	// MessageBoxでm_tstrCommandStringを表示.

	}

	// 左キーが押された時.
	if (nChar == VK_LEFT){	// VK_LEFTの時.
		m_lCurrentPos = 0;	// m_lCurrentPosを0にセット.
		SendMessage(m_hWnd, EM_GETSEL, (WPARAM)&m_lCurrentPos, NULL);	// EM_GETSELでキャレットの位置を取得.
		if (m_lCurrentPos <= m_lStartPos) {	// 開始位置より手前だったら入力キャンセルする.
			return -1;	// -1を返すと入力キャンセルになる.
		}
	}

	// 親クラスの既定処理.
	return CScalableEdit::OnKeyDown(nChar, nRepCnt, nFlags);	// CScalableEdit::OnKeyDownを呼ぶ.

}

// 文字キーが押された時.
int CConsoleCore::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags){

	// バックスペースが押されても戻るのを無効にする.
	if (nChar == VK_BACK) {	// VK_BACKの時.
		m_lCurrentPos = 0;	// m_lCurrentPosを0にセット.
		SendMessage(m_hWnd, EM_GETSEL, (WPARAM)&m_lCurrentPos, NULL);	// EM_GETSELでキャレットの位置を取得.
		if (m_lCurrentPos <= m_lStartPos) {	// 開始位置より手前だったら入力キャンセルする.
			return -1;	// -1を返すと入力キャンセルになる.
		}
	}

	// 通常は入力を有効にする.
	return 0;	// 0を返すと有効になる.

}

// マウス左ボタンが離された時.
int CConsoleCore::OnLButtonUp(UINT nFlags, POINT pt){

	// 現在位置が開始位置より前になるようにマウスでクリックされた場合, キャレットを強制的に開始位置に戻す.
	m_lCurrentPos = 0;	// m_lCurrentPosを0にセット.
	SendMessage(m_hWnd, EM_GETSEL, (WPARAM)&m_lCurrentPos, NULL);	// EM_GETSELでキャレットの位置を取得.
	if (m_lCurrentPos < m_lStartPos) {	// 開始位置より手前だったらキャレットの位置を再セット.
		SendMessage(m_hWnd, EM_SETSEL, (WPARAM)m_lStartPos, (LPARAM)m_lStartPos);	// EM_SETSELでキャレット位置をm_lStartPosに再セット.
	}

	// 入力は有効にする.
	return 0;	// 0を返すと有効になる.

}