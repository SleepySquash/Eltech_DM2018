#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <string>
#include <malloc.h>

using namespace std;

//						                 ���� ����                                                     \\
// ������ �������� �� ����� �/�++ � ����� Microsoft Visual Studio 2013 ���������� ����� 7301, 7305 � 7307.
//
// _getch() ������ �������� ������ � ���������� ��� ������ ��� �� ����� �������.
// ���� ��� _getch():
// 72 - ������� �����.
// 80 - ������� ����.
// 13 - Enter.
// 27 - Esc.
// ���� ��� ��������� ������ ����� �������� �� ��������� ��� ���������� ����������� _getch() ���������� ���� int, � ����� ������� ���� ����� ����������.
// 
// ����������, ������������ ���� � ����:
// index - �������-����� ������.
// tmp - ��������� ����������, �������� � ���� �������� ������.
// module - ������� � ���������� �������� (��� ������ ������� ���� ������).
// prevIndex - �������-�����, ������� ��������� ��������� �������.
// 
// ����� ������� (����� >) �� ���� �������� ������������ � ������� ����������� ������������� _getch() � ������ � ����������� �������.
// �������� ��� �� ���� ������������: ���� ����� _getch() ����� ���� ������ ������� �����, �� ���������� �������, ���������� ��� ������� ����.
// ����� ���������� ��������, ��� ������� �� ������ �� ������� �������� module.
// 
// ���������� ��������� �������� �� ����: �������, �������� � ���� �������, ������ �� ������� � ���� ������ �������, �������, � ���� �������, ����� ������ � ���� �������.
// 
// ������ ����� ������ ��������� ���� � ���� ����� (� �� �����) ���������, ������� ����������� ������ � �������� (� ����� ���������) ���� ���������.
// �� ���� ������ ����� ��������� �� ����� �������� ���������� � ���������������� ������� ������ ����������. 
// ������ ����� ������ ���������� ���������� ���, ������� ��� ��� ��� ������� ������.
// ������ ����� ������ ���������� ���������� ���, ����� ��� � ��������� ���� ���� ������� ������������ ������� ���������.
// ������ ����� ������ ���������� ���������� ���, ����� ��� � ��������� ���� ���� ������� ������������ ����� ���������.
// ��������� � ������ ������ ����� ���������� � ������ ���� I ������ ��� ��������� "������".
//
// ������ ������� ����� ������� �� ������ - http://pozdnkov.vm2-leti.spb.ru/ucebnye-gruppy-1/plany-lekcij/kollokvium-po-dm/kollokvium-po-dm-2
// ������ ������������� ������� �� ������� ���������� - https://docs.google.com/spreadsheets/d/1X-aLv9Yl9oKm5RbzMNQT9eqwkyXjf6FtmMNYhdbeCRA/edit#gid=0
//
// �� ������ ������� ����:
// I ������� - ������� ����
// II ������� - ������
// III ������� - �������
//
// ���������� �������� � �������� � ��� �������:
// ����� �����, ������ 7307 - 5 ������� (COM_NN_D, MUL_Nk_N, SUB_NN_N, DIV_NN_Dk, ADD_NN_N)
// ��������� ��������, ������ 7301 - 4 ������� (POZ_Z_D, MUL_ZM_Z, ADD_ZZ_Z, SUB_ZZ_Z)
// ���� �������, ������ 7301 - 4 ������� (ABS_Z_N, TRANS_N_Z, TRANS_Z_N, TRANS_Z_Q)
// ������� �������, ������ 7307 - 3 ������� (NZER_N_B, MUL_ND_N, SUB_NDN_N)
// ������� �������� ������ 7307 - 2 ������� (LED_P_Q, ADD_1N_N)
// ������ �������, ������ 7301 - 2 ������� (MUL_NN_N, MUL_ZZ_Z)
// ������ ������, ������ 7307 - 2 ������� (TRANS_Q_Z, INT_Q_B)
// ���� �������, ������ 7307 - 2 ������� (MUL_QQ_Q, DIV_QQ_Q)
// ����� ���������, ������ 7307 - 1 ������� (DER_P_P)

int COM_NN_D(int n1, int n2, int *A1, int *A2)
// ��������� ����� 2- ���� ������ ������ �������, 1 - ���� ������ ������ �������, 0 - ���� ����� �����.
// ����� �����, ������ 7307
{
	int D = 0, i;

	if (n1 > n2)
		D = 2;
	else if (n1 < n2)
		D = 1;
	else if (n1 == n2)
		for (i = 0; i < n1; i++)
			if (A1[i] > A2[i])
			{
				D = 2;
				break;
			}
			else if (A1[i] < A2[i])
			{
				D = 1;
				break;
			}

	return D;
}

void MUL_Nk_N(int n, int *A1, int k, int **A10, int *n10) 
///��������� ����� �� 10 � ������� k
// ����� �����, ������ 7307
{
	int i, m, *A2 = NULL;
	m = n + k;
	A2 = (int*)malloc(sizeof(int)*m);
	for (i = 0; i<n; i++) ///���������� ������� ��������� ������� ������� �������
		A2[i] = A1[i];

	for (; n<m; n++) ///���������� ������� ������ ����� �������� ���� (���������� ���������� � �������)
		A2[n] = 0;
	(*n10) = m;
	(*A10) = (int*)malloc(sizeof(int)*m);
	for (i = 0; i < m; i++) {
		(*A10)[i] = A2[i];
	}

	free(A2);
}

int *ABS_Z_N(int &b, int n, int *A)
// ���� �������, ������ 7301
{
	b = 0;
	return A;
}

int NZER_N_B(int n1, int * &A1)
//������� �������, ������ 7307
{
	int i, flag = 0, k = 0;
	for (i = 0; i<n1; i++)
	{
		if (A1[i] != 0)
		{
			flag = 1;
			break;
		}
	}

	return flag;
}

void MUL_ND_N(int n1, int dig, int *A1, int *n3, int **answer)
///��������� ������������ ����� �� �����
// ������� �������, ������ 7307
{
	int r = 0, p, q, i, k, z, *help_arr;
	help_arr = (int*)malloc((n1 + 1)*sizeof(int));
	for (i = n1 - 1; i >= 0; i--)
	{
		z = A1[i];
		q = z*dig + r;
		p = q % 10;
		help_arr[i + 1] = p;
		r = q / 10;
	}
	*n3 = n1;
	k = *n3;
	if (r != 0)
	{
		help_arr[0] = r;
		*n3 = n1 + 1;
		k = *n3;
	}
	else
	{
		for (i = 0; i<n1; i++)
		{
			help_arr[i] = help_arr[i + 1];
		}
	}

	(*answer) = (int*)malloc(sizeof(int)*(*n3));

	for (i = 0; i<k; i++)
	{
		(*answer)[i] = help_arr[i];
	}
	free(help_arr);

}

double LED_P_Q(int m, int *C)
// m � ������� ���������� � ������ C �������������
// ������� ����������� ���������� (������� ����������� - ����������� ��� ���������� ������� ������������)
// �������� ����������  �������� ���������� �� �������� �������� � ���� ����������.
// �������� �������, ������ 7307
{
	printf("\n�����: %lf", C[0]);
	puts("");
	return C[0]; //������� ������ ���������� ��� �������� ��� ������ ��� ���������� � ���������?
}

void TRANS_Q_Z(int b, int n, int *A, int n1, int *A1)
// ������ ������, ������ 7307
{
	int i;
	if ((n1 == 0) && (A1[0] == 1))    //�������: �������� �� ����������� ��������?
	{
		printf("����� ���������� � �����: ");
		if (b == 1)               //������ ������� ����� ���� ������� �� ����� ���������, ��� �� ������ :)
			printf("-");       //���� �� ������ ������ �������� � ���� ������ ��� �����, ������ �� ������ �����������
		for (i = n; i >= 0; i--)
			printf("%d", A[i]);
	}
	else
		printf("���������� ������� � ����� ��� ��� ����������� �� ����� 1");//���� �����������  - �� �������
	printf("\n");
}

void SUB_NN_N(int n1, int n2, int *A1, int *A2, int D, int *n6, int **A6)
// ����� �����, ������ 7307
///"��������� �� ������� �������� ������������ ����� ������� �������� ��� �������"
{
	int i, j, *A4;
	A4 = (int*)malloc(n1 * sizeof(int));
	//int m=0;
	switch (D)
	{
		///������ ����� ������ �������
	case 2:
	{
		for (i = n1 - 1, j = n2 - 1; i >= 0 && j >= 0; i--, j--)
		{
			if (A1[i]<A2[j]) ///��������� ���������
			{
				A1[i] += 10;
				A1[i - 1] += -1;
			}
			A4[i] = A1[i] - A2[j];
			(*n6)++;
		}
		i = (*n6) + 1;

		for (i = 0; i<(n1 - n2); i++) ///������ � ������ ���������, �� �������� � ������� ����, ���� ����� ������ �����
			A4[i] = A1[i];
		(*n6) += (i - 1);

		while (A4[0] == 0 && n1 > 0) ///������������ ��������� ������� � ����� ������ 0 ����� ���������� �����������
		{
			for (i = 0, (*n6) = 0; i<(n1 - 1); i++)
			{
				A4[i] = A4[i + 1];
				(*n6)++;

			}
			n1 += -1;
		}
		*n6 = *n6 + 1;

		(*A6) = (int*)malloc(sizeof(int)*(*n6));
		for (i = 0; i<(*n6); i++) ///���������� ������� �������
		{
			(*A6)[i] = A4[i];
		}
		break;
	}
	///����� �����
	case 0:
	{
		(*A6) = (int*)malloc(sizeof(int) * 1);
		(*A6)[0] = 0;

		break;
	}
	///������ ������ �������
	case 1:
	{
		printf("\n������! ������������ ����!\n");
		(*n6) = -1;
		break;
	}

	}
	free(A4);

}

void SUB_NDN_N(int *answer, int *A1, int n1, int n4, int D, int **A5, int *n5) 
// ������� �������, ������ 7307
///��������� �� ������������ ������� ������������, ����������� �� ����� ��� ������ � ��������������� �����������.
{
	int *A6 = NULL, n6 = 1, i;
	if ((D == 2) || (D == 0))
	{
		SUB_NN_N(n1, n4, A1, answer, D, &n6, &A6);
		(*n5) = n6;
		(*A5) = (int*)malloc(sizeof(int)*(*n5));
		for (i = 0; i<n6; i++)
			(*A5)[i] = A6[i];
	}
	else
	{
		printf("������!");
		(*n5) = -1;
	}

	free(A6);
}

