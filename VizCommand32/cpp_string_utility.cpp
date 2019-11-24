// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "cpp_string_utility.h"	// class_cpp_string_utility

// wstring����string�ւ̕ϊ�.
std::string class_cpp_string_utility::encode_wstring_to_string(const std::wstring &wstr){

	// ���{�ꃍ�P�[���̃Z�b�g.
	setlocale(LC_ALL, "Japanese");	// setlocale��"Japanese"���Z�b�g.

	// �ϊ���̒��������߂�.
	size_t len = wcstombs(NULL, wstr.c_str(), 0);	// wcstombs�Œ���len�����߂�.(len��NULL�����͊܂܂�Ȃ�.)

	// �z����m��.
	char *buf = new char[len + 1];	// new��char�^���I�z��buf���m��.

	// buf��0�Ŗ��߂�.
	memset(buf, 0, sizeof(char) * (len + 1));	// memset��buf��0�Ŗ��߂�.

	// �����R�[�h�ϊ�.
	wcstombs(buf, wstr.c_str(), len + 1);	// wcstombs��wstr���}���`�o�C�g�����ɕϊ���, buf�Ɋi�[.

	// std::string�I�u�W�F�N�g�Ɋi�[.
	std::string str = buf;	// str��buf�ŏ�����.

	// buf���폜.
	delete [] buf;	// delete[]��buf�����.

	// str��Ԃ�.
	return str;	// str��Ԃ�.

}

// string����wstring�ւ̕ϊ�.
std::wstring class_cpp_string_utility::decode_string_to_wstring(const std::string& str){
	
	// ���{�ꃍ�P�[���̃Z�b�g.
	setlocale(LC_ALL, "Japanese");	// setlocale��"Japanese"���Z�b�g.

	// �ϊ���̒��������߂�.
	size_t len = mbstowcs(NULL, str.c_str(), 0);	// mbstowcs�Œ���len�����߂�.(len��NULL�����͊܂܂�Ȃ�.)

	// �z����m��.
	wchar_t *wbuf = new wchar_t[len + 1];	// new��wchar_t�^���I�z��wbuf���m��.

	// wbuf��L'0'�Ŗ��߂�.
	wmemset(wbuf, L'\0', len + 1);	// wmemset��wbuf��L'\0'�Ŗ��߂�.

	// �����R�[�h�ϊ�.
	mbstowcs(wbuf, str.c_str(), len + 1);	// wcstombs��str�����C�h�����ɕϊ���, wbuf�Ɋi�[.

	// std::wstring�I�u�W�F�N�g�Ɋi�[.
	std::wstring wstr = wbuf;	// wstr��wbuf�ŏ�����.

	// wbuf���폜.
	delete [] wbuf;	// delete[]��wbuf�����.

	// wstr��Ԃ�.
	return wstr;	// wstr��Ԃ�.

}

// tstring�̒u��.
void class_cpp_string_utility::replace(tstring & target, const tstring & before, const tstring & after) {

	// tstring�̕�����u��.
	tstring::size_type pos = target.find(before);	// target�ōŏ���before�����������ꏊ��pos�Ɋi�[.
	while (pos != tstring::npos) {
		target.replace(pos, before.size(), after);	// target��before����after�ɒu��.
		pos = target.find(before, pos + after.size());	// ����pos��T��.
	}

}