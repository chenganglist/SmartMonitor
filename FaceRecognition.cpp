#include "stdafx.h"
#include "FaceRecognition.h"


/*****************************************************************************
								imgtxt.cpp
			˵����ѵ��ͼ�����D��att_faces�ļ����У�ÿ������Ϊһ�����ļ��ж���ͬһ���ˣ�
				  ��עΪ  personx.*pgm��ʽ����Ϊͼ���ʽΪpgm��.
				  �����jpg����Ϊ personx.*jpg��ʽ,��ȡѵ������·�����Ӧ�ı�ǩ
****************************************************************************/

map<string,int> imgtxt(string path)
{
	map<string,int>lbp;
    string folder = path;
    vector<string> subDir;
    int count = GetSubFolders(folder, subDir,lbp);
//    cout<<"count = "<<count<<endl;
	FILE *fp=fopen( "facename.txt", "w" ); //�ļ�ָ��
    //��ֻд�ļ������ļ��������ļ�������Ϊ0�������ļ����ݻ���ʧ�����ļ��������������ļ���
    //
    for (int i=0; i<count; i++)
   {
 //      cout<<subDir[i].c_str()<<endl;
	   GetSubfolder_picname(fp,subDir[i].c_str(),i);

   }
	  //д���ļ���Ҫ�ر�txt
    fclose(fp);
	return lbp;
 
}

