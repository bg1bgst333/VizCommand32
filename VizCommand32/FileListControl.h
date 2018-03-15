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
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
		void ScanFile(tstring tstrPath);	// �t�@�C���̒T��ScanFile.
		void ShowFileList();	// �t�@�C�����X�g�̕\��ShowFileList.
		virtual void Destroy();	// �E�B���h�E�̔j���ƏI�������֐�Destroy.

};

#endif
