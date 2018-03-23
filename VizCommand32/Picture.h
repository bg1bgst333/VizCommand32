// ��d�C���N���[�h�h�~
#ifndef __PICTURE_H__
#define __PICTURE_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "CustomControl.h"	// CCustomControl

// �s�N�`���[�R���g���[���N���XCPicture
class CPicture : public CCustomControl {

	// public�����o
	public:

		// public�����o�ϐ�
		HBITMAP m_hBitmap;	// �r�b�g�}�b�v�n���h��m_hBitmap
		BITMAP m_Bitmap;	// BITMAP�\���̃I�u�W�F�N�g.
		tstring m_tstrImageName;	// �C���[�W��m_tstrImageName
		HDC m_hMemDC;	// �������f�o�C�X�R���e�L�X�gm_hMemDC
		int m_iHScrollPos;	// �X�N���[���o�[�̐��������̈ʒum_iHScrollPos
		int m_iVScrollPos;	// �X�N���[���o�[�̐��������̈ʒum_iVScrollPos
		SCROLLINFO m_ScrollInfo;	// �X�N���[�����m_ScrollInfo.
		BOOL m_bReadOnly;	// �ǂݍ��ݐ�p�t���Om_bReadOnly.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CPicture();	// �R���X�g���N�^CPicture
		virtual ~CPicture();	// �f�X�g���N�^~CPicture()
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create(�E�B���h�E�N���X���w��o�[�W����.)
		virtual void Destroy();	// �E�B���h�E�̔j���ƏI�������֐�Destroy.
		BOOL LoadImage(HINSTANCE hInstance, LPCTSTR lpctszImageName);	// �摜�����[�h����֐�LoadImage
		BOOL SaveImage(LPCTSTR lpctszImageName);	// �摜���Z�[�u����֐�SaveImage
		void SetImage();	// �摜���Z�b�g(�\��)����֐�SetImage
		void SetReadOnly(BOOL bReadOnly);	// �ǂݍ��ݐ�p�ɂ���֐�SetReadOnly
		virtual void OnSize(UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
		virtual void OnPaint();	// �E�B���h�E�̕`���v�����ꂽ���̃n���h��OnPaint.
		virtual void OnHScroll(UINT nSBCode, UINT nPos);	// ���������X�N���[���o�[�C�x���g���̃n���h��OnHScroll.
		virtual void OnVScroll(UINT nSBCode, UINT nPos);	// ���������X�N���[���o�[�C�x���g���̃n���h��OnVScroll.
		virtual void OnMouseMove(UINT nFlags, POINT pt);	// �}�E�X���ړ����Ă��鎞.
		virtual int OnLButtonDown(UINT nFlags, POINT pt);	// �}�E�X�̍��N���b�N���s��ꂽ���̃n���h��OnLButtonDown.
		virtual int OnLButtonUp(UINT nFlags, POINT pt);		// �}�E�X�̍��{�^���������ꂽ��.

};

#endif