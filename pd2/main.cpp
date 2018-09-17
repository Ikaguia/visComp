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

void onMouseReq1( int event, int x, int y, int, void *ptr){
	auto &things = *((pair<pair<Point,Point>, int>*)ptr);
	auto &p1 = things.ff.ff;
	auto &p2 = things.ff.ss;
	auto &draw = things.ss;


	if(event == EVENT_LBUTTONDOWN){
		if(draw == 1){//first point already selected
			// cout << "setting p2: " << x << ", " << y << endl;
			p2.x = x;
			p2.y = y;
			draw = 2;

			cout << "Distância medida: " << hypot(abs(p1.x-p2.x), abs(p1.y-p2.y)) << "px" << endl;
		}
		else{//both or no points selected
			// cout << "setting p1: " << x << ", " << y << endl;
			p1.x = p2.x = x;
			p1.y = p2.y = y;
			draw = 1;
		}
	}
	else{
		if(draw == 1){
			p2.x = x;
			p2.y = y;
			// cout << "setting mouse: " << x << ", " << y << endl;
		}
	}
}
void runReq1(){
	VideoCapture cap(0); // open the default camera
	if(!cap.isOpened()) exit(1);

	pair<pair<Point,Point>, int> things;

	Point &p1 = things.ff.ff;
	Point &p2 = things.ff.ss;
	int &draw = things.ss;

	Scalar drawColor(0, 0, 255);

	Mat inFrame, outFrame;

	namedWindow("frame", 1);
	setMouseCallback("frame", onMouseReq1, &things);

	while(1){
		cap >> inFrame; // get a new frame from camera
		outFrame = inFrame.clone();

		// W(draw);
		if(draw) line(outFrame, p1, p2, drawColor, 2, 8);

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
		// case 1:{
		// 	cout << "Requisito 1:" << endl;

		// 	checkArgs(argc, argv, 1, "ARQUIVO_DE_IMAGEM");
		// 	string imagefile = argv[2];

		// 	runReq1(imagefile);
		// 	break;
		// }
		case 1:{
			cout << "Requisito 1:" << endl;
			runReq1();
			break;
		}
		default:{
			cerr << "Requisito " << req << " não existente/implementado" << endl;
			exit(1);
			break;
		}
	}
}
