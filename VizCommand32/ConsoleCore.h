// ��d�C���N���[�h�h�~
#ifndef __CONSOLE_CORE_H__
#define __CONSOLE_CORE_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "ScalableEdit.h"	// CScalableEdit

// �R���\�[���R�A�N���XCConsoleCore
class CConsoleCore : public CScalableEdit{

	// public�����o
	public:

		// public�����o�ϐ�
		tstring m_tstrCommandString;	// �R�}���h������m_tstrCommandString.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CConsoleCore();	// �R���X�g���N�^CConsoleCore
		// �����o�֐�
		tstring GetCommandString();	// �R�}���h������̎擾�֐�GetCommandString.
		virtual int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	// �L�[�������ꂽ��.

};


#endif