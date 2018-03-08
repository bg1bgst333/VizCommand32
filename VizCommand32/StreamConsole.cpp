// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "StreamConsole.h"	// �X�g���[���R���\�[���N���X
#include "StreamConsoleItemsPanel.h"	// �X�g���[���R���\�[���A�C�e���Y�p�l���N���X

// �R���X�g���N�^CStreamConsole
CStreamConsole::CStreamConsole() : CWindowListControl(){

	// �����o�̏�����.
	m_nId = 0;	// m_nId��0�ŏ�����.

}

// �f�X�g���N�^~CStreamConsole
CStreamConsole::~CStreamConsole(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CStreamConsole::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�N���X�̓o�^.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
BOOL CStreamConsole::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackground���w��.
	return CUserControl::RegisterClass(hInstance, _T("CStreamConsole"), hbrBackground);	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.
BOOL CStreamConsole::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̍쐬.
	return CUserControl::Create(_T("CStreamConsole"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ō쐬.

}

// �E�B���h�E�쐬���̃n���h��OnCreate.
int CStreamConsole::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �e�E�B���h�E��OnCreate���Ă�.
	int iRet = CWindowListControl::OnCreate(hwnd, lpCreateStruct);	// CWindowListControl::OnCreate��Ԃ�.
	
	// �E�B���h�E���X�g�A�C�e���Y�p�l���̐���.
	//m_pWindowListItemsPanel = new CWindowListItemsPanel();	// CWindowListItemsPanel�̍쐬.
	m_pWindowListItemsPanel = new CStreamConsoleItemsPanel();	// CStreamConsoleItemsPanel�̍쐬.

	// �E�B���h�E���X�g�A�C�e���Y�p�l���̃E�B���h�E����.
	m_pWindowListItemsPanel->Create(_T(""), 0, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight, hwnd, (HMENU)(WM_APP + 2), lpCreateStruct->hInstance);	// m_pWindowListItemsPanel->Create�ŃE�B���h�E����.
	
	// ����X�V�^�C�}�[���Z�b�g.
	SetTimer(hwnd, 1, 100, NULL);	// SetTimer�ōX�V�^�C�}�[���Z�b�g.(100�~���b==0.1�b)

	// �߂�l��Ԃ�.
	return iRet;	// iRet��Ԃ�.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CStreamConsole::OnSize(UINT nType, int cx, int cy){

	// �e�E�B���h�E��OnSize.
	CWindowListControl::OnSize(nType, cx, cy);	// CWindowListControl��OnSize.

	// ���ׂẴR���\�[���R�A�̃T�C�Y���E�ɂ҂��������킹��.
	if (m_pWindowListItemsPanel != NULL){	// m_pWindowListItemsPanel��NULL�łȂ���.
		size_t n = m_pWindowListItemsPanel->GetSize();	// m_pWindowListItemsPanel->GetSize�ŃT�C�Y���擾.
		for (int i = n - 1; i >= 0; i--){	// i��n - 1����0�܂�.
			CWindowListItem *pItem = Get(i);	// Get(i)��pItem���擾.
			if (pItem != NULL){	// pItem��NULL�łȂ���.
				if (pItem->m_mapChildMap.find(_T("Console")) != pItem->m_mapChildMap.end()){	// "Console"������������.
					CWindow *pWindow = pItem->m_mapChildMap[_T("Console")];	// pItem->m_mapChildMap[_T("Console")]�Ŏ��o��.(���̎�, CWindow�|�C���^�ł���.)
					MoveWindow(pWindow->m_hWnd, pWindow->m_x, pWindow->m_y, m_iWidth/* cx */, pWindow->m_iHeight, TRUE);	// MoveWindow�ŉ�����cx�Ƃ���.
				}
			}
		}
	}

}

// �^�C�}�[�C�x���g������������.
void CStreamConsole::OnTimer(UINT_PTR nIDEvent){

	// ����X�V�^�C�}�[�̎�.
	HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);	// GetWindowLong��hInstance���擾.
	if (nIDEvent == 1){	// 1�̎�.

		// �f�t�H���g�A�C�e���̑}��.
		Insert(0, _T("0"), 80, hInstance);	// Insert��0�Ԗڂ̃A�C�e����}��.
		CWindowListItem *pItem = Get(0);	// Get��0�Ԗڂ��擾��, pItem�Ɋi�[.
		//CConsoleCore *pConsoleCore = new CConsoleCore();	// CConsoleCore�I�u�W�F�N�g���쐬��, pConsoleCore�Ɋi�[.
		//pConsoleCore->Create(_T(""), 0, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight, pItem->m_hWnd, (HMENU)(WM_APP + 200 + m_nId), hInstance);	// pConsoleCore->Create�ŃE�B���h�E�쐬.
		//pItem->m_mapChildMap.insert(std::make_pair(_T("ConsoleCore"), pConsoleCore));	// pItem->m_mapChildMap.insert��"ConsoleCore"���L�[�Ƃ���, pConsoleCore��ǉ�.
		CConsole *pConsole = new CConsole();	// CConsole�I�u�W�F�N�g���쐬��, pConsole�Ɋi�[.
		pConsole->Create(_T(""), 0, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight, pItem->m_hWnd, (HMENU)(WM_APP + 200 + m_nId), hInstance);	// pConsole->Create�ŃE�B���h�E�쐬.
		pConsole->ShowInputForm();	// ���̓t�H�[�����o��.
		pItem->m_mapChildMap.insert(std::make_pair(_T("Console"), pConsole));	// pItem->m_mapChildMap.insert��"Console"���L�[�Ƃ���, pConsole��ǉ�.
		m_nId++;	// m_nId���C���N�������g.

		// �����̈���쐬���ĉ�ʂ̍X�V.
		InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�Ŗ����̈�쐬.

		// �^�C�}�[���I��.
		KillTimer(m_hWnd, 1);	// ����X�V�^�C�}�[���I��.

	}

}

