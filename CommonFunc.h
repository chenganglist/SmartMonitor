#pragma once

#include "CommonHeader.h"

//��Mat���Ƶ�Picture�ؼ���
void DrawToScreen(CStatic& Picture,Mat img);


//��ȡ����
CString GetDate();


//��ȡʱ��
CString GetTime(void);



//��ȡ�洢ʱ��
CString GetSaveTime();


//��ʶ����д�������ı��ļ���
void WriteToRecordLine(CString info);


//��ʶ����д���ֻ�����ϵͳ��
BOOL WriteToCommandLine(CString info);


//��Grid�ؼ��ƶ�λ���в����ַ���
void InsertItemToGrid(CListCtrl& m_grid,CString Time,
	CString Results,int columns);


//��IplImage*��ָͼƬ�ϻ����ı���
void DrawSelectedArea(IplImage *image,vector<CvPoint> PointArray);



//����ֻ�����ϵͳ����ʷ��Ϣ
void ClearPhoneFile();


//ɾ���ļ��У����½����ļ���=��������ļ���
BOOL DeleteDirectory(char* strDirName);


