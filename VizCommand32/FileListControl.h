// 二重インクルード防止
#ifndef __FILE_LIST_CONTROL_H__
#define __FILE_LIST_CONTROL_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "ListControl.h"	// CListControl

// ファイルリストコントロールクラスCFileListControl
class CFileListControl : public CListControl{

	// publicメンバ
	public:

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CFileListControl();	// コンストラクタCFileListControl
		virtual ~CFileListControl();	// デストラクタCFileListControl

};

#endif