int POZ_Z_D(int sign, int sum, int *arr) {
// ����������� ��������������� ����� (2 - �������������, 0 � ������ ����, 1 - �������������)
// sign - ����, sum = ����� ������� �������, arr - ������ ���� �����
// ��������� ��������, ������ 7301
	if (sign == 1) {//���� ���������� �������� ����� ����� ������� �� ����� ������������� - ���������� 1(����� �������������)
		return 1;
	}
	else {
		if (arr[0] == 0) {//���� ���������� �������� ����� �� ����� ������� �� ����� ������������� ��� ����� 0, ���� ������ ����� � ������� ����� 0  - ���������� 0(����� ����� 0)
			return 0;
		}
		else {			//���� ������ ����� � ������� �� ����� 0  - ���������� 2(����� �������������)
			return 2;
		}
	}
}

void MUL_ZM_Z(int *sign, int sum, int *arr) 
// ��������� ��������, ������ 7301
//� ������� ����������� ������ ���� ����� ����� ���������, ����������� ���� � ����� ����� 1, �������� �� ���� �����(0 - ������������� ��� ����, 1 - ������������)
{
	if (*sign == 1) {//���� ���������� �������� ����� ����� ������� �� ����� ������������� � ��� ��������� �������� ������������� �����
		cout << "����� ��������� �� (-1) ����� ��������: ";
		for (int i = 0; i <= sum; i++) {
			cout << arr[i];
		}
		*sign = 0;
		cout << "\n";
	}
	else {
		if (arr[0] == 0) {//���� ���������� �������� ����� �� ����� ������� �� ����� g����������� ��� ����� 0, ���� ������ ����� � ������� ����� 0  - ����� ����� 0 � ��� ��������� �� (-1) �������� 0
			cout << "����� ��������� �� (-1) ��������: ";
			for (int i = 0; i < sum; i++) {
				cout << arr[i];
			}
			cout << "\n";
		}
		else {			//���� ������ ����� � ������� �� ����� 0  - ����� ������������� � ��� ��������� �� (-1) �������� ������������� �����
			cout << "����� ��������� �� (-1) ��������: -";
			for (int i = 0; i <= sum; i++) {
				cout << arr[i];
			}
			*sign = 1;
			cout << "\n";
		}
	}
}

int TRANS_N_Z(int b, int n, int *A){
//���� �������, ������ 7301
	if ((b != 0) || (A[0] == 0)){
		return 2;
	}
	else return b;
}

int TRANS_Z_N(int b, int n, int *A){
	//���� �������, ������ 7301
	if (b == 1)
		return -1;
	else if (A[0] == 0)
		return -2;
	else 
		return *A;
}

int ADD_1N_N(int m, int *A)
// ������� ��������, ������ 7307
// ���������� ����� ������� ������� (������_�������-1)
// !��� ������� ����� �������� ������ ������� (��������� � ������� �������)
{
	int i;
	for (i = m; i>0; i--) //��� ������ ����� � ����� ���� ���� �� ���� �� 9
	{
		if (A[i]<9)
		{
			A[i]++; //����������� �������
			i = -1;   //����� �� �����
		}
		else
		{
			A[i - 1]++;
			A[i] = 0;
		}
	}
	if (A[0] == 10) //������, ����� ���� ������� ��������, ��������� ������ �� �������
	{
		A = (int*)realloc(A, (m + 2) * sizeof(int));
		if (!A)  //�������� �� ��������� ������
		{
			printf("Allocation error.");
			exit(1);
		}
		A[0] = 1; //������ ������� �������, ���������-����
		for (i = 1; i<m + 2; i++) //���������� ��������� ��������� ������
		{
			A[i] = 0;
		}
		m++;
	}
	return m;
}

void DIV_NN_Dk(int n1, int n2, int *A1, int *A2, int D, int **A11, int *n11)
///"���������� ������ ����� ������� �������� ������������ �� �������, ����������� �� 10^k, ��� k - ����� ������� ���� ����� (����� ��������� � ����)"
// ����� �����, ������ 7307
{
	int *A6 = NULL, n6 = 1, i, k = 0, m = 0, *A10 = NULL, n10 = 1, F, *A3 = NULL, n3 = 1;
	A3 = (int*)malloc(n1*sizeof(int));
	for (i = 0; i<n1; i++)
		A3[i] = A1[i];
	n3 = n1;
	if (D == 2)
	{
		F = COM_NN_D(n2, n2, A1, A2); ///��������� ���� �� ����� 2 ����� 

		if ((F == 2) || (F == 0)) ///����� ������� ����� 
			k = n3 - n2;
		else
			k = n3 - n2 - 1;

		MUL_Nk_N(n2, A2, k, &A10, &n10); ///��������� ����� �� 10^k 

		F = COM_NN_D(n3, n10, A3, A10);


		while (F != 1) ///���� �� ��������� ������� ����� 
		{
			SUB_NN_N(n3, n10, A3, A10, F, &n6, &A6);
			m++;
			F = COM_NN_D(n6, n10, A6, A10);

			n3 = n6; ///����������� ����������� ��������, ����� ������� ��������� �������� � ����� 
			A3 = (int*)realloc(A3, n3*sizeof(int));
			for (i = 0; i<n3; i++)
				A3[i] = A6[i];
			n6 = 1;
			A6 = (int*)realloc(A6, n6*sizeof(int));
			A6[0] = 0;
		}
		(*n11) = 1;
		(*A11) = (int*)malloc(sizeof(int)*(*n11));
		(*A11)[0] = m;
	}
	else
	{
		printf("\n������!");

	}
	free(A10);
	free(A6);
	free(A3);
}

void ADD_NN_N(int n1, int n2, int &resultN, int *first, int *second, int * &result)
// ����� �����, ������ 7307
{
	int sum, i;
	bool extraNum = false; 

	if (n1 > n2)
		resultN = n1;
	else
		resultN = n2;

	n2--; // ��� ����
	n1--;
	result = NULL;

	result = (int*)realloc(result, (resultN + 1) * sizeof(int));

	

	if (n1 > n2) // ���������� ������ � ���������� �������
	{
		for (int i = 0; i < (n1 - n2); i++)
			*(result + i) = *(first + i);

		for (int i = (n1 - n2); i <= n1; i++)
			*(result + i) = 0;
	}
	else
	{
		for (int i = 0; i < (n2 - n1); i++)
			*(result + i) = *(second + i);


		for (int i = (n2 - n1); i <= n2; i++)
			*(result + i) = 0;

	}

	if (n1 > n2) // ��� �������
	{
		for (i = n1; i >= (n1 - n2); i--)
		{
			if (extraNum)
			{
				sum = 1;
				extraNum = false;
			}
			else
				sum = 0;

			sum += *(first + i) + *(second + i - (n1 - n2));
			if (sum > 9)
			{
				sum %= 10;
				extraNum = true;
			}

			*(result + i) = *(result + i) + sum;
		}
		if (extraNum && (i == -1))
		{
			for (int i = resultN; i >= 1; i--)
				*(result + i) = *(result + (i - 1));
			resultN++;
			*(result) = 1;
		}
		else if (extraNum)
		{
			*(result + i) = *(result + i) + 1;
		}
	}
	else
	{
		for (i = n2; i >= (n2 - n1); i--)
		{
			if (extraNum)
			{
				sum = 1;
				extraNum = false;
			}
			else
				sum = 0;

			sum += *(second + i) + *(first + i - (n2 - n1));
			if (sum > 9)
			{
				sum %= 10;
				extraNum = true;
			}

			*(result + i) = *(result + i) + sum;
		}
		if (extraNum && (i == -1))
		{
			for (int i = resultN; i >= 1; i--)
				*(result + i) = *(result + (i - 1));
			resultN++;
			*(result) = 1;
		}
		else if (extraNum)
		{
			*(result + i) = *(result + i) + 1;
		}
	}
}

int INT_Q_B(int b, int n, int *A, int n1, int *A1)
// ������ ������, ������ 7307
{
	int first = 0, second = 0;
	for (int i = 0; i <= n; i++)
	{
		first += *(A + i);
		first *= 10;
	}
	for (int i = 0; i <= n1; i++)
	{
		second += *(A1 + i);
		second *= 10;
	}

	if (first % second == 0)
		return 1;
	else
		return 0;
}

int TRANS_Z_Q(int b, int n, int *A, int n1, int *A1)
//���� �������, ������ 7301
{
	A1[0] = 1;//����������� ���������� ������ �������
	n1 = 1;
	return *A1;
}

void MUL_NN_N(int n0, int n1, int *A0, int *A1, int &nresult, int * &result)
//������ �������, ������ 7301
//�������������: MUL_NN_N(n0, n1, A0, A1, &nresult, &result)
//               n1 - ���������� ���� � ������ �����
//               n2 - ���������� ���� �� ������ �����
//               A0 - ������ ���� ������� ����� (��� ������� ������� - ��� ������ ������)
//               �1 - ������ ���� ������� ����� (��� ������� ������� - ��� ������ ������)
//               nresult - ���� ����� �������� ���������� ���� �����-����������
//               result - ��� ����� ������ ���� �����-���������� (��� ������� ������� - ��� ������ �������)
//���������� �������� nresult �������, � result ������ ����� �������� NULL ��� nullptr �� ��������� ������� � ������� ������.
{
	int i, j;
	int *tmp = NULL, ntmp = 0;
	int *add = NULL, nadd = 0;
	int ntemp = 1, *temp;
	int ntmpresult = 0, *tmpresult = NULL;

	temp = (int*)malloc(sizeof(int));
	temp[ntemp] = 0;

	for (i = 0; i<n1; i++)
	{
		MUL_ND_N(n0, A1[i], A0, &ntmp, &tmp);
		MUL_Nk_N(ntmp, tmp, n1 - i, &add, &nadd);
		ADD_NN_N(ntemp, nadd, ntmpresult, temp, add, tmpresult);
		ntemp = ntmpresult;
		temp = (int*)realloc(temp, (ntemp)*sizeof(int));
		for (j = 0; j<ntemp; j++)
			temp[j] = tmpresult[j];

		tmpresult = NULL; ntmpresult = 0;
		add = NULL; nadd = 0;
		ntmp = 0; tmp = NULL;
	}

	ntemp--;
	while ((*(temp) == 0) && (ntemp > 1))
	{
		*(temp) = *(temp + 1);
		ntemp--;
	}

	nresult = ntemp;
	result = (int*)malloc(sizeof(int)*(ntemp));
	for (i = 0; i < ntemp; i++)
		(result[i]) = temp[i];

	free(tmp);
	free(add);
	free(tmpresult);
}

