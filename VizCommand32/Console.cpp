// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "Console.h"	// CConsole

// �R���X�g���N�^CConsole
CConsole::CConsole() : CScalableEditPanel(){

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CConsole::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�N���X�̓o�^.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(WHITE_BRUSH));	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
BOOL CConsole::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackground���w��.
	return CUserControl::RegisterClass(hInstance, _T("CConsole"), hbrBackground);	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.
BOOL CConsole::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̍쐬.
	m_nId = hMenu;	// m_nId��hMenu���i�[.
	BOOL bRet = CUserControl::Create(_T("CConsole"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, m_nId, hInstance);	// CWindow::Create�ō쐬.

	// ����.
	if (bRet){	// bRet��TRUE.

		// �q�R���\�[���R�A�̐���.
		m_pScalableEdit = new CConsoleCore();	// CConsoleCore�I�u�W�F�N�g�𐶐���, �|�C���^��m_pScalableEdit�Ɋi�[.
		BOOL bRet2 = m_pScalableEdit->Create(_T(""), 0, m_x, m_y, m_iClientAreaWidth, m_iClientAreaHeight, m_hWnd, m_nId + 100, hInstance);	// m_pScalableEdit->Create�Ŏq�X�J���u���G�f�B�b�g�R���g���[������.
		if (bRet2){	// bRet2��TRUE.
			// ���T�C�Y.
			MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_pScalableEdit->m_iHeight, TRUE);	// MoveWindow��m_pScalableEdit->m_iHeight�̍����Ƀ��T�C�Y.
			// �R���\�[���R�A�̃��b�Z�[�W�̓������������ɂ���.
			if (m_pScalableEdit != NULL){	// m_pScalableEdit��NULL�łȂ����.
				((CConsoleCore *)m_pScalableEdit)->SetProcWindow(m_hWnd);	// ((CConsoleCore *)m_pScalableEdit)->SetProcWindow�ŏ�������E�B���h�E�͂����ɂ���.
			}
		}

	}

	// �߂�l��Ԃ�.
	return bRet;	// bRet��Ԃ�.

}

// ���̓t�H�[���̏o��.
void CConsole::ShowInputForm(){
	
	// �R���\�[���R�A�̓��̓t�H�[���o�͂��Ă�.
	if (m_pScalableEdit != NULL){	// m_pScalableEdit��NULL�łȂ����.
		((CConsoleCore *)m_pScalableEdit)->ShowInputForm();	// ((CConsoleCore *)m_pScalableEdit)->ShowInputForm�œ��̓t�H�[���̏o��.
	}

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CConsole::OnSize(UINT nType, int cx, int cy){

	// �e��OnSize���Ă�.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSize���Ă�.

	// �q�R���\�[���R�A�̃��T�C�Y.
	if (m_pScalableEdit != NULL){	// NULL�łȂ����.
		MoveWindow(m_pScalableEdit->m_hWnd, m_pScalableEdit->m_x, m_pScalableEdit->m_y, cx, cy, TRUE);	// MoveWindow�Ŏq�R���\�[���R�A�����T�C�Y.
	}

	// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
	WPARAM wParam;	// WPARAM�^wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAM��wParam���Z�b�g.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessage��UM_SIZECHILD�𑗐M.

}

// ���[�U��`���b�Z�[�W������������.
void CConsole::OnUserMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){

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

		// �R���\�[���R�A���烁�b�Z�[�W������ꂽ��.
		case UM_CONSOLECORECOMMAND:

			// UM_CONSOLECORECOMMAND�u���b�N
			{

				// OnConsoleCoreCommand�ɔC����.
				OnConsoleCoreCommand(wParam, lParam);	// OnConsoleCoreCommand�ɔC����.

			}

			// ����̏����֌�����.
			break;	// ������DefWindowProc�Ɍ�����.

		// ����ȊO.
		default:

			// ����̏����֌�����.
			break;	// ������DefWindowProc�Ɍ�����.

	}

}

// �R���\�[���R�A���烁�b�Z�[�W������ꂽ��.
int CConsole::OnConsoleCoreCommand(WPARAM wParam, LPARAM lParam){

	// �ϐ��̐錾
	tstring tstrCommand;	// �R�}���h������tstring�^tstrCommand.
	HWND hSrc;	// ���M���E�B���h�E�n���h��HWND�^hSrc.

	// �R�}���h�ƃ\�[�X���擾.
	tstrCommand = (TCHAR *)wParam;	// wParam��TCHAR *�^�ɃL���X�g����tstrCommand�Ɋi�[.
	hSrc = (HWND)lParam;	// lParam��HWND�^�ɃL���X�g����hSrc�Ɋi�[.

	// �R�}���h�̔���.
	if (tstrCommand == _T("hello")) {	// �R�}���h"hello".

		// OnHello�ɔC����.
		OnHello(hSrc);	// hSrc�������Ƃ��ēn����, OnHello���Ă�.

	}

	// �����Ȃ�0��Ԃ�.
	return 0;	// 0��Ԃ�.

}

// "Hello, world!"�̏o�͂�v�����ꂽ��.
void CConsole::OnHello(HWND hSrc){

	// "Hello, world!"���o��.
	SendMessage(hSrc, UM_RESPONSEMESSAGE, (WPARAM)_T("Hello, world!\r\n"), 0);	// UM_RESPONSEMESSAGE��"Hello, world!"�𑗂�.

	// ���X�|���X�I��.
	SendMessage(hSrc, UM_FINISHRESPONSE, 0, 0);	// UM_FINISHRESPONSE�𑗂�.

}