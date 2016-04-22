#include "stdafx.h"
#include "DetectControl.h"
#include "WorkDlg.h"
#include "WorkAtHeight.h"//�߿���ҵ
#include "GrinderDetection.h"//��ĥ����ҵ
#include "ConstructionSiteDetection.h"//��Ա��ҵ
#define  SPAN  120//��֤ͬ������������ڲ��ظ����͵��ֻ�



//�߿ռ���������
//�߿ռ���豸��Ϣ
long HighLoginID;
char* HighIP;
unsigned short  HighPort;
char* HighUser;
char* HighPass;
long HighPlayhandle;


Mat HighMat;
vector<Mat> ImgsForHighTest;
vector<CvPoint> PointArray;//ͼ������


//ʩ���ֳ���Ƶ����
Mat BehaviorMat;
vector<Mat> ImgsForBehaviorTest;

//ʩ������豸��Ϣ
long BehaviorLoginID;
char* BehaviorIP;
unsigned short  BehaviorPort;
char* BehaviorUser;
char* BehaviorPass;
long BehaviorPlayhandle;



//��ĥ��������Ƶ����
//��ĥ������豸��Ϣ
long MillLoginID;
char* MillIP;
unsigned short  MillPort;
char* MillUser;
char* MillPass;
long MillPlayhandle;


Mat MillMat;
vector<Mat> ImgsForMillTest;


//��չ������Ƶ����
//��չ����豸��Ϣ
long MoreLoginID;
char* MoreIP;
unsigned short  MorePort;
char* MoreUser;
char* MorePass;
long MorePlayhandle;

Mat MoreMat;



//���������
BOOL HighWorkDetecting;
BOOL BehaviorDetecting;
BOOL MillDetecting;




//ȷ��һ��ֻ���һ����Ϊ������CPUռ��
CRITICAL_SECTION DetectionCritical;



CStatic BehaviorPic;
CStatic MillPic;
CStatic MorePic;
CListCtrl BehaviorGrid;
CListCtrl MillGrid;


//״̬��
CStatusBarCtrl StatusBar;
CListCtrl HighGrid;
CStatic HighPic;



//��ʱ�ɼ�����߳�
DWORD WINAPI HighDetectProc(LPVOID lpParameter)
{
	if (HighWorkDetecting==TRUE)
	{
		return 0;
	}
	HighWorkDetecting = TRUE;

	StatusBar.SetText("���ڼ��߿���ҵ", 1, 0);

	while (1)
	{
		char *pBuffer = NULL;
		int *pPicLen = NULL;
		H264_DVR_CatchPicInBuffer(HighLoginID, 
					0, pBuffer,1000000,pPicLen);
		//λͼתMat����
		cvSetData(&HighMat,pBuffer,4);
		imshow("High",HighMat);
		Sleep(1000);
	}

	HighWorkDetecting = FALSE;
	return 0;
}










