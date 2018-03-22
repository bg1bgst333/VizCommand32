// ヘッダのインクルード
// 独自のヘッダ
#include "Picture.h"	// CPicture
#include "BinaryFile.h"	// CBinaryFile

// コンストラクタCPicture
CPicture::CPicture() : CCustomControl(){

	// メンバの初期化.
	m_hBitmap = NULL;	// m_hBitmapをNULLで初期化.
	ZeroMemory(&m_Bitmap, sizeof(BITMAP));	// m_BitmapをZeroMemoryでクリア.
	m_tstrImageName.clear();	// m_tstrImageName.clear()でクリア.
	m_hMemDC = NULL;	// m_hMemDCをNULLで初期化.
	m_iHScrollPos = 0;	// m_iHScrollPosを0で初期化.
	m_iVScrollPos = 0;	// m_iVScrollPosを0で初期化.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// m_ScrollInfoをZeroMemoryでクリア.
	
}

// デストラクタ~CPicture()
CPicture::~CPicture(){

	// メンバの終了処理.
	Destroy();	// Destroyを呼ぶ.

}

// ウィンドウ作成関数Create(ウィンドウクラス名指定バージョン.)
BOOL CPicture::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// CCustomControl::Createで生成.
	return CCustomControl::Create(_T("Static"), lpctszWindowName, dwStyle | SS_BITMAP | SS_REALSIZECONTROL | WS_HSCROLL | WS_VSCROLL, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CCustomControl::Createでウィンドウクラス"Static"で作成.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CPicture::Destroy(){

	// ビットマップの破棄.
	if (m_hBitmap != NULL){	// m_hBitmapがNULLでない時.
		DeleteObject(m_hBitmap);	// m_hBitmapをDeleteObjectで破棄.
		m_hBitmap = NULL;	// m_hBitmapにNULLをセット.
	}
	ZeroMemory(&m_Bitmap, sizeof(BITMAP));	// m_BitmapをZeroMemoryでクリア.
	m_tstrImageName.clear();	// m_tstrImageName.clear()でクリア.
	if (m_hMemDC != NULL){	// m_hMemDCがNULLでない時.
		DeleteDC(m_hMemDC);	// m_hMemDCをDeleteDCで破棄.
		m_hMemDC = NULL;	// m_hMemDCにNULLをセット.
	}
	m_iHScrollPos = 0;	// m_iHScrollPosに0をセット.
	m_iVScrollPos = 0;	// m_iVScrollPosに0をセット.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// m_ScrollInfoをZeroMemoryでクリア.

	// 親クラスのDestroyを呼ぶ.
	CCustomControl::Destroy();	// CCustomControl::Destroyを呼ぶ.

}

// 画像をロードする関数LoadImage
BOOL CPicture::LoadImage(HINSTANCE hInstance, LPCTSTR lpctszImageName){

	// ビットマップの破棄.
	if (m_hBitmap != NULL) {	// NULLでなければ.
		DeleteObject(m_hBitmap);	// DeleteObjectでm_hBitmapを破棄.
		m_hBitmap = NULL;	// m_hBitmapにNULLをセット.
	}

	// 画像のロード.
	m_hBitmap = (HBITMAP)::LoadImage(hInstance, lpctszImageName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);	// LoadImageでm_tstrImageNameをロード.(とりあえず画像ファイルとしてロード.)
	if (m_hBitmap == NULL) {	// NULLなら失敗.

		// エラー処理.
		m_tstrImageName = _T("");	// 失敗したので""をセット.

		// 失敗なのでFALSEを返す.
		return FALSE;	// FALSEを返す.

	}

	// メンバにセット.
	m_tstrImageName = lpctszImageName;	// m_tstrImageNameにlpctszImageNameをセット.

	// 画像から幅と高さを取得.
	GetObject(m_hBitmap, sizeof(BITMAP), &m_Bitmap);	// GetObjectでm_hBitmapからビットマップ情報を取得し, m_Bitmapに格納.
	
	// 成功なのでTRUEを返す.
	return TRUE;	// TRUEを返す.

}

// 画像をセーブする関数SaveImage
BOOL CPicture::SaveImage(LPCTSTR lpctszImageName){

	// 変数の初期化.
	BITMAPINFO bi = {0};	// BITMAPINFO構造体変数biを{0}で初期化.
	LPBYTE lpBitsPixel = NULL;	// LPBYTE型(BYTE型ポインタ)のlpBitsPixelをNULLで初期化.
	BITMAPFILEHEADER bfh = {0};	// BITMAPFILEHEADER構造体bfhを{0}で初期化.
	HDC hDC = NULL;	// hDCをNULLで初期化.
	FILE *fp = NULL;	// ファイルポインタfpをNULLで初期化.

	// ビットマップ情報のセット.
	bi.bmiHeader.biBitCount = 24;	// ひとまず24bitビットマップのみ対応.
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);	// BITMAPINFOHEADERのサイズを指定しておく.
	bi.bmiHeader.biWidth = m_Bitmap.bmWidth;	// 画像幅m_Bitmap.bmWidthをセット.
	bi.bmiHeader.biHeight = m_Bitmap.bmHeight;	// 画像高さm_Bitmap.bmHeightをセット.
	bi.bmiHeader.biPlanes = 1;	// 1をセット.
	bi.bmiHeader.biCompression = BI_RGB;	// RGB.

	// DDBからDIBのピクセル列を取得.
	hDC = GetDC(m_hWnd);	// GetDCでm_hWndのデバイスコンテキストhDCを取得.
	GetDIBits(hDC, m_hBitmap, 0, m_Bitmap.bmHeight, NULL, &bi, DIB_RGB_COLORS);	// GetDIBitsでピクセル列のサイズ(bi.bmiHeader.biSizeImage)を取得.
	lpBitsPixel = new BYTE[bi.bmiHeader.biSizeImage];	// ピクセル列用のメモリ確保.
	GetDIBits(hDC, m_hBitmap, 0, m_Bitmap.bmHeight, lpBitsPixel, &bi, DIB_RGB_COLORS);	// GetDIBitsでピクセル列を取得.
	ReleaseDC(m_hWnd, hDC);	// hDCをリリース.

	// ビットマップファイル情報のセット.(24bitビットマップの場合.)
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);	// ピクセル列以外のサイズ.(つまりヘッダのサイズ.)
	bfh.bfSize = bfh.bfOffBits + bi.bmiHeader.biSizeImage;	// 全体のサイズはヘッダ + ピクセル列.
	bfh.bfType = 0x4d42;	// 0x4d42("BM")はビットマップであるという意味.
	bfh.bfReserved1 = 0;	// ここは0をセット.
	bfh.bfReserved2 = 0;	// ここは0をセット.

