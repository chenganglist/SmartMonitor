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
	IsHighPlaying = FALSE;
	HighVideoPath =
		_T("http://admin:admin@192.168.1.2/ipcam/mpeg4.cgi");

	BehaviorVideoPath =
		_T("http://admin:admin@192.168.1.2/ipcam/mpeg4.cgi");

	MillVideoPath =
		_T("http://admin:admin@192.168.1.2/ipcam/mpeg4.cgi");

	MoreVideoPath =
		_T("http://admin:admin@192.168.1.2/ipcam/mpeg4.cgi");

	IsHighPlaying = FALSE;
	IsMillPlaying = FALSE;
	IsHighPlaying = FALSE;
	HighWorkDetecting = FALSE;
	BehaviorDetecting = FALSE;
	MillDetecting = FALSE;
	MillCollecting = FALSE;
	BehaviorCollecting = FALSE;
	HighCollecting = FALSE;
	MoreCollecting = FALSE;
	MillRecording = FALSE;
	BehaviorRecording = FALSE;
	HighRecording = FALSE;
	MoreRecording = FALSE;

	CString Date= "D:\\Record\\"+GetDate();
	CreateDirectory(Date,NULL);

}


WorkDlg::~WorkDlg()
{

}


void WorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, HighPic);
	DDX_Control(pDX, IDC_LIST1_HIGH, m_highgrid);
	DDX_Text(pDX, IDC_EDIT1, HighVideoPath);
	DDX_Control(pDX, IDC_LIST1, m_gridcom);
	DDX_Control(pDX, IDC_MSCOMM1, m_Comm);
	DDX_Control(pDX, IDC_COMBO1, m_ComSel);
	DDX_Text(pDX, IDC_EDIT2, BehaviorVideoPath);
	DDX_Text(pDX, IDC_EDIT4, MillVideoPath);
	DDX_Text(pDX, IDC_EDIT5, MoreVideoPath);
	DDX_Control(pDX, IDC_LIST1_HIGH2, m_BehaviorGrid);
	DDX_Control(pDX, IDC_LIST1_HIGH3, m_MillGrid);
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
	ON_BN_CLICKED(IDC_BUTTON11, &WorkDlg::OnSelectHighVideo)
	ON_BN_CLICKED(IDC_BUTTON12, &WorkDlg::OnSelectHighVideo)
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
	ON_BN_CLICKED(IDC_BUTTON8, &WorkDlg::OnSelectBehaviorPath)
	ON_BN_CLICKED(IDC_BUTTON25, &WorkDlg::OnSelectMillPath)
	ON_BN_CLICKED(IDC_BUTTON28, &WorkDlg::OnSelectMorePath)
	ON_BN_CLICKED(IDC_BUTTON21, &WorkDlg::OnLinkBehaviorVideo)
	ON_BN_CLICKED(IDC_BUTTON27, &WorkDlg::OnLinkMillVideo)
	ON_BN_CLICKED(IDC_BUTTON30, &WorkDlg::OnLinkMoreVideo)
	ON_BN_CLICKED(IDC_BUTTON9, &WorkDlg::OnExitBehaviorVideo)
	ON_BN_CLICKED(IDC_BUTTON26, &WorkDlg::OnExitMillVideo)
	ON_BN_CLICKED(IDC_BUTTON29, &WorkDlg::OnExitMoreVideo)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON39, &WorkDlg::OnPausePlay)
	ON_BN_CLICKED(IDC_BUTTON40, &WorkDlg::OnResumePlay)
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
	m_choosing = FALSE;
	

	//״̬��
	m_StatusBar.Create(WS_CHILD|WS_VISIBLE|SBT_OWNERDRAW, 
		CRect(0,0,0,0), this, 0);

	int strPartDim[5]= {100,300,500,700,-1}; //�ָ�����,ʹ������
	m_StatusBar.SetParts(5, strPartDim);

	//����״̬���ı�
	m_StatusBar.SetText("ϵͳ״̬", 0, 0);
	m_StatusBar.SetText("����", 1, 0);
	m_StatusBar.SetText("����", 2, 0);
	m_StatusBar.SetText("����", 3, 0);
	m_StatusBar.SetText("����", 4, 0);

	m_StatusBar.ShowWindow(SW_SHOW);


	//onsize��С���ŶԻ����С�仯���仯
	CRect rectSize;     
	GetClientRect(&rectSize);     //ȡ�ͻ�����С   
	Old.x=rectSize.right-rectSize.left; 
	Old.y=rectSize.bottom-rectSize.top; 


	InitializeCriticalSection(&DetectionCritical);

	//����list��ʾ
	m_highgrid.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);

	m_highgrid.ModifyStyle( 0, LVS_REPORT );

	m_highgrid.InsertColumn(0,"���ʱ��");        //������
	m_highgrid.InsertColumn(1,"�߿���ҵ���");   
	   
	m_highgrid.SetColumnWidth(0,125);       //�����еĿ�ȡ�
	m_highgrid.SetColumnWidth(1,160);


	//��Ϊ
	m_BehaviorGrid.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);

	m_BehaviorGrid.ModifyStyle( 0, LVS_REPORT );

	m_BehaviorGrid.InsertColumn(0,"���ʱ��");        //������
	m_BehaviorGrid.InsertColumn(1,"ʩ���ֳ���Ϊ���");   

	m_BehaviorGrid.SetColumnWidth(0,125);       //�����еĿ�ȡ�
	m_BehaviorGrid.SetColumnWidth(1,160);


	//��ĥ��
	m_MillGrid.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);

	m_MillGrid.ModifyStyle( 0, LVS_REPORT );

	m_MillGrid.InsertColumn(0,"���ʱ��");        //������
	m_MillGrid.InsertColumn(1,"��ĥ����ҵ���");   

	m_MillGrid.SetColumnWidth(0,125);       //�����еĿ�ȡ�
	m_MillGrid.SetColumnWidth(1,160);


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

	SetTimer(2,60000,NULL);

	//SetTimer(3,100,NULL);�����������Զ���������ͷ
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void WorkDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������

	CDialogEx::OnPaint();	
}

