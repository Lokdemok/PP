#include "stdafx.h"

#include "Pipe.h"

CPipe::CPipe()
	: m_hPipe(NULL)
{
}

void CPipe::Open(const std::string& name) 
{
	m_name = name;

	m_hPipe = CreateFile(
				m_name.data(),
				GENERIC_ALL,//GENERIC_READ
				0,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_READONLY,
				NULL);


	if (m_hPipe == INVALID_HANDLE_VALUE)
	{
		THROW_LAST_ERROR("Error for open pipe " + m_name);
	}
}

CPipe::~CPipe(void)
{
	Close();
}

void CPipe::ReadBytes(void * buffer, size_t size)
{
	DWORD dwRead;
	BOOL bSuccess = ReadFile(m_hPipe, buffer, DWORD(size), &dwRead, NULL);

	if (!bSuccess || (dwRead == 0))
	{
		throw std::runtime_error("Read error");
	}

}

void CPipe::WriteBytes(const void * buffer, size_t size)
{
	DWORD dwWritten;
	BOOL bSuccess = WriteFile(m_hPipe, buffer, DWORD(size), &dwWritten, NULL);

	if (!bSuccess)
	{
		throw std::runtime_error("Read error");
	}
}

void CPipe::Close()
{
	CloseHandle(m_hPipe); //May throw an exception if a debugger is attached to the process!
	m_hPipe = nullptr;
}