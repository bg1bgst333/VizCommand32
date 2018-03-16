// ヘッダのインクルード
// 独自のヘッダ
#include "Command.h"	// CCommand

// コマンド文字列のセット.
void CCommand::Set(tstring tstrCommandString){

	// 変数の宣言
	tstringstream tstrsrStream;	// 文字列ストリームtstrsrStream.
	tstring token;	// トークンtoken.

	// メンバにセット.
	m_tstrCommandString = tstrCommandString;	// m_tstrCommandStringにtstrCommandStringを代入.

	// 文字列ストリームを受け取る.
	tstrsrStream << tstrCommandString;	// 出力演算子で文字列をストリームに投入.

	// tstrsrStreamがEOFになるまでtokenをpush.
	while (!tstrsrStream.eof()) {	// tstrsrStream.eofでない間.
		tstring tmp;	// 一時文字列tmp.
		tstrsrStream >> tmp;	// ストリームから取り出してtmpに入れとく.
		if (tmp.size() > 0) {	// 最後の文字が空白類の連続の場合, EOFにならないのでこうしている.
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