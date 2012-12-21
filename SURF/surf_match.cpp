#include <stdio.h>
#include <cv.h>
#include <ml.h>
#include <highgui.h>
#include "opencv2/nonfree/features2d.hpp"

using namespace cv;

int main( int argc, char** argv )
{
	Mat img_object = imread( "object.png", CV_LOAD_IMAGE_GRAYSCALE );
	Mat img_scene = imread( "scene.png", CV_LOAD_IMAGE_GRAYSCALE );

	int minHessian = 400;
	//-- <1> Detect the keypoints using SURF Detector
	SurfFeatureDetector detector(minHessian);
	std::vector<KeyPoint> keypoints_object, keypoints_scene;
	detector.detect( img_object, keypoints_object );
	detector.detect( img_scene, keypoints_scene );

	//-- <2> Calculate descriptors (feature vectors)
	SurfDescriptorExtractor extractor;
	Mat descriptors_object, descriptors_scene;
	extractor.compute( img_object, keypoints_object, descriptors_object );
	extractor.compute( img_scene, keypoints_scene, descriptors_scene );

	//-- <3> Matching descriptor vectors using FLANN matcher
	FlannBasedMatcher matcher;
	std::vector<DMatch> matches;
	matcher.match( descriptors_object, descriptors_scene, matches );

	double max_dist = 0; double min_dist = 100;

	//-- Quick calculation of max and min distances between keypoints
	for( int i = 0; i < matches.size(); i++ )
	{
		double dist = matches[i].distance;
		if( dist < min_dist ) min_dist = dist;
		if( dist > max_dist ) max_dist = dist;
	}
	printf("-- Max dist : %f \n", max_dist );
	printf("-- Min dist : %f \n", min_dist );

	//-- <4> Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
	std::vector< DMatch > good_matches;
	for( int i = 0; i < descriptors_object.rows; i++ )
	if( matches[i].distance < ((max_dist-min_dist)*0.65) )
		good_matches.push_back( matches[i]);

	Mat img_matches;
	drawMatches(img_object, keypoints_object,
				img_scene, keypoints_scene,
				good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
				vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

	//-- <5> Localize the object from img_1 in img_2
	std::vector<Point2f> obj;
	std::vector<Point2f> scene;
	for( size_t i = 0; i < good_matches.size(); i++ )
	{
		obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
		scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
	}
	Mat Homography = findHomography( obj, scene, CV_RANSAC );

	//-- Get the corners from the image_1 ( the object to be "detected" )
	std::vector<Point2f> obj_corners(4);
	obj_corners[0] = cvPoint( 0, 0);
	obj_corners[1] = cvPoint( img_object.cols, 0 );
	obj_corners[2] = cvPoint( img_object.cols, img_object.rows );
	obj_corners[3] = cvPoint( 0, img_object.rows );
	std::vector<Point2f> scene_corners(4);
	perspectiveTransform( obj_corners, scene_corners, Homography);

	//-- Draw lines between the corners (the mapped object in the scene - image_2 )
	Point2f offset( (float)img_object.cols, 0);
	line( img_matches, scene_corners[0] + offset, scene_corners[1] + offset, Scalar(0, 255, 0), 4 );
	line( img_matches, scene_corners[1] + offset, scene_corners[2] + offset, Scalar( 0, 255, 0), 4 );
	line( img_matches, scene_corners[2] + offset, scene_corners[3] + offset, Scalar( 0, 255, 0), 4 );
	line( img_matches, scene_corners[3] + offset, scene_corners[0] + offset, Scalar( 0, 255, 0), 4 );

	//-- Show detected matches
	imshow( "Good Matches & Object detection", img_matches );
	waitKey(0);
	return 0;
}