#if 1
	// ビットマップバイナリのファイル書き込み.
	CBinaryFile *pBinaryFile = new CBinaryFile();	// CBinaryFileオブジェクトを作成し, ポインタをpBinaryFileに格納.
	pBinaryFile->Set((BYTE *)&bfh, sizeof(BITMAPFILEHEADER));	// pBinaryFile->SetでBITMAPFILEHEADERのbfhをセット.
	pBinaryFile->Write(lpctszImageName);	// pBinaryFile->Write(ファイル名引数ありバージョン)でファイルを開いて書き込み.
	pBinaryFile->Set((BYTE *)&bi, sizeof(BITMAPINFOHEADER));	// pBinaryFile->SetでBITMAPINFOHEADERのbi(正確にはbi.bmiHeader)をセット.
	pBinaryFile->Write();	// pBinaryFile->Write(ファイル名引数なしバージョン)で書き込み.
	pBinaryFile->Set(lpBitsPixel, sizeof(BYTE) * bi.bmiHeader.biSizeImage);	// pBinaryFile->SetでlpBitsPixelをセット.
	pBinaryFile->Write();	// pBinaryFile->Write(ファイル名引数なしバージョン)で書き込み.
	delete pBinaryFile;	// pBinaryFileを解放.
	delete[] lpBitsPixel;	// delete[]でlpBitsPixelを解放.
#else
	// ファイルの書き込み.
	// 日本語ロケールのセット.
	setlocale(LC_ALL, "Japanese");	// setlocaleで"Japanese"をセット.
	// ファイル名をマルチバイトに変換.
	size_t filename_len = wcstombs(NULL, lpctszImageName, _MAX_PATH);	// wcstombsで長さfilename_lenを求める.(filename_lenにNULL文字は含まれない.)
	char *path = (char *)malloc(sizeof(char) * (filename_len + 1));	// mallocで動的配列を確保し, アドレスをpathに格納.
	wcstombs(path, lpctszImageName, _MAX_PATH);	// wcstombsでTCHARからマルチバイトへ変換.
	// ファイルを開く.
	fp = fopen(path, "wb");	// バイナリモード("wb")で開く.
	if (fp != NULL){	// fpがNULLでない時.
		fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fp);	// fwriteでbfhを書き込む.
		fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, fp);	// fwriteでbiを書き込む.
		fwrite(lpBitsPixel, sizeof(BYTE), bi.bmiHeader.biSizeImage, fp);	// fwriteでlpBitsPixelを書き込む.
		fclose(fp);	// fcloseでfpを閉じる.
	}
	// メモリの解放.
	free(path);	// freeでpathを解放.
	delete[] lpBitsPixel;	// delete[]でlpBitsPixelを解放.
