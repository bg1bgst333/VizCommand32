// ��d�C���N���[�h�h�~
#ifndef __FILE_INFO_LIST_H__
#define __FILE_INFO_LIST_H__

// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <vector>	// std::vector
// �Ǝ��̃w�b�_
#include "FileInfo.h"	// CFileInfo

// �t�@�C����񃊃X�g���i�[����N���XCFileInfoList
class CFileInfoList{

	// public�����o
	public:

		// public�����o�ϐ�
		tstring m_tstrScanPath;	// �X�L�����Ώۃp�Xm_tstrScanPath.
		std::vector<CFileInfo *> m_vecpFileInfo;	// �t�@�C�����|�C���^���X�gm_vecpFileInfo.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CFileInfoList();	// �R���X�g���N�^CFileInfoList
		virtual ~CFileInfoList();	// �f�X�g���N�^~CFileInfoList
		// �����o�֐�
		virtual void AddInfo(tstring tstrFileName, HICON hIcon);	// �t�@�C�����̒ǉ�.
		virtual void RemoveInfo();	// �t�@�C�����̍폜.
		virtual void Scan(tstring tstrScanPath);	// �t�@�C���̒T��.
		virtual void RemoveAllInfo();	// ���ׂẴt�@�C�������폜.

};

#endif