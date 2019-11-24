// ヘッダのインクルード
// 独自のヘッダ
#include "cpp_string_utility.h"	// class_cpp_string_utility

// wstringからstringへの変換.
std::string class_cpp_string_utility::encode_wstring_to_string(const std::wstring &wstr){

	// 日本語ロケールのセット.
	setlocale(LC_ALL, "Japanese");	// setlocaleで"Japanese"をセット.

	// 変換後の長さを求める.
	size_t len = wcstombs(NULL, wstr.c_str(), 0);	// wcstombsで長さlenを求める.(lenにNULL文字は含まれない.)

	// 配列を確保.
	char *buf = new char[len + 1];	// newでchar型動的配列bufを確保.

	// bufを0で埋める.
	memset(buf, 0, sizeof(char) * (len + 1));	// memsetでbufを0で埋める.

	// 文字コード変換.
	wcstombs(buf, wstr.c_str(), len + 1);	// wcstombsでwstrをマルチバイト文字に変換し, bufに格納.

	// std::stringオブジェクトに格納.
	std::string str = buf;	// strをbufで初期化.

	// bufを削除.
	delete [] buf;	// delete[]でbufを解放.

	// strを返す.
	return str;	// strを返す.

}

// stringからwstringへの変換.
std::wstring class_cpp_string_utility::decode_string_to_wstring(const std::string& str){
	
	// 日本語ロケールのセット.
	setlocale(LC_ALL, "Japanese");	// setlocaleで"Japanese"をセット.

	// 変換後の長さを求める.
	size_t len = mbstowcs(NULL, str.c_str(), 0);	// mbstowcsで長さlenを求める.(lenにNULL文字は含まれない.)

	// 配列を確保.
	wchar_t *wbuf = new wchar_t[len + 1];	// newでwchar_t型動的配列wbufを確保.

	// wbufをL'0'で埋める.
	wmemset(wbuf, L'\0', len + 1);	// wmemsetでwbufをL'\0'で埋める.

	// 文字コード変換.
	mbstowcs(wbuf, str.c_str(), len + 1);	// wcstombsでstrをワイド文字に変換し, wbufに格納.

	// std::wstringオブジェクトに格納.
	std::wstring wstr = wbuf;	// wstrをwbufで初期化.

	// wbufを削除.
	delete [] wbuf;	// delete[]でwbufを解放.

	// wstrを返す.
	return wstr;	// wstrを返す.

}

// tstringの置換.
void class_cpp_string_utility::replace(tstring & target, const tstring & before, const tstring & after) {

	// tstringの文字列置換.
	tstring::size_type pos = target.find(before);	// targetで最初にbeforeが見つかった場所をposに格納.
	while (pos != tstring::npos) {
		target.replace(pos, before.size(), after);	// targetをbeforeからafterに置換.
		pos = target.find(before, pos + after.size());	// 次のposを探す.
	}

}