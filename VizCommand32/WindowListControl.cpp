// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "WindowListControl.h"	// CWindowListControl

// �R���X�g���N�^CWindowListControl
CWindowListControl::CWindowListControl() : CUserControl(){

	// �����o�ϐ��̏�����.
	m_pWindowListItemsPanel = NULL;	// m_pWindowListItemsPanel��NULL�ŏ�����.
	m_iHScrollPos = 0;	// m_iHScrollPos��0�ŏ�����.
	m_iVScrollPos = 0;	// m_iVScrollPos��0�ŏ�����.

}

// �f�X�g���N�^~CWindowListControl
CWindowListControl::~CWindowListControl(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CWindowListControl::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�N���X�̓o�^.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
BOOL CWindowListControl::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackground���w��.
	return CUserControl::RegisterClass(hInstance, _T("CWindowListControl"), hbrBackground);	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.
BOOL CWindowListControl::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̍쐬.
	return CUserControl::Create(_T("CWindowListControl"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ō쐬.

}

// �E�B���h�E�̔j���ƏI�������֐�Destroy.
void CWindowListControl::Destroy(){

	// �E�B���h�E���X�g�A�C�e���Y�p�l���̔j��.
	if (m_pWindowListItemsPanel != NULL){	// m_pWindowListItemsPanel��NULL�łȂ���.
		m_pWindowListItemsPanel->Destroy();	// m_pWindowListItemsPanel->Destroy�Ŕj��.
		delete m_pWindowListItemsPanel;	// delete��m_pWindowListItemsPanel�����.
		m_pWindowListItemsPanel = NULL;	// m_pWindowListItemsPanel��NULL���Z�b�g.
	}

	// �e�E�B���h�E��Destroy���Ă�.
	CUserControl::Destroy();	// CUserControl::Destroy���Ă�.

}

// �A�C�e���𖖔�����ǉ�����֐�Add.
void CWindowListControl::Add(LPCTSTR lpctszWindowName, int x, int y, int iWidth, int iHeight, HINSTANCE hInstance){

	// �A�C�e���Y�p�l���ɒǉ�.
	if (m_pWindowListItemsPanel != NULL){	// m_pWindowListItemsPanel��NULL�łȂ����.
		m_pWindowListItemsPanel->Add(lpctszWindowName, x, y, iWidth, iHeight, hInstance);	// Add�Ŗ����ɒǉ�.
	}

}

// �A�C�e���𖖔�����ǉ�����֐�Add.
void CWindowListControl::Add(LPCTSTR lpctszWindowName, int iHeight, HINSTANCE hInstance){

	// �A�C�e���Y�p�l���ɒǉ�.
	if (m_pWindowListItemsPanel != NULL){	// m_pWindowListItemsPanel��NULL�łȂ����.
		m_pWindowListItemsPanel->Add(lpctszWindowName, iHeight, hInstance);	// Add�Ŗ����ɒǉ�.
	}

}

// �A�C�e�����w��̏ꏊ�ɑ}������֐�Insert.
void CWindowListControl::Insert(int iIndex, LPCTSTR lpctszWindowName, int iHeight, HINSTANCE hInstance){

	// �A�C�e���Y�p�l���ɒǉ�.
	if (m_pWindowListItemsPanel != NULL){	// m_pWindowListItemsPanel��NULL�łȂ����.
		m_pWindowListItemsPanel->Insert(iIndex, lpctszWindowName, iHeight, hInstance);	// m_pWindowListItemsPanel->Insert��iIndex�Ԗڂɑ}��.
	}

}

// �A�C�e���𖖔�����폜����֐�Remove.
void CWindowListControl::Remove(){

	// �A�C�e���Y�p�l������폜.
	if (m_pWindowListItemsPanel != NULL){	// m_pWindowListItemsPanel��NULL�łȂ����.
		m_pWindowListItemsPanel->Remove();	// Remove�Ŗ�������폜.
	}

}

// �w��̏ꏊ�̃A�C�e�����폜����֐�Delete.
void CWindowListControl::Delete(int iIndex){

	// �A�C�e���Y�p�l������폜.
	if (m_pWindowListItemsPanel != NULL){	// m_pWindowListItemsPanel��NULL�łȂ����.
		m_pWindowListItemsPanel->Delete(iIndex);	// Delete��iIndex�Ԗڂ��폜.
	}

}

// �A�C�e�����擾����֐�Get.
CWindowListItem * CWindowListControl::Get(int iIndex){

	// �A�C�e���Y�p�l������擾.
	if (m_pWindowListItemsPanel != NULL){	// m_pWindowListItemsPanel��NULL�łȂ����.
		return m_pWindowListItemsPanel->Get(iIndex);	// 
	}

	// �Ȃ����NULL.
	return NULL;	// NULL��Ԃ�.

}

// �S�ẴA�C�e�����폜����֐�RemoveAll.
void CWindowListControl::RemoveAll(){

	// �A�C�e���Y�p�l������S�č폜.
	if (m_pWindowListItemsPanel != NULL){	// m_pWindowListItemsPanel��NULL�łȂ����.
		m_pWindowListItemsPanel->RemoveAll();
	}

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CWindowListControl::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �N���C�A���g�̈�̃T�C�Y���擾.
	RECT rc = {0};	// rc��{0}�ŏ�����.
	GetClientRect(hwnd, &rc);	// GetClientRect�ŃN���C�A���g�̈��RECT���擾.
	m_iClientAreaWidth = rc.right - rc.left;	// ��.
	m_iClientAreaHeight = rc.bottom - rc.top;	// ����.

	// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
	return 0;	// 0��Ԃ���, �E�B���h�E�쐬�ɐ��������Ƃ������ƂɂȂ�.

}

// �E�B���h�E���j�����ꂽ��.
void CWindowListControl::OnDestroy(){

	// �����o�̏I������
	//Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

	// �e�N���X��OnDestroy���Ă�.
	CUserControl::OnDestroy();	// CUserControl::OnDestroy���Ă�.

}

// �E�B���h�E�̕`���v�����ꂽ���̃n���h��OnPaint.
void CWindowListControl::OnPaint(){

	// �ϐ��̏�����.
	HDC hDC = NULL;	// hDC��NULL�ŏ�����.
	PAINTSTRUCT ps = {0};	// ps��{0}�ŏ�����.
	HPEN hPen = NULL;	// hPen��NULL�ŏ�����.
	HBRUSH hBrush = NULL;	// hBrush��NULL�ŏ�����.

	// �`��J�n.
	hDC = BeginPaint(m_hWnd, &ps);	// BeginPaint�ŕ`��J�n.

#if 0
	// �y���ƃu���V�̐���.
	hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 0xff));	// CreatePen�Ő�(�W)�̃y�����쐬.
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0x7f));		// CreateSolidBrush�Ő�(�Z)�̃u���V���쐬.

	// �y���ƃu���V�̑I��.
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);		// �̃y����I��.
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);	// �̃u���V��I��.

	// ��`�`��.
	Rectangle(hDC, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight);	// Rectangle�ŋ�`��`��.
	
	// �y���ƃu���V�̕���
	SelectObject(hDC, hOldBrush);		// �Â��u���V��I��.
	SelectObject(hDC, hOldPen);		// �Â��y����I��.

	// �y���ƃu���V�̔j��.
	DeleteObject(hBrush);	// �u���V�̔j��.
	DeleteObject(hPen);	// �y���̔j��.

