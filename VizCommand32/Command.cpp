// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "Command.h"	// CCommand

// �R�}���h������̃Z�b�g.
void CCommand::Set(tstring tstrCommandString){

	// �ϐ��̐錾
	tstringstream tstrsrStream;	// ������X�g���[��tstrsrStream.
	tstring token;	// �g�[�N��token.

	// �����o�ɃZ�b�g.
	m_tstrCommandString = tstrCommandString;	// m_tstrCommandString��tstrCommandString����.

	// ������X�g���[�����󂯎��.
	tstrsrStream << tstrCommandString;	// �o�͉��Z�q�ŕ�������X�g���[���ɓ���.

	// tstrsrStream��EOF�ɂȂ�܂�token��push.
	while (!tstrsrStream.eof()) {	// tstrsrStream.eof�łȂ���.
		tstring tmp;	// �ꎞ������tmp.
		tstrsrStream >> tmp;	// �X�g���[��������o����tmp�ɓ���Ƃ�.
		if (tmp.size() > 0) {	// �Ō�̕������󔒗ނ̘A���̏ꍇ, EOF�ɂȂ�Ȃ��̂ł������Ă���.
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