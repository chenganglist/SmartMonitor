// WorkDlg.cpp : ʵ���ļ�
#include "stdafx.h"
#include "Moniter.h"
#include "WorkDlg.h"
#include "afxdialogex.h"

// WorkDlg �Ի���
IMPLEMENT_DYNAMIC(WorkDlg, CDialogEx)

WorkDlg::WorkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(WorkDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);

	HighWorkDetecting = FALSE;
	BehaviorDetecting = FALSE;
	MillDetecting = FALSE;


	CString Date= "D:\\Record\\"+GetDate();
	CreateDirectory(Date,NULL);
	ClearPhoneFile();

	try
	{
		NoPic = imread("NoPic.jpg");
	}
	catch (...)
	{
		AfxMessageBox("ͼƬ�ļ�ȱʧ��");
	}

	if (NoPic.empty()==false)
	{
		CString path = "D:\\ʩ���ֳ������Ϣ\\notificationPhoto\\" + GetSaveTime()+".jpg";
		cvSaveImage(path,
			&(IplImage)NoPic);
	}


}




WorkDlg::~WorkDlg()
{

}




void WorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, HighPic);
	DDX_Control(pDX, IDC_LIST1_HIGH, HighGrid);
	DDX_Control(pDX, IDC_LIST1, m_gridcom);
	DDX_Control(pDX, IDC_MSCOMM1, m_Comm);
	DDX_Control(pDX, IDC_COMBO1, m_ComSel);
	DDX_Control(pDX, IDC_LIST1_HIGH2, BehaviorGrid);
	DDX_Control(pDX, IDC_LIST1_HIGH3, MillGrid);
	DDX_Control(pDX, IDC_PICTURE2, BehaviorPic);
	DDX_Control(pDX, IDC_PICTURE3, MillPic);
	DDX_Control(pDX, IDC_PICTURE4, MorePic);
}




BEGIN_MESSAGE_MAP(WorkDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &WorkDlg::OnLinkHighVideo)
	ON_BN_CLICKED(IDC_BUTTON2, &WorkDlg::OnExitHighVideo)
	ON_BN_CLICKED(IDC_BUTTON3, &WorkDlg::OnSelectMoniterArea)
	ON_BN_CLICKED(IDC_BUTTON4, &WorkDlg::OnCancelSelect)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EMPTY_GRID, &WorkDlg::OnEmptyGrid)
	ON_COMMAND(ID_REFRESH, &WorkDlg::OnRefresh)
	ON_CBN_SELCHANGE(IDC_COMBO1, &WorkDlg::OnComSelect)
	ON_BN_CLICKED(IDC_BUTTON13, &WorkDlg::OnDetectAngle)
	ON_BN_CLICKED(IDC_BUTTON14, &WorkDlg::OnAngleStop)
	ON_WM_TIMER()
	ON_COMMAND(ID_RUN_IN_BACK, &WorkDlg::OnRunInBack)
	ON_COMMAND(ID_32771, &WorkDlg::OnExit)
	ON_COMMAND(ID_32784, &WorkDlg::OnStartPhoneSystem)
	ON_MESSAGE(WM_HIDE_RUN,OnHideRun)
	ON_COMMAND(ID_32793, &WorkDlg::OnFaceRecognize)
	ON_COMMAND(ID_32794, &WorkDlg::OnOpenDoc)
	ON_COMMAND(ID_32795, &WorkDlg::OnOrgDoc)
	ON_BN_CLICKED(IDC_BUTTON21, &WorkDlg::OnLinkBehaviorVideo)
	ON_BN_CLICKED(IDC_BUTTON27, &WorkDlg::OnLinkMillVideo)
	ON_BN_CLICKED(IDC_BUTTON30, &WorkDlg::OnLinkMoreVideo)
	ON_BN_CLICKED(IDC_BUTTON9, &WorkDlg::OnExitBehaviorVideo)
	ON_BN_CLICKED(IDC_BUTTON26, &WorkDlg::OnExitMillVideo)
	ON_BN_CLICKED(IDC_BUTTON29, &WorkDlg::OnExitMoreVideo)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON38, &WorkDlg::OnRecordHighVideo)
	ON_BN_CLICKED(IDC_BUTTON37, &WorkDlg::OnStopHighRecord)
	ON_BN_CLICKED(IDC_BUTTON36, &WorkDlg::OnRecordBehavior)
	ON_BN_CLICKED(IDC_BUTTON35, &WorkDlg::OnStopBehavior)
	ON_BN_CLICKED(IDC_BUTTON34, &WorkDlg::OnMillRecord)
	ON_BN_CLICKED(IDC_BUTTON33, &WorkDlg::OnStopMillRecord)
	ON_BN_CLICKED(IDC_BUTTON31, &WorkDlg::OnMoreRecord)
	ON_BN_CLICKED(IDC_BUTTON32, &WorkDlg::OnStopMoreRecord)
	ON_BN_CLICKED(IDC_BUTTON41, &WorkDlg::OnLookDiary)