//ѡ���
void WorkDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_choosing)
	{
		if (m_Dot.size( )!=4)
		{
			m_Dot.push_back(point);
		}
	}
	
	CDialogEx::OnLButtonDown(nFlags, point);
}

//��ʼѡ������ѡ��
void WorkDlg::OnSelectMoniterArea()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_choosing = TRUE;
	m_Dot.clear();
	PointArray.clear();
	DrawToScreen(HighPic,HighImg);
}

//ȡ��ѡ��
void WorkDlg::OnCancelSelect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Dot.clear();
	m_choosing = FALSE;
	PointArray.clear();
	//����ѡ�����򵽿ؼ���
}

//ȷ��ѡ��
void WorkDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_Dot.size()==4)
	{
		//��picture�ؼ��л�ͼ
		int width;
		int height;
		CRect tempRect;
		HighPic.GetWindowRect(&tempRect);
		ScreenToClient(tempRect);
		PointArray.clear();
		for(int i=0;i<4;i++)
		{
			POINT Adder;
			Adder.x = (tempRect.TopLeft()).x;
			Adder.y = (tempRect.TopLeft()).y;
			POINT m_ExactDot;
			//ͼƬ�ؼ��ϵ�����
			m_ExactDot.x = m_Dot[i].x - Adder.x;
			m_ExactDot.y = m_Dot[i].y - Adder.y;

			if (HighImg.empty()==FALSE)
			{
				width = HighImg.cols;
				height = HighImg.rows;
			}
			else
			{
				return;
			}
	     
			POINT m_RealDot;
			m_RealDot.x = m_ExactDot.x*width/tempRect.Width();
			m_RealDot.y = m_ExactDot.y*height/tempRect.Height();
			//ԭͼƬ�ϵ���ʵ��λ
			PointArray.push_back(cvPoint(m_RealDot.x,m_RealDot.y));
		
		}
		//OnLButtonUpҪ�޸�
		if (m_choosing==TRUE)
		{
			Mat imgCopy = HighImg.clone();
			DrawSelectedArea(&(IplImage)imgCopy,PointArray);
			//����ѡ�����򵽿ؼ���
			DrawToScreen(HighPic,imgCopy);
			m_choosing = FALSE;
		}
	
	}
	CDialogEx::OnLButtonUp(nFlags, point);

}


void WorkDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	KillTimer(1);

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
	m_highgrid.DeleteAllItems();
	m_gridcom.DeleteAllItems();
	m_BehaviorGrid.DeleteAllItems();
	m_MillGrid.DeleteAllItems();
	
	UpdateData(FALSE);
}

void WorkDlg::OnRefresh()
{
	// TODO: �ڴ���������������
	Invalidate(TRUE);

}

void WorkDlg::OnSelectHighVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		NULL,AfxGetMainWnd()); //open

	if (dlg.DoModal()==IDOK)
	{
		HighVideoPath = dlg.GetPathName();

		UpdateData(FALSE);
	}

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
					static long LastTime = 0;
					static long PresentTime = 0;
					static long Span = 0;
					PresentTime = time(0);
					Span = PresentTime - LastTime;
					 if (Span>120)
					 {
						LastTime = PresentTime;
						WriteToCommandLine("7");
						Mat Gun = imread("NoPic");
						cvSaveImage("D:\\ʩ���ֳ������Ϣ\\notificationPhoto\\Gun.jpg",
							&(IplImage)Gun);
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


	if (nIDEvent==2)
	{
		OnPausePlay();
		Sleep(200);
		OnResumePlay();
	}

	if (nIDEvent==3)
	{
		 KillTimer(3);
		 OnLinkHighVideo();
		 OnLinkBehaviorVideo();
		 OnLinkMillVideo();
		 OnLinkMoreVideo();
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
		"E:\\���ϵͳ�������\\NTFClient\\NTFClient.exe",
		NULL,
		NULL,SW_SHOWNORMAL);
}



void WorkDlg::OnFaceRecognize()
{
	// TODO: �ڴ���������������
	ShellExecute(NULL,"open",
		"E:\\������ϵͳ\\Debug\\Moniter.exe",
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


void WorkDlg::OnSelectBehaviorPath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		NULL,AfxGetMainWnd()); //open

	if (dlg.DoModal()==IDOK)
	{
		BehaviorVideoPath = dlg.GetPathName();

		UpdateData(FALSE);
	}


}


void WorkDlg::OnSelectMillPath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		NULL,AfxGetMainWnd()); //open

	if (dlg.DoModal()==IDOK)
	{
		MillVideoPath = dlg.GetPathName();

		UpdateData(FALSE);
	}



}


void WorkDlg::OnSelectMorePath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		NULL,AfxGetMainWnd()); //open

	if (dlg.DoModal()==IDOK)
	{
		MoreVideoPath = dlg.GetPathName();
		UpdateData(FALSE);
	}

}


void WorkDlg::OnLinkBehaviorVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	IsBehaviorPlaying = FALSE;
	BehaviorCollecting = FALSE;
	Sleep(100);

	CreateThread(NULL,0,BehaviorPlayerProc,NULL,0,NULL);
	
	if (BehaviorDetecting==FALSE)
	{
		CreateThread(NULL,0,BeheviorDetectProc,NULL,0,NULL);
	}

	CreateThread(NULL,0,BehaviorDataGetProc,
		NULL,0,NULL);

}


void WorkDlg::OnLinkMillVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	IsMillPlaying = FALSE;
	MillCollecting = FALSE;
	Sleep(100);

	
	CreateThread(NULL,0,MillPlayerProc,NULL,0,NULL);
	
	if (MillDetecting==FALSE)
	{
		CreateThread(NULL,0,MillDetectProc,NULL,0,NULL);
	}

	CreateThread(NULL,0,MillDataGetProc,NULL,0,NULL);

}

