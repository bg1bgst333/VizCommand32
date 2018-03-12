// ヘッダのインクルード
// 独自のヘッダ
#include "WindowListItemsPanel.h"	// CWindowListItemsPanel

// コンストラクタCWindowListItemsPanel
CWindowListItemsPanel::CWindowListItemsPanel() : CUserControl(){

	// メンバの初期化.
	m_vecWindowListItem.clear();	// m_vecWindowListItem.clearでクリア.
	m_nNextId = 0;	// m_nNextIdを0で初期化.
	m_iTotalHeight = 0;	// m_iTotalHeightを0で初期化.

}

// デストラクタ~CWindowListItemsPanel
CWindowListItemsPanel::~CWindowListItemsPanel(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CWindowListItemsPanel::RegisterClass(HINSTANCE hInstance){

	// ウィンドウクラスの登録.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CUserControl::RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
BOOL CWindowListItemsPanel::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackgroundを指定.
	return CUserControl::RegisterClass(hInstance, _T("CWindowListItemsPanel"), hbrBackground);	// CUserControl::RegisterClassで登録.

}

// ウィンドウ作成関数Create.
BOOL CWindowListItemsPanel::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウの作成.
	return CUserControl::Create(_T("CWindowListItemsPanel"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createで作成.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CWindowListItemsPanel::Destroy(){

	// ウィンドウリストアイテムリストの終了処理.
	m_vecWindowListItem.clear();	// m_vecWindowListItem.clearでクリア.
	m_nNextId = 0;	// m_nNextIdに0をセット.

	// 親ウィンドウのDestroyを呼ぶ.
	CUserControl::Destroy();	// CUserControl::Destroyを呼ぶ.

}

// アイテムを末尾から追加する関数Add.
void CWindowListItemsPanel::Add(LPCTSTR lpctszWindowName, int x, int y, int iWidth, int iHeight, HINSTANCE hInstance){

	// ウィンドウリストアイテムの追加.
	CWindowListItem *pWindowListItem = new CWindowListItem();	// CWindowListItemオブジェクトを生成し, ポインタをpWindowListItemに格納.
	pWindowListItem->Create(lpctszWindowName, WS_CHILD | WS_VISIBLE, x, y, iWidth, iHeight, m_hWnd, (HMENU)(WINDOW_LIST_ITEM_ID_START + m_nNextId), hInstance);	// pWindowListItem->Createでアイテム作成.
	m_vecWindowListItem.push_back(pWindowListItem);	// m_vecWindowListItem.push_backで末尾に追加.
	m_nNextId++;	// m_nNextIdをインクリメント.

}

// アイテムを末尾から追加する関数Add.
void CWindowListItemsPanel::Add(LPCTSTR lpctszWindowName, int iHeight, HINSTANCE hInstance){

	// ウィンドウリストアイテムの追加.
	CWindowListItem *pWindowListItem = new CWindowListItem();	// CWindowListItemオブジェクトを生成し, ポインタをpWindowListItemに格納.
	pWindowListItem->Create(lpctszWindowName, WS_CHILD | WS_VISIBLE, 0, m_iTotalHeight, m_iClientAreaWidth, iHeight, m_hWnd, (HMENU)(WINDOW_LIST_ITEM_ID_START + m_nNextId), hInstance);	// pWindowListItem->Createでアイテム作成.
	m_vecWindowListItem.push_back(pWindowListItem);	// m_vecWindowListItem.push_backで末尾に追加.
	m_iTotalHeight += iHeight;	// m_iTotalHeightにiHeightを足す.
	m_nNextId++;	// m_nNextIdをインクリメント.

}

// アイテムを指定の場所に挿入する関数Insert.
void CWindowListItemsPanel::Insert(int iIndex, LPCTSTR lpctszWindowName, int iHeight, HINSTANCE hInstance){

	// iIndexの値とm_vecWindowListItemの要素数で振り分ける.
	int iIdx = 0;	// int型iIdxを0で初期化.
	int iInsertPosY;	// int型iInsertPosYを0で初期化.
	if (m_vecWindowListItem.size() == 0){	// 要素数が0.
		iIdx = 0;	// iIdxを0とする.
		iInsertPosY = 0;	// iInsertPosYを0として一番上に配置.
	}
	else{	// 要素数が1以上.
		if (iIndex < 0){	// インデックスが負の数.
			iIdx = 0;	// iIdxを0とする.
			iInsertPosY = 0;	// iInsertPosYを0として一番上に配置.
		}
		else if (iIndex >= m_vecWindowListItem.size()){	// インデックスが要素数以上.
			iIdx = m_vecWindowListItem.size();	// iIdxをm_vecWindowListItem.sizeの値とする.
			iInsertPosY = m_iTotalHeight;	// iInsertPosYはm_iTotalHeight.
		}
		else{
			iIdx = iIndex;	// iIndexの値を代入.
			iInsertPosY = m_vecWindowListItem[iIdx]->m_y;	// 現在のiIdx番目のY座標.
		}
	}

	// オブジェクト作成.
	CWindowListItem *pWindowListItem = new CWindowListItem();	// CWindowListItemオブジェクトを生成し, ポインタをpWindowListItemに格納.
	
	// ウィンドウ作成.
	pWindowListItem->Create(lpctszWindowName, WS_CHILD | WS_VISIBLE, 0, iInsertPosY, m_iClientAreaWidth, iHeight, m_hWnd, (HMENU)(WINDOW_LIST_ITEM_ID_START + m_nNextId), hInstance);	// pWindowListItem->Createでアイテム作成.

	// ベクタ挿入.
	m_vecWindowListItem.insert(m_vecWindowListItem.begin() + iIdx, pWindowListItem);	// m_vecWindowListItem.insertでiIdx番目にpWindowListItemを追加.

	// 下の要素をずらす.
	if (iIdx != m_vecWindowListItem.size()){	// 末尾ではない時.
		for (std::vector<CWindowListItem *>::iterator itor = m_vecWindowListItem.begin() + iIdx + 1; itor != m_vecWindowListItem.end(); itor++){	// m_vecWindowListItemのiIdx + 1番目から最後まで繰り返す.
			MoveWindow((*itor)->m_hWnd, (*itor)->m_x, (*itor)->m_y + iHeight, (*itor)->m_iWidth, (*itor)->m_iHeight, TRUE);	// MoveWindowでiHeight分ずらす.
		}
	}

	// 次への準備.
	m_iTotalHeight += iHeight;	// m_iTotalHeightにiHeightを足す.
	m_nNextId++;	// m_nNextIdをインクリメント.

	// サイズ変更.
	if (m_hWnd != NULL){	// m_hWndがNULLでない時.
		MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_iTotalHeight, TRUE);	// MoveWindowでアイテムズパネルを拡大.
	}
#if 0
	// iIndexの値で動作を振り分ける.
	if (iIndex == 0){	// 0の場合.
		CWindowListItem *pWindowListItem = new CWindowListItem();	// CWindowListItemオブジェクトを生成し, ポインタをpWindowListItemに格納.
		pWindowListItem->Create(lpctszWindowName, WS_CHILD | WS_VISIBLE, 0, 0, m_iClientAreaWidth, iHeight, m_hWnd, (HMENU)(WINDOW_LIST_ITEM_ID_START + m_nNextId), hInstance);	// pWindowListItem->Createでアイテム作成.
		m_vecWindowListItem.insert(m_vecWindowListItem.begin() + 0, pWindowListItem);	// m_vecWindowListItem.insertで0番目にpWindowListItemを追加.
		for (std::vector<CWindowListItem *>::iterator itor = m_vecWindowListItem.begin() + 1; itor != m_vecWindowListItem.end(); itor++){	// m_vecWindowListItemの1番目から最後まで繰り返す.
			MoveWindow((*itor)->m_hWnd, (*itor)->m_x, (*itor)->m_y + iHeight, (*itor)->m_iWidth, (*itor)->m_iHeight, TRUE);	// MoveWindowでiHeight分ずらす.
		}
	}
	else if (iIndex == m_vecWindowListItem.size()){	// ベクタの要素数と同じ場合.(つまり一番最後.)
		CWindowListItem *pWindowListItem = new CWindowListItem();	// CWindowListItemオブジェクトを生成し, ポインタをpWindowListItemに格納.
		pWindowListItem->Create(lpctszWindowName, WS_CHILD | WS_VISIBLE, 0, m_iTotalHeight, m_iClientAreaWidth, iHeight, m_hWnd, (HMENU)(WINDOW_LIST_ITEM_ID_START + m_nNextId), hInstance);	// pWindowListItem->Createでアイテム作成.(挿入位置はm_iTotalHeight.)
		m_vecWindowListItem.insert(m_vecWindowListItem.begin() + iIndex, pWindowListItem);	// m_vecWindowListItem.insertでiIndex番目にpWindowListItemを追加.
	}
	else{	// 0と要素数の間の場合.
		CWindowListItem *pWindowListItem = new CWindowListItem();	// CWindowListItemオブジェクトを生成し, ポインタをpWindowListItemに格納.
		pWindowListItem->Create(lpctszWindowName, WS_CHILD | WS_VISIBLE, 0, m_vecWindowListItem[iIndex]->m_y, m_iClientAreaWidth, iHeight, m_hWnd, (HMENU)(WINDOW_LIST_ITEM_ID_START + m_nNextId), hInstance);	// pWindowListItem->Createでアイテム作成.(挿入位置はm_vecWindowListItem[iIndex]->m_y.)
		m_vecWindowListItem.insert(m_vecWindowListItem.begin() + iIndex, pWindowListItem);	// m_vecWindowListItem.insertでiIndex番目にpWindowListItemを追加.
		for (std::vector<CWindowListItem *>::iterator itor = m_vecWindowListItem.begin() + iIndex + 1; itor != m_vecWindowListItem.end(); itor++){	// m_vecWindowListItemのiIndex + 1番目から最後まで繰り返す.
			MoveWindow((*itor)->m_hWnd, (*itor)->m_x, (*itor)->m_y + iHeight, (*itor)->m_iWidth, (*itor)->m_iHeight, TRUE);	// MoveWindowでiHeight分ずらす.
		}
	}
#endif

}

// アイテムを末尾から削除する関数Remove.
void CWindowListItemsPanel::Remove(){

	// ウィンドウリストアイテムの削除.
	CWindowListItem *pWindowListItem = m_vecWindowListItem[m_vecWindowListItem.size() - 1];	// 末尾要素を取得.
	delete pWindowListItem;	// deleteでpWindowListItemの削除.
	m_vecWindowListItem.pop_back();	// m_vecWindowListItem.pop_backでリストを1つ減らす.
	m_nNextId--;

}

// 指定の場所のアイテムを削除する関数Delete.
void CWindowListItemsPanel::Delete(int iIndex){

	// iIndexの値とm_vecWindowListItemの要素数で振り分ける.
	int iIdx = 0;	// int型iIdxを0で初期化.
	if (m_vecWindowListItem.size() == 0){	// 要素数が0なら.
		return;	// ここで終了.
	}
	else if (iIndex < 0){	// iIndexが負の値.
		iIdx = 0;	// iIdxを0とする.
	}
	else if (iIndex > m_vecWindowListItem.size() - 1){	// iIndexが要素番号を超える.
		iIdx = m_vecWindowListItem.size() - 1;	// iIdxを最後の要素番号とする.
	}
	else{	// それ以外.
		iIdx = iIndex;	// iIdxをiIndexの値とする.
	}

	// ベクタから削除.
	int iHeight = 0;	// ずらす高さ.
	std::vector<CWindowListItem *>::iterator itor = m_vecWindowListItem.begin() + iIdx;	// itorはiIdx番目.
	if ((*itor) != NULL){	// NULLでない時.
		iHeight = (*itor)->m_iHeight;	// iHeightにm_iHeightをセット.
		(*itor)->Destroy();	// (*itor)->Destroyで破棄.
		delete (*itor);	// deleteで(*itor)を削除.
		(*itor) = NULL;	// NULLをセット.
		m_vecWindowListItem.erase(itor);	// itorの指す要素を削除.
		// アイテムをずらす.
		for (std::vector<CWindowListItem *>::iterator itor2 = m_vecWindowListItem.begin() + iIdx; itor2 != m_vecWindowListItem.end(); itor2++){	// 新しいiIdx番目から最後まで繰り返す.
			MoveWindow((*itor2)->m_hWnd, (*itor2)->m_x, (*itor2)->m_y - iHeight, (*itor2)->m_iWidth, (*itor2)->m_iHeight, TRUE);	// MoveWindowで上にずらす.
		}
		// 次への準備.
		m_iTotalHeight -= iHeight;	// m_iTotalHeightからiHeightを引く.
		// サイズ変更.
		if (m_hWnd != NULL){	// m_hWndがNULLでない時.
			MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_iTotalHeight, TRUE);	// MoveWindowでアイテムズパネルを拡大.
		}
	}

}

// アイテムを取得する関数Get.
CWindowListItem * CWindowListItemsPanel::Get(int iIndex){

	// iIndex番目の要素を返す.
	return m_vecWindowListItem[iIndex];	// m_vecWindowListItem[iIndex]を返す.

}

// 全てのアイテムを削除する関数RemoveAll.
void CWindowListItemsPanel::RemoveAll(){

	// アイテムの数だけ繰り返す.
	size_t n = GetSize();	// GetSizeでサイズを取得し, nに格納.
	for (size_t i = 0; i < n; i++){	// nの数だけ繰り返す.
		Remove();	// Removeで末尾を削除.
	}

}

// アイテムの数を返す関数GetSize.
size_t CWindowListItemsPanel::GetSize(){

	// アイテムの要素数を返す.
	return m_vecWindowListItem.size();	// m_vecWindowListItem.sizeで要素数を返す.

}

// ウィンドウの作成が開始された時.
int CWindowListItemsPanel::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// 親のOnCreateを呼ぶ.
	return CUserControl::OnCreate(hwnd, lpCreateStruct);

}

