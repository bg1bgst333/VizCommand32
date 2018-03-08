// 二重インクルード防止
#ifndef __CONSOLE_CORE_H__
#define __CONSOLE_CORE_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "ScalableEdit.h"	// CScalableEdit

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
		long m_lStartPos;				// 入力開始位置m_lStartPos.
		long m_lCurrentPos;				// 入力現在位置m_lCurrentPos.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CConsoleCore();	// コンストラクタCConsoleCore
		// メンバ関数
		tstring GetProfilePath(HWND hWnd);	// ホームフォルダ(CSIDL_PROFILE)のパスを取得.
		tstring GetInputFormString();	// 入力フォーム文字列の取得.
		void PutConsole(tstring tstrString);	// コンソールに文字列を出力.
		void ShowInputForm();	// 入力フォームの出力.
		tstring GetCommandString();	// コマンド文字列の取得関数GetCommandString.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		virtual int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	// キーが押された時.
		virtual int OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);		// 文字キーが押された時.
		virtual int OnLButtonUp(UINT nFlags, POINT pt);	// マウス左ボタンが離された時.

};

#endif