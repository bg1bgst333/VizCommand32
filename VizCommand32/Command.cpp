// ヘッダのインクルード
// 独自のヘッダ
#include "cpp_string_utility.h"	// class_cpp_string_utility
#include "Command.h"	// CCommand

// コマンド文字列のセット.
void CCommand::Set(tstring tstrCommandString){

	// 変数の宣言
	tstringstream tstrsrStream;	// 文字列ストリームtstrsrStream.
	tstring token;	// トークンtoken.
	int dqSecCount = 0;	// ダブルクォートの数dqSecCountを0で初期化.

	// メンバにセット.
	m_tstrCommandString = tstrCommandString;	// m_tstrCommandStringにtstrCommandStringを代入.

	// 終わるまで繰り返す.
	while (true){	// trueなので無限ループ.

		int n = 0;	// 照合開始位置nを0で初期化.
		int s = m_tstrCommandString.find(_T("\""), n);	// "を探す.
		if (s == -1 && dqSecCount == 0){	// 1つもない.
			break;	// 抜ける.
		}
		n = s + 1;	// 開始位置は見つかった場所の次.
		int e = m_tstrCommandString.find(_T("\""), n);	// 終了位置.
		if (e == -1){	// 見つからない.
			e = m_tstrCommandString.length() - 1;	// 最後.
		}
		tstring dqToken = m_tstrCommandString.substr(s, e - s + 1);	// ダブルクォートで囲まれたトークンを取り出す.
		tstring spToken = dqToken;	// コピー.
		tstring b = _T(" ");	// スペース.
		tstring a = _T("<space>");	// "<space>".
		class_cpp_string_utility::replace(spToken, b, a);	// " "を<space>に.
		tstring ss = spToken;	// コピー.
		tstring c = _T("");	// "".
		class_cpp_string_utility::replace(ss, _T("\""), _T(""));	// "を除去.
		tstring nodqToken = ss;	// ダブルクォートの無いトークン.
		class_cpp_string_utility::replace(m_tstrCommandString, dqToken, nodqToken);	// 元のテキストで置換.

	}

	// 文字列ストリームを受け取る.
	tstrsrStream << m_tstrCommandString;	// 出力演算子で文字列をストリームに投入.

	// tstrsrStreamがEOFになるまでtokenをpush.
	while (!tstrsrStream.eof()) {	// tstrsrStream.eofでない間.
		tstring tmp;	// 一時文字列tmp.
		tstrsrStream >> tmp;	// ストリームから取り出してtmpに入れとく.
		if (tmp.size() > 0) {	// 最後の文字が空白類の連続の場合, EOFにならないのでこうしている.
			tstring b = _T("<space>");	// bは"<space>".
			tstring a = _T(" ");	// aは" ".
			class_cpp_string_utility::replace(tmp, b, a);	// スペースを戻す.
			token = tmp;	// tokenにtmpを代入.
			m_vectstrCommandToken.push_back(token);	// m_vectstrCommandTokenにtokenをpush_back.
		}
	}

	// 0番目をメインのコマンド名にする.
	if (m_vectstrCommandToken.size() > 0) {	// トークンが1以上.
		m_tstrCommandName = m_vectstrCommandToken[0];	// m_vectstrCommandTokenの0番目をm_tstrCommandNameに格納.
	}

}

// コマンドのクリア.
void CCommand::Clear(){

	// クリア
	m_tstrCommandString.clear();	// m_tstrCommandString.clearでクリア.
	m_vectstrCommandToken.clear();	// m_vectstrCommandToken.clearでクリア.
	m_tstrCommandName.clear();	// m_tstrCommandName.clearでクリア.

}

// コマンド名の取得.
tstring CCommand::GetCommandName(){

	// コマンド名を返す.
	return m_tstrCommandName;	// m_tstrCommandNameを返す.

}

// コマンド文字列の取得.
tstring CCommand::GetCommandString(){

	// コマンド文字列を返す.
	return m_tstrCommandString;	// m_tstrCommandStringを返す.

}