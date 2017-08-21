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
	Mat frameWithFish;
	for (;;){
		cap >> frame;
		cvtColor(frame, frameWithFish, CV_BGR2GRAY);
		
	}
	return 0;
}