#endif

	// メンバにセット.
	m_tstrImageName = lpctszImageName;	// m_tstrImageNameにlpctszImageNameをセット.

	// とりあえずTRUEとする.
	return TRUE;	// TRUEを返す.

}

// 画像をセット(表示)する関数SetImage
void CPicture::SetImage(){

	// 変数の宣言.
	HDC hDC;	// HDC型デバイスコンテキストハンドルhDC.

	// メモリデバイスコンテキストの破棄.
	if (m_hMemDC != NULL) {	// NULLでなければ.
		DeleteDC(m_hMemDC);	// DeleteDCでm_hMemDCを破棄.
		m_hMemDC = NULL;	// m_hMemDCにNULLをセット.
	}

	// デバイスコンテキストハンドルの取得.
	hDC = GetDC(m_hWnd);	// GetDCでm_hWndからデバイスコンテキストハンドルhDCを取得.

	// メモリデバイスコンテキストの作成.
	m_hMemDC = CreateCompatibleDC(hDC);	// CreateCompatibleDCで作成したデバイスコンテキストハンドルをm_hMemDCに格納.

	// 画像の表示.
	SendMessage(m_hWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hBitmap);	// SendMessageでSTM_SETIMAGEを送信することで画像を表示.

	// スクロールバーの位置を初期化.
	m_iHScrollPos = 0;	// m_iHScrollPosに0をセット.
	m_iVScrollPos = 0;	// m_iVScrollPosに0をセット.

	// ピクチャーの再描画.
	InvalidateRect(m_hWnd, NULL, TRUE);

	// デバイスコンテキストの解放.
	ReleaseDC(m_hWnd, hDC);	// ReleaseDCでhDCを解放.

}

// ウィンドウのサイズが変更された時.
void CPicture::OnSize(UINT nType, int cx, int cy){

	// 親のOnSizeを呼ぶ.
	CCustomControl::OnSize(nType, cx, cy);	// CCustomControl::OnSizeを呼ぶ.

	// UM_SIZECHILDで子ウィンドウのサイズに合わせる.
	WPARAM wParam;	// WPARAM型wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAMでwParamをセット.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessageでUM_SIZECHILDを送信.

	// 更新.
	InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRectで更新.

}

// ウィンドウの描画を要求された時のハンドラOnPaint.
void CPicture::OnPaint(){

	// 変数の初期化.
	HDC hDC = NULL;	// hDCをNULLで初期化.
	PAINTSTRUCT ps = {0};	// psを{0}で初期化.
	HBITMAP hOld = NULL;	// hOldをNULLで初期化.
	int iDrawWidth;	// 実際の描画幅.
	int iDrawHeight;	// 実際の描画高さ.

	// 描画開始.
	hDC = BeginPaint(m_hWnd, &ps);	// BeginPaintで描画開始.

	// ビットマップの選択.
	hOld = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);	// SelectObjectでm_hMemDCにm_hBitmapを選択.
	
	// ビット転送.
	iDrawWidth = m_iClientAreaWidth;	// 描画幅 = ピクチャーコントロール幅 - スクロールバー幅.
	iDrawHeight = m_iClientAreaHeight;	// 描画高さ = ピクチャーコントロール高さ - スクロールバー高さ.
	BitBlt(hDC, 0, 0, iDrawWidth, iDrawHeight, m_hMemDC, m_iHScrollPos, m_iVScrollPos, SRCCOPY);	// BitBltでm_hMemDCをhDCに転送.

	// 古いビットマップを再選択して戻す.
	SelectObject(m_hMemDC, hOld);	// SelectObjectでhOldを選択.

	// スクロールバー設定.
	// 水平方向.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemoryでm_ScrollInfoをクリア.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズ
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// フラグ
	m_ScrollInfo.nPage = iDrawWidth;	// 描画幅
	m_ScrollInfo.nMin = 0;	// 最小値
	m_ScrollInfo.nMax = m_Bitmap.bmWidth;	//最大値
	SetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo, TRUE);	// SetScrollInfoでセット.(SetImageのInvalidateRectと第4引数のTRUEがないとスクロールバーつまみが即座に更新されない.)
	// 垂直方向.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemoryでm_ScrollInfoをクリア.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズ
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// フラグ
	m_ScrollInfo.nPage = iDrawHeight;	// 描画高さ
	m_ScrollInfo.nMin = 0;	// 最小値
	m_ScrollInfo.nMax = m_Bitmap.bmHeight;	//最大値
	SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);	// SetScrollInfoでセット.(SetImageのInvalidateRectと第4引数のTRUEがないとスクロールバーつまみが即座に更新されない.)

	// 描画終了.
	EndPaint(m_hWnd, &ps);	// EndPaintで描画終了.

}