// ���[�U��`���b�Z�[�W������������.
void CStreamConsole::OnUserMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){

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

		// ���ւ̃X�N���[�����v�����ꂽ��.
		case UM_REQUESTSCROLLBOTTOM:

			// UM_REQUESTSCROLLBOTTOM�u���b�N
			{

				// OnRequestScrollBottom�ɔC����.
				OnRequestScrollBottom(wParam, lParam);	// OnRequestScrollBottom�ɔC����.

			}

			// ����̏����֌�����.
			break;	// ������DefWindowProc�Ɍ�����.

		// ����ȊO.
		default:

			// ����̏����֌�����.
			break;	// ������DefWindowProc�Ɍ�����.

	};

}

// ���ւ̃X�N���[�����v�����ꂽ��.
void CStreamConsole::OnRequestScrollBottom(WPARAM wParam, LPARAM lParam){

	// �X�N���[�������擾����.
	ZeroMemory(&m_ScrollInfo, sizeof(m_ScrollInfo));	// ZeroMemory��0�ŏ�����.
	m_ScrollInfo.fMask = SIF_POS | SIF_RANGE | SIF_PAGE;	// m_ScrollInfo.fMask�Ń}�X�N���Z�b�g.
	GetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo);	// GetScrollInfo�ŃX�N���[��

	// �X�N���[���\�ɂȂ�����.
	if (m_ScrollInfo.nMax > m_ScrollInfo.nPage){	// nMax�̂ق���nPage���傫��.

		// �A�C�e���Y�p�l���̃g�[�^���̍������擾.
		int iTotalHeight = (int)wParam;	// wParam��int�ɃL���X�g��, iTotalHeight�ɑ��.
		m_ScrollInfo.nMax = iTotalHeight;	// m_ScrollInfo.nMax��iTotalHeight.
		m_ScrollInfo.nPos = m_ScrollInfo.nMax;	// m_ScrollInfo.nPos��m_ScrollInfo.nMax.

		// �X�N���[������ݒ肷��.
		SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);	// SetScrollInfo��m_ScrollInfo���Z�b�g.

		// �A�C�e���Y�p�l���̈ړ�.
		MoveWindow(m_pWindowListItemsPanel->m_hWnd, m_pWindowListItemsPanel->m_x, -m_ScrollInfo.nPos + m_ScrollInfo.nPage, m_pWindowListItemsPanel->m_iWidth, m_pWindowListItemsPanel->m_iHeight, TRUE);	// MoveWindow��-m_ScrollInfo.nPos�̈ʒu�Ɉړ�.

	}

}