// ��d�C���N���[�h�h�~
#ifndef __COMMAND_H__
#define __COMMAND_H__

// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <string>	// std::string
#include <vector>	// std::vector
#include <sstream>	// std::stringstream
#include <tchar.h>		// TCHAR�^
#include <windows.h>	// �W��WindowsAPI

// �}�N���̒�`
// UNICODE�؂�ւ�
#ifdef UNICODE
#define tstring std::wstring
#define tstringstream std::wstringstream
#else
#define tstring std::string
#define tstringstream std::stringstream
#endif

// �R�}���h�N���XCCommand
class CCommand{

	// private�����o
	private:

		// private�����o�ϐ�
		tstring m_tstrCommandString;	// �R�}���h������m_tstrCommandString.
		tstring m_tstrCommandName;	// �R�}���h��m_tstrCommandName.

	// public�����o
	public:

		// public�����o�ϐ�
		std::vector<tstring> m_vectstrCommandToken;	// �R�}���h������̃g�[�N�����X�gm_vectstrCommandToken.
		// public�����o�֐�
		void Set(tstring tstrCommandString);	// �R�}���h������̃Z�b�g.
		void Clear();	// �R�}���h�̃N���A.
		tstring GetCommandName();	// �R�}���h���̎擾.
		tstring GetCommandString();	// �R�}���h������̎擾.

};

#endif