// 水平方向スクロールバーイベント時のハンドラOnHScroll.
void CPicture::OnHScroll(UINT nSBCode, UINT nPos){

	// スクロール情報取得.
	m_ScrollInfo.fMask = SIF_POS;	// 位置だけ変更モード(これがないと, スクロールバーが元の位置に戻ってしまうので注意!こっちが前!)
	GetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo);	// マスクを設定してからGetScrollInfo.(こっちが後!)

	// スクロールバー処理.
	switch (nSBCode) {	// nSBCodeごとに振り分け.

		// 一番左
		case SB_LEFT:

			// 位置を最小値に.
			m_ScrollInfo.nPos = m_ScrollInfo.nMin;
			break;

		// 一番右
		case SB_RIGHT:

			// 位置を最大値に.
			m_ScrollInfo.nPos = m_ScrollInfo.nMax;
			break;

		// 1列左
		case SB_LINELEFT:

			// nPosが0でなければデクリメント.
			if (m_ScrollInfo.nPos > 0) {
				m_ScrollInfo.nPos--;
			}
			break;

		// 1列右
		case SB_LINERIGHT:

			// nPosが最大値-1でなければインクリメント.
			if (m_ScrollInfo.nPos < m_ScrollInfo.nMax - 1) {
				m_ScrollInfo.nPos++;
			}
			break;

		// 1ページ左
		case SB_PAGELEFT:

			// nPage分減らす.
			m_ScrollInfo.nPos -= m_ScrollInfo.nPage;
			break;

		// 1ページ右
		case SB_PAGERIGHT:

			// nPage分増やす.
			m_ScrollInfo.nPos += m_ScrollInfo.nPage;
			break;

		// つまみをドラッグ中.
		case SB_THUMBTRACK:

			// 引数のnPosをセット
			m_ScrollInfo.nPos = nPos;
			break;

		// つまみをドラッグ後.
		case SB_THUMBPOSITION:

			// 引数のnPosをセット
			m_ScrollInfo.nPos = nPos;
			break;

		// それ以外.
		default:

			break;

	}

	// スクロール情報設定.
	SetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo, TRUE);
	// メンバにもセット.
	m_iHScrollPos = m_ScrollInfo.nPos;
	// 無効領域を作成して画面の更新.
	InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRectで無効領域作成.

}