END_MESSAGE_MAP()




// WorkDlg ��Ϣ�������
BOOL WorkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_ComSel.SetCurSel(0);


	//״̬��
	StatusBar.Create(WS_CHILD|WS_VISIBLE|SBT_OWNERDRAW, 
		CRect(0,0,0,0), this, 0);

	int strPartDim[5]= {100,300,500,700,-1}; //�ָ�����,ʹ������
	StatusBar.SetParts(5, strPartDim);

	//����״̬���ı�
	StatusBar.SetText("ϵͳ״̬", 0, 0);
	StatusBar.SetText("����", 1, 0);
	StatusBar.SetText("����", 2, 0);
	StatusBar.SetText("����", 3, 0);
	StatusBar.SetText("����", 4, 0);

	StatusBar.ShowWindow(SW_SHOW);


	//onsize��С���ŶԻ����С�仯���仯
	CRect rectSize;     
	GetClientRect(&rectSize);     //ȡ�ͻ�����С   
	Old.x=rectSize.right-rectSize.left; 
	Old.y=rectSize.bottom-rectSize.top; 


	InitializeCriticalSection(&DetectionCritical);

	//����list��ʾ
	HighGrid.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);

	HighGrid.ModifyStyle( 0, LVS_REPORT );

	HighGrid.InsertColumn(0,"���ʱ��");        //������
	HighGrid.InsertColumn(1,"�߿���ҵ���");   
	   
	HighGrid.SetColumnWidth(0,125);       //�����еĿ�ȡ�
	HighGrid.SetColumnWidth(1,160);


	//��Ϊ
	BehaviorGrid.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);

	BehaviorGrid.ModifyStyle( 0, LVS_REPORT );

	BehaviorGrid.InsertColumn(0,"���ʱ��");        //������
	BehaviorGrid.InsertColumn(1,"ʩ���ֳ���Ϊ���");   

	BehaviorGrid.SetColumnWidth(0,125);       //�����еĿ�ȡ�
	BehaviorGrid.SetColumnWidth(1,160);


	//��ĥ��
	MillGrid.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);

	MillGrid.ModifyStyle( 0, LVS_REPORT );

	MillGrid.InsertColumn(0,"���ʱ��");        //������
	MillGrid.InsertColumn(1,"��ĥ����ҵ���");   

	MillGrid.SetColumnWidth(0,125);       //�����еĿ�ȡ�
	MillGrid.SetColumnWidth(1,160);


	m_gridcom.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_gridcom.ModifyStyle( 0, LVS_REPORT );

	m_gridcom.InsertColumn(0,"���ʱ��");        //������
	m_gridcom.InsertColumn(1,"�������"); 
	m_gridcom.SetColumnWidth(0,125);       //�����еĿ�ȡ�
	m_gridcom.SetColumnWidth(1,170);


	//������־
	CFileFind fileExist;

	CString m_date = GetDate();
	CString SaveDataPath = "D:\\ʩ���ֳ������Ϣ\\��ҵ���"
		+m_date+".txt";

	BOOL IsFind = fileExist.FindFile(SaveDataPath);

	if (!IsFind)
	{
		CFile file(SaveDataPath,CFile::modeCreate);
		file.Close();
	}

	//SDK��ʼ��
	H264_DVR_Init(NULL,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}



void WorkDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������

	CDialogEx::OnPaint();	
}


//��ʼѡ������ѡ��
void WorkDlg::OnSelectMoniterArea()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}





//ȡ��ѡ��
void WorkDlg::OnCancelSelect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}




void WorkDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	KillTimer(1);
	H264_DVR_Cleanup();
}




void WorkDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if(nType==SIZE_RESTORED||nType==SIZE_MAXIMIZED) 
	{ 
		float fsp[2]; 
		POINT Newp; //��ȡ���ڶԻ���Ĵ�С 
		CRect recta;     
		GetClientRect(&recta);     //ȡ�ͻ�����С   
		Newp.x=recta.right-recta.left; 
		Newp.y=recta.bottom-recta.top; 
		fsp[0]=(float)Newp.x/Old.x; 
		fsp[1]=(float)Newp.y/Old.y; 
		CRect Rect; 
		int woc; 
		CPoint OldTLPoint,TLPoint; //���Ͻ� 
		CPoint OldBRPoint,BRPoint; //���½� 
		HWND  hwndChild=::GetWindow(m_hWnd,GW_CHILD);  //�г����пؼ�   
		while(hwndChild)     
		{     
			woc=::GetDlgCtrlID(hwndChild);//ȡ��ID 
			GetDlgItem(woc)->GetWindowRect(Rect);   
			ScreenToClient(Rect);   
			OldTLPoint = Rect.TopLeft();   
			TLPoint.x = long(OldTLPoint.x*fsp[0]);   
			TLPoint.y = long(OldTLPoint.y*fsp[1]);   
			OldBRPoint = Rect.BottomRight();   
			BRPoint.x = long(OldBRPoint.x *fsp[0]);   
			BRPoint.y = long(OldBRPoint.y *fsp[1]);  

			//����Ͽ�ؼ��������⴦��
			HWND hwnd1 = m_ComSel.GetSafeHwnd(); // ȡ�ÿؼ��ľ��
			if (hwndChild==hwnd1)
			{
				BRPoint.y = BRPoint.y+100;
			}
			//������Ͽ�ؼ����

			Rect.SetRect(TLPoint,BRPoint);   
			GetDlgItem(woc)->MoveWindow(Rect,TRUE); 
			hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);     
		} 
		Old=Newp; 
		Invalidate();
	} 

}




BOOL WorkDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if (pMsg->message == WM_KEYDOWN   &&   pMsg->wParam == 0x1b)
	{
		return TRUE;
	}


	if (pMsg->message == WM_KEYDOWN   &&   pMsg->wParam == 0x0d)
	{
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}





void WorkDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: �ڴ˴������Ϣ����������
	CMenu menu;
	menu.LoadMenu(IDR_RIGHT_MENU); //��ȡ��Դ
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, 
		point.x, point.y, this);
}




void WorkDlg::OnEmptyGrid()
{
	// TODO: �ڴ���������������
	HighGrid.DeleteAllItems();
	m_gridcom.DeleteAllItems();
	BehaviorGrid.DeleteAllItems();
	MillGrid.DeleteAllItems();
	
	UpdateData(FALSE);
}





void WorkDlg::OnRefresh()
{
	// TODO: �ڴ���������������
	Invalidate(TRUE);

}




//������
BEGIN_EVENTSINK_MAP(WorkDlg, CDialogEx)
	ON_EVENT(WorkDlg, IDC_MSCOMM1, 1, WorkDlg::OnCommMscomm, VTS_NONE)
END_EVENTSINK_MAP()





void WorkDlg::OnCommMscomm()
{
	// TODO: �ڴ˴������Ϣ����������
	VARIANT m_input1; //��ȡ�������ڵ�����
	COleSafeArray m_input2;

	long length,i;
	BYTE data[1024];

	switch (m_Comm.get_CommEvent())
	{	
	case 2://��������
		{
			m_input1 = m_Comm.get_Input();
			m_input2 = m_input1;

			//��VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���
			length=m_input2.GetOneDimSize();//ȷ�����ݳ���

			for(i=0;i<length;i++)
				m_input2.GetElement(&i,data+i);
			//������ת��ΪBYTE������

			for(i=0;i<length;i++)//������ת��ΪCstring�ͱ���
			{
				BYTE a=* (int *)(data+i);

				m_ReceiveByte[i] = a;
			}


			//����ָ�����ȷ��
			BOOL IsWright = TRUE;
			IsWright = IsWrightCode(m_ReceiveByte);


			//���ָ����ȷ
			if (IsWright)
			{
				double x = DecodeX(m_ReceiveByte);
				double y = DecodeY(m_ReceiveByte);

				double m_Angle =180*AngCosReturn(x,y)/3.1415927;

				CString m_time = GetTime();  //ʱ��
				CString m_CurrentAngle;  //���
				m_CurrentAngle.Format("���Ϊ%f��",m_Angle);

				UpdateData(TRUE);

				if (m_Angle>15) 
				{
					CString m_IsOver = "��Ǵ���15��";
					m_gridcom.InsertItem(0,"");
					m_gridcom.SetItemText(0,0,m_time);
					m_gridcom.SetItemText(0,1,m_IsOver);


					//�ֻ�����ϵͳ��120s�ڲ��ظ�����
					static time_t LastTime = 0;
					static time_t PresentTime = 0;
					static time_t Span = 0;
					PresentTime = time(0);
					Span = PresentTime - LastTime;
					 if (Span>4)
					 {
						LastTime = PresentTime;
						WriteToCommandLine("7");
						if (NoPic.empty()==false)
						{
							cvSaveImage("D:\\ʩ���ֳ������Ϣ\\notificationPhoto\\NoPic.jpg",
								&(IplImage)NoPic);
						}
	
					 }

				}
				else 
				{

					static int i = 0;
					i++;
					if (i==8)
					{
						m_gridcom.InsertItem(0,"");
						m_gridcom.SetItemText(0,0,m_time);
						m_gridcom.SetItemText(0,1,m_CurrentAngle);
						i = 0;
					}

				}
				UpdateData(FALSE);

			}
		}
		break;
	}

}