void MUL_ZZ_Z(int sizeFirst, int sizeSecond, int *first, int *second, int markFirst, int markSecond, int &sizeResult, int * &result, int &markResult)
// ������ �������, ������ 7301
{
	int isPositiveFirst, isPositiveSecond;
	markResult = 1;
	MUL_NN_N(sizeFirst, sizeSecond, first, second, sizeResult, result);

	isPositiveFirst = POZ_Z_D(markFirst, sizeFirst, first);
	isPositiveSecond = POZ_Z_D(markSecond, sizeSecond, second);

	if (isPositiveFirst == isPositiveSecond)
		ABS_Z_N(markResult, sizeResult, result);
}

void DER_PP_P(int m, int *C)
{
	int i, j = 0;
	for (i = 0; i <= 2 * m + 1; i = i + 2)
	{
		printf("���������: %d, �����������: %d", C[i] * j, C[i + 1]);
		j++;
	}
}

void ADD_ZZ_Z(int *sum1, int *arr1, int *sign1, int *sum2, int *arr2, int *sign2, int *sum3, int *&arr3, int *sign3) {
	int D = 2;
	if (*sign1 == *sign2) {//���� ����� � ����� ���������� - ���������� ������ ����� � ������ ���� ����� ����� ������ ������ ���������
		ADD_NN_N((*sum1), (*sum2), (*sum3), arr1, arr2, *&arr3);
		*sign3 = *sign1;
		*sum3 = *sum3;
	}
	else {
		if (POZ_Z_D(*sign1, *sum1, arr1) == 2 || POZ_Z_D(*sign1, *sum1, arr1) == 0) {//���� ����� �� �����, �� �� ���������� ����� �� ����� �� ������ ������, ������������� ��� �������������, ���� ������������� ������ �� �� �������� �� �������������� ������������� �� ������ � ����������� ����� ����� ���� �����
			if (COM_NN_D((*sum1), (*sum2), arr1, arr2) == 2 || COM_NN_D(*sum1, *sum2, arr1, arr2) == 0) {//���� ������������� ������ �� �������� �� �������������� ������������� � ����������� ����� ����� ���� ����
				*sign3 = 0;
				SUB_NN_N((*sum1), (*sum2), arr1, arr2, D, sum3, &arr3);

			}
			else {
				*sign3 = 1;
				SUB_NN_N((*sum2), (*sum1), arr2, arr1, D, sum3, &arr3);
			}

		}
		if (POZ_Z_D(*sign2, *sum2, arr2) == 2 || POZ_Z_D(*sign2, *sum2, arr2) == 0) {
			if (COM_NN_D((*sum2), (*sum1), arr2, arr1) == 2 || COM_NN_D(*sum2, *sum1, arr2, arr1) == 0) {
				*sign3 = 0;
				cout << "������";
				SUB_NN_N((*sum2), (*sum1), arr2, arr1, D, sum3, &arr3);

			}
			else {
				cout << "cducd";
				*sign3 = 1;
				SUB_NN_N((*sum1), (*sum2), arr1, arr2, D, sum3, &arr3);
			}

		}
	}
}

void SUB_ZZ_Z(int *sum1, int *arr1, int *sign1, int *sum2, int *arr2, int *sign2, int *sum3, int *&arr3, int *sign3) {
	int D = 2;
	//if (COM_NN_D(*sum1, *sum2, arr1, arr2) == 2 || COM_NN_D(*sum1, *sum2, arr1, arr2) == 0) {//�������� ����� ������ ������� ��� ����� ��� ����� ����� � �������� �������������� ���
	//	*sum3 = *sum1;
	//}
	//else {
	//	*sum3 = *sum2;
	//}
	//int *arr3 = new int[*sum3 + 2];//������� ������
	if (*sign1 != *sign2) {//���� ����� � ����� ������ - ���������� ������ ����� � ������ ���� ����� ����� ������ ����� �������
		if (*sign2 == 1) {
			ADD_NN_N((*sum1), (*sum2), (*sum3), arr1, arr2, *&arr3);
			*sign3 = 0;
		}
		else {
			ADD_NN_N((*sum1), (*sum2), (*sum3), arr1, arr2, *&arr3);
			*sign3 = 1;

		}
		//ADD_NN_N( (*sum1), (*sum2), (*sum3), arr1,  arr2, *&arr3);
		//*sign3 = *sign1;
	}
	else {
		if (POZ_Z_D(*sign1, *sum1, arr1) == 2 || POZ_Z_D(*sign1, *sum1, arr1) == 0) {//���� ����� ����� �� ���������� ������ ����� �����, ����� �������� ����� �� ��� �� ������ ������ 
			if (COM_NN_D((*sum1), (*sum2), arr1, arr2) == 2 || COM_NN_D((*sum1), (*sum2), arr1, arr2) == 0) {//� � ����������� �� ����� ���������� ��� �������� ������ ����� � ������ ������ ����
				*sign3 = 0;
				SUB_NN_N((*sum1), (*sum2), arr1, arr2, D, sum3, &arr3);
				//������ ������ ���� ��� ����� 0, ������ ������ ����
			}													//������ ������ - �������� �� ������� ������ � ������ ���� +
			else {												//� �������� ������ ������ ������� - �������� �� ������� ������ � ���� -
				*sign3 = 1;
				SUB_NN_N((*sum2), (*sum1), arr2, arr1, D, sum3, &arr3);
			}

		}
		if (POZ_Z_D(*sign2, *sum2, arr2) == 1) {
			if (COM_NN_D((*sum2), (*sum1), arr2, arr1) == 2 || COM_NN_D((*sum2), (*sum1), arr2, arr1) == 0) {
				*sign3 = 0;
				SUB_NN_N((*sum2), (*sum1), arr2, arr1, D, sum3, &arr3);
			}													//������ � ������ ������ ����
			else {												//������ ������ - �������� �� ������� ������ � ������ ���� -
				*sign3 = 1;										//� �������� ������ ������ ������� - �������� �� ������� ������ � ���� +
				SUB_NN_N((*sum1), (*sum2), arr1, arr2, D, sum3, &arr3);
			}

		}
	}
}


/// ������ ������, ����� 7307
/////////////////////////
struct FLOAT //����� � ���� ���������
{
	int b; //���� �����
	int n, n1; //���������� ���� � ��������� � �����������
	int *A, *A1; //����� ��������� � �����������
};
//Xmax - ������� �����������; str3 - ������ �������� � �������������� ����������; k - �����, �� ������ ��������.
//b - ����; n, n1 - ������ ������� ��������; �, �1 - �����, �������� � ��������� � �����������.
struct FLOAT *MUL_Pxk_P(int Xmax, struct FLOAT *str3, int k) ///��������� ���������� �� x^k
{
	int i;
	struct FLOAT *str4;
	str4 = (struct FLOAT*)malloc((Xmax + 1 + k)*sizeof(struct FLOAT)); //�������� ������� ���������� �� k ������ ���������
	for (i = Xmax + k; i >= k; i--) //����������� ��������� ������� � �������������� �� ������� ������������� �� k � ������� ��������
	{
		str4[i].A = (int*)malloc((sizeof(str3[i].A)));
		str4[i].A1 = (int*)malloc((sizeof(str3[i].A1)));
		str4[i] = str3[i - k];
	}
	for (i = k - 1; i >= 0; i--) //������������� ������ ������ ����� �������
	{
		str4[i].b = 0;
		str4[i].n = 0;
		str4[i].n1 = 0;
		str4[i].A = (int*)malloc((sizeof(int)));
		str4[i].A[0] = 0;
		str4[i].A1 = (int*)malloc((sizeof(int)));
		str4[i].A1[0] = 1;
	}
	return str4; //����� ��������� �� �������������� ������
};
void scan_float(struct FLOAT *str2, int i)//���������� � ���������� ����� ����� (� ������ � ���������)
{
	int x, j;
	str2[i].b = 0; //�������������
	str2[i].n = -1;
	str2[i].n1 = -1;
	printf("������� ��������� ������������ ��� �^%d: ", i);
	scanf_s("%d", &x);
	if (x<0)               //����������� �����
	{
		str2[i].b = 1;
		x = -x;
	}
	str2[i].A = (int*)malloc((str2[i].n + 1)*sizeof(int));
	for (j = 0; x>0; j++)      //������ ��������� � ������
	{
		str2[i].n++;
		str2[i].A = (int*)realloc(str2[i].A, (str2[i].n + 1)*sizeof(int));
		str2[i].A[j] = x % 10;
		x = x / 10;
	}
	printf("������� ����������� ������������ ��� �^%d: ", i);
	scanf_s("%d", &x);
	str2[i].A1 = (int*)malloc((str2[i].n1 + 1)*sizeof(int));
	for (j = 0; x>0; j++)     //������ ����������� � ������
	{
		str2[i].n1++;
		str2[i].A1 = (int*)realloc(str2[i].A1, (str2[i].n1 + 1)*sizeof(int));
		str2[i].A1[j] = x % 10;
		x = x / 10;
	}
}
void print_result(struct FLOAT *str4, int max) //����� ���������� �� �����.
{
	int i, j;
	printf("��������� ���������:\n");
	for (i = max; i >= 0; i--)
	{
		if (str4[i].b == 1) //����� ����� ������������
		{
			printf(" - ");
		}
		else
		{
			printf(" + ");
		}

		for (j = str4[i].n; j >= 0; j--) //����� ���������
		{
			printf("%d", str4[i].A[j]);
		}
		printf("/");
		for (j = str4[i].n1; j >= 0; j--) //����� �����������
		{
			printf("%d", str4[i].A1[j]);
		}
		printf(" x^%d", i);
	}
}
/* void p_4(void) //���� ���������� � ����������
{
	int i, Xmax, k, Xmax1; //Xmax - ������� ����, Xmax1 - ������� ���� ����� ���������
	printf("������� ������� ������� ����������: ");
	scanf("%d", &Xmax);
	printf("������� �������� ������� k, ����� �������� ��������� �� �^k : ");
	scanf("%d", &k);       //������� k, �� ������� ���������� ���������

	struct FLOAT str1[Xmax + 1], *u; //������ ������������� � ��������� �� ���������

	for (i = Xmax; i >= 0; i--)
	{
		scan_float(str1, i);//���� � ���������� ���� ������������� � ������ �� � ������
	}


	u = MUL_Pxk_P(Xmax, str1, k);//��������� ���������� �� x^k (���� �������)
	Xmax1 = Xmax + k; //��������� �������� ������������
	print_result(u, Xmax1); //����� ���������� �� �����


	for (i = Xmax; i >= 0; i--) //������� ������
	{
		free(str1[i].A);
		free(str1[i].A1);
	}
	for (i = Xmax1; i >= 0; i--) //������� ���������� ������ �������
	{
		free(u[i].A);
		free(u[i].A1);
	}
	free(u);
} */
////////////////////////

