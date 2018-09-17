#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

#define FOR(cont,start,end)	for(int (cont) = (start), cont##_END = (end);   (cont) <  cont##_END; (cont)++)
#define ROF(cont,start,end)	for(int (cont) = (end)-1, cont##_END = (start); (cont) >= cont##_END; (cont)--)
#define LOG(x)				(31 - __builtin_clz(x))
#define W(x)				cerr << "\033[31m" << #x << " = " << x << "\033[0m" << endl;

#define oo 					int(1e9)
#define ep					int(1e-9)
#define pb					emplace_back
#define ff					first
#define ss					second
#define sz(v)				ll(v.size())

using ll = long long;
using llu = unsigned ll;
using uint = unsigned;
using ii = pair<int,int>;

void checkArgs(int argc, char **argv, int argcnt, string errorMsg){
	if(argc < (argcnt + 2)){
		cerr << "Modo de uso: " << argv[0] << " " << argv[1] << " " << errorMsg << endl;
		exit(1);
	}
}

void runReq1(string filename){
	// Read image
	Mat img = imread(filename, CV_LOAD_IMAGE_COLOR);
	imshow("Image", img);
	waitKey(0);
}

void onMouse( int event, int x, int y, int, void *ptr){
	if(event != EVENT_LBUTTONDOWN) return;

	auto &things = *((pair<Mat, uchar[3]>*)ptr);

	auto &frame = things.ff;
	auto &color = things.ss;

	memcpy(color, frame.ptr(y, x), 3*sizeof(uchar));

	cout << "Click coords = {" << x << ", " << y << "}" << endl;
	cout << "Click color = {" << (int)color[0] << ", " << (int)color[1] << ", " << (int)color[2] << "}" << endl;
}

void runReq2(){
	VideoCapture cap(0); // open the default camera
	if(!cap.isOpened()) exit(1);

	pair<Mat, uchar[3]> things;
	auto &inFrame = things.ff;
	Mat outFrame;
	auto &color = things.ss;

	color[0] = uchar(-1);

	namedWindow("frame", 1);
	setMouseCallback("frame", onMouse, &things);


	uchar theColor[3];
	theColor[0] = 0;  //b
	theColor[1] = 0;  //g
	theColor[2] = 255;//r


	while(1){
		cap >> inFrame; // get a new frame from camera
		outFrame = inFrame.clone();

		if(color[0] != uchar(-1)){
			FOR(y, 0, inFrame.rows){
				FOR(x, 0, inFrame.cols){
					uchar *pix = inFrame.ptr(y, x);
					ll dist = 0;

					dist += pow(pix[0] - color[0], 2);//b
					dist += pow(pix[1] - color[1], 2);//g
					dist += pow(pix[2] - color[2], 2);//r
					if(dist < 13*13) memcpy(outFrame.ptr(y, x), theColor, sizeof(theColor));
				}
			}
		}

		imshow("frame", outFrame);
		if(waitKey(30) >= 0) break;
	}
}

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	if(argc < 2) return cerr << "Modo de uso: " << argv[0] << " REQUISITO [ARGUMENTOS DO REQUISITO]" << endl, 0;
	uint req = atoi(argv[1]);

	switch(req){
		case 1:{
			cout << "Requisito 1:" << endl;

			checkArgs(argc, argv, 1, "ARQUIVO_DE_IMAGEM");
			string imagefile = argv[2];

			runReq1(imagefile);
			break;
		}
		case 2:{
			cout << "Requisito 2:" << endl;
			runReq2();
			break;
		}
		default:{
			cerr << "Requisito " << req << " não existente/implementado" << endl;
			exit(1);
			break;
		}
	}
}
