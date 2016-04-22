#include "stdafx.h"


//�ж�ָ�����ȷ��
BOOL IsWrightCode(BYTE* m_ReceiveByte)
{
	BOOL IsWright = TRUE;
	for (int j=0;j<4;j++)
	{
		BYTE test = *(int*)(m_ReceiveByte+j);

		if (j==0)
		{
			if (test != 104)
			{
				IsWright = FALSE;
				break;
			} 
		}

		if (j==1)
		{
			if (test != 13)
			{
				IsWright = FALSE;
				break;
			} 
		}

		if (j==2)
		{
			if (test != 0)
			{
				IsWright = FALSE;
				break;
			} 
		}

		if (j==3)
		{
			if (test != 132)
			{
				IsWright = FALSE;
				break;
			} 
		}
	}

	return IsWright;

}


//����X����
double DecodeX(BYTE* ReceiveByte)
{
	double x;
	double x11,x12,x21,x22;
	double signx ;

	for (int i=4;i<7;i++)
	{
		BYTE ReceiveBytei = *(int*)(ReceiveByte+i);

		if (i==4)
		{
			if ( ReceiveBytei==16)
			{
				signx = -1.00;
			}
			else 
			{
				signx = 1.00;
			}
		}

		if (i==5)
		{
			x11 = ReceiveBytei/16;
			x12 = ReceiveBytei%16;
		}
		if (i==6)
		{
			x21 = ReceiveBytei/16;
			x22 = ReceiveBytei%16;
		}
	}

	x = signx*(x11*10 + x12 + 0.1*x21 + 0.01*x22);

	return x;

}


//����Y����
double DecodeY(BYTE* ReceiveByte)
{
	double y;       
	double y11,y12,y21,y22;
	double signy ;

	for (int i=7;i<10;i++)
	{

		BYTE ReceiveBytei = *(int*)(ReceiveByte+i);
		if (i==7)
		{
			if ( ReceiveBytei==16)
			{
				signy = -1.00;
			}
			else 
			{
				signy = 1.00;
			}
		}

		if (i==8)
		{
			y11 = ReceiveBytei/16;
			y12 = ReceiveBytei%16;
		}
		if (i==9)
		{
			y21 = ReceiveBytei/16;
			y22 = ReceiveBytei%16;
		}
	}

	y = signy*(y11*10 + y12 + 0.1*y21 + 0.01*y22);

	return y;

}


//������б��--�ɷ����ҵõ����
double AngCosReturn(double x,double y)
{//��ֵ�����������㺯��
	double AnX = x*3.1415927/180;
	double AnY = y*3.1415927/180;

	double a = cos(AnX);
	double b = cos(AnY);
	double c = a*a + b*b - a*a*b*b;

	double AnCos;

	AnCos = (a*b)/sqrtl(c) ;

	double z = acos(AnCos);

	return z ;

}


char HexChar(char c)//���һ���ַ��ǲ���ʮ�������ַ������Ƿ�����Ӧ��ֵ�����򷵻�0x10��
{	if((c>='0')&&(c<='9'))
return c-0x30;
else if((c>='A')&&(c<='F'))
	return c-'A'+10;
else if((c>='a')&&(c<='f'))
	return c-'a'+10;
else return 0x10;
}


int Str2Hex(CString str,CByteArray &data)
{ //��һ���ַ�����Ϊʮ�����ƴ�ת��Ϊһ���ֽ����飬�ֽڼ���ÿո�ָ���
	//����ת������ֽ����鳤�ȣ�ͬʱ�ֽ����鳤���Զ����á�
	int t,t1;
	int rlen=0,len=str.GetLength();
	data.SetSize(len/2);
	for(int i=0;i<len;)
	{char l,h=str[i];
	if(h==' ')
	{i++;
	continue;
	}
	i++;
	if(i>=len)break;
	l=str[i];
	t=HexChar(h);
	t1=HexChar(l);
	if((t==16)||(t1==16))
		break;
	else t=t*16+t1;
	i++;
	data[rlen]=(char)t;
	rlen++;
	}
	data.SetSize(rlen);
	return rlen;
}


//�ַ����Ƿ�Ϊ����
bool IsNumString( CString str )
{
	bool bIsDigit = TRUE;
	int nCount = str.GetLength(); // ����ַ�����
	for ( int i = 0; i < nCount; i ++ )
	{
		if ( FALSE == isdigit( str.GetAt(i) ) ) // �������־��ñ�־λ
		{
			bIsDigit = FALSE;
			break;// �˳�
		}
	}

	return bIsDigit;

}
