// ��d�C���N���[�h�h�~
#ifndef __WINDOW_LIST_CONTROL_H__
#define __WINDOW_LIST_CONTROL_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "UserControl.h"	// CUserControl
#include "WindowListItemsPanel.h"	// CWindowListItemsPanel

// �}�N����`
#define SCROLLBAR_THICKNESS 16	// �Ƃ肠�����X�N���[���o�[�̌����̓}�N����16�Ƃ��Ă���.

// �E�B���h�E���X�g�R���g���[���N���XCWindowListControl
class CWindowListControl : public CUserControl{

	// public�����o
	public:

		// public�����o�ϐ�
		CWindowListItemsPanel *m_pWindowListItemsPanel;	// CWindowListItemsPanel�I�u�W�F�N�g�|�C���^m_pWindowListItemsPanel.
		int m_iHScrollPos;	// �X�N���[���o�[�̐��������̈ʒum_iHScrollPos
		int m_iVScrollPos;	// �X�N���[���o�[�̐��������̈ʒum_iVScrollPos
		SCROLLINFO m_ScrollInfo;	// �X�N���[�����m_ScrollInfo.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CWindowListControl();	// �R���X�g���N�^CWindowListControl
		virtual ~CWindowListControl();	// �f�X�g���N�^~CWindowListControl
		// static�����o�֐�
		static BOOL RegisterClass(HINSTANCE hInstance);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.
		virtual void Destroy();	// �E�B���h�E�̔j���ƏI�������֐�Destroy.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�̍쐬���J�n���ꂽ��.
		virtual void OnDestroy();	// �E�B���h�E���j�����ꂽ��.
		virtual void OnPaint();	// �E�B���h�E�̕`���v�����ꂽ���̃n���h��OnPaint.
		virtual void OnSize(UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
		virtual void OnHScroll(UINT nSBCode, UINT nPos);	// ���������X�N���[���o�[�C�x���g��.
		virtual void OnVScroll(UINT nSBCode, UINT nPos);	// ���������X�N���[���o�[�C�x���g��.

};

#endif