#pragma once


//�ж�ָ�����ȷ��
BOOL IsWrightCode(BYTE* m_ReceiveByte);



//�������ڽ����ַ��Եõ�X�������
double DecodeX(BYTE* ReceiveByte);



//�������ڽ����ַ��Եõ�Y�������
double DecodeY(BYTE* ReceiveByte);



//��X������Y���������������������ˮƽ�����
double AngCosReturn(double x,double y);



//���һ���ַ��ǲ���ʮ�������ַ�(0-F)�����Ƿ�����Ӧ��ֵ�����򷵻�0x10(��F)��
char HexChar(char c);



//��һ���ַ�����Ϊʮ�����ƴ�ת��Ϊһ���ֽ����飬�ֽڼ���ÿո�ָ���
//����ת������ֽ����鳤�ȣ�ͬʱ�����ֽ����鳤�ȡ�
int Str2Hex(CString str,CByteArray &data);



//�ж��ַ����Ƿ�Ϊ����
bool IsNumString( CString str );