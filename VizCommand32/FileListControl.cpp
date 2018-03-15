// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "FileListControl.h"	// CFileListControl

// �R���X�g���N�^CFileListControl
CFileListControl::CFileListControl() : CListControl(){

	// �����o�̏�����.
	m_pFileInfoList = NULL;	// m_pFileInfoList��NULL�ŏ�����.
	m_tstrPath = _T("");	// m_tstrPath��""�ŏ�����.

}

// �f�X�g���N�^~CFileListControl
CFileListControl::~CFileListControl(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
BOOL CFileListControl::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �e�E�B���h�E��Create�ō쐬.
	BOOL bRet = CListControl::Create(lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CListControl::Create�ō쐬.

	// �t�@�C����񃊃X�g�̍쐬.
	m_pFileInfoList = new CFileInfoList();	// CFileInfoList�I�u�W�F�N�g�𐶐���, �|�C���^��m_pFileInfoList�Ɋi�[.

	// �쐬���ʂ�Ԃ�.
	return bRet;	// bRet��Ԃ�.

}

// �t�@�C���̒T��ScanFile.
void CFileListControl::ScanFile(tstring tstrPath){

	// �����o�ɃZ�b�g.
	m_tstrPath = tstrPath;	// m_tstrPath��tstrPath���Z�b�g.

	// �t�@�C���X�L����.
	m_pFileInfoList->Scan(m_tstrPath);	// m_pFileInfoList->Scan�ŃX�L����.

}

// �t�@�C�����X�g�̕\��ShowFileList.
void CFileListControl::ShowFileList(){

	// �C���[�W���X�g�̃Z�b�g.
	SetImageList(LVSIL_NORMAL);	// SetImageList�Ńm�[�}���̃C���[�W���X�g���Z�b�g.

	// �t�@�C�����̒ǉ�.
	int i = 0;	// i��0�ɏ�����.
	for (std::vector<CFileInfo *>::iterator itor = m_pFileInfoList->m_vecpFileInfo.begin(); itor !=  m_pFileInfoList->m_vecpFileInfo.end(); itor++){	// �t�@�C����񃊃X�g�S��.
		int icon = AddIcon((*itor)->m_hIcon);	// AddIcon�ŃA�C�R���n���h����ǉ�.
		//SetImageList(LVSIL_NORMAL);	// SetImageList�Ńm�[�}���̃C���[�W���X�g���Z�b�g.(���ꂪ�Ȃ��ƃ_�����Ƃ���������, �R�����g���Ă����̂Ƃ��됳��ɕ\������Ă���.)
		LV_ITEM item = {0};	// item��{0}�ŏ�����.
		item.mask = LVIF_TEXT | LVIF_IMAGE;	// �}�X�N�̓e�L�X�g�ƃC���[�W.		T
		TCHAR tszTitleText[1024] = {0};	// tszTitleText��{0}�ŏ�����.
		_tcscpy(tszTitleText, (*itor)->m_tstrFileTitle.c_str());	// _tcscpy��(*itor)->m_tstrFileTitle��tszTitleText�ɃR�s�[.
		item.pszText = tszTitleText;	// �e�L�X�g��tszTitleText.
		item.iItem = i;	// �C���f�b�N�X��i.
		item.iSubItem = 0;	// �T�u�A�C�e���͂Ȃ�.
		item.iImage = icon;	// �A�C�R����icon.
		InsertItem(&item);	// InsertItem��item��ǉ�.
		i++;	// i���C���N�������g.
	}

}

// �E�B���h�E�̔j���ƏI�������֐�Destroy.
void CFileListControl::Destroy(){

	// �t�@�C����񃊃X�g���폜.
	if (m_pFileInfoList != NULL){	// m_pFileInfoList��NULL�łȂ���.
		m_pFileInfoList->RemoveAllInfo();	// m_pFileInfoList->RemoveAllInfo�őS�č폜.
		delete m_pFileInfoList;	// delete��m_pFileInfoList�����.
		m_pFileInfoList = NULL;	// m_pFileInfoList��NULL���Z�b�g.
	}

	// �e�N���X��Destroy���Ă�.
	CListControl::Destroy();	// CListControl::Destroy���Ă�.

}