///////////////////////////////////////////////////////////////////
///////////////�ӳ��򣺻�ȡ���ļ�·��///////////////////////
int GetSubPath(string& folder, vector<string>& subFolders)
{
	int num=0;
	//map<string,int>sub_folder_name;
   subFolders.clear();
   WIN32_FIND_DATAA fileFindData;
   string nameWC = folder + "\\*";
   HANDLE hFind = ::FindFirstFileA(nameWC.c_str(), &fileFindData);
   if (hFind == INVALID_HANDLE_VALUE)
   {
     //cout<<"folder path error...."<<endl;
      system("pause");
      return 0;
   }
  
  do 
  {
	 
    if (fileFindData.cFileName[0] == '.')
  {
     continue; // filter the '..' and '.' in the path
   }
   
  if (fileFindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
  {
     subFolders.push_back(folder+"\\"+fileFindData.cFileName);
   }
  _mkdir(fileFindData.cFileName);
  
  num++;
 } while (::FindNextFileA(hFind, &fileFindData));


   FindClose(hFind);

   return (int)subFolders.size();
}

///////////////////////////////////////////////////////////////
/////////////////////�ӳ��򣺻�ȡ���ļ���·��/////////////////////////////////////////////
int GetSubFolders(string& folder, vector<string>& subFolders ,map<string,int>&sub_folder_name)
{
	int num=0;
	//map<string,int>sub_folder_name;
   subFolders.clear();
   WIN32_FIND_DATAA fileFindData;
   string nameWC = folder + "\\*";
   HANDLE hFind = ::FindFirstFileA(nameWC.c_str(), &fileFindData);
   if (hFind == INVALID_HANDLE_VALUE)
   {
     //cout<<"folder path error...."<<endl;
      system("pause");
      return 0;
   }
  
  do 
  {
	 
    if (fileFindData.cFileName[0] == '.')
  {
     continue; // filter the '..' and '.' in the path
   }
   
  if (fileFindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
  {
     subFolders.push_back(folder+"\\"+fileFindData.cFileName);
   }
  _mkdir(fileFindData.cFileName);
  sub_folder_name.insert(pair<string,int>(fileFindData.cFileName,num));
  num++;
 } while (::FindNextFileA(hFind, &fileFindData));


   FindClose(hFind);

   return (int)subFolders.size();
}

//---------------------��ȡ���ļ�����--------------------------
void GetSubfolder_picname(FILE *fp,string dir_path,int subi)
{
    Directory dir;
	string dir_path_new=dir_path+"\\";
    vector<string> fileNames = dir.GetListFiles(dir_path_new, "*.jpg", false);
    for(int i = 0; i < fileNames.size(); i++)
    {
        string fileName = fileNames[i];
        string fileFullName = dir_path_new + fileName;
        const char *cstr = fileFullName.c_str();
      //  cout<<"file name:"<<fileName<<endl;
      //  cout<<"file paht:"<<fileFullName<<endl;
        //fileName:x.png
        //fileFullName:trainpic/x.png
        //Image processing
       // Mat pScr;
       // pScr=imread(fileFullName,1);
        fprintf(fp,"%s;%d\r\n",cstr,subi);  //д�����ݣ�д���ļ������ϱ�ǩsubi
    }
}

//---------------------��ȡ���ļ�����(��Ҫ��ǩ)--------------------------
void GetSubfolder_picname_non_lable(FILE *fp,string dir_path)
{
    Directory dir;
	string dir_path_new=dir_path+"\\";
    vector<string> fileNames = dir.GetListFiles(dir_path_new, "*.jpg", false);
    for(int i = 0; i < fileNames.size(); i++)
    {
        string fileName = fileNames[i];
        string fileFullName = dir_path_new + fileName;
        const char *cstr = fileFullName.c_str();
      //  cout<<"file name:"<<fileName<<endl;
      //  cout<<"file paht:"<<fileFullName<<endl;
        //fileName:x.png
        //fileFullName:trainpic/x.png
        //Image processing
       // Mat pScr;
       // pScr=imread(fileFullName,1);
        fprintf(fp,"%s\r\n",cstr);  //д�����ݣ�д���ļ������ϱ�ǩsubi
    }
}


/*****************************************************************************
								prepareORL.cpp
****************************************************************************/
void prepareORL(string path)
{
	string folder = path;
    vector<string> subDir;
	int count = GetSubPath(folder,subDir);
	

	FILE *fp=fopen( "ORLfacename.txt", "w" ); //�ļ�ָ��
	for (int i=0; i<count; i++)
	{
	   GetSubfolder_picname_non_lable(fp,subDir[i].c_str());
	}

	fclose(fp);
	
	//FILE *fp1=fopen( "ORLfacename.txt", "r" ); //�ļ�ָ��
 // 	char buf[100]; /* ������ */
	// /* ÿ�ζ���һ�� */
	//while(fgets(buf, 100, fp1) != NULL)
	//{
	//	int len =strlen(buf);
	//	buf[len - 1] = '\0'; 
	//	string path =buf;
	//	cout<<path<<endl;
	//	replaceImg(path);
	//	system("pause");
	//}
	//fclose(fp1);

	string filename ="ORLfacename.txt" ;
	std::ifstream file(filename.c_str(), ifstream::in);
	string line;
	while(1){
	getline(file, line);
	if(line=="")
		break;
	
	replaceImg(line);
	}
	
}

void replaceImg(string path)
{
	CascadeClassifier faceDetector; 
	faceDetector.load("haarcascade_frontalface_alt2.xml");
	Mat temp = imread(path);
//	//imshow("temp",temp);
//	waitKey();
	vector<Rect> faces; 
	faceDetector.detectMultiScale(temp,faces,1.1f,4, 4,Size(30,30));
	if(faces.size()!=0){
	Mat face_img = (temp)(faces[0]);
    resize(face_img, face_img, Size(150,150));
	imwrite(path,face_img);
	}
}

/*****************************************************************************
								Process_face.cpp
1�����ø����Ĳ�����ͼ����Ѱ��Ŀ�꣬��������
2������ʹ��Haar����������LBP��������������⣬���������۾������ӣ��������
3��Ϊ��ʹ�����죬����ͼ����ʱ����С��'scaledWidth'����ΪѰ������200�ĳ߶��Ѿ��㹻�ˡ�
****************************************************************************/
const double DESIRED_LEFT_EYE_X = 0.16;     // ���ƴ���������Ķ��ٲ����ǿɼ���
const double DESIRED_LEFT_EYE_Y = 0.14;
const double FACE_ELLIPSE_CY = 0.40;
const double FACE_ELLIPSE_W = 0.50;         // Ӧ������Ϊ0.5
const double FACE_ELLIPSE_H = 0.80;         // ������������ĸ߶�



Mat Process_face(Mat origin_img)
{
	CascadeClassifier faceDetector;  
	try{  
		faceDetector.load("haarcascade_frontalface_alt2.xml");  
	}catch (cv::Exception e){}  
	if(faceDetector.empty())  
	{  
		//cerr<<"error:couldn't load face detector (";  
		//cerr<<"haarcascade_frontalface_alt2.xml)!"<<endl;  
		exit(1);  
	}  
	Mat img=origin_img;
	//Mat or_img=img.clone();
	Mat gray;
	if (img.channels() == 3) {
		cvtColor(img, gray, CV_BGR2GRAY);
	}
	else if (img.channels() == 4) {
		cvtColor(img, gray, CV_BGRA2GRAY);
	}
	else {
		// ֱ��ʹ������ͼ�񣬼�Ȼ���Ѿ��ǻҶ�ͼ��
		gray = img;
	}
	Rect largestObject;
	const int scaledWidth=320;
	detectLargestObject(img,faceDetector,largestObject,scaledWidth);
	//rectangle(img,Point(largestObject.x,largestObject.y),Point(largestObject.x+largestObject.width,largestObject.y+largestObject.height),Scalar(0,0,255),2,8);
	if((largestObject.x==-1)||(largestObject.y==-1)||(largestObject.width==-1)||(largestObject.height==-1))
	{
		resize(gray,gray,Size(200,200));//��С��һ����64*64�����û�ҵ�������ԭͼ
		return gray;
	}
	else
	{
		Rect roi(largestObject.x, largestObject.y, largestObject.width, largestObject.height);//Rect roi(x, y, w, h);
		//getPreprocessedFace
		////imshow("img",img);
		Mat roi_of_image = gray(roi);
	//	resize(gray,gray,Size(64,64));//���ҵ�������һ����64*64
		resize(roi_of_image,roi_of_image,Size(200,200));//���ҵ�������һ����64*64
		return roi_of_image;
		/*//imshow("roi",roi_of_image);
		waitKey();*/
	}
}

void detectObjectsCustom(const Mat &img, CascadeClassifier &cascade, vector<Rect> &objects, int scaledWidth, int flags, Size minFeatureSize, float searchScaleFactor, int minNeighbors)
{

	//��������ͼ���ǻҶ�ͼ��,��ô��BRG����BGRA��ɫͼ��ת��Ϊ�Ҷ�ͼ��
	Mat gray;
	if (img.channels() == 3) {
		cvtColor(img, gray, CV_BGR2GRAY);
	}
	else if (img.channels() == 4) {
		cvtColor(img, gray, CV_BGRA2GRAY);
	}
	else {
		// ֱ��ʹ������ͼ�񣬼�Ȼ���Ѿ��ǻҶ�ͼ��
		gray = img;
	}

	// ���ܵ���Сͼ���Ǽ�������
	Mat inputImg;

	float scale = img.cols / (float)scaledWidth;
	if (img.cols > scaledWidth) {
		// ��Сͼ�񲢱���ͬ���Ŀ�߱�
		int scaledHeight = cvRound(img.rows / scale);
		resize(gray, inputImg, Size(scaledWidth, scaledHeight));
	}
	else {
		// ֱ��ʹ������ͼ�񣬼�Ȼ���Ѿ�С��
		inputImg = gray;
	}

	//��׼�����ȺͶԱȶ������ư���ͼ��
	Mat equalizedImg;
	equalizeHist(inputImg, equalizedImg);

	// ��С�Ļ�ɫͼ���м���Ŀ��
	cascade.detectMultiScale(equalizedImg, objects, searchScaleFactor, minNeighbors, flags, minFeatureSize);
//	cascade.detectMultiScale(equalizedImg,objects,1.1f,4, 4,Size(30,30));

	// ���ͼ���ڼ��֮ǰ��ʱ�ı���С�ˣ���Ŵ���ͼ��
	if (img.cols > scaledWidth) {
		for (int i = 0; i < (int)objects.size(); i++ ) {
			objects[i].x = cvRound(objects[i].x * scale);
			objects[i].y = cvRound(objects[i].y * scale);
			objects[i].width = cvRound(objects[i].width * scale);
			objects[i].height = cvRound(objects[i].height * scale);
		}
	}

	//ȷ��Ŀ��ȫ����ͼ���ڲ����Է����ڱ߽��� 
	for (int i = 0; i < (int)objects.size(); i++ ) {
		if (objects[i].x < 0)
			objects[i].x = 0;
		if (objects[i].y < 0)
			objects[i].y = 0;
		if (objects[i].x + objects[i].width > img.cols)
			objects[i].x = img.cols - objects[i].width;
		if (objects[i].y + objects[i].height > img.rows)
			objects[i].y = img.rows - objects[i].height;
	}

	// ���ؼ�⵽���������Σ��洢��objects��
}

void detectLargestObject(const Mat &img, CascadeClassifier &cascade, Rect &largestObject, int scaledWidth)
{
	
	int flags = CV_HAAR_FIND_BIGGEST_OBJECT;// | CASCADE_DO_ROUGH_SEARCH;
	Size minFeatureSize = Size(20, 20);
	float searchScaleFactor = 1.1f;
	int minNeighbors = 1;
	vector<Rect> objects;
	detectObjectsCustom(img, cascade, objects, scaledWidth, flags, minFeatureSize, searchScaleFactor, minNeighbors);
	if (objects.size() > 0) {
		largestObject = (Rect)objects.at(0);
	}
	else {
		largestObject = Rect(-1,-1,-1,-1);
	}
}

/*********************************************************************************************
                                    read_csv.cpp
**************************************************************************************************/

void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels,map<string,int>lbptest, char separator) 
{
	std::ifstream file(filename.c_str(), ifstream::in);
	if (!file) {
		string error_message ="No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, classlabel;
	int num_name_use=0;
	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, path, separator);//�ѣ�ǰ���ͼƬ·����ȡ����
		getline(liness, classlabel);//�ѣ�����ı�ǩ��ȡ����
		if(!path.empty()&&!classlabel.empty()) {
			Mat image_process_again=labelchoice(atoi(classlabel.c_str()),path,lbptest,num_name_use);//atoi��label���ַ���ת��������
			images.push_back(image_process_again);
			labels.push_back(atoi(classlabel.c_str()));
			num_name_use++;
		}
	}
}