void WorkDlg::OnComSelect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		if (m_Comm.get_PortOpen())
		{
			m_Comm.put_PortOpen(FALSE); //�رմ���
		}
		m_Comm.put__CommPort(m_ComSel.GetCurSel()+1); //ѡ�񴮿�

		if (!m_Comm.get_PortOpen())
		{
			m_Comm.put_PortOpen(TRUE); //�򿪴���
		}
		m_Comm.put_Settings("9600,n,8,1"); //����ͨ�Ų���
		m_Comm.put_InputMode(1);//����Ϊ�����ƶ�ȡ��ʽ
		m_Comm.put_InputLen(0);//���õ�ǰ�������ĳ���Ϊ��
		m_Comm.get_Input();//��Ԥ���������������������
		m_Comm.put_RThreshold(14);//���ý��ܴ����ֽ���
	}
	catch (...)
	{
		MessageBox("��Ч����");
	}

}





void WorkDlg::OnDetectAngle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetTimer(1,500,NULL);

}


void WorkDlg::OnAngleStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(1);

}


void WorkDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent==1)
	{
		if( m_Comm.get_PortOpen())
		{
			try
			{
				CByteArray data ;
				CString SendStr = "68 04 00 04 08";
				int len = Str2Hex(SendStr,data);
				m_Comm.put_InputLen(0);
				m_Comm.get_Input();//��ս�����
				m_Comm.put_Output(COleVariant(data));//����16����������
			}
			catch (...)
			{
				KillTimer(1);
				MessageBox("�����Ѱγ�");
			}

		}
		else
		{
			KillTimer(1);
		}
	}

	CDialogEx::OnTimer(nIDEvent);

}



//�˵��¼�
void WorkDlg::OnRunInBack()
{
	// TODO: �ڴ���������������
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDI_ICON1;
	nid.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP ;

	nid.uCallbackMessage = WM_HIDE_RUN;
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDI_ICON1));

	strcpy_s(nid.szTip,"��̨����");

	Shell_NotifyIcon(NIM_ADD,&nid);

	ShowWindow(SW_HIDE);

}


LRESULT WorkDlg::OnHideRun( WPARAM wParam,LPARAM lParam )
{
	if (wParam!=IDI_ICON1)
	{
		return 1;
	}

	switch(lParam)
	{
	case WM_RBUTTONUP: //�Ҽ�������ݲ˵�
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);
			CMenu menu;
			menu.CreatePopupMenu();//����һ������ʽ�˵�
			menu.AppendMenu(MF_STRING,IDCANCEL,"�˳�");

			//ȷ������ʽ�˵���λ��
			menu.TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,
				lpoint->y,this);

			//��Դ����
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;

			break;
		}
	case WM_LBUTTONDOWN:
		{
			this->ShowWindow(SW_SHOW);
			break;
		}
	default:
		break;

	}

	return 0;

}


void WorkDlg::OnExit()
{
	// TODO: �ڴ���������������
	OnClose();
	OnOK();
}



void WorkDlg::OnStartPhoneSystem()
{
	// TODO: �ڴ���������������
	ShellExecute(NULL,"open",
		//"F:\\NTF8-8\\NTFClient.jar",
		"E:\\���ϵͳ�������\\NTFClient\\NTFClient.exe",
		//F:\NTF8-8
		NULL,
		NULL,SW_SHOWNORMAL);
}



