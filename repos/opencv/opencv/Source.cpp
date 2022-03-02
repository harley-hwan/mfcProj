#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

using namespace cv;
using namespace std;


int main(int ac, char** av) {

	ifstream in("SD_2021.12.23_17.08.59_000_4ms_amp0.log");
	if (!in) exit(1);

	typedef vector<int> Row;
	typedef vector<Row>    Matrix;

	Matrix matrix;
	string line;
	while (getline(in, line))
	{
		istringstream ss(line);
		matrix.push_back(Row(istream_iterator<int>(ss),
			istream_iterator<int>()));
	}
	Mat img(matrix.size(), matrix[1].size(), CV_8U);

	/*for (auto i : matrix) {
		for (auto j : i) {
			cout << j << " ";
			img.at<uchar>(i ,j) = j;
		}
		cout << endl;
	}*/

	//Mat img;

	for (int y = 0; y < matrix.size(); y++)
	{
		for (int x = 0; x < matrix[1].size(); x++)
		{
			img.at<uchar>(y, x) = matrix[x][y];
		}
	}

	//fstream file("SD_2021.12.23_17.08.59_000_4ms_amp0.log");
	//fstream file("SD_2021.12.23_17.08.59_000_4ms_amp1.log");
	//fstream file("SD_2021.12.23_17.08.59_000_4ms_amp2.log");
	
	//vector<vector<int> > v1;

	//if (file.is_open()) {
	//	string line;
	//	while (getline(in, line)) {
	//		istringsteam ss(line);
	//		getline(file, s);
	//		cout << s << endl;
	//		
	//	}
	//	file.close();

	//}
	//else {
	//	cout << "file open fail" << endl;
	//}


	imshow("img", img);

	waitKey(0);

	return 0;
}				