#pragma once
#include "Deffsa.h"

class CArrayFilter {
public:
	CArrayFilter() { 
		nSumLeft = 0;
		nSumRight = 0;
		nLength = 0; 
		pnBegin = &aFilter[0];
		pnEnd = &aFilter[501];
		pnCurN = pnBegin;
		int i=0;
		while (pnCurN<=pnEnd) { 
			*pnCurN = 0; pnCurN++;
			i++;
		}
		pnCurN = pnBegin;
	}
	double aFilter[501];
	void Put(double &d, int n, bool bType);
	double Get(int n, bool bType);
	int nLength;				// ����� �������
	double *pnBegin;			// ��������� �� ������
	double *pnEnd;				// ��������� �� �����
	double *pnCurN;				// ��������� �� ������� �������
	double nSumLeft;			// ����� ����� ���������
	double nSumRight;			// ����� ����� ���������
};

class CArithmeticMean :
	public CArrayFilter
{
public:
	CArithmeticMean(void);
	~CArithmeticMean(void);
};
