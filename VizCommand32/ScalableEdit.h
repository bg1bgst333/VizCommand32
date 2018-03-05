// 二重インクルード防止
#ifndef __SCALABLE_EDIT_H__
#define __SCALABLE_EDIT_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "Edit.h"	// CEdit

// スカラブルエディットコントロールクラスCScalableEdit
class CScalableEdit : public CEdit{

	// publicメンバ
	public:

		// publicメンバ変数
		int m_iLineHeight;	// 行の高さ.
		int m_iLineCount;	// 行数.

		// publicメンバ巻数
		// コンストラクタ・デストラクタ
		CScalableEdit();	// コンストラクタCScalableEdit
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		virtual int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	// キーが押された時.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.

};

#endif