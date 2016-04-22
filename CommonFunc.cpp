#include "stdafx.h"
#include "CommonFunc.h"

void DrawToScreen(CStatic& Picture,Mat img)
{

	CRect rect;
	Picture.GetClientRect(&rect); //ͼƬ�ؼ�����
	CDC* pDC = Picture.GetDC();
	HDC hDC = pDC->GetSafeHdc(); //��ȡ��ͼ��ȫ���

	CvvImage cimg;
	cimg.CopyOf(&(IplImage)img,1);
	cimg.DrawToHDC(hDC ,&rect); //��ͼƬ�ؼ���ͼ--ʵʱ������Ƶ

}




BOOL WriteToCommandLine(const CString info)
{
	const CString CommandPath = 
		"D:\\ʩ���ֳ������Ϣ\\notificationMsg\\command.txt";
	CFile file(CommandPath,CFile::modeWrite);
	//��Ҫ�Դ�����ʽ���ļ����ж���
	char write[200];
	strcpy_s(write,info);
	file.SeekToEnd();
	file.Write("\r\n",2);
	file.Write(write,info.GetLength());

	file.Close();

	return TRUE;

}



void WriteToRecordLine(CString info)
{
	CString filePath = "D:\\ʩ���ֳ������Ϣ\\��ҵ���"
		+GetDate()+".txt";;
	CFile file(filePath,CFile::modeWrite);
	//��Ҫ�Դ�����ʽ���ļ����ж���
	char write[100];
	strcpy_s(write,info);
	file.SeekToEnd();
	file.Write("\r\n",2);
	file.Write(write,info.GetLength());

	file.Close();
}



void ClearPhoneFile()
{
	CString CommandPath = 
		"D:\\ʩ���ֳ������Ϣ\\notificationMsg\\command.txt";
	CFile Commandfile(CommandPath,CFile::modeCreate);

	DeleteDirectory("D:\\ʩ���ֳ������Ϣ\\notificationPhoto");
	CreateDirectory("D:\\ʩ���ֳ������Ϣ\\notificationPhoto",NULL);
	CreateDirectory("D:\\ʩ���ֳ������Ϣ\\notificationPhoto",NULL);

}



BOOL DeleteDirectory(char* strDirName)
{
    CFileFind tempFind;
    
    char strTempFileFind[MAX_PATH];

    sprintf(strTempFileFind,"%s//*.*", strDirName);

    BOOL IsFinded = tempFind.FindFile(strTempFileFind);

    while (IsFinded)
    {
        IsFinded = tempFind.FindNextFile();

        if (!tempFind.IsDots()) 
        {
            char strFoundFileName[MAX_PATH];

            strcpy(strFoundFileName, 
				tempFind.GetFileName().GetBuffer(MAX_PATH));

            if (tempFind.IsDirectory())
            {
                char strTempDir[MAX_PATH];

                sprintf(strTempDir,"%s//%s",
					strDirName, strFoundFileName);

                DeleteDirectory(strTempDir);
            }
            else
            {
                char strTempFileName[MAX_PATH];

                sprintf(strTempFileName,"%s//%s",
					strDirName, strFoundFileName);

                DeleteFile(strTempFileName);
            }
        }
    }

    tempFind.Close();

    if(!RemoveDirectory(strDirName))
    {
        return FALSE;
    }

    return TRUE;
}



//��ȡ�洢ʱ��
CString GetSaveTime()
{
	CTime tm;
	CString str;
	tm=CTime::GetCurrentTime();
	str.Format("%d-%d-%d",tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	return str;

}



//��ȡʱ��
CString GetTime(void)
{
	CTime tm;
	CString str;
	tm=CTime::GetCurrentTime();
	str.Format("%d-%d-%d %d:%d:%d",tm.GetYear(),tm.GetMonth(),tm.GetDay(),
		tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	return str;
}


//��ȡ����
CString GetDate(void)
{
	CTime tm;
	CString str;
	tm=CTime::GetCurrentTime();
	str.Format("%d-%d-%d",tm.GetYear(),tm.GetMonth(),tm.GetDay());
	return str;
}



void InsertItemToGrid(CListCtrl& m_grid,CString Time,
	CString Results,int columns)
{
	m_grid.InsertItem(0,"");
	m_grid.SetItemText(0,0,Time);
	m_grid.SetItemText(0,columns,Results);
}



void DrawSelectedArea(IplImage *image,vector<CvPoint> PointArray)
{
	if (PointArray.size()==4)
	{
		int arr[1];
		arr[0] = 4;
		CvPoint **pt = new CvPoint*[1];
		pt[0] = new CvPoint[4];
		pt[0][0] = PointArray[0];
		pt[0][1] = PointArray[1];
		pt[0][2] = PointArray[2];
		pt[0][3] = PointArray[3];
		cvPolyLine(image,pt,arr,1,1,CV_RGB(0,255,0),2);
		delete[] pt[0];
		delete[] pt;
	}
}



