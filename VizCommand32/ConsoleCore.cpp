// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "ConsoleCore.h"	// CConsoleCore
#include <shlobj.h>	// �V�F���I�u�W�F�N�g

// �R���X�g���N�^CConsoleCore
CConsoleCore::CConsoleCore() : CScalableEdit(){

	// �����o�̏�����.
	m_tstrCommandString = _T("");	// m_tstrCommandString��""�ŏ�����.
	m_tstrFormString = GREATER_THAN;	// m_tstrFormString��">"�ɏ�����.
	m_lStartPos = 0;	// m_lStartPos��0�ɏ�����.
	m_lCurrentPos = 0;	// m_lCurrentPos��0�ɏ�����.

}

// �R�}���h������̎擾�֐�GetCommandString.
tstring CConsoleCore::GetCommandString(){

	// �e�L�X�g�̎擾.
	m_tstrCommandString = GetText();	// GetText�Ŏ擾�����������m_tstrCommandString�Ɋi�[.

	// �R�}���h�������Ԃ�.
	return m_tstrCommandString;	// m_tstrCommandString��Ԃ�.

}

// �z�[���t�H���_(CSIDL_PROFILE)�̃p�X���擾.
tstring CConsoleCore::GetProfilePath(HWND hWnd){

	// �z��̏�����.
	TCHAR tszPath[1024] = {0};	// CSIDL_PROFILE�ȃp�X���i�[����z��tszPath��{0}�ŏ�����.

	// �z�[���t�H���_�̃p�X���擾.
	SHGetSpecialFolderPath(hWnd, tszPath, CSIDL_PROFILE, FALSE);	// SHGetSpecialFolderPath��CSIDL_PROFILE�ȃp�X���擾.

	// �z�[���t�H���_�̃p�X�������o�Ɋi�[.
	m_tstrProfilePath = tszPath;	// m_tstrProfilePath��tszPath���i�[.

	// �z�[���t�H���_�̃p�X��Ԃ�.
	return m_tstrProfilePath;	// m_tstrProfilePath��Ԃ�.

}

// ���̓t�H�[��������̎擾.
tstring CConsoleCore::GetInputFormString(){

	// ���̓t�H�[��������̐���.
	m_tstrInputFormString = m_tstrCurrentPath + m_tstrFormString;	// ���̓t�H�[�������� = ���݂̃p�X + �t�H�[��������.

	// ���̓t�H�[���������Ԃ�.
	return m_tstrInputFormString;	// m_tstrInputFormString��Ԃ�.

}

// �R���\�[���ɕ�������o��.
void CConsoleCore::PutConsole(tstring tstrString){

	// �������ǉ�����.
	SendMessage(m_hWnd, EM_REPLACESEL, 0, (LPARAM)tstrString.c_str());	// EM_REPLACESEL��tstrString��ǉ�����.(�{���͒u������, 0���w�肵���Ƃ��͒ǉ�(�}��)�������ƂɂȂ�.)

	// ���͈ʒu�̍X�V.
	SendMessage(m_hWnd, EM_GETSEL, (WPARAM)&m_lStartPos, NULL);	// EM_GETSEL�őI�����Ă��Ȃ��ꍇ�͊J�n�ʒu���擾�ł���.

}

// ���̓t�H�[���̏o��.
void CConsoleCore::ShowInputForm(){

	// ���̓t�H�[����������o��.
	PutConsole(m_tstrInputFormString);	// PutConsole��m_tstrInputFormString���o��.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CConsoleCore::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �e�N���X��OnCreate���Ă�.
	CScalableEdit::OnCreate(hwnd, lpCreateStruct);	// CScalableEdit::OnCreate���Ă�.

	// �z�[���t�H���_�̎擾.
	GetProfilePath(hwnd);	// GetProfilePath�Ńz�[���t�H���_���擾.

	// ���݂̃p�X���z�[���t�H���_�ɃZ�b�g.
	m_tstrCurrentPath = m_tstrProfilePath;	// m_tstrCurrentPath��m_tstrProfilePath���Z�b�g.

	// ���̓t�H�[����������擾.
	GetInputFormString();	// GetInputFormString���擾.

	// ����.
	return 0;	// �����Ȃ̂�0��Ԃ�.

}

// �L�[�������ꂽ��.
int CConsoleCore::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){

	// ���^�[���L�[�������ꂽ��.
	if (nChar == VK_RETURN){	// nChar��VK_RETURN�̎�.

		// �R�}���h������̎擾.
		GetCommandString();	// GetCommandString�ŃR�}���h��������擾.
		MessageBox(m_hWnd, m_tstrCommandString.c_str(), _T("VizCommand"), MB_OK);	// MessageBox��m_tstrCommandString��\��.

	}

	// ���L�[�������ꂽ��.
	if (nChar == VK_LEFT){	// VK_LEFT�̎�.
		m_lCurrentPos = 0;	// m_lCurrentPos��0�ɃZ�b�g.
		SendMessage(m_hWnd, EM_GETSEL, (WPARAM)&m_lCurrentPos, NULL);	// EM_GETSEL�ŃL�����b�g�̈ʒu���擾.
		if (m_lCurrentPos <= m_lStartPos) {	// �J�n�ʒu����O����������̓L�����Z������.
			return -1;	// -1��Ԃ��Ɠ��̓L�����Z���ɂȂ�.
		}
	}

	// �e�N���X�̊��菈��.
	return CScalableEdit::OnKeyDown(nChar, nRepCnt, nFlags);	// CScalableEdit::OnKeyDown���Ă�.

}

// �����L�[�������ꂽ��.
int CConsoleCore::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags){

	// �o�b�N�X�y�[�X��������Ă��߂�̂𖳌��ɂ���.
	if (nChar == VK_BACK) {	// VK_BACK�̎�.
		m_lCurrentPos = 0;	// m_lCurrentPos��0�ɃZ�b�g.
		SendMessage(m_hWnd, EM_GETSEL, (WPARAM)&m_lCurrentPos, NULL);	// EM_GETSEL�ŃL�����b�g�̈ʒu���擾.
		if (m_lCurrentPos <= m_lStartPos) {	// �J�n�ʒu����O����������̓L�����Z������.
			return -1;	// -1��Ԃ��Ɠ��̓L�����Z���ɂȂ�.
		}
	}

	// �ʏ�͓��͂�L���ɂ���.
	return 0;	// 0��Ԃ��ƗL���ɂȂ�.

}

// �}�E�X���{�^���������ꂽ��.
int CConsoleCore::OnLButtonUp(UINT nFlags, POINT pt){

	// ���݈ʒu���J�n�ʒu���O�ɂȂ�悤�Ƀ}�E�X�ŃN���b�N���ꂽ�ꍇ, �L�����b�g�������I�ɊJ�n�ʒu�ɖ߂�.
	m_lCurrentPos = 0;	// m_lCurrentPos��0�ɃZ�b�g.
	SendMessage(m_hWnd, EM_GETSEL, (WPARAM)&m_lCurrentPos, NULL);	// EM_GETSEL�ŃL�����b�g�̈ʒu���擾.
	if (m_lCurrentPos < m_lStartPos) {	// �J�n�ʒu����O��������L�����b�g�̈ʒu���ăZ�b�g.
		SendMessage(m_hWnd, EM_SETSEL, (WPARAM)m_lStartPos, (LPARAM)m_lStartPos);	// EM_SETSEL�ŃL�����b�g�ʒu��m_lStartPos�ɍăZ�b�g.
	}

	// ���͂͗L���ɂ���.
	return 0;	// 0��Ԃ��ƗL���ɂȂ�.

}