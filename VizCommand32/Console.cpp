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
		}

	}

	// �߂�l��Ԃ�.
	return bRet;	// bRet��Ԃ�.

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