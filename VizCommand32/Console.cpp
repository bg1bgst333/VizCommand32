// ヘッダのインクルード
// 独自のヘッダ
#include "Console.h"	// CConsole
#include "Command.h"	// CCommand

// コンストラクタCConsole
CConsole::CConsole() : CScalableEditPanel(){

	// メンバの初期化.
	m_hbrBackground = NULL;	// m_hbrBackgroundをNULLで初期化.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CConsole::RegisterClass(HINSTANCE hInstance){

	// ウィンドウクラスの登録.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(WHITE_BRUSH));	// CUserControl::RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
BOOL CConsole::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackgroundを指定.
	return CUserControl::RegisterClass(hInstance, _T("CConsole"), hbrBackground);	// CUserControl::RegisterClassで登録.

}

// ウィンドウ作成関数Create.
BOOL CConsole::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウの作成.
	m_nId = hMenu;	// m_nIdにhMenuを格納.
	BOOL bRet = CUserControl::Create(_T("CConsole"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, m_nId, hInstance);	// CWindow::Createで作成.

	// 成功.
	if (bRet){	// bRetがTRUE.

		// 子コンソールコアの生成.
		m_pScalableEdit = new CConsoleCore();	// CConsoleCoreオブジェクトを生成し, ポインタをm_pScalableEditに格納.
		BOOL bRet2 = m_pScalableEdit->Create(_T(""), 0, m_x, m_y, m_iClientAreaWidth, m_iClientAreaHeight, m_hWnd, m_nId + 100, hInstance);	// m_pScalableEdit->Createで子スカラブルエディットコントロール生成.
		if (bRet2){	// bRet2がTRUE.
			// リサイズ.
			MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_pScalableEdit->m_iHeight, TRUE);	// MoveWindowでm_pScalableEdit->m_iHeightの高さにリサイズ.
			// コンソールコアのメッセージの投げる先をここにする.
			if (m_pScalableEdit != NULL){	// m_pScalableEditがNULLでなければ.
				// 処理するウィンドウのセット.
				((CConsoleCore *)m_pScalableEdit)->SetProcWindow(m_hWnd);	// ((CConsoleCore *)m_pScalableEdit)->SetProcWindowで処理するウィンドウはここにする.
				// 黒ブラシ作成.
				m_hbrBackground = CreateSolidBrush(RGB(0x0, 0x0, 0x0));	// CreateSolidBrushで黒ブラシを作成し, m_hbrBackgroundに格納.
				SetFocus(m_pScalableEdit->m_hWnd);	// SetFocusでm_pScalableEdit->m_hWndにフォーカスを当てる.
			}
		}

	}

	// 戻り値を返す.
	return bRet;	// bRetを返す.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CConsole::Destroy(){

	// ブラシの破棄.
	if (m_hbrBackground != NULL){	// m_hbrBackgroundがNULLでない時.
		DeleteObject(m_hbrBackground);	// DeleteObjectで削除.
		m_hbrBackground = NULL;	// m_hbrBackgroundにNULlをセット.
	}

	// 親のDestroyを呼ぶ.
	CScalableEditPanel::Destroy();

}

// 入力フォームの出力.
void CConsole::ShowInputForm(){
	
	// コンソールコアの入力フォーム出力を呼ぶ.
	if (m_pScalableEdit != NULL){	// m_pScalableEditがNULLでなければ.
		((CConsoleCore *)m_pScalableEdit)->ShowInputForm();	// ((CConsoleCore *)m_pScalableEdit)->ShowInputFormで入力フォームの出力.
	}

}

// ウィンドウのサイズが変更された時.
void CConsole::OnSize(UINT nType, int cx, int cy){

	// 親のOnSizeを呼ぶ.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSizeを呼ぶ.

	// 子コンソールコアのリサイズ.
	if (m_pScalableEdit != NULL){	// NULLでなければ.
		MoveWindow(m_pScalableEdit->m_hWnd, m_pScalableEdit->m_x, m_pScalableEdit->m_y, cx, cy, TRUE);	// MoveWindowで子コンソールコアをリサイズ.
	}

	// UM_SIZECHILDで子ウィンドウのサイズに合わせる.
	WPARAM wParam;	// WPARAM型wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAMでwParamをセット.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessageでUM_SIZECHILDを送信.

}

