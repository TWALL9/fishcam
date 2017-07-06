#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv){
	VideoCapture cap(0);
	if(!cap.isOpened()){
		cout << "cannot open camera!" << endl;
		return -1;
	}
	Mat frame;
	Mat edges;
	for (;;){
		cap >> frame;
		cvtColor(frame, edges, CV_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
		Canny(edges, edges, 0, 30, 3);
		if(waitKey(30) >= 0)
			break;
	}
	return 0;
}
