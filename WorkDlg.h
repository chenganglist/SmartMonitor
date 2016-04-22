#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"

//��̨����
#define WM_HIDE_RUN  (WM_USER+102)
// WorkDlg �Ի���

class WorkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(WorkDlg)

public:
	WorkDlg(CWnd* pParent = NULL); //��׼���캯��
	virtual ~WorkDlg();

    // �Ի�������
	enum { IDD = IDD_CAMERADLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);   
	// DDX/DDV ֧��
	HICON m_hIcon;
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
	
public:
	//��̨����
	LRESULT OnHideRun(WPARAM wParam,LPARAM lParam);
	POINT Old;
	//�������
	afx_msg void OnDestroy();
	//��ʼ���������
	virtual BOOL OnInitDialog();
	//��󻯣���С��
	afx_msg void OnSize(UINT nType,int cx,int cy);
	
	//�߿ռ������ͷ����
	afx_msg void OnLinkHighVideo();
	//�˳��߿ռ��
	afx_msg void OnExitHighVideo();

	//ѡ��������
	afx_msg void OnSelectMoniterArea();
	//ȡ���������
	afx_msg void OnCancelSelect();


	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEmptyGrid();
	afx_msg void OnRefresh();


	//������
	CListCtrl m_gridcom;
	int m_ReceiveNum;
	BYTE m_ReceiveByte[14];
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm();
	CMSComm m_Comm;
	CComboBox m_ComSel;
	afx_msg void OnComSelect();
	afx_msg void OnDetectAngle();
	afx_msg void OnAngleStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);


public:
	afx_msg void OnRunInBack();
	afx_msg void OnExit();
	afx_msg void OnStartPhoneSystem();
	afx_msg void OnFaceRecognize();

	afx_msg void OnOpenDoc();
	afx_msg void OnOrgDoc();

	afx_msg void OnLinkBehaviorVideo();
	afx_msg void OnLinkMillVideo();
	afx_msg void OnLinkMoreVideo();
	afx_msg void OnExitBehaviorVideo();
	afx_msg void OnExitMillVideo();
	afx_msg void OnExitMoreVideo();
	virtual void OnOK();

public:
	Mat NoPic;
	afx_msg void OnClose();
	afx_msg void OnRecordHighVideo();
	afx_msg void OnStopHighRecord();
	afx_msg void OnRecordBehavior();
	afx_msg void OnStopBehavior();
	afx_msg void OnMillRecord();
	afx_msg void OnStopMillRecord();
	afx_msg void OnMoreRecord();
	afx_msg void OnStopMoreRecord();
	//�鿴��¼
	afx_msg void OnLookDiary();


};