#if 0
	// �X�N���[���o�[�ݒ�.
	// ��������.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemory��m_ScrollInfo���N���A.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �t���O
	m_ScrollInfo.nPage = m_iClientAreaWidth;	// �y�[�W��
	m_ScrollInfo.nMin = 0;	// �ŏ��l
	m_ScrollInfo.nMax = m_pWindowListItemsPanel->m_iWidth;	//�ő�l
	SetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo, TRUE);	// SetScrollInfo�ŃZ�b�g.(SetImage��InvalidateRect�Ƒ�4������TRUE���Ȃ��ƃX�N���[���o�[�܂݂������ɍX�V����Ȃ�.)
	// ��������.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemory��m_ScrollInfo���N���A.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �t���O
	m_ScrollInfo.nPage = m_iClientAreaHeight;	// �y�[�W����
	m_ScrollInfo.nMin = 0;	// �ŏ��l
	m_ScrollInfo.nMax = m_pWindowListItemsPanel->m_iHeight;	//�ő�l
	SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);	// SetScrollInfo�ŃZ�b�g.(SetImage��InvalidateRect�Ƒ�4������TRUE���Ȃ��ƃX�N���[���o�[�܂݂������ɍX�V����Ȃ�.)
#endif
#endif

  	// �`��I��.
	EndPaint(m_hWnd, &ps);	// EndPaint�ŕ`��I��.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CWindowListControl::OnSize(UINT nType, int cx, int cy){

	// �e�E�B���h�E�̊��菈��.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSize���Ă�.

	// �E�B���h�E���X�g�A�C�e���Y�p�l���̕��̓E�B���h�E���X�g�R���g���[���̕��ɂ҂����荇�킹��.
	if (m_pWindowListItemsPanel != NULL){	// NULL�łȂ����.
		MoveWindow(m_pWindowListItemsPanel->m_hWnd, m_pWindowListItemsPanel->m_x, m_pWindowListItemsPanel->m_y, cx, m_pWindowListItemsPanel->m_iHeight, TRUE);	// MoveWindow��m_pWindowListControl->m_hWnd�̃T�C�Y�𕝂����ύX.
	}

	// ��ʍX�V.
	//InvalidateRect(m_hWnd, NULL, FALSE);	// InvalidateRect�ōX�V.