//ʩ����Ϊ���
DWORD WINAPI BeheviorDetectProc(LPVOID lpParameter)
{
	if (BehaviorDetecting==TRUE)
	{
		return 0;
	}
	BehaviorDetecting = TRUE;
	vector<Mat> ImgsForBehaviorTest; 
	StatusBar.SetText("���ڼ�⹤����Ϊ", 2, 0);
	while(1)
	{

		if (BehaviorDetecting==FALSE)
		{
			StatusBar.SetText("����", 2, 0);
			return 0;
		}

		if (!BehaviorMat.empty())
		{
			if (ImgsForBehaviorTest.size()< 5)
			{
				ImgsForBehaviorTest.push_back(BehaviorMat.clone());

				Sleep(100);
				continue;
			}
		}
		else
		{
			Sleep(1000);
			continue;
		}

		if (ImgsForBehaviorTest.size()==5)
		{
			vector<Rect> noHelmetPedestrianRect;
			vector<Rect> smokePedestrianRect;
			bool ClassDetectionResult = true;
			vector<Rect> noBeltPedestrianRect;


	       EnterCriticalSection(&DetectionCritical);
		   try
		   {
			   DetectConstructionSite(ImgsForBehaviorTest,noHelmetPedestrianRect,
				   smokePedestrianRect,ClassDetectionResult,
				   noBeltPedestrianRect);
		   }
		   catch (...)
		   {
		   	    //AfxMessageBox("ʩ��������");
		   }
		   LeaveCriticalSection(&DetectionCritical);



			if (noHelmetPedestrianRect.size()>0)
			{

				//�ֻ�����ϵͳ
				static time_t LastTime = 0;
				static time_t PresentTime = 0;
				static time_t Span = 0;
				PresentTime = time(0);
				Span = PresentTime - LastTime;

				if (Span>SPAN)
				{
					LastTime = PresentTime;
					cvSaveImage("D:\\ʩ���ֳ������Ϣ\\notificationPhoto\\"
						+GetSaveTime()+"��ȫñ.jpg",
						&(IplImage)ImgsForBehaviorTest[0]);
					WriteToCommandLine("2");
				}


				//��ʾ���м����Ϣ
				InsertItemToGrid(BehaviorGrid,GetTime(),
					"����δ����ȫñ",1);
				cvSaveImage("D:\\ʩ���ֳ������Ϣ\\����ͼƬ\\"
					+GetSaveTime()+"��ȫñ.jpg",
					&(IplImage)ImgsForBehaviorTest[0]);
				WriteToRecordLine(GetTime()+ "       "+"����δ����ȫñ");


			}


			if (smokePedestrianRect.size()>0)
			{

				//�ֻ�����ϵͳ
				static time_t LastTime = 0;
				static time_t PresentTime = 0;
				static time_t Span = 0;
				PresentTime = time(0);
				Span = PresentTime - LastTime;

				if (Span>SPAN)
				{
					LastTime = PresentTime;
					cvSaveImage("D:\\ʩ���ֳ������Ϣ\\notificationPhoto\\"
						+GetSaveTime()+"����.jpg",
						&(IplImage)ImgsForBehaviorTest[0]);
					WriteToCommandLine("3");
				}


				//��ʾ���м����Ϣ
				InsertItemToGrid(BehaviorGrid,GetTime(),
					"��������",1);
				cvSaveImage("D:\\ʩ���ֳ������Ϣ\\����ͼƬ\\"
					+GetSaveTime()+"����.jpg",
					&(IplImage)ImgsForBehaviorTest[0]);
				

				WriteToRecordLine(GetTime()+ "       "+"��������");

			}


			if (ClassDetectionResult==FALSE)
			{
				    
				//�ֻ�����ϵͳ
				static time_t LastTime = 0;
				static time_t PresentTime = 0;
				static time_t Span = 0;
				PresentTime = time(0);
				Span = PresentTime - LastTime;

				if (Span>SPAN)
				{
					LastTime = PresentTime;
					WriteToCommandLine("4");
					cvSaveImage("D:\\ʩ���ֳ������Ϣ\\notificationPhoto\\"
						+GetSaveTime()+"���.jpg",
						&(IplImage)ImgsForBehaviorTest[4]);
				}


				//��ʾ���м����Ϣ
				InsertItemToGrid(BehaviorGrid,GetTime(),
						"�ල��Աδ��λ",1);
				cvSaveImage("D:\\ʩ���ֳ������Ϣ\\����ͼƬ\\"
						+GetSaveTime()+"��Աδ��λ.jpg",
						&(IplImage)ImgsForBehaviorTest[4]);
				WriteToRecordLine(GetTime()+ "       "+"�ල��Աδ��λ");


			}


			if (noBeltPedestrianRect.size()>0)
			{
				//�ֻ�����ϵͳ
				static time_t LastTime = 0;
				static time_t PresentTime = 0;
				static time_t Span = 0;
				PresentTime = time(0);
				Span = PresentTime - LastTime;

				if (Span>SPAN)
				{
					LastTime = PresentTime;
					cvSaveImage("D:\\ʩ���ֳ������Ϣ\\notificationPhoto\\"
						+GetSaveTime()+"����.jpg",
						&(IplImage)ImgsForBehaviorTest[0]);
					WriteToCommandLine("5");
				}


				//��ʾ���м����Ϣ
				InsertItemToGrid(BehaviorGrid,
					GetTime(),"���˰�ȫñ����δϵ��",1);
				cvSaveImage("D:\\ʩ���ֳ������Ϣ\\����ͼƬ\\"
					+GetSaveTime()+"����.jpg",
					&(IplImage)ImgsForBehaviorTest[0]);
				WriteToRecordLine(GetTime()+ "       "+"���˰�ȫñ����δϵ��");


			}

		}
		Sleep(5000);
		ImgsForBehaviorTest.clear();
	}

	BehaviorDetecting = FALSE;
	return 0;

}









