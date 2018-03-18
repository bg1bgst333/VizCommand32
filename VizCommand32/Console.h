// 二重インクルード防止
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "ScalableEditPanel.h"	// CScalableEditPanel
#include "ConsoleCore.h"	// CConsoleCore

// コンソールクラスCConsole
class CConsole : public CScalableEditPanel{

	// publicメンバ
	public:

		// publicメンバ変数
		HBRUSH m_hbrBackground;	// 背景色ブラシm_hbrBackground.
		HWND m_hProcWnd;	// コマンドに対する処理を実行するウィンドウのウィンドウハンドルm_hProcWnd.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CConsole();	// コンストラクタCCConsole
		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.
		virtual void Destroy();	// ウィンドウの破棄と終了処理関数Destroy.
		void ShowInputForm();	// 入力フォームの出力.
		void SetProcWindow(HWND hWnd);	// コマンドに対する処理を実行するウィンドウをセット.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.
		virtual HBRUSH OnCtlColorEdit(HDC hDC, HWND hEdit);	// 子エディットコントロールの描画時.
		virtual void OnUserMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);	// ユーザ定義メッセージが発生した時.
		virtual int OnConsoleCoreCommand(WPARAM wParam, LPARAM lParam);	// コンソールコアからメッセージが送られた時.
		virtual void OnHello(HWND hSrc, CCommand *pCommand);	// "Hello, world!"の出力を要求された時.
		virtual void OnList(HWND hSrc, CCommand *pCommand);	// ファイルリストの出力を要求された時.
		virtual void OnWalk(HWND hSrc, CCommand *pCommand);	// カレントフォルダの移動を要求された時.
		virtual void OnErrorCommandNotFound(HWND hSrc);	// コマンドが見つからないエラーが発生した時.

};

#endif