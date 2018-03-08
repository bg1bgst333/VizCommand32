// ヘッダのインクルード
// 独自のヘッダ
#include "ConsoleCore.h"	// CConsoleCore
#include <shlobj.h>	// シェルオブジェクト

// コンストラクタCConsoleCore
CConsoleCore::CConsoleCore() : CScalableEdit(){

	// メンバの初期化.
	m_tstrFormString = GREATER_THAN;	// m_tstrFormStringを">"に初期化.
	m_tstrCommandString = _T("");	// m_tstrCommandStringを""で初期化.
	m_lStartPos = 0;	// m_lStartPosを0に初期化.
	m_lCurrentPos = 0;	// m_lCurrentPosを0に初期化.

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

	// 変数の初期化
	int iCount = 0;	// 改行の個数iCountを0に初期化.

	// 改行の数を数える.
	for (int i = 1; i < (int)tstrString.length(); i++){	// iは1からtstrString.length() - 1まで.
		if (tstrString.at(i - 1) == _T('\r') && tstrString.at(i) == _T('\n')){	// 改行がみつかったら.

			// 変数の宣言
			int iHeight;	// 新しい高さiHeight.
			WPARAM wParam;	// WPARAM型wParam.

			// 改行したら1行分大きくする.
			iHeight = m_iHeight + m_iLineHeight;	// 現在のウィンドウの高さに1行分の高さを足す.
			MoveWindow(m_hWnd, m_x, m_y, m_iWidth, iHeight, TRUE);	// MoveWindowで高さをiHeightにする.
			m_iLineCount++;	// 行数m_LineCountを増やす.

			// UM_SIZECHILDで子ウィンドウのサイズに合わせる.
			wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAMでm_iWidthとm_iHeightからwParamを作成.
			SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// UM_SIZECHILDで親ウィンドウをこのウィンドウのサイズに合わせる.

			// iCountを増やす.
			iCount++;	// iCountをインクリメント.

		}
	}

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

// コマンド文字列の取得関数GetCommandString.
tstring CConsoleCore::GetCommandString(){

	// 変数の宣言
	unsigned int uiCommandStringLen;	// コマンド文字列の長さuiCommandStringLen.
	tstring tstrText;	// テキストtstrText.

	// テキストの取得.
	tstrText = GetText();	// GetTextでテキストを取得し, tstrTextに格納.

	// コマンド文字列の切り出し.
	uiCommandStringLen = (unsigned int)tstrText.length() - m_lStartPos;	// uiCommandStringLenにtstrTextの長さからm_iStartPosを引いたものを格納.
	m_tstrCommandString = tstrText.substr(m_lStartPos, uiCommandStringLen);	// tstrText.substrでm_lStartPosからuiCommandStringLen分の部分文字列を抜き出して, m_tstrCommandStringに格納.

	// コマンド文字列を返す.
	return m_tstrCommandString;	// m_tstrCommandStringを返す.

}

// コマンドに対する処理を実行するウィンドウをセット.
void CConsoleCore::SetProcWindow(HWND hWnd){

	// メンバにセット.
	m_hProcWnd = hWnd;	// m_hProcWndにhWndをセット.

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

		// レスポンスを返すウィンドウにコマンド文字列を投げる.
		PostMessage(m_hProcWnd, UM_CONSOLECORECOMMAND, (WPARAM)m_tstrCommandString.c_str(), (LPARAM)m_hWnd);	// UM_CONSOLECORECOMMANDでコマンド文字列を送信.

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

// マウス左ボタンが押された時.
int CConsoleCore::OnLButtonDown(UINT nFlags, POINT pt){

	// キャレットを非表示にする.
	HideCaret(m_hWnd);	// HideCaretでキャレットを非表示にする.

	// 入力は有効にする.
	return 0;	// 0を返すと有効になる.

}

// マウス左ボタンが離された時.
int CConsoleCore::OnLButtonUp(UINT nFlags, POINT pt){

	// キャレットを表示する.
	ShowCaret(m_hWnd);	// ShowCaretでキャレットを表示する.

	// 現在位置が開始位置より前になるようにマウスでクリックされた場合, キャレットを強制的に開始位置に戻す.
	m_lCurrentPos = 0;	// m_lCurrentPosを0にセット.
	SendMessage(m_hWnd, EM_GETSEL, (WPARAM)&m_lCurrentPos, NULL);	// EM_GETSELでキャレットの位置を取得.
	if (m_lCurrentPos < m_lStartPos) {	// 開始位置より手前だったらキャレットの位置を再セット.
		SendMessage(m_hWnd, EM_SETSEL, (WPARAM)m_lStartPos, (LPARAM)m_lStartPos);	// EM_SETSELでキャレット位置をm_lStartPosに再セット.
	}

	// 入力は有効にする.
	return 0;	// 0を返すと有効になる.

}

// ユーザ定義メッセージが発生した時.
void CConsoleCore::OnUserMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){

	// switch-case文で振り分ける.
	switch (uMsg) {

		// 子から親へウィンドウサイズ変更の要求が発生した時.
		case UM_SIZECHILD:

			// UM_SIZECHILDブロック
			{

				// OnSizeChildに任せる.
				OnSizeChild(wParam, lParam);	// OnSizeChildに任せる.

			}

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

		// レスポンスメッセージが来た時.
		case UM_RESPONSEMESSAGE:

			// UM_RESPONSEMESSAGEブロック
			{
		
				// OnResponseMessageに任せる.
				OnResponseMessage(wParam, lParam);	// OnResponseMessageに任せる.

			}

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

		// レスポンスが終了した時.
		case UM_FINISHRESPONSE:

			// UM_FINISHRESPONSEブロック
			{

				// OnFinishResponseに任せる.
				OnFinishResponse(wParam, lParam);	// OnFinishResponseに任せる.

			}

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

		// それ以外.
		default:

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

	}

}

// レスポンスメッセージが来た時.
void CConsoleCore::OnResponseMessage(WPARAM wParam, LPARAM lParam){

	// 変数の宣言
	tstring tstrMessage;	// メッセージ文字列を格納するtstrMessage.

	// メッセージ文字列を取得.
	tstrMessage = (TCHAR *)wParam;	// wParamを(TCHAR *)にキャストしてtstrMessageにセット.

	// メッセージを出力.
	PutConsole(tstrMessage);	// PutConsoleでtstrMessageを出力.

}

// レスポンスが終了した時.
void CConsoleCore::OnFinishResponse(WPARAM wParam, LPARAM lParam){

	// 入力フォームを出力.
	ShowInputForm();	// ShowInputFormで入力フォームを出力.

}