void WorkDlg::OnFaceRecognize()
{
	// TODO: �ڴ���������������
	ShellExecute(NULL,"open",
		"E:\\������ϵͳ\\FaceRegSystem\\Debug\\FaceRegSystem.exe",
		NULL,
		NULL,SW_SHOWNORMAL);
}



//����־
void WorkDlg::OnOpenDoc()
{
	// TODO: �ڴ���������������
	CString m_date = GetDate();
	CString SaveDataPath = "D:\\ʩ���ֳ������Ϣ\\��ҵ���"+m_date+".txt";

	//���ü��±��򿪹�����Ϣ
	ShellExecute(NULL,"open",(LPCSTR)SaveDataPath,NULL,
		NULL,SW_SHOWNORMAL);

}


//������־
void WorkDlg::OnOrgDoc()
{
	// TODO: �ڴ���������������
	CString SaveDataPath = "D:\\ʩ���ֳ������Ϣ";

	//���ü��±��򿪹�����Ϣ
	ShellExecute(NULL,"open",(LPCSTR)SaveDataPath,NULL,
		NULL,SW_SHOWNORMAL);
}



void WorkDlg::OnLinkBehaviorVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������



}


void WorkDlg::OnLinkMillVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������




}

void WorkDlg::OnLinkHighVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	HighIP = "192.168.1.2";
	HighPort = 0;
	HighUser = "admin";
	HighPass = "admin";
	H264_DVR_SetConnectTime(3000, 1);//���ó�������1�Σ��ȴ�ʱ��3s

	HighLoginID = H264_DVR_Login(HighIP, HighPort, 
			HighUser, HighPass, NULL, NULL,NULL);

	//������Ƶ��
	H264_DVR_CLIENTINFO playstru;

	playstru.nChannel = 0;
	playstru.nStream = 0;
	playstru.nMode = 0;
	playstru.hWnd = HighPic.m_hWnd;
	HighPlayhandle = H264_DVR_RealPlay(HighLoginID, &playstru);	

	StatusBar.SetText("��ѡ��������", 1, 0);

}


void WorkDlg::OnLinkMoreVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	


}



void WorkDlg::OnExitBehaviorVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������



}


void WorkDlg::OnExitMillVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������



}


void WorkDlg::OnExitMoreVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}


void WorkDlg::OnExitHighVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	H264_DVR_StopRealPlay(HighPlayhandle,HighPic.m_hWnd); 

}


void WorkDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialogEx::OnOK();
}


void WorkDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	HighWorkDetecting = FALSE;
	BehaviorDetecting = FALSE;
	MillDetecting = FALSE;

	KillTimer(1);
	KillTimer(2);
	Sleep(200);
	CDialogEx::OnClose();
}



void WorkDlg::OnRecordHighVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//H264_DVR_StartDVRRecord(HighPlayhandle, 0 ,SDK_RECORD_MANUAL);
	CString RecordPath = "D:\\Record\\"+GetDate()
		+"\\"+GetSaveTime();
	//��ʼ����¼��
	H264_DVR_StartLocalRecord(HighPlayhandle,
		RecordPath.GetBuffer(0),0);

}


void WorkDlg::OnStopHighRecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�رձ���¼��
	H264_DVR_StopLocalRecord(HighPlayhandle);
	AfxMessageBox("¼�ƽ���,�뵽D:\\RecordĿ¼�²鿴");
}


void WorkDlg::OnRecordBehavior()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}


void WorkDlg::OnStopBehavior()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	AfxMessageBox("¼�ƽ���,�뵽D:\\RecordĿ¼�²鿴");
}


void WorkDlg::OnMillRecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}


void WorkDlg::OnStopMillRecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	AfxMessageBox("¼�ƽ���,�뵽D:\\RecordĿ¼�²鿴");
}


void WorkDlg::OnMoreRecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}


void WorkDlg::OnStopMoreRecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	AfxMessageBox("¼�ƽ���,�뵽D:\\RecordĿ¼�²鿴");
}


void WorkDlg::OnLookDiary()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString SaveDataPath = "D:\\ʩ���ֳ������Ϣ";

	//���ü��±��򿪹�����Ϣ
	ShellExecute(NULL,"open",(LPCSTR)SaveDataPath,NULL,
		NULL,SW_SHOWNORMAL);

}
