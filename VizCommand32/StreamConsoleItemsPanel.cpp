// ヘッダのインクルード
// 独自のヘッダ
#include "StreamConsoleItemsPanel.h"	// CStreamConsoleItemsPanel

// 子から親へウィンドウサイズ変更の要求が発生した時.
void CStreamConsoleItemsPanel::OnSizeChild(WPARAM wParam, LPARAM lParam){

	// 親のOnSizeChildを呼ぶ.
	CWindowListItemsPanel::OnSizeChild(wParam, lParam);	// CWindowListItemsPanel::OnSizeChildを呼ぶ.

	// 下へのスクロール要求.
	SendMessage(GetParent(m_hWnd), UM_REQUESTSCROLLBOTTOM, m_iTotalHeight, 0);	// UM_REQUESTSCROLLBOTTOMで下へのスクロールを要求する.

}