#if 1
	// �X�N���[���o�[�ݒ�.
#if 0
	// ��������.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemory��m_ScrollInfo���N���A.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �t���O
	m_ScrollInfo.nPage = m_iClientAreaWidth;	// �y�[�W��
	m_ScrollInfo.nMin = 0;	// �ŏ��l
	m_ScrollInfo.nMax = m_pWindowListItemsPanel->m_iWidth;	//�ő�l
	SetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo, TRUE);	// SetScrollInfo�ŃZ�b�g.(SetImage��InvalidateRect�Ƒ�4������TRUE���Ȃ��ƃX�N���[���o�[�܂݂������ɍX�V����Ȃ�.)
#endif
	// ��������.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemory��m_ScrollInfo���N���A.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �t���O
	m_ScrollInfo.nPage = m_iClientAreaHeight;	// �y�[�W����
	m_ScrollInfo.nMin = 0;	// �ŏ��l
	m_ScrollInfo.nMax = m_pWindowListItemsPanel->m_iHeight;	//�ő�l
	SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);	// SetScrollInfo�ŃZ�b�g.(SetImage��InvalidateRect�Ƒ�4������TRUE���Ȃ��ƃX�N���[���o�[�܂݂������ɍX�V����Ȃ�.)
#endif

}

// ���������X�N���[���o�[�C�x���g��.
void CWindowListControl::OnHScroll(UINT nSBCode, UINT nPos){

	// �X�N���[�����擾.
	m_ScrollInfo.fMask = SIF_POS;	// �ʒu�����ύX���[�h(���ꂪ�Ȃ���, �X�N���[���o�[�����̈ʒu�ɖ߂��Ă��܂��̂Œ���!���������O!)
	GetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo);	// �}�X�N��ݒ肵�Ă���GetScrollInfo.(����������!)

	// �X�N���[���o�[����.
	switch (nSBCode) {	// nSBCode���ƂɐU�蕪��.

		// ��ԍ�
		case SB_LEFT:

			// �ʒu���ŏ��l��.
			m_ScrollInfo.nPos = m_ScrollInfo.nMin;
			break;

		// ��ԉE
		case SB_RIGHT:

			// �ʒu���ő�l��.
			m_ScrollInfo.nPos = m_ScrollInfo.nMax;
			break;

		// 1��
		case SB_LINELEFT:

			// nPos��0�łȂ���΃f�N�������g.
			if (m_ScrollInfo.nPos > 0) {
				m_ScrollInfo.nPos--;
			}
			break;

		// 1��E
		case SB_LINERIGHT:

			// nPos���ő�l-1�łȂ���΃C���N�������g.
			if (m_ScrollInfo.nPos < m_ScrollInfo.nMax - 1) {
				m_ScrollInfo.nPos++;
			}
			break;

		// 1�y�[�W��
		case SB_PAGELEFT:

			// nPage�����炷.
			m_ScrollInfo.nPos -= m_ScrollInfo.nPage;
			break;

		// 1�y�[�W�E
		case SB_PAGERIGHT:

			// nPage�����₷.
			m_ScrollInfo.nPos += m_ScrollInfo.nPage;
			break;

		// �܂݂��h���b�O��.
		case SB_THUMBTRACK:

			// ������nPos���Z�b�g
			m_ScrollInfo.nPos = nPos;
			break;

		// �܂݂��h���b�O��.
		case SB_THUMBPOSITION:

			// ������nPos���Z�b�g
			m_ScrollInfo.nPos = nPos;
			break;

		// ����ȊO.
		default:

			break;

	}

	// �X�N���[�����ݒ�.
	SetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo, TRUE);
	// �����o�ɂ��Z�b�g.
	m_iHScrollPos = m_ScrollInfo.nPos;
	// �A�C�e���Y�p�l���̈ړ�.
	MoveWindow(m_pWindowListItemsPanel->m_hWnd, 0 - m_iHScrollPos, 0 - m_iVScrollPos, m_pWindowListItemsPanel->m_iWidth, m_pWindowListItemsPanel->m_iHeight, TRUE);	// MoveWindow�ňړ�.
	// �����̈���쐬���ĉ�ʂ̍X�V.
	//InvalidateRect(m_hWnd, NULL, FALSE);	// InvalidateRect�Ŗ����̈�쐬.

}