void MUL_QQ_Q(int b, int n0, int n1, int *A0, int *A1, int b_1, int n0_1, int n1_1, int *A0_1, int *A1_1, int &b_result, int &n0_result, int &n1_result, int *&A0_result, int *&A1_result)
///��������� ������� ����, ��.7307
//��������� ������
// ������ �����: n0 -������ ���������, n1 - ������ �����������, A0 - ������ ���������, A1 - ������ �����������;
//���������� n0_1 � �.�. ��� ������ �����
//(_result) - ���������� - ���������
{
	MUL_ZZ_Z(n0, n0_1, A0, A0_1, b, b_1, n0_result, A0_result, b_result);
	MUL_NN_N(n1, n1_1, A1, A1_1, n1_result, A1_result); //���������� ��� �������, ��� ��� ����������� - ����������� �����
	//����� �������� ������� ���������� �����
}

void DIV_QQ_Q(int b, int n0, int n1, int *A0, int *A1, int b_1, int n0_1, int n1_1, int *A0_1, int *A1_1, int &b0_result, int &b1_result, int &n0_result, int &n1_result, int * &A0_result, int * &A1_result)
///��������� ������� ����, ��.7307
//��������� ������
// ������ �����: n0 -������ ���������, n1 - ������ �����������, A0 - ������ ���������, A1 - ������ �����������;
//���������� n0_1 � �.�. ��� ������ �����
//(_result) - ���������� - ���������
{
	MUL_ZZ_Z(n0, n1_1, A0, A1_1, b, 0, n0_result, A0_result, b0_result);
	MUL_ZZ_Z(n1, n0_1, A1, A0_1, 0, b_1, n1_result, A1_result, b1_result);//���������� ��� �������, ��� ��� ����������� - ����������� �����
	//����� �������� ������� ���������� �����
}

/* void DIV_ZZ_Z(int sizeFirst, int sizeSecond, int *first, int *second, int markFirst, int markSecond, int &sizeResult, int * &result, int &markResult)
// ������ �������, ������ 7301
{
	int isPositiveFirst, isPositiveSecond;
	markResult = 1;
	DIV_NN_N(sizeFirst, sizeSecond, first, second, sizeResult, result);

	isPositiveFirst = POZ_Z_D(markFirst, sizeFirst, first);
	isPositiveSecond = POZ_Z_D(markSecond, sizeSecond, second);

	if (isPositiveFirst == isPositiveSecond)
		ABS_Z_N(markResult, sizeResult, result);
} */

void naturalNum() // ������, � ������� ���� �������� � ������������ ������� 
{
	string module[14] = {"1. ��������� ����������� ����� ",
						 "2. �������� �� ����", 
						 "3. ���������� 1",
						 "4. �������� ����������� �����", 
						 "5. ��������� �� ������� �������� ������������...",
						 "6. ��������� ������������ ����� �� �����",
						 "7. ��������� ������������ ����� �� 10^k",
						 "8. ��������� ����������� �����",
						 "9. ��������� �� ������������ ������� ������������...",
						 "10. ���������� ������ ����� ������� ��������...",
						 "11*. ������� �� ������� �������� ������������ �����...",
						 "12*. ������� �� ������� �������� ������������ �����...",
						 "13*. ��� ����������� �����",
						 "14*. ��� ����������� �����"};

	// ���������� ��� ������ ������
	int index = 0, tmp, prevIndex = -1;

	// ���������� ��� ������
	int n0, n1, n2, n4, n5, n6, n10, n11, k, D, dig, m, nresult,
		*A = NULL,
		*A0 = NULL, 
		*A1 = NULL,
		*A2 = NULL,
		*A3 = NULL,
		*A5 = NULL,
		*A6 = NULL,
		*A10 = NULL,
		*A11 = NULL, 
		*answer = NULL,
		*result = NULL, 
		n3 = 0;

	do
	{
		if (prevIndex != index)
		{
			prevIndex = index;
			system("cls");
			puts("��������, ������ ����� �����, ���������� ������������� ������ �������.");
			puts("��������! ��������� ��������, ��� ������ ����� ������� �� ����������.\n"
				"��� ��������� ������� ������ �������� ��������������� ����� ����.\n"
				"�������� �������, ������� ������ ���������:\n");

			for (int i = 0; i < 14; i++)
			{
				if (i != index)
					cout << " " << module[i] << "\n";
				else
					cout << ">" << module[i] << "\n";
			}

			puts("\n��� �������� � ������� ���� ������� Esc.");
		}

		tmp = _getch();
		switch (tmp)
		{
			case 72:
				if (index > 0)
					index--;
				break;

			case 80:
				if (index < 13)
					index++;
				break;

			case 13:
				prevIndex = -1;

				system("cls");
				switch (index)
				{
					case 0:
						// ����� �����, ������ 7307
						//���� ���������� ���� � ������
						puts("��������� ����������� �����: 2 - ���� ������ ������ �������, 0, ���� �����, 1 �����.\n");
						printf("������� ���������� ���� � ������ �����: ");
						scanf_s("%d", &n1);

						printf("������� ���������� ���� �� ������ �����: ");
						scanf_s("%d", &n2);
						A1 = (int*)realloc(A1, (n1 + 1) * sizeof(int));
						A2 = (int*)realloc(A1, (n2 + 1) * sizeof(int));
						for (int i = 0; i<n1; i++)
						{
							printf("A1[%d] = ", i);
							scanf_s("%d", &A1[i]);
						}

						for (int i = 0; i<n2; i++)
						{
							printf("A2[%d] = ", i);
							scanf_s("%d", &A2[i]);
						}

						D = COM_NN_D(n1, n2, A1, A2);
						printf("\n��������� ��������� = %d\n", D);
						system("pause");
						break;

					case 1:
						// ������� �������, ������ 7307
						//���� ���������� ���� � ������
						puts("�������� �� ����: ���� ����� �� ����� ����, �� ��� ����� ����");
						printf("������� ���������� ���� � �����: ");
						scanf_s("%d", &n1);

						A1 = (int*) realloc (A1, (n1 + 1) * sizeof(int));
						//���� ����� ����� Enter
						for (int i = 0; i<n1; i++)
						{
							printf("a[%d] = ", i);
							scanf_s("%d", &A1[i]);
						}
						D = NZER_N_B(n1, A1);
						printf("��������� = %d", D);
						puts("");
						system("pause");
						break;

					case 2:
						// ������� ��������, ������ 7301
						// m - ����� ������� ������� (������_�������)
						// *A - ��������� �� ������ ������� ����
						// i -���������� ��� �����
						puts("���������� 1 � ������������ �����");
						printf("������� ����� ������� ������� (���������� ����): ");
						scanf_s("%d", &m);
						--m;
						A = (int*)malloc((m + 1) * sizeof(int));//��������� ������ ��� ������
						printf("������� ������ ����:\n");
						for (int i = 0; i<m + 1; i++)
						{
							printf("A[%d] = ", i);
							scanf_s("%d", &A[i]);
							if ((A[i]>9) || (A[i]<0)) //�������� �� ������
							{
								printf("%d- �� �����, ��� �����. ������� �������� ��������.\n", A[i]);
								i--;
							}
						}

						m = ADD_1N_N(m, A);

						printf("���������� �����: ");
						for (int i = 0; i<m + 1; i++)
						{
							printf("%d", A[i]);
						}
						printf("\n");

						free(A);
						puts("");
						system("pause");
						break;

					case 3:
						// ����� �����, ������ 7307
						//���� ���������� ���� � ������
						puts("�������� ����������� �����");
						n5 = 1;
						printf("������� ���������� ���� � ������ �����: ");
						scanf_s("%d", &n1);

						printf("������� ���������� ���� �� ������ �����: ");
						scanf_s("%d", &n2);

						A1 = (int*)malloc(n1*sizeof(int));
						A2 = (int*)malloc(n2*sizeof(int));
						//���� ����� ����� Enter
						for (int i = 0; i<n1; i++)
						{
							printf("A1[%d] = ", i);
							scanf_s("%d", &A1[i]);
						}

						for (int i = 0; i<n2; i++)
						{
							printf("A2[%d] = ", i);
							scanf_s("%d", &A2[i]);
						}
						// system ("cls");
						ADD_NN_N(n1, n2, n5, A1, A2, A5);
						printf("\n�����: ");
						for (int i = 0; i<n5; i++)
							printf("%d", A5[i]);

						free(A1);
						free(A2);
						free(A5);

						puts("");
						system("pause");
						break;

					case 4:
						// ����� �����, ������ 7307
						// ���� ���������� ���� � ������
						n3 = 1;
						puts("��������� �� ������� �������� ������������ ����� ������� �������� ��� �������");
						printf("������� ���������� ���� � ������ �����: ");
						scanf_s("%d", &n1);

						printf("������� ���������� ���� �� ������ �����: ");
						scanf_s("%d", &n2);

						A1 = (int*)realloc(A1, (n1 + 1) * sizeof(int));
						A2 = (int*)realloc(A2, (n2 + 1) * sizeof(int));
						//���� ����� ����� Enter
						for (int i = 0; i<n1; i++)
						{
							printf("A1[%d] = ", i);
							scanf_s("%d", &A1[i]);
						}

						for (int i = 0; i<n2; i++)
						{
							printf("A2[%d] = ", i);
							scanf_s("%d", &A2[i]);
						}

						D = COM_NN_D(n1, n2, A1, A2);
						//  printf("Comparison result= %d\n", D);
						SUB_NN_N(n1, n2, A1, A2, D, &n3, &A3);
						printf("\n�����: ");
						for(int i=0;i<n3;i++)
						{
							printf("%d",A3[i]);
							// printf("%d\n",n3);
						}
						puts("");
						free(A1);
						free(A2);
						free(A3);
						system("pause");
						break;

					case 5:
						// ������� �������, ������ 7307
						//���� ���������� ���� � ������
						puts("��������� ������������ ����� �� �����");
						printf("������� ���������� ���� � ������ �����: ");
						scanf_s("%d", &n1);
						A1 = (int*)malloc(sizeof(int)*n1);
						//���� ����� ����� Enter
						for (int i = 0; i<n1; i++)
						{
							printf("A1[%d] = ", i);
							scanf_s("%d", &A1[i]);
						}
						printf("������� �����: ");
						scanf_s("%d", &dig);
						MUL_ND_N(n1, dig, A1, &n3, &answer);
						printf("�����: ");
						for (int i = 0; i<n3; i++)
							printf("%d", answer[i]);
						puts("");
						free(A1);
						free(answer);
						system("pause");
						break;

					case 6:
						// ����� �����, ������ 7307
						//���� ���������� ���� � ������
						puts("��������� ������������ ����� �� 10^k");
						printf("������� ���������� ���� � �����: ");
						scanf_s("%d", &n1);

						A1 = (int*)realloc(A1, (n1 + 1) * sizeof(int));
						//���� ����� ����� Enter
						for (int i = 0; i<n1; i++)
						{
							printf("A1[%d] = ", i);
							scanf_s("%d", &A1[i]);
						}

						cout << "������� ������� k: ";
						cin >> k;
						n10 = 1;
						MUL_Nk_N(n1, A1, k, &A10, &n10);
						puts("");
						cout << "�����: ";
						for (int i = 0; i < n10; i++)
							cout << *(A10 + i);

						puts("");
						system("pause");
						break;

					case 7:
						// ������ �������, ������ 7301
						puts("��������� ����������� �����");
						cout << "������� ���������� ���� � ������ �����: ";
						cin >> n0;

						cout << "������� ���������� ���� �� ������ �����: ";
						cin >> n1;

						A0 = (int*)realloc(A0, (n0 + 1) * sizeof(int)); 
						A1 = (int*)realloc(A1, (n1 + 1) * sizeof(int));

						for (int i = 0; i < n0; i++)
						{
							cout << "A0[" << i << "] = ";
							cin >> *(A0 + i);
						}

						for (int i = 0; i < n1; i++)
						{
							cout << "A1[" << i << "] = ";
							cin >> *(A1 + i);
						}

						MUL_NN_N(n0, n1, A0, A1, nresult, result);

						cout << "�����: ";
						for (int i = 0; i < nresult; i++)
							cout << *(result + i);

						puts("");
						system("pause");
						break;

					case 8:
						// ������� �������, ������ 7307
						//���� ���������� ���� � ������
						n3 = 1;
						n4 = 0;
						n5 = 1;
						puts("��������� �� ������������ ������� ������������, ����������� �� ����� ��� ������ �	��������������� �����������");
						printf("������� ���������� ���� � ������ �����: ");
						scanf_s("%d", &n1);

						printf("������� ���������� ���� �� ������ �����: ");
						scanf_s("%d", &n2);

						A1 = (int*)malloc(n1*sizeof(int));
						A2 = (int*)malloc(n2*sizeof(int));
						//���� ����� ����� Enter
						for (int i = 0; i<n1; i++)
						{
							printf("A1[%d] = ", i);
							scanf_s("%d", &A1[i]);
						}

						for (int i = 0; i<n2; i++)
						{
							printf("A2[%d] = ", i);
							scanf_s("%d", &A2[i]);
						}
						printf("������� �����: ");
						scanf_s("%d", &dig);

						D = COM_NN_D(n1, n2, A1, A2);
						MUL_ND_N(n2, dig, A2, &n4, &answer);
						SUB_NDN_N(answer, A1, n1, n4, D, &A5, &n5);

						printf("�����: ");

						for (int i = 0; i<n5; i++)
						{
							printf("%d", A5[i]);
						}

						free(A1);
						free(A2);
						free(answer);
						free(A5);

						puts("");
						system("pause");
						break;

					case 9:
						// ����� �����, ������ 7307
						n6 = 1; 
						n11 = 1;
						puts("���������� ������ ����� ������� �������� ������������ �� �������, ����������� �� 10 ^ k, \n" 
							 "��� k - ����� ������� ���� �����(����� ��������� � ����)");

						//���� ���������� ���� � ������
						printf("������� ���������� ���� � ������ �����: ");
						scanf_s("%d", &n1);

						printf("������� ���������� ���� �� ������ �����: ");
						scanf_s("%d", &n2);

						A1 = (int*)malloc(n1*sizeof(int));
						A2 = (int*)malloc(n2*sizeof(int));

						//���� ����� ����� Enter
						for (int i = 0; i<n1; i++)
						{
							printf("A1[%d] = ", i);
							scanf_s("%d", &A1[i]);
						}

						for (int i = 0; i<n2; i++)
						{
							printf("A2[%d] = ", i);
							scanf_s("%d", &A2[i]);
						}

						D = COM_NN_D(n1, n2, A1, A2);

						DIV_NN_Dk(n1, n2, A1, A2, D, &A11, &n11);
						if (A11 != NULL)
						{
							printf("\n����� = ");
							printf("%d", A11[0]);
						}
						else
						{
							printf("������!");
						}

						free(A1);
						free(A2);
						free(A6);
						free(A11);

						puts("");
						system("pause");
						break;

					case 10:

						break;

					case 11:
						break;

					case 12:
						break;

					case 13:
						break;

				}
				break;
		}
	} while (tmp != 27);
}

