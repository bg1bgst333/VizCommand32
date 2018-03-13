// 二重インクルード防止
#ifndef __FILE_INFO_H__
#define __FILE_INFO_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "Window.h"	// CWindow

// ファイル情報を格納するクラスCFileInfo
class CFileInfo{

	// publicメンバ
	public:

		// publicメンバ変数
		tstring m_tstrFileName;	// ファイル名m_tstrFileName.(フルパス.)
		tstring m_tstrFileTitle;	// ファイルタイトルm_tstrFileTitle.(ファイル名部分のみ.)
		tstring m_tstrFileExt;	// ファイル拡張子m_tstrFileExt.
		HICON m_hIcon;	// ファイルアイコンハンドルm_hIcon.

};

#endif
