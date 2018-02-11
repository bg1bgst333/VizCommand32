// ヘッダのインクルード
// 独自のヘッダ
#include "WindowListItem.h"	// CWindowListItem

// コンストラクタCWindowListItem
CWindowListItem::CWindowListItem() : CUserControl(){

}

// デストラクタ~CWindowListItem
CWindowListItem::~CWindowListItem(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CWindowListItem::RegisterClass(HINSTANCE hInstance){

	// ウィンドウクラスの登録.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CUserControl::RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
BOOL CWindowListItem::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackgroundを指定.
	return CUserControl::RegisterClass(hInstance, _T("CWindowListItem"), hbrBackground);	// CUserControl::RegisterClassで登録.

}

// ウィンドウ作成関数Create.
BOOL CWindowListItem::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウの作成.
	return CUserControl::Create(_T("CWindowListItem"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createで作成.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CWindowListItem::Destroy(){

	// 親ウィンドウのDestroyを呼ぶ.
	CUserControl::Destroy();	// CUserControl::Destroyを呼ぶ.

}

// ウィンドウの作成が開始された時.
int CWindowListItem::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// 常にウィンドウ作成に成功するものとする.
	return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

}

// ウィンドウが破棄された時.
void CWindowListItem::OnDestroy(){

	// メンバの終了処理
	//Destroy();	// Destroyでこのウィンドウの終了処理をする.

	// 親クラスのOnDestroyを呼ぶ.
	CUserControl::OnDestroy();	// CUserControl::OnDestroyを呼ぶ.

}

// ウィンドウの描画を要求された時のハンドラOnPaint.
void CWindowListItem::OnPaint(){

	// 変数の初期化.
	HDC hDC = NULL;	// hDCをNULLで初期化.
	PAINTSTRUCT ps = {0};	// psを{0}で初期化.
	HPEN hPen = NULL;	// hPenをNULLで初期化.
	HBRUSH hBrush = NULL;	// hBrushをNULLで初期化.

	// 描画開始.
	hDC = BeginPaint(m_hWnd, &ps);	// BeginPaintで描画開始.

	// ペンとブラシの生成.
	hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0xff, 0, 0xff));	// CreatePenで紫(淡)のペンを作成.
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0x7f, 0, 0x7f));		// CreateSolidBrushで紫(濃)のブラシを作成.

	// ペンとブラシの選択.
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);		// 紫のペンを選択.
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);	// 紫のブラシを選択.

	// 矩形描画.
	Rectangle(hDC, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight);	// Rectangleで矩形を描画.
	
	// ペンとブラシの復元
	SelectObject(hDC, hOldBrush);		// 古いブラシを選択.
	SelectObject(hDC, hOldPen);		// 古いペンを選択.

	// ペンとブラシの破棄.
	DeleteObject(hBrush);	// ブラシの破棄.
	DeleteObject(hPen);	// ペンの破棄.

	// 描画終了.
	EndPaint(m_hWnd, &ps);	// EndPaintで描画終了.

}

// ウィンドウのサイズが変更された時.
void CWindowListItem::OnSize(UINT nType, int cx, int cy){

	// 親ウィンドウの既定処理.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSizeを呼ぶ.

}

// 子から親へウィンドウサイズ変更の要求が発生した時.
void CWindowListItem::OnSizeChild(WPARAM wParam, LPARAM lParam){

	// サイズ取り出し.
	int iWidth = LOWORD(wParam);	// LOWORDはiWidth.
	int iHeight = HIWORD(wParam);	// HIWORDはiHeight.

	// 自身のウィンドウサイズ変更.
	MoveWindow(m_hWnd, 0, 0, iWidth, iHeight, TRUE);	// MoveWindowで子ウィンドウのサイズに合わせる.

}