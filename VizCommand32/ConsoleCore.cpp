// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "ConsoleCore.h"	// CConsoleCore

// �R���X�g���N�^CConsoleCore
CConsoleCore::CConsoleCore() : CScalableEdit(){

	// �����o�̏�����.
	m_tstrCommandString = _T("");	// m_tstrCommandString��""�ŏ�����.

}

// �R�}���h������̎擾�֐�GetCommandString.
tstring CConsoleCore::GetCommandString(){

	// �e�L�X�g�̎擾.
	m_tstrCommandString = GetText();	// GetText�Ŏ擾�����������m_tstrCommandString�Ɋi�[.

	// �R�}���h�������Ԃ�.
	return m_tstrCommandString;	// m_tstrCommandString��Ԃ�.

}

// �L�[�������ꂽ��.
int CConsoleCore::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){

	// ���^�[���L�[�������ꂽ��.
	if (nChar == VK_RETURN){	// nChar��VK_RETURN�̎�.

		// �R�}���h������̎擾.
		GetCommandString();	// GetCommandString�ŃR�}���h��������擾.
		MessageBox(m_hWnd, m_tstrCommandString.c_str(), _T("VizCommand"), MB_OK);	// MessageBox��m_tstrCommandString��\��.

	}

	// �e�N���X�̊��菈��.
	return CScalableEdit::OnKeyDown(nChar, nRepCnt, nFlags);	// CScalableEdit::OnKeyDown���Ă�.

}