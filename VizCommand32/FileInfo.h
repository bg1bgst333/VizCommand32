// ��d�C���N���[�h�h�~
#ifndef __FILE_INFO_H__
#define __FILE_INFO_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "Window.h"	// CWindow

// �t�@�C�������i�[����N���XCFileInfo
class CFileInfo{

	// public�����o
	public:

		// public�����o�ϐ�
		tstring m_tstrFileName;	// �t�@�C����m_tstrFileName.(�t���p�X.)
		tstring m_tstrFileTitle;	// �t�@�C���^�C�g��m_tstrFileTitle.(�t�@�C���������̂�.)
		tstring m_tstrFileExt;	// �t�@�C���g���qm_tstrFileExt.
		HICON m_hIcon;	// �t�@�C���A�C�R���n���h��m_hIcon.

};

#endif
