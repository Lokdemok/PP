#pragma once

#include <vector>
#include <string>
#include <Windows.h>
#include <ctime>
#include <string>
#include <iostream>

#include "../NamedPipe.h"
#include "../Postman.h"

class CClientApplication
{
public:
	CClientApplication(size_t numberProcess);
	~CClientApplication();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void							WaitCommand();
	double							GetPi(size_t amountIteration);
private:

	std::string						GetFinalMessage(size_t amountIteration, double result);
//////////////////////////////////////////////////////////////////////
// Static Methods
public:
	static size_t		CalculateHits(size_t numIter);

private:

	static double		RandomNumber();
	static bool			InCircle(double x, double y);
//////////////////////////////////////////////////////////////////////
// Data
public:
	CNamedPipe				m_outputChannel;
	CPipe					m_inputChannel;
private:
	size_t			m_numberProcess;
	size_t			m_amountIterations;
	std::string		m_namePipe;
};