Mat labelchoice(int lab_num,string path,map<string,int>name,int num_name_use)
{
	char buffer[40];
	char *intStr = itoa(num_name_use,buffer,10);//itoa������ת�����ַ�����10����ʮ����
	string str = string(intStr);
	string name_of_human,path_new;

	replaceImg(path);

	Mat img_process=imread(path);//����ԭʼͼƬ

	Mat retinexImg = retinex(img_process);

	Mat img_process_last=Process_face(retinexImg);//��ԭʼͼ���ȡ����������һ����64*64


	for (map<string,int>::iterator it=name.begin();it!=name.end();++it)
	{
		if (it->second==lab_num)
		{
			name_of_human=it->first;

		}
	}


	path_new=name_of_human+"\\"+str+".jpg";
	imwrite(path_new,img_process_last );
	return img_process_last;
}



/********************************************************************************
                                  retin.cpp
							   ���߶�Retinexͼ����ǿ����
                                srcΪ������ͼ��
                                sigmaΪ��˹ģ����׼��
                                scaleΪ�Աȶ�ϵ��
*********************************************************************************/
void SSR(IplImage* src,int sigma,int scale)
{
        IplImage* src_fl  = cvCreateImage(cvGetSize(src),IPL_DEPTH_32F,src->nChannels);
        IplImage* src_fl1 = cvCreateImage(cvGetSize(src),IPL_DEPTH_32F,src->nChannels);
        IplImage* src_fl2 = cvCreateImage(cvGetSize(src),IPL_DEPTH_32F,src->nChannels);
         float a=0.0,b=0.0,c=0.0;
        cvConvertScale(src,src_fl,1.0,1.0);//ת����Χ������ͼ��Ԫ������1.0��֤cvlog����
        cvLog(src_fl,src_fl1);
        
        cvSmooth(src_fl,src_fl2,CV_GAUSSIAN,0,0,sigma);        //SSR�㷨�ĺ���֮һ����˹ģ��

        cvLog(src_fl2,src_fl2);
        cvSub(src_fl1,src_fl2,src_fl);//Retinex��ʽ��Log(R(x,y))=Log(I(x,y))-Log(Gauss(I(x,y)))

        //����ͼ��ľ�ֵ�����SSR�㷨�ĺ���֮��
        //ʹ��GIMP��ת��������ʹ��ͼ��ľ�ֵ�������Ϣ���б任
        //û���������ж�
        CvScalar mean;
        CvScalar dev;
        cvAvgSdv(src_fl,&mean,&dev,NULL);//����ͼ��ľ�ֵ�ͱ�׼��
        double min[3];
        double max[3];
        double maxmin[3];
        for (int i=0;i<3;i++)
        {
                min[i]=mean.val[i]-scale*dev.val[i];
                max[i]=mean.val[i]+scale*dev.val[i];
                maxmin[i]=max[i]-min[i];
        }
        float* data2=(float*)src_fl->imageData;
        for (int i=0;i<src_fl2->width;i++)
        {
                for(int j=0;j<src_fl2->height;j++)
                {
                        data2[j*src_fl->widthStep/4+3*i+0]=255*(data2[j*src_fl->widthStep/4+3*i+0]-min[0])/maxmin[0];
                        data2[j*src_fl->widthStep/4+3*i+1]=255*(data2[j*src_fl->widthStep/4+3*i+1]-min[1])/maxmin[1];
                        data2[j*src_fl->widthStep/4+3*i+2]=255*(data2[j*src_fl->widthStep/4+3*i+2]-min[2])/maxmin[2];
                }
        }

        cvConvertScale(src_fl,src,1,0);
        cvReleaseImage(&src_fl);
        cvReleaseImage(&src_fl1);
        cvReleaseImage(&src_fl2);
}

