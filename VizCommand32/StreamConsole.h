// ��d�C���N���[�h�h�~
#ifndef __STREAM_CONSOLE_H__
#define __STREAM_CONSOLE_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "UserControl.h"	// CUserControl
#include "WindowListControl.h"	// CWindowListControl
#include "Console.h"	// �R���\�[���N���X

// �X�g���[���R���\�[���N���XCStreamConsole
class CStreamConsole : public CWindowListControl{

	// public�����o
	public:

		// public�����o�ϐ�
		HMENU m_nId;	// HMENU�^���j���[ID.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CStreamConsole();	// �R���X�g���N�^CStreamConsole
		virtual ~CStreamConsole();	// �f�X�g���N�^~CStreamConsole
		// static�����o�֐�
		static BOOL RegisterClass(HINSTANCE hInstance);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�쐬���̃n���h��OnCreate.
		virtual void OnSize(UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
		virtual void OnTimer(UINT_PTR nIDEvent);	// �^�C�}�[�C�x���g������������.
		virtual void OnUserMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);	// ���[�U��`���b�Z�[�W������������.
		virtual void OnRequestScrollBottom(WPARAM wParam, LPARAM lParam);	// ���ւ̃X�N���[�����v�����ꂽ��.
		virtual int OnStreamCommand(WPARAM wParam, LPARAM lParam);	// �R���\�[������X�g���[���R���\�[���ւ̃��b�Z�[�W������ꂽ��.
		virtual void OnHello(HWND hSrc, CCommand *pCommand);	// "Hello, world!"�̏o�͂�v�����ꂽ��.

};

#endif