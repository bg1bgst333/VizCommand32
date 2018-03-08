// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "ConsoleCore.h"	// CConsoleCore
#include <shlobj.h>	// �V�F���I�u�W�F�N�g

// �R���X�g���N�^CConsoleCore
CConsoleCore::CConsoleCore() : CScalableEdit(){

	// �����o�̏�����.
	m_tstrFormString = GREATER_THAN;	// m_tstrFormString��">"�ɏ�����.
	m_tstrCommandString = _T("");	// m_tstrCommandString��""�ŏ�����.
	m_lStartPos = 0;	// m_lStartPos��0�ɏ�����.
	m_lCurrentPos = 0;	// m_lCurrentPos��0�ɏ�����.

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

	// �ϐ��̏�����
	int iCount = 0;	// ���s�̌�iCount��0�ɏ�����.

	// ���s�̐��𐔂���.
	for (int i = 1; i < (int)tstrString.length(); i++){	// i��1����tstrString.length() - 1�܂�.
		if (tstrString.at(i - 1) == _T('\r') && tstrString.at(i) == _T('\n')){	// ���s���݂�������.

			// �ϐ��̐錾
			int iHeight;	// �V��������iHeight.
			WPARAM wParam;	// WPARAM�^wParam.

			// ���s������1�s���傫������.
			iHeight = m_iHeight + m_iLineHeight;	// ���݂̃E�B���h�E�̍�����1�s���̍����𑫂�.
			MoveWindow(m_hWnd, m_x, m_y, m_iWidth, iHeight, TRUE);	// MoveWindow�ō�����iHeight�ɂ���.
			m_iLineCount++;	// �s��m_LineCount�𑝂₷.

			// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
			wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAM��m_iWidth��m_iHeight����wParam���쐬.
			SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// UM_SIZECHILD�Őe�E�B���h�E�����̃E�B���h�E�̃T�C�Y�ɍ��킹��.

			// iCount�𑝂₷.
			iCount++;	// iCount���C���N�������g.

		}
	}

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

// �R�}���h������̎擾�֐�GetCommandString.
tstring CConsoleCore::GetCommandString(){

	// �ϐ��̐錾
	unsigned int uiCommandStringLen;	// �R�}���h������̒���uiCommandStringLen.
	tstring tstrText;	// �e�L�X�gtstrText.

	// �e�L�X�g�̎擾.
	tstrText = GetText();	// GetText�Ńe�L�X�g���擾��, tstrText�Ɋi�[.

	// �R�}���h������̐؂�o��.
	uiCommandStringLen = (unsigned int)tstrText.length() - m_lStartPos;	// uiCommandStringLen��tstrText�̒�������m_iStartPos�����������̂��i�[.
	m_tstrCommandString = tstrText.substr(m_lStartPos, uiCommandStringLen);	// tstrText.substr��m_lStartPos����uiCommandStringLen���̕���������𔲂��o����, m_tstrCommandString�Ɋi�[.

	// �R�}���h�������Ԃ�.
	return m_tstrCommandString;	// m_tstrCommandString��Ԃ�.

}

// �R�}���h�ɑ΂��鏈�������s����E�B���h�E���Z�b�g.
void CConsoleCore::SetProcWindow(HWND hWnd){

	// �����o�ɃZ�b�g.
	m_hProcWnd = hWnd;	// m_hProcWnd��hWnd���Z�b�g.

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

		// ���X�|���X��Ԃ��E�B���h�E�ɃR�}���h������𓊂���.
		PostMessage(m_hProcWnd, UM_CONSOLECORECOMMAND, (WPARAM)m_tstrCommandString.c_str(), (LPARAM)m_hWnd);	// UM_CONSOLECORECOMMAND�ŃR�}���h������𑗐M.

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
int CConsoleCore::OnLButtonDown(UINT nFlags, POINT pt){

	// �L�����b�g���\���ɂ���.
	HideCaret(m_hWnd);	// HideCaret�ŃL�����b�g���\���ɂ���.

	// ���͂͗L���ɂ���.
	return 0;	// 0��Ԃ��ƗL���ɂȂ�.

}

// �}�E�X���{�^���������ꂽ��.
int CConsoleCore::OnLButtonUp(UINT nFlags, POINT pt){

	// �L�����b�g��\������.
	ShowCaret(m_hWnd);	// ShowCaret�ŃL�����b�g��\������.

	// ���݈ʒu���J�n�ʒu���O�ɂȂ�悤�Ƀ}�E�X�ŃN���b�N���ꂽ�ꍇ, �L�����b�g�������I�ɊJ�n�ʒu�ɖ߂�.
	m_lCurrentPos = 0;	// m_lCurrentPos��0�ɃZ�b�g.
	SendMessage(m_hWnd, EM_GETSEL, (WPARAM)&m_lCurrentPos, NULL);	// EM_GETSEL�ŃL�����b�g�̈ʒu���擾.
	if (m_lCurrentPos < m_lStartPos) {	// �J�n�ʒu����O��������L�����b�g�̈ʒu���ăZ�b�g.
		SendMessage(m_hWnd, EM_SETSEL, (WPARAM)m_lStartPos, (LPARAM)m_lStartPos);	// EM_SETSEL�ŃL�����b�g�ʒu��m_lStartPos�ɍăZ�b�g.
	}

	// ���͂͗L���ɂ���.
	return 0;	// 0��Ԃ��ƗL���ɂȂ�.

}

// ���[�U��`���b�Z�[�W������������.
void CConsoleCore::OnUserMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){

	// switch-case���ŐU�蕪����.
	switch (uMsg) {

		// �q����e�փE�B���h�E�T�C�Y�ύX�̗v��������������.
		case UM_SIZECHILD:

			// UM_SIZECHILD�u���b�N
			{

				// OnSizeChild�ɔC����.
				OnSizeChild(wParam, lParam);	// OnSizeChild�ɔC����.

			}

			// ����̏����֌�����.
			break;	// ������DefWindowProc�Ɍ�����.

		// ���X�|���X���b�Z�[�W��������.
		case UM_RESPONSEMESSAGE:

			// UM_RESPONSEMESSAGE�u���b�N
			{
		
				// OnResponseMessage�ɔC����.
				OnResponseMessage(wParam, lParam);	// OnResponseMessage�ɔC����.

			}

			// ����̏����֌�����.
			break;	// ������DefWindowProc�Ɍ�����.

		// ���X�|���X���I��������.
		case UM_FINISHRESPONSE:

			// UM_FINISHRESPONSE�u���b�N
			{

				// OnFinishResponse�ɔC����.
				OnFinishResponse(wParam, lParam);	// OnFinishResponse�ɔC����.

			}

			// ����̏����֌�����.
			break;	// ������DefWindowProc�Ɍ�����.

		// ����ȊO.
		default:

			// ����̏����֌�����.
			break;	// ������DefWindowProc�Ɍ�����.

	}

}

// ���X�|���X���b�Z�[�W��������.
void CConsoleCore::OnResponseMessage(WPARAM wParam, LPARAM lParam){

	// �ϐ��̐錾
	tstring tstrMessage;	// ���b�Z�[�W��������i�[����tstrMessage.

	// ���b�Z�[�W��������擾.
	tstrMessage = (TCHAR *)wParam;	// wParam��(TCHAR *)�ɃL���X�g����tstrMessage�ɃZ�b�g.

	// ���b�Z�[�W���o��.
	PutConsole(tstrMessage);	// PutConsole��tstrMessage���o��.

}

// ���X�|���X���I��������.
void CConsoleCore::OnFinishResponse(WPARAM wParam, LPARAM lParam){

	// ���̓t�H�[�����o��.
	ShowInputForm();	// ShowInputForm�œ��̓t�H�[�����o��.

}