Mat retinex(Mat src)
{
		
		IplImage* Iplsrc = &src.operator IplImage(); 
		IplImage* src1=cvCreateImage(cvGetSize(Iplsrc),IPL_DEPTH_32F,Iplsrc->nChannels);
		 cvConvertScale(Iplsrc,src1,1.0/255,0);
        SSR(Iplsrc,30,2);
		Mat srcNew(Iplsrc);
		return srcNew;

}

/********************************************************************
                           faceRecognition.cpp
********************************************************************/

void TrainFaceRecognizer() {
	//-------CSV�ļ��Ĵ���facename.txt
	map<string,int>lbp_test=imgtxt("D:\\ORL");
	//--------------------------------
	string fn_csv = string("facename.txt");
	vector<Mat> images;//����ѵ��ͼƬ
	vector<int> labels;//����ѵ��ͼƬ��Ӧ�ı�ǩ
	try {
		read_csv(fn_csv, images, labels,lbp_test);//lbp_test:ͼƬ�ͱ�ǩ��ӳ��
	} catch (cv::Exception& e) {
		cerr <<"Error opening file "<< fn_csv <<". Reason: "<< e.msg << endl;
		// nothing more we can do
		exit(1);
	}
	if(images.size()<=1) {
		string error_message ="This demo needs at least 2 images to work. Please add more images to your data set!";
		CV_Error(CV_StsError, error_message);
	}
	Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
	for(int i=0;i<images.size();i++)
	{
		resize(images[i],images[i],Size(200,200));
	}
//	Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
//	Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
	model->train(images, labels);
	model->save("haar_facename.xml"); //���ɷ�����
}

