// ��d�C���N���[�h�h�~
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "ScalableEditPanel.h"	// CScalableEditPanel
#include "ConsoleCore.h"	// CConsoleCore

// �R���\�[���N���XCConsole
class CConsole : public CScalableEditPanel{

	// public�����o
	public:

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CConsole();	// �R���X�g���N�^CCConsole
		// static�����o�֐�
		static BOOL RegisterClass(HINSTANCE hInstance);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.
		void ShowInputForm();	// ���̓t�H�[���̏o��.
		virtual void OnSize(UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.

};

#endif