// ウィンドウが破棄された時.
void CWindowListItemsPanel::OnDestroy(){

	// メンバの終了処理
	//Destroy();	// Destroyでこのウィンドウの終了処理をする.

	// 親クラスのOnDestroyを呼ぶ.
	CUserControl::OnDestroy();	// CUserControl::OnDestroyを呼ぶ.

}

// ウィンドウの描画を要求された時のハンドラOnPaint.
void CWindowListItemsPanel::OnPaint(){

	// 変数の初期化.
	HDC hDC = NULL;	// hDCをNULLで初期化.
	PAINTSTRUCT ps = {0};	// psを{0}で初期化.
	HPEN hPen = NULL;	// hPenをNULLで初期化.
	HBRUSH hBrush = NULL;	// hBrushをNULLで初期化.

	// 描画開始.
	hDC = BeginPaint(m_hWnd, &ps);	// BeginPaintで描画開始.

#if 0
	// ペンとブラシの生成.
	hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0xff, 0, 0));	// CreatePenで赤(淡)のペンを作成.
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0x7f, 0, 0));		// CreateSolidBrushで赤(濃)のブラシを作成.

	// ペンとブラシの選択.
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);		// 赤のペンを選択.
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);	// 赤のブラシを選択.

	// 矩形描画.
	Rectangle(hDC, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight);	// Rectangleで矩形を描画.
	
	// ペンとブラシの復元
	SelectObject(hDC, hOldBrush);		// 古いブラシを選択.
	SelectObject(hDC, hOldPen);		// 古いペンを選択.

	// ペンとブラシの破棄.
	DeleteObject(hBrush);	// ブラシの破棄.
	DeleteObject(hPen);	// ペンの破棄.