int GetMin(int a,int b,int c)
{
	int min=a;
	if(b<min)
	{
		min=b;
	}
	if(c<min)
	{
		min =c;
	}
	return min;

}


vector<string> RecognizeFace(Mat src)
{
	
	
	map<string,int>lbp_test=imgtxt("D:\\ORL");
	Mat retinexImg = retinex(src);
	//--------------------Process_image------------------
	Mat testSample1=Process_face(retinexImg);//�ҵ�����ͼ�е�����
//	Mat testSample1 = retinex(testSample);
	Ptr<FaceRecognizer> model2 = createLBPHFaceRecognizer();
//	Ptr<FaceRecognizer> model3 = createFisherFaceRecognizer();
//	Ptr<FaceRecognizer> model4 = createEigenFaceRecognizer();
	model2->load("haar_facename.xml");//Ҫʶ��ʱ���ط�����
//	int predictedLabel = model2->predict(testSample1);//ʶ�𵽵���
	int predictedLabel;
	double confident;
	model2->predict(testSample1,predictedLabel,confident);//ʶ�𵽵���

	vector<string> str;
	for (map<string,int>::iterator it=lbp_test.begin();it!=lbp_test.end();++it)
	{
		if (it->second==predictedLabel)
		{
		//	cout<<"�ñ�ǩ��Ӧ�����������Ϊ��"<<it->first<<endl;//�����Ӧ������
		//	cout<<"�ñ�ǩΪ��"<<it->first<<"���Ŷ�Ϊ��"<<confident<<endl;//�����Ӧ������
			str.push_back(it->first);
			str.push_back(to_string((long double)confident));
			str.push_back(to_string((long double)predictedLabel));
		}
	}

	String result_message = format("Predicted class = %d ", predictedLabel);//ʶ�������ڼ��ࡣ����������ɸ�����������

//	return result_message;

		

	return str;
}


