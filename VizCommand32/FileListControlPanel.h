// 二重インクルード防止
#ifndef __FILE_LIST_CONTROL_PANEL_H__
#define __FILE_LIST_CONTROL_PANEL_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "ListControlPanel.h"	// CListControlPanel
#include "FileListControl.h"	// CFileListControl

// ファイルリストコントロールパネルクラスCFileListControlPanel
class CFileListControlPanel : public CListControlPanel{

	// publicメンバ
	public:

		// publicメンバ変数
		tstring m_tstrPath;	// 探索しているパスm_tstrPath.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CFileListControlPanel();	// コンストラクタCFileListControlPanel
		virtual ~CFileListControlPanel();	// デストラクタ~CFileListControlPanel
		// メンバ関数
		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.
		void ScanFile(tstring tstrPath);	// ファイルの探索ScanFile.
		virtual void Destroy();	// ウィンドウの破棄と終了処理関数Destroy.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		virtual void OnTimer(UINT_PTR nIDEvent);	// タイマーイベントが発生した時.

};

#endif