// 垂直方向スクロールバーイベント時のハンドラOnVScroll.
void CPicture::OnVScroll(UINT nSBCode, UINT nPos){

	// スクロール情報取得.
	m_ScrollInfo.fMask = SIF_POS;	// 位置だけ変更モード(これがないと, スクロールバーが元の位置に戻ってしまうので注意!こっちが前!)
	GetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo);	// マスクを設定してからGetScrollInfo.(こっちが後!)

	// スクロールバー処理.
	switch (nSBCode) {	// nSBCodeごとに振り分け.

		// 一番上
		case SB_TOP:

			// 位置を最小値に.
			m_ScrollInfo.nPos = m_ScrollInfo.nMin;
			break;

		// 一番下
		case SB_BOTTOM:

			// 位置を最大値に.
			m_ScrollInfo.nPos = m_ScrollInfo.nMax;
			break;

		// 1行上
		case SB_LINEUP:

			// nPosが0でなければデクリメント.
			if (m_ScrollInfo.nPos > 0) {
				m_ScrollInfo.nPos--;
			}
			break;

		// 1行下
		case SB_LINEDOWN:

			// nPosが最大値-1でなければインクリメント.
			if (m_ScrollInfo.nPos < m_ScrollInfo.nMax - 1) {
				m_ScrollInfo.nPos++;
			}
			break;

		// 1ページ上
		case SB_PAGEUP:

			// nPage分減らす.
			m_ScrollInfo.nPos -= m_ScrollInfo.nPage;
			break;

		// 1ページ下
		case SB_PAGEDOWN:

			// nPage分増やす.
			m_ScrollInfo.nPos += m_ScrollInfo.nPage;
			break;

		// つまみをドラッグ中.
		case SB_THUMBTRACK:
	
			// 引数のnPosをセット
			m_ScrollInfo.nPos = nPos;
			break;

		// つまみをドラッグ後.
		case SB_THUMBPOSITION:

			// 引数のnPosをセット
			m_ScrollInfo.nPos = nPos;
			break;

		// それ以外.
		default:

			break;

	}

	// スクロール情報設定.
	SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);
	// メンバにもセット.
	m_iVScrollPos = m_ScrollInfo.nPos;
	// 無効領域を作成して画面の更新.
	InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRectで無効領域作成.

}

// マウスが移動している時.
void CPicture::OnMouseMove(UINT nFlags, POINT pt){

	// マウスダウンフラグが立っている時.
	if (nFlags == MK_LBUTTON){	// 左ボタンが押されている時.

		// ビットマップの選択.
		HBITMAP hOld = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);	// SelectObjectでm_hBitmapを選択.

		// 押された場所に黒い点をセット.
		SetPixel(m_hMemDC, pt.x + m_iHScrollPos, pt.y + m_iVScrollPos, RGB(0x0, 0x0, 0x0));	// SetPixelで黒い点をセット.

		// 前回の場所から押された場所までの直線を描く.
		LineTo(m_hMemDC, pt.x + m_iHScrollPos, pt.y + m_iVScrollPos);	// LineToで押された場所までの直線を描く.

		// 押された場所に始点を移動.
		MoveToEx(m_hMemDC, pt.x + m_iHScrollPos, pt.y + m_iVScrollPos, NULL);	// MoveToExで始点を移動.

		// 古いビットマップを再選択.
		SelectObject(m_hMemDC, hOld);	// SelectObjectでhOldを選択.

		// 画面更新.
		InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRectで画面更新.

	}
	else{	// マウスダウンフラグが立っていない時.

		// マウスの移動場所に始点を移動.
		MoveToEx(m_hMemDC, pt.x + m_iHScrollPos, pt.y + m_iVScrollPos, NULL);	// MoveToExで始点を移動.

	}
}

// マウスの左クリックが行われた時のハンドラOnLButtonDown.
int CPicture::OnLButtonDown(UINT nFlags, POINT pt){

	// マウスダウンフラグが立っている時.
	if (nFlags == MK_LBUTTON){	// 左ボタンが押されている時.

		// ビットマップの選択.
		HBITMAP hOld = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);	// SelectObjectでm_hBitmapを選択.

		// 押された場所に黒い点をセット.
		SetPixel(m_hMemDC, pt.x + m_iHScrollPos, pt.y + m_iVScrollPos, RGB(0x0, 0x0, 0x0));	// SetPixelで黒い点をセット.

		// 古いビットマップを再選択.
		SelectObject(m_hMemDC, hOld);	// SelectObjectでhOldを選択.

		// 画面更新.
		InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRectで画面更新.

	}

	// 成功なら0を返す.
	return 0;	// returnで0を返す.

}

// マウスの左ボタンが離された時.
int CPicture::OnLButtonUp(UINT nFlags, POINT pt){

	// マウスダウンフラグが立っている時.
	if (nFlags == MK_LBUTTON){	// 左ボタンが押されている時.

		// ビットマップの選択.
		HBITMAP hOld = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);	// SelectObjectでm_hBitmapを選択.

		// 押された場所に黒い点をセット.
		SetPixel(m_hMemDC, pt.x + m_iHScrollPos, pt.y + m_iVScrollPos, RGB(0x0, 0x0, 0x0));	// SetPixelで黒い点をセット.

		// 古いビットマップを再選択.
		SelectObject(m_hMemDC, hOld);	// SelectObjectでhOldを選択.

		// 画面更新.
		InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRectで画面更新.

	}

	// 成功なら0を返す.
	return 0;	// returnで0を返す.

}