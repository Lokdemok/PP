#include "stdafx.h"
#include "NamedPipe.h"

CNamedPipe::CNamedPipe()
	: CPipe()
{
}

CNamedPipe::~CNamedPipe()
{
	Close();
}


void CNamedPipe::Open(const std::string& name)
{
	m_name = name;

	m_hPipe = CreateNamedPipe(m_name.data(),// ��� ������������ ������          
		PIPE_ACCESS_DUPLEX,       // �������� ������ �� ������ � ������ 
		PIPE_TYPE_BYTE |   //������ ���������
		PIPE_WAIT,                // ����������� ����� 
		PIPE_UNLIMITED_INSTANCES, // ����� ����������� ������ �������������  
		BUFFER_PIPE_SIZE,                  // ������ ������ ��������� ��������� 
		BUFFER_PIPE_SIZE,                  // ������ ������ �������� ��������� 
		TIME_OUT,                        // ����-��� �������� (0=����������) 
		NULL);


	if (m_hPipe == INVALID_HANDLE_VALUE)
	{
		THROW_LAST_ERROR("Error for open pipe " + m_name);
	}
}


void CNamedPipe::ReadBytes(void * buffer, size_t size)
{

	if (ConnectNamedPipe(m_hPipe, NULL) != FALSE)
	{

		DWORD dwRead;
		BOOL bSuccess = ReadFile(m_hPipe, buffer, DWORD(size), &dwRead, NULL);

		if (!bSuccess || (dwRead == 0))
		{
			throw std::runtime_error("Read error");
		}


	}
	DisconnectNamedPipe(m_hPipe);

}

void CNamedPipe::WriteBytes(const void * buffer, size_t size)
{
	if (ConnectNamedPipe(m_hPipe, NULL) != FALSE)
	{

		DWORD dwWritten;
		BOOL bSuccess = WriteFile(m_hPipe, buffer, DWORD(size), &dwWritten, NULL);

		if (!bSuccess)
		{
			throw std::runtime_error("Read error");
		}

	}
	DisconnectNamedPipe(m_hPipe);

}

void CNamedPipe::Close()
{
	DisconnectNamedPipe(m_hPipe);
	CloseHandle(m_hPipe); //May throw an exception if a debugger is attached to the process!
	m_hPipe = nullptr;
}