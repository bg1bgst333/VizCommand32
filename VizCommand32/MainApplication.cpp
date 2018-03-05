// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainApplication.h"	// CMainApplication
#include "MainWindow.h"	// CMainWindow

// �C���X�^���X�������֐�InitInstance.
BOOL CMainApplication::InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd){

	// �E�B���h�E�N���X�̓o�^.
	CMainWindow::RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CMainWindow::RegisterClass�ŃE�B���h�E�N���X"CMainWindow"��o�^.
	CStreamConsole::RegisterClass(hInstance, (HBRUSH)GetStockObject(GRAY_BRUSH));	// CStreamConsole::RegisterClass�ŃE�B���h�E�N���X"CStreamConsole"��o�^.
	CWindowListItemsPanel::RegisterClass(hInstance, (HBRUSH)GetStockObject(BLACK_BRUSH));	// CWindowListItemsPanel::RegisterClass�ŃE�B���h�E�N���X"CWindowListItemsPanel"��o�^.
	CWindowListItem::RegisterClass(hInstance, (HBRUSH)GetStockObject(GRAY_BRUSH));	// CWindowListItem::RegisterClass�ŃE�B���h�E�N���X"CWindowListItem"��o�^.
	
	// CMainWindow�I�u�W�F�N�g�̍쐬.
	m_pMainWnd = new CMainWindow();	// CMainWindow�I�u�W�F�N�g���쐬��, m_pMainWnd�Ɋi�[.

	// �E�B���h�E�̍쐬.
	if (!m_pMainWnd->Create(_T("VizCommand"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance)){	// m_pMainWnd->Create�ŃE�B���h�E�쐬��, ���s�����ꍇ.

		// �G���[����
		return FALSE;	// return��FALSE��Ԃ��Ĉُ�I��.

	}

	// �E�B���h�E�̕\��.
	m_pMainWnd->ShowWindow(SW_SHOW);	// m_pMainWnd->ShowWindow�ŕ\��.

	// TRUE��Ԃ�.
	return TRUE;	// return��TRUE��Ԃ�.

}