/*******************************************************************
���룺10֡ͼƬ��ÿһ֡���500,���Ŷȵ���ֵ
��������ֵ�������Ա���֣��浽vector<string>
****************************************************************/
vector<String> GetAttendance(vector<Mat> vecImg,int ConfThreshold)
{
	map<string,int>lbp_test=imgtxt("D:\\ORL");

	vector<int> resultLable;
	vector<string> resultName;
	CascadeClassifier faceDetector;
	faceDetector.load("haarcascade_frontalface_alt2.xml");
	for(int i=0;i<vecImg.size();i++)
	{
		Mat src = vecImg[i];
		vector<Rect> faces;//�洢��⵽������
		faceDetector.detectMultiScale(src,faces,1.1f,4, 1,Size(30,30));
        //faceDetector.detectMultiScale(src,faces);
	 	for( int j=0; j<faces.size(); j++ )
		{
			Mat faceRcg = src(faces[j]);
			vector<string> name =RecognizeFace(faceRcg);
			if(name.size()>0 && atoi(name[1].c_str())<ConfThreshold)
			{
				resultLable.push_back(atoi(name[2].c_str()));
				putText(src, name[0], Point(faces[j].x+faces[j].width,faces[j].y), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 3);
				putText(src, name[1], Point(faces[j].x+faces[j].width,faces[j].y+faces[j].height), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 3);	
			}
		 }
	  //cout<<"faceSize:"<<faces.size()<<endl;
	  //imshow("Recg",src);
	  //waitKey();
	}
	//ɾ��vector<int>�е��ظ�Ԫ��
	sort(resultLable.begin(),resultLable.end()); 
    vector<int>::iterator iter=unique(resultLable.begin(),resultLable.end()); 
	resultLable.erase(iter,resultLable.end()); 

	for (int m =0;m<resultLable.size();m++)
	{
		for (map<string,int>::iterator it=lbp_test.begin();it!=lbp_test.end();++it)
		{
			if (it->second==resultLable[m])
			{
				resultName.push_back(it->first);
			}
		}
	}

	return resultName;

}