void WorkDlg::OnLinkHighVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
    IsHighPlaying = FALSE;
	HighCollecting = FALSE;
	Sleep(100);

	CreateThread(NULL,0,HighPlayerProc,NULL,0,NULL);
	
	if (HighWorkDetecting==FALSE)
	{
		CreateThread(NULL,0,HighDetectProc,NULL,0,NULL);
	}

	CreateThread(NULL,0,HighDataGetProc,
		this,0,NULL);

}


void WorkDlg::OnLinkMoreVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	IsMorePlaying = FALSE;
	MoreCollecting = FALSE;
	Sleep(100);
	CreateThread(NULL,0,MorePlayerProc,NULL,0,NULL);
	CreateThread(NULL,0,MoreDataGetProc,NULL,0,NULL);

}



void WorkDlg::OnExitBehaviorVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	IsBehaviorPlaying = FALSE;
	BehaviorDetecting = FALSE;
	BehaviorCollecting = FALSE;
	BehaviorRecording = FALSE;

}


void WorkDlg::OnExitMillVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IsMillPlaying = FALSE;
	MillDetecting = FALSE;
	MillCollecting = FALSE;
	MillRecording = FALSE;
}


void WorkDlg::OnExitMoreVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
    IsMorePlaying = FALSE;
	MoreCollecting = FALSE;
	MoreRecording = FALSE;
}


void WorkDlg::OnExitHighVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	IsHighPlaying = FALSE;
	HighWorkDetecting = FALSE;
	HighCollecting = FALSE;
	HighRecording = FALSE;

}


void WorkDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialogEx::OnOK();
}


void WorkDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	IsHighPlaying = FALSE;
	IsMillPlaying = FALSE;
	IsMorePlaying = FALSE;
	IsBehaviorPlaying = FALSE;
	MillCollecting = FALSE;
	BehaviorCollecting = FALSE;
	HighCollecting = FALSE;
	MoreCollecting = FALSE;
	HighWorkDetecting = FALSE;
	BehaviorDetecting = FALSE;
	MillDetecting = FALSE;
	MillRecording = FALSE;
	BehaviorRecording = FALSE;
	HighRecording = FALSE;
	MoreRecording = FALSE;
	KillTimer(1);
	KillTimer(2);
	Sleep(200);
	CDialogEx::OnClose();
}




void WorkDlg::OnPausePlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IsHighPlaying = FALSE;
	IsMillPlaying = FALSE;
	IsMorePlaying = FALSE;
	IsBehaviorPlaying = FALSE;


}


void WorkDlg::OnResumePlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CreateThread(NULL,0,MorePlayerProc,NULL,0,NULL);
	CreateThread(NULL,0,MillPlayerProc,NULL,0,NULL);
	CreateThread(NULL,0,HighPlayerProc,NULL,0,NULL);
	CreateThread(NULL,0,BehaviorPlayerProc,NULL,0,NULL);

}


void WorkDlg::OnRecordHighVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CreateThread(NULL,0,HighRecordProc,NULL,0,NULL);
}


void WorkDlg::OnStopHighRecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HighRecording = FALSE;
	AfxMessageBox("¼�ƽ���,�뵽D:\\RecordĿ¼�²鿴");
}


void WorkDlg::OnRecordBehavior()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CreateThread(NULL,0,BehaviorRecordProc,NULL,0,NULL);
}


void WorkDlg::OnStopBehavior()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BehaviorRecording = FALSE;
	AfxMessageBox("¼�ƽ���,�뵽D:\\RecordĿ¼�²鿴");
}


void WorkDlg::OnMillRecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CreateThread(NULL,0,MillRecordProc,NULL,0,NULL);
}


void WorkDlg::OnStopMillRecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MillRecording = FALSE;
	AfxMessageBox("¼�ƽ���,�뵽D:\\RecordĿ¼�²鿴");
}


void WorkDlg::OnMoreRecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CreateThread(NULL,0,MoreRecordProc,NULL,0,NULL);
}


void WorkDlg::OnStopMoreRecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MoreRecording = FALSE;
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
