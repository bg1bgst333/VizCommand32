// ヘッダのインクルード
// 独自のヘッダ
#include "ConsoleCore.h"	// CConsoleCore
#include <shlobj.h>	// シェルオブジェクト
#include <shlwapi.h>	// シェルAPI

// コンストラクタCConsoleCore
CConsoleCore::CConsoleCore() : CScalableEdit(){

	// メンバの初期化.
	m_tstrFormString = GREATER_THAN;	// m_tstrFormStringを">"に初期化.
	m_tstrCurrentPath = _T("");	// m_tstrCurrentPathを""で初期化.
	m_tstrCommandString = _T("");	// m_tstrCommandStringを""で初期化.
	m_lStartPos = 0;	// m_lStartPosを0に初期化.
	m_lCurrentPos = 0;	// m_lCurrentPosを0に初期化.
	m_ccmdCommand.Clear();	// コマンドのクリア.

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

// カレントパスのセット.
void CConsoleCore::SetCurrentPath(tstring tstrPath){

	// 指定されたパスを現在のパスとしてセット.
	m_tstrCurrentPath = tstrPath;	// m_tstrCurrentPathをtstrPathにする.
	SetCurrentDirectory(m_tstrCurrentPath.c_str());	// SetCurrentDirectoryで現在のパスとしてm_tstrCurrentPathをセット.

}

// カレントパスの取得.
tstring CConsoleCore::GetCurrentPath(){

	// 変数の初期化.
	TCHAR tszPath[1024] = { 0 };	// tszPathを{0}で初期化.
	
	// 現在のパスを取得.
	GetCurrentDirectory(1024, tszPath);	// GetCurrentDirectoryで現在のパスを取得.
	m_tstrCurrentPath = tszPath;	// tszPathをm_tstrCurrentPathにセット.

	// パスを返す.
	return m_tstrCurrentPath;	// m_tstrCurrentPathを返す.

}

// フルパスの取得.
tstring CConsoleCore::GetFullPath(tstring tstrPath){

	// 変数の初期化.
	TCHAR tszPath[1024] = { 0 };	// tszPathを{0}で初期化.

	// 相対パスかそうでないかを判定.
	if (PathIsRelative(tstrPath.c_str())){	// PathIsRelativeがTRUEなら.

		// 現在のパスの相対パスをしていしても絶対パスになるようにする.
		tstring tstrRelativePath = m_tstrCurrentPath;	// カレントパスのセット.
		tstrRelativePath = tstrRelativePath + _T("\\");	// "\"の連結.
		tstrRelativePath = tstrRelativePath + tstrPath;	// カレントパスの相対パス.

		// フルパスを取得.
		GetFullPathName(tstrRelativePath.c_str(), 1024, tszPath, NULL);	// GetFullPathNameでtstrRelativePathのフルパスを取得.

	}
	else{	// FALSEなら.

		// フルパスを取得.
		GetFullPathName(tstrPath.c_str(), 1024, tszPath, NULL);	// GetFullPathNameでtstrPathのフルパスを取得.

	}

	// パスが存在するかをチェック.
	if (!PathFileExists(tszPath)){	// 存在しない時.
		return tstring(_T(""));	// ""を返す.
	}
	
	// tszPathを返す.
	return tstring(tszPath);	// tszPathをtstringに変換して返す.

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

	// ホームフォルダをカレントパスにする.
	SetCurrentPath(GetProfilePath(hwnd));	// GetProfilePathで取得したホームフォルダパスをSetCurrentPathでセットしてカレントパスとする.

	// 入力フォーム文字列を取得.
	GetInputFormString();	// GetInputFormStringを取得.

	// 成功.
	return 0;	// 成功なので0を返す.

}

// キーが押された時.
int CConsoleCore::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){

	// 上キーが押された時.
	if (nChar == VK_UP){	// VK_UPの時.
		// 上キーはとりあえず無効にして, 上に戻れなくする.
		return -1;	// -1を返すと入力キャンセルになる.
	}

	// リターンキーが押された時.
	if (nChar == VK_RETURN){	// nCharがVK_RETURNの時.

		// コマンド情報をいったんクリア.
		m_ccmdCommand.Clear();	// m_ccmdCommand.Clearでクリア.

		// コマンド文字列の取得.
		GetCommandString();	// GetCommandStringでコマンド文字列を取得.

		// コマンド文字列をコマンドオブジェクトにセット.
		m_ccmdCommand.Set(m_tstrCommandString);	// m_ccmdCommand.Setでm_tstrCommandStringをセット.

		// レスポンスを返すウィンドウにコマンドオブジェクトを投げる.
		PostMessage(m_hProcWnd, UM_CONSOLECORECOMMAND, (WPARAM)&m_ccmdCommand, (LPARAM)m_hWnd);	// UM_CONSOLECORECOMMANDでm_ccmdCommandを送信.

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
	m_ccmdCommand.Clear();	// m_ccmdCommand.Clearでクリア.
	ShowInputForm();	// ShowInputFormで入力フォームを出力.

}