void totalNum() // ������, � ������� ��� ������ � ������ �������
{
	string module[10] = {"1. ���������� �������� �����",
						 "2. ����������� ��������������� �����...",
						 "3. ��������� ������ �� (-1)",
						 "4. �������������� ������������ � �����",
						 "5. �������������� ������ ���������������� � �����������",
						 "6. �������� ����� �����",
						 "7. ��������� ����� �����",
						 "8. ��������� ����� �����",
						 "9*. ������� �� ������� �������� ������ ����� �� �������...",
						 "10*. ������� �� ������� �������� ������ ����� �� �������..."};

	// ���������� ��� ������ ������
	int index = 0, tmp, prevIndex = -1;

	// ���������� ��� ������
	int *A = NULL, *arr = NULL, *first = NULL, *second = NULL, *result = NULL, *sum1 = NULL, *sum2 = NULL, *sum3 = NULL, *arr1 = NULL, *arr2 = NULL, *arr3 = NULL, *sign1, *sign2, *sign3,
		b = 0, n = 0, 
		t, sign, sum, t1, sign11, tmpCase, sizeFirst, sizeSecond, markFisrt, markSecond, sizeResult, markResult;



	do
	{
		if (prevIndex != index)
		{
			prevIndex = index;
			system("cls");
			puts("��������, ������ ����� �����, ���������� ������������� ������ �������.");
			puts("��������! ��������� ��������, ��� ������ ����� ������� �� ����������.\n"
				"��� ��������� ������� ������ �������� ��������������� ����� ����.\n"
				"�������� �������, ������� ������ ���������:\n");

			for (int i = 0; i < 10; i++)
			{
				if (i != index)
					cout << " " << module[i] << "\n";
				else
					cout << ">" << module[i] << "\n";
			}

			puts("\n��� �������� � ������� ���� ������� Esc.");
		}
		tmp = _getch();
		switch (tmp)
		{
			case 72:
				if (index > 0)
					index--;
				break;

			case 80:
				if (index < 9)
					index++;
				break;

			case 13:
				prevIndex = -1;

				system("cls");
				switch (index)
				{
				case 0:
					// ���� �������, ������ 7301
					puts("���������� �������� �����, ��������� - �����������");
					cout << "������� ���� b (1 - �����, 0 - ����): ";
					cin >> b;
					cout << "������� ���� � �����: ";
					cin >> n;
					A = (int*)realloc(A, (n + 1) * sizeof(int));
					for (int i = 0; i < n; i++)
					{
						cout << "a[" << i + 1 << "] = ";
						cin >> *(A + i);
					}
					cout << "���������� �����: " << ABS_Z_N(b, n, A);
					puts("");
					system("pause");
					break;

				case 1:
					// �������� ��������, ������ 7301
					puts("����������� ��������������� ����� (2 - �������������,	0 � ������ ����, 1 - �������������)");
					cout << "������� ����� �����: ";
					cin >> t;
					sum = 0;
					if (t < 0) {
						sign = 1;
						t = -t;
					}
					else {
						sign = 0;
					}
					t1 = t;
					while (t1 > 0) {
						t1 = t1 / 10;
						sum++;
					}
					t1 = t;
					if (t != 0) {
						sum = sum;
					}
					else {
						sum = sum + 1;
					}
					arr = new int[sum];
					if (t != 0) {
						sum = sum - 1;
					}
					for (int i = sum; i >= 0; i--) {
						arr[i] = t1 % 10;
						t1 = t1 / 10;
					}
					sign11 = POZ_Z_D(sign, sum, arr);
					cout << "\n";
					cout << "���� �����: " << sign11;

					free(arr);
					system("pause");
					break;

				case 2:
					// ��������� ��������, ������ 7301
					puts("��������� ������ �� (-1)");
					cout << "������� ����� �����: ";
					cin >> t;
					sum = 0;
					if (t < 0) {
						sign = 1;
						t = -t;
					}
					else {
						sign = 0;
					}
					t1 = t;
					while (t1 > 0) {
						t1 = t1 / 10;
						sum++;
					}
					t1 = t;
					if (t != 0) {
						sum = sum;
					}
					else {
						sum = sum + 1;
					}
					arr = new int[sum];
					if (t != 0) {
						sum = sum - 1;
					}
					for (int i = sum; i >= 0; i--) {
						arr[i] = t1 % 10;
						t1 = t1 / 10;
					}

					MUL_ZM_Z(&sign, sum, arr);

					free(arr);
					system("pause");
					break;

				case 3:
					// ���� �������, ������ 7301
					puts("������� �� ������������ ����� � �����, ��������� - ���� �����");
					cout << "������� ���� b (1 - �����, 0 - ����): ";
					cin >> b;
					cout << "������� ���������� ���� � �����: ";
					cin >> n;
					A = (int*)realloc(A, (n + 1) * sizeof(int));
					for (int i = 0; i < n; i++)
					{
						cout << "a[" << i << "] = ";
						cin >> *(A + i);
					}
					if (TRANS_N_Z(b, n, A) == 2)
						cout << "����� ������� �����������, �.�. ��� ������ ���� �����������";
					else
					{
						cout << "��������� - ���� �����: " << TRANS_N_Z(b, n, A);
						puts(" ");
						cout << "�����: ";
						for (int i = 0; i < n; i++)
							cout << A[i];
						cout << endl;
					}

					puts("");
					free(A);
					system("pause");
					break;

				case 4:
					// ���� �������, ������ 7301
					puts("������� �� ������ ���������������� ����� � �����������, ��������� - ����������� �����");
					cout << "������� ���� b (1 - �����, 0 - ����): ";
					cin >> b;
					cout << "������� ���� � �����: ";
					cin >> n;
					A = (int*)realloc(A, (n + 1) * sizeof(int));
					for (int i = 0; i < n; i++)
					{
						cout << "a[" << i << "] = ";
						cin >> *(A + i);
					}
					tmpCase = TRANS_Z_N(b, n, A);
					if (tmpCase == -1)
						cout << "����� ������� �����������, �.�. ��� ������ ���� �����������";
					if (tmpCase == -2)
						cout << "����� ������� �����������, �.�. ����� 0 ������ ��������� � �����������";
					if ((tmpCase != -1) && (tmpCase != -2))
					{
						cout << "��������� - ������ � ������� � ������� �������: ";
						for (int i = 0; i < n; i++)
							cout << A[i];
						cout << endl;
						cout << "������� ����� - " << n << endl;
					}

					free(A);
					puts("");
					system("pause");
					break;

				case 5:
					// ��������� ��������, ������ 7301
					sum1 = (int*)malloc(1 * sizeof(int));
					sum2 = (int*)malloc(sizeof(int) * 1);
					sum3 = (int*)malloc(sizeof(int) * 1);
					sign1 = (int*)malloc(sizeof(int) * 1);
					sign2 = (int*)malloc(sizeof(int) * 1);
					sign3 = (int*)malloc(sizeof(int) * 1);
					*sum1 = 0;
					*sum2 = 0;
					*sum3 = 0;

					puts("�������� ����� �����");
					cout << "������� ���������� ���� � ������ �����: ";
					cin >> *sum1;
					cout << "������� ���������� ���� �� ������ �����: ";
					cin >> *sum2;
					arr1 = (int*)malloc(sizeof(int) * (*sum1));
					arr2 = (int*)malloc(sizeof(int) * (*sum2));
					arr3 = NULL;

					for (int i = 0; i < *sum1; i++) {
						cout << "A0[" << i << "] = ";
						cin >> arr1[i];
					}
					for (int i = 0; i < *sum2; i++) {
						cout << "A1[" << i << "] = ";
						cin >> arr2[i];
					}
					cout << "������� ���� ������� ����� (1 - �����, 0 - ����): ";
					cin >> *sign1;
					cout << "������� ���� ������� ����� (1 - �����, 0 - ����): ";
					cin >> *sign2;
					ADD_ZZ_Z(sum1, arr1, sign1, sum2, arr2, sign2, sum3, arr3, sign3);
					cout << "���������: ";

					if (*sign3 == 1) {
						cout << "-";
					}
					for (int i = 0; i < (*sum3); i++) {
						cout << arr3[i];
					}

					cout << "\n\n";
					system("pause");
					break;

				case 6:
					// ��������� ��������, ������ 7301
					sum1 = (int*)malloc(1 * sizeof(int));
					sum2 = (int*)malloc(sizeof(int) * 1);
					sum3 = (int*)malloc(sizeof(int) * 1);
					sign1 = (int*)malloc(sizeof(int) * 1);
					sign2 = (int*)malloc(sizeof(int) * 1);
					sign3 = (int*)malloc(sizeof(int) * 1);
					*sum1 = 0;
					*sum2 = 0;
					*sum3 = 0;

					puts("��������� ����� �����");
					cout << "������� ���������� ���� � ������ �����: ";
					cin >> *sum1;
					cout << "������� ���������� ���� �� ������ �����: ";
					cin >> *sum2;
					arr1 = (int*)malloc(sizeof(int) * (*sum1));
					arr2 = (int*)malloc(sizeof(int) * (*sum2));
					arr3 = NULL;

					for (int i = 0; i < *sum1; i++) {
						cout << "A0[" << i << "] = ";
						cin >> arr1[i];
					}
					for (int i = 0; i < *sum2; i++) {
						cout << "A1[" << i << "] = ";
						cin >> arr2[i];
					}
					cout << "������� ���� ������� ����� (1 - �����, 0 - ����): ";
					cin >> *sign1;
					cout << "������� ���� ������� ����� (1 - �����, 0 - ����): ";
					cin >> *sign2;
					SUB_ZZ_Z(sum1, arr1, sign1, sum2, arr2, sign2, sum3, arr3, sign3);
					cout << "���������: ";

					if (*sign3 == 1) {
						cout << "-";
					}
					for (int i = 0; i < (*sum3); i++) {
						cout << arr3[i];
					}

					cout << "\n\n";
					system("pause");
					break;

				case 7:
					// ������ �������, ������ 7301
					puts("��������� ����� �����");
					
					first = NULL;
					second = NULL;

					cout << "������� ���� ������� ����� (1 - �����, 0 - ����): ";
					cin >> markFisrt;

					cout << "������� ���� ������� ����� (1 - �����, 0 - ����): ";
					cin >> markSecond;

					cout << "������� ���������� ���� � ������ �����: ";
					cin >> sizeFirst;

					cout << "������� ���������� ���� �� ������ �����: ";
					cin >> sizeSecond;

					first = (int*)realloc(first, (sizeFirst + 1) * sizeof(int));
					second = (int*)realloc(second, (sizeSecond + 1) * sizeof(int));

					for (int i = 0; i < sizeFirst; i++)
					{
						cout << "A0[" << i << "] = ";
						cin >> *(first + i);
					}

					for (int i = 0; i < sizeSecond; i++)
					{
						cout << "A1[" << i << "] = ";
						cin >> *(second + i);
					}

					sizeResult = 0;
					result = NULL;
					MUL_ZZ_Z(sizeFirst, sizeSecond, first, second, markFisrt, markSecond, sizeResult, result, markResult);

					cout << "�����: ";
					if (markResult)
						cout << "-";

					for (int i = 0; i < sizeResult; i++)
						cout << *(result + i);

					free(result);
					free(first);
					free(second);

					puts("");
					system("pause");
					break;

				case 8:
					// ������ �������, ������ 7301
					puts("������� �� ������� ����� �����");

					first = NULL;
					second = NULL;

					cout << "������� ���� ������� ����� (1 - �����, 0 - ����): ";
					cin >> markFisrt;

					cout << "������� ���� ������� ����� (1 - �����, 0 - ����): ";
					cin >> markSecond;

					cout << "������� ���������� ���� � ������ �����: ";
					cin >> sizeFirst;

					cout << "������� ���������� ���� �� ������ �����: ";
					cin >> sizeSecond;

					first = (int*)realloc(first, (sizeFirst + 1) * sizeof(int));
					second = (int*)realloc(second, (sizeSecond + 1) * sizeof(int));

					for (int i = 0; i < sizeFirst; i++)
					{
						cout << "A0[" << i << "] = ";
						cin >> *(first + i);
					}

					for (int i = 0; i < sizeSecond; i++)
					{
						cout << "A1[" << i << "] = ";
						cin >> *(second + i);
					}

					sizeResult = 0;
					result = NULL;
					//DIV_ZZ_Z(sizeFirst, sizeSecond, first, second, markFisrt, markSecond, sizeResult, result, markResult);

					cout << "�����: ";
					if (markResult)
						cout << "-";

					for (int i = 0; i < sizeResult; i++)
						cout << *(result + i);

					free(result);
					free(first);
					free(second);

					puts("");
					system("pause");
					break;

				case 9:
					break;
				}
				break;
		}
	} while (tmp != 27);
}

