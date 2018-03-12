// 二重インクルード防止
#ifndef __STATIC_PANEL_H__
#define __STATIC_PANEL_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "UserControl.h"	// CUserControl
#include "Static.h"	// CStatic

// スタティックパネルクラス
class CStaticPanel : public CUserControl{

	// publicメンバ
	public:

		// publicメンバ変数
		CStatic *m_pStatic;	// CStaticオブジェクトポインタ.
		HMENU m_nId;	// HMENU型メニューID.
		HBRUSH m_hbrBackground;	// 背景色ブラシm_hbrBackground.
		HFONT m_hFont;	// フォントm_hFont.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CStaticPanel();	// コンストラクタCStaticPanel
		virtual ~CStaticPanel();	// デストラクタ~CStaticPanel
		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.
		virtual void Destroy();	// ウィンドウの破棄と終了処理関数Destroy.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.
		virtual HBRUSH OnCtlColorStatic(HDC hDC, HWND hStatic);	// 子スタティックコントロールの描画時.

};

#endif