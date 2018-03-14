// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <shlwapi.h>	// �V�F��API
// �Ǝ��̃w�b�_
#include "FileInfoList.h"	// CFileListControlPanel

// �R���X�g���N�^CFileInfoList
CFileInfoList::CFileInfoList(){

	// �����o�̏�����.
	m_tstrScanPath = _T("");	// m_tstrScanPath��""�ŏ�����.
	m_vecpFileInfo.clear();	// m_vecpFileInfo.clear�ŃN���A.

}

// �f�X�g���N�^~CFileInfoList
CFileInfoList::~CFileInfoList(){

	// �I������.
	RemoveAllInfo();	// ���ׂẴA�C�e�����폜.

}

// �t�@�C�����̒ǉ�.
void CFileInfoList::AddInfo(tstring tstrFileName, HICON hIcon){

	// �t�@�C�����ƃA�C�R������t�@�C�����̐���.
	CFileInfo *pFileInfo = new CFileInfo();	// CFileInfo�I�u�W�F�N�g�𐶐���, �|�C���^��pFileInfo�Ɋi�[.
	
	// �t�@�C���t���p�X.
	pFileInfo->m_tstrFileName = tstrFileName;	// pFileInfo->m_tstrFileName��tstrFileName���Z�b�g.

	// �t�@�C���^�C�g��.
	TCHAR tszFileNameTitle[_MAX_PATH] = {0};	// �t�@�C�����̕����������i�[����tszFileNameTitle��{0}�ŏ�����.
	GetFileTitle(tstrFileName.c_str(), tszFileNameTitle, _MAX_PATH);	// GetFileTitle�Ńt�@�C���^�C�g���擾.
	pFileInfo->m_tstrFileTitle = tszFileNameTitle;	// m_tstrCurrentFileNameTitle��tszFileNameTitle���Z�b�g.

	// �t�@�C���g���q.
	pFileInfo->m_tstrFileExt = PathFindExtension(pFileInfo->m_tstrFileName.c_str());	// PathFindExtension�Ŏ擾�����g���q��pFileInfo->m_tstrFileExt�Ɋi�[.

	// �t�@�C���A�C�R��.
	pFileInfo->m_hIcon = hIcon;	// pFileInfo->m_hIcon��hIcon���Z�b�g.

	// �t�@�C����񃊃X�g�ɒǉ�.
	m_vecpFileInfo.push_back(pFileInfo);	// m_vecpFileInfo.push_back��pFileInfo��ǉ�.

}

// �t�@�C�����̍폜.
void CFileInfoList::RemoveInfo(){

}

// �t�@�C���̒T��.
void CFileInfoList::Scan(tstring tstrScanPath){

	// �ϐ��̏�����.
	tstring tstrPattern = _T("");	// �����p�^�[��tstrPattern��""�ŏ�����.
	WIN32_FIND_DATA wfdFindData = {0};	// �����f�[�^wfdFindData��{0}�ŏ�����.
	HANDLE hFind = NULL;	// �����n���h��hFind��NULL�ŏ�����.
	tstring tstrFileName = _T("");	// tstrFileName��""�ŏ�����.
	SHFILEINFO sfi = {0};	// �V�F���t�@�C�����sfi��{0}�ŏ�����.

	// �����o�ɃZ�b�g.
	m_tstrScanPath = tstrScanPath;	// m_tstrScanPath��tstrScanPath���Z�b�g.

	// ��������p�X��'*'��A��.
	tstrPattern = m_tstrScanPath;	// tstrPattern��m_tstrScanPath���Z�b�g.
	tstrPattern = tstrPattern + _T("\\*");	// tstrPattern��"\\*"��A��.

	// �ŏ��̌���.
	hFind = FindFirstFile(tstrPattern.c_str(), &wfdFindData);	// FindFirstFile��hFind���擾.
	if (hFind != INVALID_HANDLE_VALUE){	// �s���Ȓl�łȂ����.
		if (!((_tcscmp(wfdFindData.cFileName, _T(".")) == 0) || (_tcscmp(wfdFindData.cFileName, _T("..")) == 0))){	// "."�܂���".."�łȂ���.
			tstrFileName = tstrScanPath;	// tstrFileName��tstrScanPath����.
			tstrFileName = tstrFileName + _T("\\");	// "\"��A��.
			tstrFileName = tstrFileName + wfdFindData.cFileName;	// wfdFindData.cFileName��A��.
			SHGetFileInfo(tstrFileName.c_str(), 0, &sfi, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_LARGEICON);	// SHGetFileInfo�Ńt�@�C�������擾.
			AddInfo(tstrFileName.c_str(), sfi.hIcon);	// AddInfo�Ńt�@�C������ǉ�.
		}
	}
	else{
		return;	// �ُ�I��.
	}

	// �ȍ~�̌���.
	while (FindNextFile(hFind, &wfdFindData)){	// FindNextFile�Ŏ��̃t�@�C�������擾.
		tstrFileName = _T("");	// tstrFileName��""���Z�b�g.
		ZeroMemory(&sfi, sizeof(SHFILEINFO));	// ZeroMemory��sfi���N���A.
		if (!((_tcscmp(wfdFindData.cFileName, _T(".")) == 0) || (_tcscmp(wfdFindData.cFileName, _T("..")) == 0))){	// "."�܂���".."�łȂ���.
			tstrFileName = tstrScanPath;	// tstrFileName��tstrScanPath����.
			tstrFileName = tstrFileName + _T("\\");	// "\"��A��.
			tstrFileName = tstrFileName + wfdFindData.cFileName;	// wfdFindData.cFileName��A��.
			SHGetFileInfo(tstrFileName.c_str(), 0, &sfi, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_LARGEICON);	// SHGetFileInfo�Ńt�@�C�������擾.
			AddInfo(tstrFileName.c_str(), sfi.hIcon);	// AddInfo�Ńt�@�C������ǉ�.
			MessageBox(NULL, tstrFileName.c_str(), _T("VizCommand"), MB_OK);	// MessageBox��tstrFileName��\��.
		}
	}

	// �I������.
	FindClose(hFind);	// FindClose��hFind�����.

}

// ���ׂẴt�@�C�������폜.
void CFileInfoList::RemoveAllInfo(){

	// �S�č폜.
	for (std::vector<CFileInfo *>::iterator itor = m_vecpFileInfo.begin(); itor != m_vecpFileInfo.end(); itor++){	// begin()����end()�܂�.
		delete (*itor);	// delete�ō폜.
		(*itor) = NULL;	// NULL���Z�b�g.
	}
	m_vecpFileInfo.clear();	// �N���A.
	m_tstrScanPath = _T("");	// m_tstrScanPath��""���Z�b�g.

}