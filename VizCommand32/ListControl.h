// 二重インクルード防止
#ifndef __LIST_CONTROL_H__
#define __LIST_CONTROL_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "CustomControl.h"	// CCustomControl
// 既定のヘッダ
#include <commctrl.h>	// コモンコントロール

// リストコントロールクラスCListControl
class CListControl : public CCustomControl{

	// publicメンバ
	public:

		// publicメンバ変数
		HIMAGELIST m_hImageList;	// アイコンのイメージリストハンドルm_hImageList.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CListControl();	// コンストラクタCListControl
		virtual ~CListControl();	// デストラクタ~CListControl
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
		virtual void SetImageList(int nImageListType);	// イメージリストのセットSetImageList.
		virtual int AddIcon(HICON hIcon);	// イメージリストにアイコンを追加するAddIcon.
		virtual int InsertItem(LPLVITEM pItem);	// リストコントロールにアイテムを追加InsertItem.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.
		virtual void Destroy();	// ウィンドウの破棄と終了処理関数Destroy.

};

#endif