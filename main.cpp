#include <iostream>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;

//Global variables
string faceCascade = "/home/kurt/ClionProjects/Vision/haarcascade_frontalface_alt.xml";
string eyeCascade = "/home/kurt/ClionProjects/Vision/haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face, eyes;

//Vectors for eyes and face detection
vector<Rect> faceVector, eyesVector;

//Mat variables
Mat source, gray, faceROI, output;

//Load image and store it in a Mat
Mat loadImage(string path){
    Mat image = imread(path,1);
    return image;
}

//Detect a face from the loaded Mat and return a vector
vector<Rect> detectFace(Mat frame){

    vector<Rect> faceVec;

    //Checks if cascade files where loaded
    if(!face.load(faceCascade)) {
        cout << "Error loading face cascade" << endl;
        return faceVec;
    }

    //Detect the features and store it into vector face
    face.detectMultiScale(frame, faceVec, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, Size(10, 10));

    return faceVec;
}

//Detect the eyes from a loaded mat and return a vector
vector<Rect> detectEyes(Mat frame){

    vector<Rect> eyeVec;

    // checks if casacde files are loaded
    if(!eyes.load(eyeCascade)) {
        cout << "Error loading eye cascade" << endl;
        return eyeVec;
    }

    eyes.detectMultiScale(frame, eyeVec, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));

    return eyeVec;
}

//Draw function for drawing the eyes and face
void drawFace(){

    //Detect the face and eye features then store them into vectors
    faceVector = detectFace(source);

    //Draw the face shape
    for(int i = 0; i < faceVector.size(); i++){

        //Draw an ellipse around the face
        Point center(faceVector[i].x + faceVector[i].width / 2, faceVector[i].y + faceVector[i].height / 2);
        ellipse(output, center, Size(faceVector[i].width / 2, faceVector[i].height / 2), 0, 0, 360, Scalar(0, 0, 255), 2);

        //Create a Region of Interest of the face
        faceROI = gray(faceVector[i]);

        //Detect eyes
        eyesVector = detectEyes(faceROI);

        //Draw the eye shapes
        for(int j = 0; j < eyesVector.size(); j++){

            //Draw the ellipse around the eyes
            Point center(faceVector[i].x + eyesVector[j].x + eyesVector[j].width / 2, faceVector[i].y + eyesVector[j].y + eyesVector[j].height / 2);
            int radius = cvRound((eyesVector[j].width + eyesVector[j].height) * .25);
            circle(output, center, radius, Scalar(255, 0, 0), 2);
        }
    }
}

//Draw the detected features

int main(int argc, char* argv[]) {

    while(1) {

        //Load the image onto source
        source = imread("/home/kurt/ClionProjects/Vision/face10.jpg");

        //Convert to gray scale
        cvtColor(source, gray, CV_BGR2GRAY);

        //Copy source image into output/
        source.copyTo(output);

        drawFace();

        namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
        imshow("Display window", output);                   // Show our image inside it.

        if (waitKey(30) == 27) {

            destroyAllWindows();
            break;
        }
    }

    return 0;
}
