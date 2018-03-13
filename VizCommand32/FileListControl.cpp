// ヘッダのインクルード
// 独自のヘッダ
#include "FileListControl.h"	// CFileListControl

// コンストラクタCFileListControl
CFileListControl::CFileListControl() : CListControl(){

}

// デストラクタ~CFileListControl
CFileListControl::~CFileListControl(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}