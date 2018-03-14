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

// �t�@�C���̒T��ScanFile.
void CFileListControl::ScanFile(tstring tstrPath){

	// �����o�ɃZ�b�g.
	m_tstrPath = tstrPath;	// m_tstrPath��tstrPath���Z�b�g.

	// �t�@�C����񃊃X�g���쐬.
	if (m_pFileInfoList == NULL){	// m_pFileInfoList��NULL�Ȃ�.
		m_pFileInfoList = new CFileInfoList();	// CFileInfoList�I�u�W�F�N�g�𐶐���, �|�C���^��m_pFileInfoList�Ɋi�[.
	}

	// �t�@�C���X�L����.
	m_pFileInfoList->Scan(m_tstrPath);	// m_pFileInfoList->Scan�ŃX�L����.

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