#endif

	// 描画終了.
	EndPaint(m_hWnd, &ps);	// EndPaintで描画終了.

}

// ウィンドウのサイズが変更された時.
void CWindowListItemsPanel::OnSize(UINT nType, int cx, int cy){

	// 親ウィンドウの既定処理.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSizeを呼ぶ.

	// 各ウィンドウリストアイテムの幅を右に合わせる.
	for (std::vector<CWindowListItem *>::iterator itor = m_vecWindowListItem.begin(); itor != m_vecWindowListItem.end(); itor++){	// m_vecWindowListItemの要素分繰り返す.
		MoveWindow((*itor)->m_hWnd, (*itor)->m_x, (*itor)->m_y, cx, (*itor)->m_iHeight, TRUE);	// 幅だけcxにする.
	}

}

// 子から親へウィンドウサイズ変更の要求が発生した時.
void CWindowListItemsPanel::OnSizeChild(WPARAM wParam, LPARAM lParam){

	// サイズ取り出し.
	int iWidth = LOWORD(wParam);	// LOWORDはiWidth.
	int iHeight = HIWORD(wParam);	// HIWORDはiHeight.
	HWND hSrc = (HWND)lParam;	// lParamをHWNDにキャストして, hSrcに格納.

	// ウィンドウマップからウィンドウオブジェクト取得.
	CWindow *pWindow = m_mapWindowMap[hSrc];	// m_mapWindowMap[hSrc]からpWindowを取得.

#if 0	
	// 右端, 下端を取得.
	int w = pWindow->m_x + pWindow->m_iWidth;	// 取得したウィンドウの右端を取得.
	int h = pWindow->m_y + pWindow->m_iHeight;	// 取得したウィンドウの下端を取得.

	// パネルが小さかったら拡大.
	if (m_iWidth < w){	// wが大きい.
		MoveWindow(m_hWnd, m_x, m_y, w, m_iHeight, TRUE);	// MoveWindowで横をwの大きさに拡大.
	}
	if (m_iHeight < h){	// hが大きい.
		MoveWindow(m_hWnd, m_x, m_y, m_iWidth, h, TRUE);	// MoveWindowで縦をhの大きさに拡大.
	}

	// アイテムの幅はアイテムズパネルに合わせる.
	MoveWindow(pWindow->m_hWnd, pWindow->m_x, pWindow->m_y, m_iClientAreaWidth, pWindow->m_iClientAreaHeight, TRUE);	// MoveWindowで横につける.
#endif

	// 変更されたhSrcが何番目かを調べる.
	BOOL bHit = FALSE;	// bHitをFALSEで初期化.
	m_iTotalHeight = 0;	// m_iTotalHeightを0に初期化.
	for (std::vector<CWindowListItem *>::iterator itor = m_vecWindowListItem.begin(); itor != m_vecWindowListItem.end(); itor++){	// m_vecWindowListItemの要素分繰り返す.
		
		// hSrcと等しいアイテムを探す.
		m_iTotalHeight += (*itor)->m_iHeight;	// 高さを足す.
		if ((*itor)->m_hWnd == hSrc){	// m_hWndとhSrcが等しい.
			bHit = TRUE;	// bHitをTRUEにする.
			continue;	// 次へ向かう.
		}
		if (bHit){	// bHit
			MoveWindow((*itor)->m_hWnd, (*itor)->m_x, (*(itor - 1))->m_y + (*(itor - 1))->m_iHeight, (*itor)->m_iWidth, (*itor)->m_iHeight, TRUE);
		}

	}

	// パネルのサイズ調整.
	MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_iTotalHeight, TRUE);	// MoveWindowでサイズ調整.

	// UM_SIZECHILDで子ウィンドウのサイズに合わせる.
	WPARAM wp;	// WPARAM型wp.
	wp = MAKEWPARAM(m_iWidth, m_iTotalHeight);	// MAKEWPARAMでwpをセット.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wp, (LPARAM)m_hWnd);	// SendMessageでUM_SIZECHILDを送信.

}