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

		// public�����o�ϐ�
		HBRUSH m_hbrBackground;	// �w�i�F�u���Vm_hbrBackground.
		HWND m_hProcWnd;	// �R�}���h�ɑ΂��鏈�������s����E�B���h�E�̃E�B���h�E�n���h��m_hProcWnd.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CConsole();	// �R���X�g���N�^CCConsole
		// static�����o�֐�
		static BOOL RegisterClass(HINSTANCE hInstance);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.
		virtual void Destroy();	// �E�B���h�E�̔j���ƏI�������֐�Destroy.
		void ShowInputForm();	// ���̓t�H�[���̏o��.
		void SetProcWindow(HWND hWnd);	// �R�}���h�ɑ΂��鏈�������s����E�B���h�E���Z�b�g.
		virtual void OnSize(UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
		virtual HBRUSH OnCtlColorEdit(HDC hDC, HWND hEdit);	// �q�G�f�B�b�g�R���g���[���̕`�掞.
		virtual void OnUserMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);	// ���[�U��`���b�Z�[�W������������.
		virtual int OnConsoleCoreCommand(WPARAM wParam, LPARAM lParam);	// �R���\�[���R�A���烁�b�Z�[�W������ꂽ��.
		virtual void OnHello(HWND hSrc, CCommand *pCommand);	// "Hello, world!"�̏o�͂�v�����ꂽ��.
		virtual void OnList(HWND hSrc, CCommand *pCommand);	// �t�@�C�����X�g�̏o�͂�v�����ꂽ��.
		virtual void OnWalk(HWND hSrc, CCommand *pCommand);	// �J�����g�t�H���_�̈ړ���v�����ꂽ��.
		virtual void OnErrorCommandNotFound(HWND hSrc);	// �R�}���h��������Ȃ��G���[������������.

};

#endif