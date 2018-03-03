// 二重インクルード防止
#ifndef __WINDOW_LIST_CONTROL_H__
#define __WINDOW_LIST_CONTROL_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "UserControl.h"	// CUserControl
#include "WindowListItemsPanel.h"	// CWindowListItemsPanel

// マクロ定義
#define SCROLLBAR_THICKNESS 16	// とりあえずスクロールバーの厚さはマクロで16としておく.

// ウィンドウリストコントロールクラスCWindowListControl
class CWindowListControl : public CUserControl{

	// publicメンバ
	public:

		// publicメンバ変数
		CWindowListItemsPanel *m_pWindowListItemsPanel;	// CWindowListItemsPanelオブジェクトポインタm_pWindowListItemsPanel.
		int m_iHScrollPos;	// スクロールバーの水平方向の位置m_iHScrollPos
		int m_iVScrollPos;	// スクロールバーの垂直方向の位置m_iVScrollPos
		SCROLLINFO m_ScrollInfo;	// スクロール情報m_ScrollInfo.
		
		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CWindowListControl();	// コンストラクタCWindowListControl
		virtual ~CWindowListControl();	// デストラクタ~CWindowListControl
		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.
		virtual void Destroy();	// ウィンドウの破棄と終了処理関数Destroy.
		virtual void Add(LPCTSTR lpctszWindowName, int x, int y, int iWidth, int iHeight, HINSTANCE hInstance);	// アイテムを末尾から追加する関数Add.
		virtual void Add(LPCTSTR lpctszWindowName, int iHeight, HINSTANCE hInstance);	// アイテムを末尾から追加する関数Add.
		virtual void Insert(int iIndex, LPCTSTR lpctszWindowName, int iHeight, HINSTANCE hInstance);	// アイテムを指定の場所に挿入する関数Insert.
		virtual void Remove();	// アイテムを末尾から削除する関数Remove.
		virtual void Delete(int iIndex);	// 指定の場所のアイテムを削除する関数Delete.
		virtual CWindowListItem * Get(int iIndex);	// アイテムを取得する関数Get.
		virtual void RemoveAll();	// 全てのアイテムを削除する関数RemoveAll.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		virtual void OnDestroy();	// ウィンドウが破棄された時.
		virtual void OnPaint();	// ウィンドウの描画を要求された時のハンドラOnPaint.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.
		virtual void OnTimer(UINT_PTR nIDEvent);	// タイマーイベントが発生した時.
		virtual void OnHScroll(UINT nSBCode, UINT nPos);	// 水平方向スクロールバーイベント時.
		virtual void OnVScroll(UINT nSBCode, UINT nPos);	// 垂直方向スクロールバーイベント時.
		virtual void OnSizeChild(WPARAM wParam, LPARAM lParam);	// 子から親へウィンドウサイズ変更の要求が発生した時.

};

#endif