#pragma once
#include "CommonHeader.h"


//�߿ռ��
//�߿ռ���豸��Ϣ
extern long HighLoginID;
extern char* HighIP;
extern unsigned short  HighPort;
extern char* HighUser;
extern char* HighPass;
extern long HighPlayhandle;


extern CStatic HighPic;//�߿ռ����Ƶ���Ŵ���
extern Mat HighMat;//ʵʱ��Ƶ֡
extern vector<CvPoint> PointArray;//�ı��ζ�λ��������
extern vector<Mat> ImgsForHighTest;//�߿ռ���ܼ���ͼƬ����
extern BOOL HighWorkDetecting;//�߿ռ��״̬
extern CListCtrl HighGrid;//�߿ռ��������ʾ


//�߿ռ�����߳�
DWORD WINAPI HighDetectProc(LPVOID lpParameter);






//ʩ���ֳ����
//ʩ������豸��Ϣ
extern long BehaviorLoginID;
extern char* BehaviorIP;
extern unsigned short  BehaviorPort;
extern char* BehaviorUser;
extern char* BehaviorPass;
extern long BehaviorPlayhandle;


extern CStatic BehaviorPic;//��Ϊ�����Ƶ���Ŵ���
extern Mat BehaviorMat;//��Ϊ���ʵʱ��Ƶ֡
extern vector<Mat> ImgsForBehaviorTest;//��Ϊ����ܼ��ͼƬ����
extern BOOL BehaviorDetecting;//��Ϊ��ⴰ�ڼ��״̬
extern CListCtrl BehaviorGrid;//��Ϊ������������

//��Ϊ����߳�
DWORD WINAPI BeheviorDetectProc(LPVOID lpParameter);





//��ĥ��������Ƶ����
//��ĥ������豸��Ϣ
extern long MillLoginID;
extern char* MillIP;
extern unsigned short  MillPort;
extern char* MillUser;
extern char* MillPass;
extern long MillPlayhandle;


extern CStatic MillPic;//��ĥ����Ƶ���Ŵ���
extern Mat MillMat;//��ĥ�����ʵʱ��Ƶ֡
extern vector<Mat> ImgsForMillTest;//��ĥ������ܼ���Ƶ֡���м�
extern BOOL MillDetecting;//��ĥ�����״̬
extern CListCtrl MillGrid;//��ĥ��������������


//��ĥ����ҵ����߳�
DWORD WINAPI MillDetectProc(LPVOID lpParameter);




//��չ������Ƶ����
//��չ����豸��Ϣ
extern long MoreLoginID;
extern char* MoreIP;
extern unsigned short  MorePort;
extern char* MoreUser;
extern char* MorePass;
extern long MorePlayhandle;


extern Mat MoreMat;//��չ����ʵʱ��Ƶ֡
extern CStatic MorePic;//��չ��Ƶ���Ŵ���




//ʹ���ٽ������ּ���̵߳Ķ�ռ��
extern CRITICAL_SECTION DetectionCritical;


//ϵͳ״̬������ʾϵͳ����״̬��Ϣ
extern CStatusBarCtrl StatusBar;