// 子エディットコントロールの描画時.
HBRUSH CConsole::OnCtlColorEdit(HDC hDC, HWND hEdit){

	// 背景を黒, テキストを白にする.
	SetBkColor(hDC, RGB(0x0, 0x0, 0x0));	// 背景は黒.
	SetTextColor(hDC, RGB(0xff, 0xff, 0xff));	// テキストは白.
	return m_hbrBackground;	// m_hbrBackgroundを返す.

}

// ユーザ定義メッセージが発生した時.
void CConsole::OnUserMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){

	// switch-case文で振り分ける.
	switch (uMsg) {

		// 子から親へウィンドウサイズ変更の要求が発生した時.
		case UM_SIZECHILD:

			// UM_SIZECHILDブロック
			{

				// OnSizeChildに任せる.
				OnSizeChild(wParam, lParam);	// OnSizeChildに任せる.

			}

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

		// コンソールコアからメッセージが送られた時.
		case UM_CONSOLECORECOMMAND:

			// UM_CONSOLECORECOMMANDブロック
			{

				// OnConsoleCoreCommandに任せる.
				OnConsoleCoreCommand(wParam, lParam);	// OnConsoleCoreCommandに任せる.

			}

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

		// それ以外.
		default:

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

	}

}

// コンソールコアからメッセージが送られた時.
int CConsole::OnConsoleCoreCommand(WPARAM wParam, LPARAM lParam){

	// 変数の初期
	CCommand *pCommand = NULL;	// CCommandオブジェクトポインタpCommandをNULLで初期化.
	HWND hSrc = NULL;	// 送信元ウィンドウハンドルhSrcをNULLで初期化.

	// コマンドとソースを取得.
	pCommand = (CCommand *)wParam;	// wParamを(CCommand *)にキャストしてpCommandに格納.
	hSrc = (HWND)lParam;	// lParamをHWNDにキャストしてhSrcに格納.

	// コマンドの判別.
	tstring tstrCommandName = pCommand->GetCommandName();	// pCommand->GetCommandNameで取得したコマンド名をtstrCommandNameに格納.
	if (tstrCommandName == _T("hello")){	// helloコマンド.

		// OnHelloに任せる.
		OnHello(hSrc, pCommand);	// hSrc, pCommandを引数として渡して, OnHelloを呼ぶ.

	}
	else {	// コマンドが見つからない.

		// コマンドが見つからないエラー.
		OnErrorCommandNotFound(hSrc);	// hSrcを引数として渡して, OnErrorCommandNotFoundを呼ぶ.

 	}

	// 成功なら0を返す.
	return 0;	// 0を返す.

}

// "Hello, world!"の出力を要求された時.
void CConsole::OnHello(HWND hSrc, CCommand *pCommand){

	// "/g"オプションがあれば, StreamConsoleに投げる.
	if (pCommand->m_vectstrCommandToken.size() > 1){	// オプションがある場合.
		if (pCommand->m_vectstrCommandToken[1] == _T("/g")){	// "/g"オプションなら.

			// "Hello, GUI world!"を出力.
			SendMessage(hSrc, UM_RESPONSEMESSAGE, (WPARAM)_T("Hello, GUI world!\r\n"), 0);	// UM_RESPONSEMESSAGEで"Hello, GUI world!"を送る.

			// レスポンス終了.
			SendMessage(hSrc, UM_FINISHRESPONSE, 0, 0);	// UM_FINISHRESPONSEを送る.

			// 終了.
			return;	// ここで終了.

		}
	}

	// "Hello, world!"を出力.
	SendMessage(hSrc, UM_RESPONSEMESSAGE, (WPARAM)_T("Hello, world!\r\n"), 0);	// UM_RESPONSEMESSAGEで"Hello, world!"を送る.

	// レスポンス終了.
	SendMessage(hSrc, UM_FINISHRESPONSE, 0, 0);	// UM_FINISHRESPONSEを送る.

}

// コマンドが見つからないエラーが発生した時.
void CConsole::OnErrorCommandNotFound(HWND hSrc){

	// "Error: Command not found!"を出力.
	SendMessage(hSrc, UM_RESPONSEMESSAGE, (WPARAM)_T("Error: Command not found!\r\n"), 0);	// UM_RESPONSEMESSAGEで"Error: Command not found!"を送る.

	// レスポンス終了.
	SendMessage(hSrc, UM_FINISHRESPONSE, 0, 0);	// UM_FINISHRESPONSEを送る.

}