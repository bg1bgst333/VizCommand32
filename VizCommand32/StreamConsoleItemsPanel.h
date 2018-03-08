// 二重インクルード防止
#ifndef __STREAM_CONSOLE_ITEMS_PANEL_H__
#define __STREAM_CONSOLE_ITEMS_PANEL_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "WindowListItemsPanel.h"	// CWindowListItemsPanel

// ストリームコンソールアイテムズパネルクラスCStreamConsoleItemsPanel
class CStreamConsoleItemsPanel : public CWindowListItemsPanel{

	// publicメンバ
	public:

		// publicメンバ関数
		// メンバ関数
		virtual void OnSizeChild(WPARAM wParam, LPARAM lParam);	// 子から親へウィンドウサイズ変更の要求が発生した時.

};

#endif