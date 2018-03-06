// 二重インクルード防止
#ifndef __CONSOLE_CORE_H__
#define __CONSOLE_CORE_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "ScalableEdit.h"	// CScalableEdit

// コンソールコアクラスCConsoleCore
class CConsoleCore : public CScalableEdit{

	// publicメンバ
	public:

		// publicメンバ変数
		tstring m_tstrCommandString;	// コマンド文字列m_tstrCommandString.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CConsoleCore();	// コンストラクタCConsoleCore
		// メンバ関数
		tstring GetCommandString();	// コマンド文字列の取得関数GetCommandString.
		virtual int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	// キーが押された時.

};


#endif