//��ĥ�����
DWORD WINAPI MillDetectProc(LPVOID lpParameter)
{
	if (MillDetecting==TRUE)
	{
		return 0;
	}
	MillDetecting = TRUE;
	vector<Mat> ImgsForHighTest; 
	StatusBar.SetText("���ڼ���ĥ������", 3, 0);
	while (1)
	{

		if (MillMat.empty()==FALSE)
		{
			if (ImgsForMillTest.size()< 20)
			{
				ImgsForMillTest.push_back(MillMat.clone());
				Sleep(100);
				continue;
			}
		}
		else
		{
			Sleep(1000);
			continue;
		}


		if (MillDetecting == FALSE)
		{
			StatusBar.SetText("����", 3, 0);
			return 0;
		}



		if (ImgsForMillTest.size()==20)
		{
			vector<int> results;

			EnterCriticalSection(&DetectionCritical);
			try
			{
				results = DetectGrinderOperation(ImgsForMillTest);
			}
			catch (...)
			{
				//AfxMessageBox("��ĥ��������");
			}
			LeaveCriticalSection(&DetectionCritical);




			for (unsigned int i=0;i<results.size();i++)
			{
				switch (results[i])
				{
				case NO_5TURNS:
					{
						//�ֻ�����ϵͳ
						static time_t LastTime = 0;
						static time_t PresentTime = 0;
						static time_t Span = 0;
						PresentTime = time(0);
						Span = PresentTime - LastTime;

						if (Span>SPAN)
						{
							LastTime = PresentTime;
							WriteToCommandLine("6");
							cvSaveImage("D:\\ʩ���ֳ������Ϣ\\notificationPhoto\\"
								+GetSaveTime()+"��ĥ��.jpg",
								&(IplImage)ImgsForMillTest[19]);
						}


						//��ʾ���м����Ϣ
						InsertItemToGrid(MillGrid,GetTime(),
							"δ����5Ȧ",1);
						cvSaveImage("D:\\ʩ���ֳ������Ϣ\\����ͼƬ\\"
							+GetSaveTime()+"��ĥ��δ��������.jpg",
							&(IplImage)ImgsForMillTest[19]);
						WriteToRecordLine(GetTime()+ "       "+"δ����5Ȧ");

						break;
					}
				case REGUALR_TURNS :
					{
						InsertItemToGrid(MillGrid,GetTime(),
							"����5Ȧ",1);
						break;
					}

				case STAND_ON_COIL:
					{

						//�ֻ�����ϵͳ
						static time_t LastTime = 0;
						static time_t PresentTime = 0;
						static time_t Span = 0;
						PresentTime = time(0);
						Span = PresentTime - LastTime;

						if (Span>SPAN)
						{
							LastTime = PresentTime;
							WriteToCommandLine("9");
							cvSaveImage("D:\\ʩ���ֳ������Ϣ\\notificationPhoto\\"
								+GetSaveTime()+"��ĥ��.jpg",
								&(IplImage)ImgsForMillTest[19]);
						}


						//��ʾ���м����Ϣ
						InsertItemToGrid(MillGrid,GetTime(),
							"���˲���������",1);
						cvSaveImage("D:\\ʩ���ֳ������Ϣ\\����ͼƬ\\"
							+GetSaveTime()+"��ĥ������.jpg",
							&(IplImage)ImgsForMillTest[19]);
						WriteToRecordLine(GetTime()+ "       "+"���˲���������");
						break;

					}


				case PEOPLE_STAND_WRONG:
					{

						//�ֻ�����ϵͳ
						static time_t LastTime = 0;
						static time_t PresentTime = 0;
						static time_t Span = 0;
						PresentTime = time(0);
						Span = PresentTime - LastTime;

						if (Span>SPAN)
						{
							LastTime = PresentTime;
							WriteToCommandLine("10");
							cvSaveImage("D:\\ʩ���ֳ������Ϣ\\notificationPhoto\\"
								+GetSaveTime()+"��ĥ��.jpg",
								&(IplImage)ImgsForMillTest[19]);
						}


						//��ʾ���м����Ϣ
						InsertItemToGrid(MillGrid,GetTime(),
							"��ĥ��������Ավλ����",1);
						cvSaveImage("D:\\ʩ���ֳ������Ϣ\\����ͼƬ\\"
							+GetSaveTime()+"��ĥ����Ավλ.jpg",
							&(IplImage)ImgsForMillTest[19]);
						WriteToRecordLine(GetTime()+ "       "+"��Ավλ����");

						break;
					}
				}
			}
		}


		Sleep(6000);
		ImgsForMillTest.clear();
	}

	MillDetecting = FALSE;
	return 0;

}