void fractionNum() // ������, � ������� ��� ������ � �������
{
	string module[8] = {"1*. ���������� �����",
						"2. �������� �� �����",
						"3. �������������� ������ � �������",
						"4. �������������� �������� � �����",
						"5*. �������� ������",
						"6*. ��������� ������",
						"7. ��������� ������",
						"8. ������� ������ (�������� ������� �� ����)"};
	
	// ���������� ��� ������ ������
	int index = 0, tmp, prevIndex = -1;

	// ���������� ��� ������
	int *A0_1, *A1_1, *A0_result, *A1_result, *A = NULL, *A0 = NULL, *A1 = NULL, **result = NULL,
		b = 0, b_1, n0, n0_1, n1_1, n0_result, n1_result, b_result, b0_result, b1_result, n = -1, n1 = -1,
		x;


	do
	{
		if (prevIndex != index)
		{
			prevIndex = index;
			system("cls");
			puts("��������, ������ ����� �����, ���������� ������������� ������ �������.");
			puts("�������� �������, ������� ������ ���������:\n");

			for (int i = 0; i < 8; i++)
			{
				if (i != index)
					cout << " " << module[i] << "\n";
				else
					cout << ">" << module[i] << "\n";
			}

			puts("\n��� �������� � ������� ���� ������� Esc.");
		}

		tmp = _getch();
		switch (tmp)
		{
			case 72:
				if (index > 0)
					index--;
				break;

			case 80:
				if (index < 7)
					index++;
				break;

			case 13:
				prevIndex = -1;

				system("cls");
				switch (index)
				{
				case 0:
					break;

				case 1:
					// ������ ������, ������ 7307	
					puts("�������� �� �����, ���� ������������ ����� �������� �����, �� ���, ����� ����");
					printf("����������, ������� ���������: ");
					scanf_s("%d", &x);
					b = 0;
					n = -1;
					n1 = -1;
					if (x<0)               //����������� �����
					{
						b = 1;
						x = -x;
					}
					A = (int*)malloc((n + 1)*sizeof(int));
					for (int i = 0; x>0; i++)      //������ ��������� � ������ (����������)
					{
						n++;
						A = (int*)realloc(A, (n + 1)*sizeof(int));
						A[i] = x % 10;
						x = x / 10;
					}

					do
					{
						printf("����������, ������� �����������: ");
						scanf_s("%d", &x);
						if (x == 0)
							puts("������� �����������, �������� �� ����!");
					} while (x == 0);

					A1 = (int*)malloc((n1 + 1)*sizeof(int));
					for (int i = 0; x>0; i++)     //������ ����������� � ������
					{
						n1++;
						A1 = (int*)realloc(A1, (n1 + 1)*sizeof(int));
						A1[i] = x % 10;
						x = x / 10;
					}

					if (INT_Q_B(b, n, A, n1, A1) == 1)//�� ���� ���� ��� ��� ��������
						puts("��, ����� �����");
					else
						puts("���, ����� �� �����");

					free(A); //������������ ������
					free(A1);

					puts("");
					system("pause");
					break;

				case 2:
					// ���� �������, ������ 7301
					puts("�������������� �������� � �����");
					cout << "������� ���� b (1 - �����, 0 - ����): ";
					cin >> b;
					cout << "������� ���������� ���� � �����: ";
					cin >> n;
					A = (int*)realloc(A, (n + 1) * sizeof(int));
					for (int i = 0; i < n; i++)
					{
						cout << "a[" << i << "] = ";
						cin >> *(A + i);
					}
					A1 = (int*)malloc((n + 1)*sizeof(int));

					cout << "��������� - �����: " << endl;
					cout << "��������� : ";
					if (b == 1) cout << "-";
					for (int i = 0; i < n; i++)
						cout << A[i];
					cout << endl;
					cout << "����������� : ";
					cout << TRANS_Z_Q(b, n, A, n1, A1);
					free(A);
					free(A1);

					puts("\n");
					system("pause");
					break;

				case 3:
					// ������ ������, ������ 7307
					puts("�������������� �������� � ����� (���� ����������� ����� 1)");
					printf("����������, ������� ���������: ");
					scanf_s("%d", &x);
					b = 0;
					n = -1;
					n1 = -1;
					if (x<0)   //����������� �����
					{
						b = 1;
						x = -x;
					}
					A = (int*)malloc((n + 1)*sizeof(int));
					for (int i = 0; x>0; i++)   //������ ��������� � ������ (����������)
					{
						n++;
						A = (int*)realloc(A, (n + 1)*sizeof(int));
						A[i] = x % 10;
						x = x / 10;
					}
					printf("����������, ������� �����������: ");
					scanf_s("%d", &x);
					A1 = (int*)malloc((n + 1)*sizeof(int));
					for (int i = 0; x>0; i++)     //������ ����������� � ������
					{
						n1++;
						A1 = (int*)realloc(A1, (n1 + 1)*sizeof(int));
						A1[i] = x % 10;
						x = x / 10;
					}

					TRANS_Q_Z(b, n, A, n1, A1);//�� ���� ���� ��� ��� ��������
					free(A); //������������ ������
					free(A1);

					system("pause");
					break;

				case 4:
					break;

				case 5:
					break;

				case 6:
					// ���� �������, ������ 7307
					puts("��������� ������");
					printf("������� ���� ������� ����� (0 - �������������, 1 - �������������): ");
					scanf_s("%d", &b);

					printf("������ ��������� ������� �����: ");
					scanf_s("%d", &n0);
					A0 = (int*)malloc(n0*sizeof(int)); 
					printf("������� ��������� ������ �����: \n");
					for (int i = 0; i < n0; i++)
					{
						cout << "A0[" << i << "] = ";
						scanf_s("%d", &A0[i]);
					}

					printf("\n���������: ");
					for (int i = 0; i<n0; i++)
						printf("%d", A0[i]);

					printf("\n������ ����������� ������� �����: ");
					scanf_s("%d", &n1);
					A1 = (int*)malloc(n1*sizeof(int));
					printf("������� ����������� ������� �����: \n");
					for (int i = 0; i < n1; i++)
					{
						cout << "A0[" << i << "] = ";
						scanf_s("%d", &A1[i]);
					}
					printf("\n�����������: ");

					for (int i = 0; i<n1; i++)
						printf("%d", A1[i]);


					printf("\n������� ���� ������� ����� (0 - �������������, 1 - �������������): ");
					scanf_s("%d", &b_1);

					printf("������ ��������� ������� �����: ");
					scanf_s("%d", &n0_1);
					A0_1 = (int*)malloc(n0_1*sizeof(int));
					printf("������� ��������� ������ �����: \n");
					for (int i = 0; i < n0_1; i++)
					{
						cout << "A1[" << i << "] = ";
						scanf_s("%d", &A0_1[i]);
					}
					printf("\n���������: ");
					for (int i = 0; i<n0_1; i++)
						printf("%d", A0_1[i]);

					printf("\n������ ����������� ������� �����: ");
					scanf_s("%d", &n1_1);
					A1_1 = (int*)malloc(n1_1*sizeof(int));
					printf("������� ����������� ������ �����: \n");
					for (int i = 0; i < n1; i++)
					{
						cout << "A1[" << i << "] = ";
						scanf_s("%d", &A1_1[i]);
					}

					printf("\n�����������: ");
					for (int i = 0; i<n1; i++)
						printf("%d", A1_1[i]);

					MUL_QQ_Q(b, n0, n1, A0, A1, b_1, n0_1, n1_1, A0_1, A1_1, b_result, n0_result, n1_result, A0_result, A1_result); //��������� ������

					printf("\n���������: ");
					for (int i = 0; i<n0_result; i++)
						printf("%d", A0_result[i]);
					printf("/");
					for (int i = 0; i<n1_result; i++)
						printf("%d", A1_result[i]);

					free(A0);
					free(A1);
					free(A0_result);
					free(A1_result);
					free(A1_1);
					free(A0_1);

					puts("");
					system("pause");
					break;

				case 7:

					// ���� �������, ������ 7307
					puts("������� ������");
					printf("������� ���� ������� ����� (0 - �������������, 1 - �������������): ");
					scanf_s("%d", &b);

					printf("������ ��������� ������� �����: ");
					scanf_s("%d", &n0);
					A0 = (int*)malloc(n0*sizeof(int));
					printf("������� ��������� ������ �����: \n");
					for (int i = 0; i < n0; i++)
					{
						cout << "A0[" << i << "] = ";
						scanf_s("%d", &A0[i]);
					}

					printf("\n���������: ");
					for (int i = 0; i<n0; i++)
						printf("%d", A0[i]);

					printf("\n������ ����������� ������� �����: ");
					scanf_s("%d", &n1);
					A1 = (int*)malloc(n1*sizeof(int));
					printf("������� ����������� ������� �����: \n");
					for (int i = 0; i < n1; i++)
					{
						cout << "A0[" << i << "] = ";
						scanf_s("%d", &A1[i]);
					}
					printf("\n�����������: ");

					for (int i = 0; i<n1; i++)
						printf("%d", A1[i]);


					printf("\n������� ���� ������� ����� (0 - �������������, 1 - �������������): ");
					scanf_s("%d", &b_1);

					printf("������ ��������� ������� �����: ");
					scanf_s("%d", &n0_1);
					A0_1 = (int*)malloc(n0_1*sizeof(int));
					printf("������� ��������� ������ �����: \n");
					for (int i = 0; i < n0_1; i++)
					{
						cout << "A1[" << i << "] = ";
						scanf_s("%d", &A0_1[i]);
					}
					printf("\n���������: ");
					for (int i = 0; i<n0_1; i++)
						printf("%d", A0_1[i]);

					printf("\n������ ����������� ������� �����: ");
					scanf_s("%d", &n1_1);
					A1_1 = (int*)malloc(n1_1*sizeof(int));
					printf("������� ����������� ������ �����: \n");
					for (int i = 0; i < n1; i++)
					{
						cout << "A1[" << i << "] = ";
						scanf_s("%d", &A1_1[i]);
					}

					printf("\n�����������: ");
					for (int i = 0; i<n1; i++)
						printf("%d", A1_1[i]);

					DIV_QQ_Q(b, n0, n1, A0, A1, b_1, n0_1, n1_1, A0_1, A1_1, b0_result, b1_result, n0_result, n1_result, A0_result, A1_result);  //������� ������

					printf("\n���������: ");
					if (b0_result != b1_result)
						printf("-");

					for (int i = 0; i<n0_result; i++)
						printf("%d", A0_result[i]);
					printf("/");
					for (int i = 0; i<n1_result; i++)
						printf("%d", A1_result[i]);

					free(A0);
					free(A1);
					free(A0_result);
					free(A1_result);
					free(A1_1);
					free(A0_1);

					puts("");
					system("pause");
					break;
				}
				break;
		}
	} while (tmp != 27);

}

