// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "cpp_string_utility.h"	// class_cpp_string_utility
#include "Command.h"	// CCommand

// �R�}���h������̃Z�b�g.
void CCommand::Set(tstring tstrCommandString){

	// �ϐ��̐錾
	tstringstream tstrsrStream;	// ������X�g���[��tstrsrStream.
	tstring token;	// �g�[�N��token.
	int dqSecCount = 0;	// �_�u���N�H�[�g�̐�dqSecCount��0�ŏ�����.

	// �����o�ɃZ�b�g.
	m_tstrCommandString = tstrCommandString;	// m_tstrCommandString��tstrCommandString����.

	// �I���܂ŌJ��Ԃ�.
	while (true){	// true�Ȃ̂Ŗ������[�v.

		int n = 0;	// �ƍ��J�n�ʒun��0�ŏ�����.
		int s = m_tstrCommandString.find(_T("\""), n);	// "��T��.
		if (s == -1 && dqSecCount == 0){	// 1���Ȃ�.
			break;	// ������.
		}
		n = s + 1;	// �J�n�ʒu�͌��������ꏊ�̎�.
		int e = m_tstrCommandString.find(_T("\""), n);	// �I���ʒu.
		if (e == -1){	// ������Ȃ�.
			e = m_tstrCommandString.length() - 1;	// �Ō�.
		}
		tstring dqToken = m_tstrCommandString.substr(s, e - s + 1);	// �_�u���N�H�[�g�ň͂܂ꂽ�g�[�N�������o��.
		tstring spToken = dqToken;	// �R�s�[.
		tstring b = _T(" ");	// �X�y�[�X.
		tstring a = _T("<space>");	// "<space>".
		class_cpp_string_utility::replace(spToken, b, a);	// " "��<space>��.
		tstring ss = spToken;	// �R�s�[.
		tstring c = _T("");	// "".
		class_cpp_string_utility::replace(ss, _T("\""), _T(""));	// "������.
		tstring nodqToken = ss;	// �_�u���N�H�[�g�̖����g�[�N��.
		class_cpp_string_utility::replace(m_tstrCommandString, dqToken, nodqToken);	// ���̃e�L�X�g�Œu��.

	}

	// ������X�g���[�����󂯎��.
	tstrsrStream << m_tstrCommandString;	// �o�͉��Z�q�ŕ�������X�g���[���ɓ���.

	// tstrsrStream��EOF�ɂȂ�܂�token��push.
	while (!tstrsrStream.eof()) {	// tstrsrStream.eof�łȂ���.
		tstring tmp;	// �ꎞ������tmp.
		tstrsrStream >> tmp;	// �X�g���[��������o����tmp�ɓ���Ƃ�.
		if (tmp.size() > 0) {	// �Ō�̕������󔒗ނ̘A���̏ꍇ, EOF�ɂȂ�Ȃ��̂ł������Ă���.
			tstring b = _T("<space>");	// b��"<space>".
			tstring a = _T(" ");	// a��" ".
			class_cpp_string_utility::replace(tmp, b, a);	// �X�y�[�X��߂�.
			token = tmp;	// token��tmp����.
			m_vectstrCommandToken.push_back(token);	// m_vectstrCommandToken��token��push_back.
		}
	}

	// 0�Ԗڂ����C���̃R�}���h���ɂ���.
	if (m_vectstrCommandToken.size() > 0) {	// �g�[�N����1�ȏ�.
		m_tstrCommandName = m_vectstrCommandToken[0];	// m_vectstrCommandToken��0�Ԗڂ�m_tstrCommandName�Ɋi�[.
	}

}

// �R�}���h�̃N���A.
void CCommand::Clear(){

	// �N���A
	m_tstrCommandString.clear();	// m_tstrCommandString.clear�ŃN���A.
	m_vectstrCommandToken.clear();	// m_vectstrCommandToken.clear�ŃN���A.
	m_tstrCommandName.clear();	// m_tstrCommandName.clear�ŃN���A.

}

// �R�}���h���̎擾.
tstring CCommand::GetCommandName(){

	// �R�}���h����Ԃ�.
	return m_tstrCommandName;	// m_tstrCommandName��Ԃ�.

}

// �R�}���h������̎擾.
tstring CCommand::GetCommandString(){

	// �R�}���h�������Ԃ�.
	return m_tstrCommandString;	// m_tstrCommandString��Ԃ�.

}