// ���������X�N���[���o�[�C�x���g��.
void CWindowListControl::OnVScroll(UINT nSBCode, UINT nPos){

	// �X�N���[�����擾.
	m_ScrollInfo.fMask = SIF_POS;	// �ʒu�����ύX���[�h(���ꂪ�Ȃ���, �X�N���[���o�[�����̈ʒu�ɖ߂��Ă��܂��̂Œ���!���������O!)
	GetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo);	// �}�X�N��ݒ肵�Ă���GetScrollInfo.(����������!)

	// �X�N���[���o�[����.
	switch (nSBCode) {	// nSBCode���ƂɐU�蕪��.

		// ��ԏ�
		case SB_TOP:

			// �ʒu���ŏ��l��.
			m_ScrollInfo.nPos = m_ScrollInfo.nMin;
			break;

		// ��ԉ�
		case SB_BOTTOM:

			// �ʒu���ő�l��.
			m_ScrollInfo.nPos = m_ScrollInfo.nMax;
			break;

		// 1�s��
		case SB_LINEUP:

			// nPos��0�łȂ���΃f�N�������g.
			if (m_ScrollInfo.nPos > 0) {
				m_ScrollInfo.nPos--;
			}
			break;

		// 1�s��
		case SB_LINEDOWN:

			// nPos���ő�l-1�łȂ���΃C���N�������g.
			if (m_ScrollInfo.nPos < m_ScrollInfo.nMax - 1) {
				m_ScrollInfo.nPos++;
			}
			break;

		// 1�y�[�W��
		case SB_PAGEUP:

			// nPage�����炷.
			m_ScrollInfo.nPos -= m_ScrollInfo.nPage;
			break;

		// 1�y�[�W��
		case SB_PAGEDOWN:

			// nPage�����₷.
			m_ScrollInfo.nPos += m_ScrollInfo.nPage;
			break;

		// �܂݂��h���b�O��.
		case SB_THUMBTRACK:
	
			// ������nPos���Z�b�g
			m_ScrollInfo.nPos = nPos;
			break;

		// �܂݂��h���b�O��.
		case SB_THUMBPOSITION:

			// ������nPos���Z�b�g
			m_ScrollInfo.nPos = nPos;
			break;

		// ����ȊO.
		default:

			break;

	}

	// �X�N���[�����ݒ�.
	SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);
	// �����o�ɂ��Z�b�g.
	m_iVScrollPos = m_ScrollInfo.nPos;
	// �A�C�e���Y�p�l���̈ړ�.
	MoveWindow(m_pWindowListItemsPanel->m_hWnd, 0 - m_iHScrollPos, 0 - m_iVScrollPos, m_pWindowListItemsPanel->m_iWidth, m_pWindowListItemsPanel->m_iHeight, TRUE);	// MoveWindow�ňړ�.
	// �����̈���쐬���ĉ�ʂ̍X�V.
	//InvalidateRect(m_hWnd, NULL, FALSE);	// InvalidateRect�Ŗ����̈�쐬.

}

// �q����e�փE�B���h�E�T�C�Y�ύX�̗v��������������.
void CWindowListControl::OnSizeChild(WPARAM wParam, LPARAM lParam){

	// ��������.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemory��m_ScrollInfo���N���A.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �t���O
	m_ScrollInfo.nPage = m_iClientAreaHeight;	// �y�[�W����
	m_ScrollInfo.nMin = 0;	// �ŏ��l
	m_ScrollInfo.nMax = m_pWindowListItemsPanel->m_iHeight;	//�ő�l
	SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);	// SetScrollInfo�ŃZ�b�g.(SetImage��InvalidateRect�Ƒ�4������TRUE���Ȃ��ƃX�N���[���o�[�܂݂������ɍX�V����Ȃ�.)

}