void polyNum() // ������, � ������� ��� ������ � ������������
{	
	string module[13] = {"1*. �������� �����������",
						 "2*. ��������� �����������", 
						 "3*. ��������� ���������� �� ������������ �����",
						 "4*. ��������� ���������� �� x^k", 
						 "5. ������� ����������� ����������",
						 "6*. ������� ����������",
						 "7*. ��������� �� ���������� ��� ������������...",
						 "8*. ��������� �����������",
						 "9*. ������� �� ������� ���������� �� ���������...",
						 "10*. �������� �� ������� ���������� �� ��������� ...",
						 "11*. ��� �����������",
						 "12. ����������� ����������",
						 "13*. �������������� ���������� � ������� ����� � �������"};

	// ���������� ��� ������ ������
	int index = 0, tmp, prevIndex = -1;

	// ���������� ��� case
	int m, 
	    *C = NULL;
	do
	{
		if (prevIndex != index)
		{
			prevIndex = index;
			system("cls");
			puts("��������, ������ ����� �����, ���������� ������������� ������ �������.");
			puts("��������! ��������� ��������, ��� ������ ����� ������� �� ����������.\n"
				"��� ��������� ������� ������ �������� ��������������� ����� ����.\n"
				"�������� �������, ������� ������ ���������:\n");

			for (int i = 0; i < 13; i++)
			{
				if (i != index)
					cout << " " << module[i] << "\n";
				else
					cout << ">" << module[i] << "\n";
			}

			puts("\n��� �������� � ������� ���� ������� Esc.");
		}

		tmp = _getch();
		switch (tmp)
		{
			case 72:
				if (index > 0)
					index--;
				break;

			case 80:
				if (index < 12)
					index++;
				break;

			case 13:
				prevIndex = -1;

				system("cls");
				switch (index)
				{
				case 0:
					break;

				case 1:
					break;

				case 2:
					break;

				case 3:
					break;

				case 4:
					// ������� ��������, ������ 7307
					puts("������� ����������� ����������");
					cout << "������� ������� ����������: ";
					cin >> m;
					cout << "������� ������������: \n";
					C = (int*)realloc(C, (m + 1) * sizeof(int));
					for (int i = 0; i<m; i++)
					{
						cout << "c[" << i + 1 << "] = ";
						cin >> *(C + i);
					}
					LED_P_Q(m, C);
					system("pause");
					break;

				case 5:
					break;

				case 6:
					break;

				case 7:
					break;

				case 8:
					break;

				case 9:
					break;

				case 10:
					break;

				case 11:
					// ����� ���������, ������ 7307
					printf("������� ������� ������� ����������: ");
					scanf_s("%d", &m);

					C = (int*)realloc(C, (2 * m + 2) * sizeof(int));

					printf("������� ������������ ����������:\n");

					for (int i = 2 * m + 1; i >= 0; i = i - 2) // ���� ���������� � ������������ ������� ����������
					{
						printf("���������: %");
						scanf_s("%d", &C[i - 1]);
						printf("�����������: ");
						scanf_s("%d", &C[i]);
					}
					DER_PP_P(m, C);

					puts("");
					system("pause");
					break;

				case 12:
					break;
				}
				break;
		}
	} while (tmp != 27);
}

