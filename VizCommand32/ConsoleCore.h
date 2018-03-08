// ��d�C���N���[�h�h�~
#ifndef __CONSOLE_CORE_H__
#define __CONSOLE_CORE_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "ScalableEdit.h"	// CScalableEdit

// �}�N���̒�`
// ���͋L��.
#define GREATER_THAN _T(">")

// �R���\�[���R�A�N���XCConsoleCore
class CConsoleCore : public CScalableEdit{

	// public�����o
	public:

		// public�����o�ϐ�
		tstring m_tstrFormString;	// �t�H�[��������m_tstrFormString.
		tstring m_tstrProfilePath;	// �z�[���t�H���_(CSIDL_PROFILE)�̃p�Xm_tstrProfilePath.
		tstring m_tstrInputFormString;	// ���ۂɏo�͂�����̓t�H�[��������m_tstrInputFormString.
		tstring m_tstrCurrentPath;	// ���݂̃p�Xm_tstrCurrentPath.
		tstring m_tstrCommandString;	// �R�}���h������m_tstrCommandString.
		long m_lStartPos;				// ���͊J�n�ʒum_lStartPos.
		long m_lCurrentPos;				// ���͌��݈ʒum_lCurrentPos.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CConsoleCore();	// �R���X�g���N�^CConsoleCore
		// �����o�֐�
		tstring GetProfilePath(HWND hWnd);	// �z�[���t�H���_(CSIDL_PROFILE)�̃p�X���擾.
		tstring GetInputFormString();	// ���̓t�H�[��������̎擾.
		void PutConsole(tstring tstrString);	// �R���\�[���ɕ�������o��.
		void ShowInputForm();	// ���̓t�H�[���̏o��.
		tstring GetCommandString();	// �R�}���h������̎擾�֐�GetCommandString.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�̍쐬���J�n���ꂽ��.
		virtual int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	// �L�[�������ꂽ��.
		virtual int OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);		// �����L�[�������ꂽ��.
		virtual int OnLButtonUp(UINT nFlags, POINT pt);	// �}�E�X���{�^���������ꂽ��.

};

#endif