// 二重インクルード防止
#ifndef __CONSOLE_CORE_H__
#define __CONSOLE_CORE_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "ScalableEdit.h"	// CScalableEdit
#include "Command.h"	// CCommand

// マクロの定義
// 入力記号.
#define GREATER_THAN _T(">")

// コンソールコアクラスCConsoleCore
class CConsoleCore : public CScalableEdit{

	// publicメンバ
	public:

		// publicメンバ変数
		tstring m_tstrFormString;	// フォーム文字列m_tstrFormString.
		tstring m_tstrProfilePath;	// ホームフォルダ(CSIDL_PROFILE)のパスm_tstrProfilePath.
		tstring m_tstrInputFormString;	// 実際に出力する入力フォーム文字列m_tstrInputFormString.
		tstring m_tstrCurrentPath;	// 現在のパスm_tstrCurrentPath.
		tstring m_tstrCommandString;	// コマンド文字列m_tstrCommandString.
		CCommand m_ccmdCommand;	// コマンドオブジェクトm_ccmdCommand.
		long m_lStartPos;				// 入力開始位置m_lStartPos.
		long m_lCurrentPos;				// 入力現在位置m_lCurrentPos.
		HWND m_hProcWnd;	// コマンドに対する処理を実行するウィンドウのウィンドウハンドルm_hProcWnd.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CConsoleCore();	// コンストラクタCConsoleCore
		// メンバ関数
		tstring GetProfilePath(HWND hWnd);	// ホームフォルダ(CSIDL_PROFILE)のパスを取得.
		tstring GetInputFormString();	// 入力フォーム文字列の取得.
		void PutConsole(tstring tstrString);	// コンソールに文字列を出力.
		void ShowInputForm();	// 入力フォームの出力.
		tstring GetCommandString();	// コマンド文字列の取得関数GetCommandString.
		void SetProcWindow(HWND hWnd);	// コマンドに対する処理を実行するウィンドウをセット.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		virtual int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	// キーが押された時.
		virtual int OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);		// 文字キーが押された時.
		virtual int OnLButtonDown(UINT nFlags, POINT pt);	// マウス左ボタンが押された時.
		virtual int OnLButtonUp(UINT nFlags, POINT pt);	// マウス左ボタンが離された時.
		virtual void OnUserMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);	// ユーザ定義メッセージが発生した時.
		virtual void OnResponseMessage(WPARAM wParam, LPARAM lParam);	// レスポンスメッセージが来た時.
		virtual void OnFinishResponse(WPARAM wParam, LPARAM lParam);	// レスポンスが終了した時.

};

#endif