// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "FileListControlPanel.h"	// CFileListControlPanel
#include <commctrl.h>	// �R�����R���g���[��

// �R���X�g���N�^CFileListControlPanel
CFileListControlPanel::CFileListControlPanel() : CListControlPanel(){

	// �����o�̏�����.
	m_tstrPath = _T("");	// m_tstrPath��""���Z�b�g.

}

// �f�X�g���N�^~CFileListControlPanel
CFileListControlPanel::~CFileListControlPanel(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CFileListControlPanel::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�N���X�̓o�^.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(WHITE_BRUSH));	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
BOOL CFileListControlPanel::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackground���w��.
	return CUserControl::RegisterClass(hInstance, _T("CFileListControlPanel"), hbrBackground);	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.
BOOL CFileListControlPanel::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̍쐬.
	m_nId = hMenu;	// m_nId��hMenu���i�[.
	return CUserControl::Create(_T("CFileListControlPanel"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, m_nId, hInstance);	// CWindow::Create�ō쐬.

}

// �t�@�C���̒T��ScanFile.
void CFileListControlPanel::ScanFile(tstring tstrPath){

	// �����o�ɃZ�b�g.
	m_tstrPath = tstrPath;	// m_tstrPath��tstrPath���Z�b�g.

	// �t�@�C���̃X�L����.
	((CFileListControl *)m_pListControl)->ScanFile(tstrPath);	// ((CFileListControl *)m_pListControl)->ScanFile��tstrPath�̃t�@�C�����X�L����.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CFileListControlPanel::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �e��OnCreate���Ă�.
	int iRet = CUserControl::OnCreate(hwnd, lpCreateStruct);	// CUserControl::OnCreate���Ă�.

	// �q���X�g�R���g���[���̐���.
	m_pListControl = new CFileListControl();	// CFileListControl�I�u�W�F�N�g�𐶐���, �|�C���^��m_pListControl�Ɋi�[.
	m_pListControl->Create(_T(""), LVS_ICON, m_x, m_y, m_iClientAreaWidth, m_iClientAreaHeight, hwnd, m_nId + 100, lpCreateStruct->hInstance);	// m_pListControl->Create�Ŏq���X�g�R���g���[������.

	// ����X�V�^�C�}�[���Z�b�g.
	SetTimer(hwnd, 2, 100, NULL);	// SetTimer�ōX�V�^�C�}�[���Z�b�g.(100�~���b==0.1�b)

	// iRet��Ԃ�.
	return iRet;	// iRet��Ԃ�.

}

// �^�C�}�[�C�x���g������������.
void CFileListControlPanel::OnTimer(UINT_PTR nIDEvent){

	// �^�C�}�[���I��.
	KillTimer(m_hWnd, 2);	// ����X�V�^�C�}�[���I��.

}

// �E�B���h�E�̔j���ƏI�������֐�Destroy.
void CFileListControlPanel::Destroy(){

	// ���X�g�R���g���[�����폜.
	if (m_pListControl != NULL){	// m_pListControl��NULL�łȂ���.
		m_pListControl->Destroy();	// m_pListControl->Destroy�ŏI������.
		delete m_pListControl;	// delete��m_pListControl�����.
		m_pListControl = NULL;	// m_pListControl��NULL���Z�b�g.
	}

	// �e�N���X��Destroy���Ă�.
	CListControlPanel::Destroy();	// CListControlPanel::Destroy���Ă�.

}