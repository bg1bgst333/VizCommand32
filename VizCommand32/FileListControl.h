// ��d�C���N���[�h�h�~
#ifndef __FILE_LIST_CONTROL_H__
#define __FILE_LIST_CONTROL_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "ListControl.h"	// CListControl
#include "FileInfoList.h"	// CFileInfoList

// �t�@�C�����X�g�R���g���[���N���XCFileListControl
class CFileListControl : public CListControl{

	// public�����o
	public:

		// public�����o�ϐ�
		CFileInfoList *m_pFileInfoList;	// �t�@�C����񃊃X�gm_pFileInfoList.
		tstring m_tstrPath;	// �T�����Ă���p�Xm_tstrPath.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CFileListControl();	// �R���X�g���N�^CFileListControl
		virtual ~CFileListControl();	// �f�X�g���N�^CFileListControl
		// �����o�֐�
		void ScanFile(tstring tstrPath);	// �t�@�C���̒T��ScanFile.
		virtual void Destroy();	// �E�B���h�E�̔j���ƏI�������֐�Destroy.

};

#endif