void modulePick() // ����� ������
{
	string module[4] = {"1. ����������� ����� � �����",
						"2. ����� �����",
						"3. ������������ ����� (�����)",
						"4. ��������� � ������������� ��������������"};
	
	// ���������� ��� ������ ������
	int index = 0, tmp, prevIndex = -1;

	do
	{
		if (prevIndex != index)
		{
			prevIndex = index;
			system("cls");
			puts("�������� ������, � ������� �� ������ ���������� ����������:\n");

			for (int i = 0; i < 4; i++)
			{
				if (i != index)
					cout << " " << module[i] << "\n";
				else
					cout << ">" << module[i] << "\n";
			}

			puts("\n��� �������� � ������� ���� ������� Esc.");
		}
		tmp = _getch();
		switch (tmp)
		{
			case 72:
				if (index > 0)
					index--;
				break;

			case 80:
				if (index < 3)
					index++;
				break;

			case 13:
				prevIndex = -1;

				switch (index)
				{
					case 0:
						naturalNum();
						break;

					case 1:
						totalNum();
						break;

					case 2:
						fractionNum();
						break;

					case 3:
						polyNum();
						break;

				}
				break;
		}
	} while (tmp != 27);
}

void devTeam() // ������� �������������
{
	system("cls");
	puts("������ �����, ��������������� ���� ������:\n"
		 "����������:                      ������������:\n"
		 "������� �������, ������ 7305     ����� �����, ������ 7307\n"
		 "                                 ������� �������, ������ 7307\n"
		 "                                 ������� ��������, ������ 7307\n"
		 "                                 ������ ������, ������ 7307\n"
		 "������������� �� ��������:       ���� �������, ������ 7307\n"
		 "������ �������, ������ 7305      ��������� �������, ������ 7307\n"
		 "                                 ����� ���������, ������ 7307\n"
		 "                                 ��������� ��������, ������ 7301\n"
		 "                                 ������ �������, ������ 7301\n"
		 "                                 ��������� �������, ������ 7301\n\n"
		 "��� �������� � ������� ���� ������� Esc.");
	do
	{ }
	while (_getch() != 27);
}

void fixJournal() // ������ ���� �����������
{
	system("cls");
	puts("������ 1.0 BETA - ������ ���������: \n"
		 "1. ������ ���������� �������\n"
		 "2. ������� ������ � �������������\n"
		 "3. ����� ��� ���������� ���������\n"
		 "4. ������� �������:\n"
		 "I  ������ (����) - ����� ����, ������� �������������, ������ �����������\n"
		 "II ������ (������) - ����������� �����, ����� �����, ������������ �����, ���������� \n"
		 "����� ������� 30.03.2018 � 15:15 \n\n" 

		 "������ 1.0.1 - ������ ���������: \n"
		 "1. ������� ������� I ������ '������'\n"
		 "2. ����������� ������ ������\n"
		 "3. ����������� ��������� \n"
		 "4. ������� ������ ����������� \n"
		 "5. ����������� ����������� ����� ��� ��������� ������(������ ��� ��������� �������) \n"
		 "����� ������� 30.03.2018 � 17:20 \n\n" 

		 "������ 1.1.0 - ������ ���������: \n"
		 "1. �������� ���� ����, ���������� �� �������� ������� \n"
		 "2. ��������� ������� N - 1 (III �������) \n"
		 "3. ��������� ������� N - 2 (III �������) \n"
		 "4. ��������� ������� N - 7 (III �������) \n"
		 "5. ��������� ������� Z - 1 (III �������) \n"
		 "6. ��������� ������� Q - 4 (III �������) \n"
		 "����� ������� 30.03.2018 � 23:30 \n\n" 

		 "������ 1.2.0 - ������ ���������: \n"
		 "1. ��������� ��������� ������������ � ����� ���� \n"
		 "2. ��������� ����������� �� ���� ���������"
		 "3. ��������� ������� N - 6 (III �������) \n"
		 "4. ��������� ������� P - 5 (III �������) \n"
		 "5. ������������ ����������� ����� ���� \n"
		 "����� ������� 03.04.2018 � 00:30 \n\n" 

		 "������ 1.2.1 - ������ ���������: \n"
		 "1. ��������� ������� N - 5 (III �������) \n"
		 "2. ����������� ������ ������ \n"
		 "����� ������� 03.04.2018 � 13:30 \n\n" 

		 "������ 1.2.2 - ������ ���������: \n"
		 "1. ��������� ������� N - 9 (III �������) \n"
		 "2. ���������� �������� ��� ������ ������ ���� \n"
		 "2.1 ���������� �������� �� ������ ������������ ������ ��� ������� ������� ����, ������� �������� ������ \n"
		 "3. ����������� ������ ������ \n"
		 "����� ������� 03.04.2018 � 16:30 \n\n"

		 "������ 1.2.3 - ������ ���������: \n"
		 "1. ��������� ������� Z - 2 (III �������) \n"
		 "2. ��������� ������� Z - 3 (III �������) \n"
		 "3. ����������� ������ ������ \n"
		 "����� ������� 04.04.2018 � 20:00 \n\n"

		 "������ 1.2.4 - ������ ���������: \n"
		 "1. ��������� ������� N - 3 (III �������) \n"
		 "2. ��������� ������� Z - 4 (III �������) \n"
		 "3. ��������� ������� Z - 5 (III �������) \n"
		 "4. ����������� ������ ������ \n"
		 "����� ������� 05.04.2018 � 12:30 \n\n"

		 "������ 1.2.5 - ������ ���������: \n"
		 "1. ��������� ������� N - 7 (III �������) \n"
		 "2. ��������� ������� N - 10 (III �������) \n"
		 "3. ����������� ������ ������ \n"
		 "����� ������� 05.04.2018 � 20:30 \n\n"

		 "������ 1.2.6 - ������ ���������: \n"
		 "1. ��������� ������� N - 4 (III �������) \n"
		 "2. ��������� ������� Q - 2 (III �������) \n"
		 "3. ����������� ������ ������ \n"
		 "����� ������� 06.04.2018 � 19:00 \n\n"

		 "������ 1.2.7 - ������ ���������: \n"
		 "1. ���������� ������� N - 4 (III �������) \n"
		 "2. ��������� ������� Q - 3 (III �������) \n"
		 "3. ����������� ������ ������ \n"
		 "����� ������� 08.04.2018 � 02:00 \n\n"

		 "������ 1.2.8 - ������ ���������: \n"
		 "1. ��������� ������� N - 8 (III �������) \n"
		 "2. ���������� ������� Z - 1 (III �������) \n"
		 "3. ��������� ������� Z - 8 (III �������) \n"
		 "4. ����������� ������ ������ \n"
		 "����� ������� 08.04.2018 � 17:30 \n\n"

		 "������ 1.2.9 RELEASE - ������ ���������: \n"
		 "1. ��������� ������� N - 4 (III �������) \n"
		 "2. ��������� ������� N - 10 (III �������) \n"
		 "3. ��������� ������� P - 12 (III �������) \n"
		 "4. ����������� ������ ������ \n"
		 "����� ������� 10.04.2018 � 22:30 \n\n"

		 "(����������) ������ 1.2.10 RELEASE - ������ ���������: \n"
		 "1. ��������� ������� Z - 6 (III �������) \n"
		 "2. ��������� ������� Z - 7 (III �������) \n"
		 "3. ��������� ������� N - 5 (III �������) \n"
		 "4. ��������� ������� Q - 7 (III �������) \n"
		 "5. ��������� ������� Q - 8 (III �������) \n"
		 "6. ����������� ������ ������ \n"
		 "����� ������� 11.04.2018 � 17:00 \n\n"

		 "������ ������� ������������ (��� ���������������� �������):\n"
		 "1. ���������� ���� ������� �� ���� ������� (III �������) \n"
		 "2. ����������� ���������\n"
		 "3. �������� ����� ������������\n"
		 "4. (���������) �������� '�����-������', ���������� �� ��������� ������\n"
		 "4.1 (���������) �������� ����������� �������������� ���� ��������� ��������� ������\n"
		 "5. (���������) ��������� ������������ ���������� ��������� \n"
		 "����� ������� 30.03.2018 � 16:30 \n\n" 

		 "��� �������� � ������� ���� ������� Esc.");
	do
	{
	} while (_getch() != 27);
}

void help() // ������
{
	system("cls");
	puts("��� ������������� ��������, ����� � ����������� - ���������� �� �����:\n"
		 "dimon@kezling.ru\n\n"
		 "��� �������� � ������� ���� ������� Esc.");
	do
	{
	} while (_getch() != 27);
}

void menuPick() // ����� ����
{
	string mainMenu[4] = {"1. ������� � �������� ����� ���������",
						  "2. ������� �������������",
						  "3. ������ ����������",
						  "4. ������"};

	// ���������� ��� ������ ������
	int index = 0, tmp, prevIndex = -1;

	do
	{
		if (prevIndex != index)
		{
			prevIndex = index;
			system("cls");
			puts("������ ���������: 1.2.10 RELEASE \n\n"
				"������������!\n"
				"��� ���������� ���������� ����������� ������� �����/���� �� ����������\n"
				"��� ����� � ����� ���� ����������� Enter, ��� ������ - Esc.\n"
				"��������� �������������!\n");

			for (int i = 0; i < 4; i++)
			{
				if (i != index)
					cout << " " << mainMenu[i] << "\n";
				else
					cout << ">" << mainMenu[i] << "\n";
			}

			puts("\n��� ������ �� ��������� ������� Esc.");
		}

		tmp = _getch(); 
		switch (tmp)
		{
			case 72:
				if (index > 0)
					index--;
				break;

			case 80:
				if (index < 3)
					index++;
				break;
			
			case 13:
				prevIndex = -1;

				switch (index)
				{
					case 0:
						modulePick();
						break;

					case 1:
						devTeam();
						break;

					case 2:
						fixJournal();
						break;

					case 3:
						help();
						break;
				}
				break;
		}
	} while (tmp != 27);
}

int main() // �������� �������
{
	setlocale(LC_ALL, "RUS"); // ����������� ������� �����������
	 
	menuPick();

	system("cls");
	puts("������� ������������� ���������� ��� �� ������������� ����� ����������! \n"
		 "�������� ������� ��� �����! \n"
		 "�� ��������!");
	system("pause");
	return 0;
}