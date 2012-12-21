#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int main()
{
    Mat img(500, 500, CV_8UC3);
    RNG& rng = theRNG();

    for(;;)
    {
        char key;
        int i, count = (unsigned)rng%100 + 1;

        /* generate points */
        vector<Point> points;
        for( i = 0; i < count; i++ )
        {
            Point pt;
            pt.x = rng.uniform(img.cols/5, img.cols*4/5);
            pt.y = rng.uniform(img.rows/5, img.rows*4/5);
            points.push_back(pt);
        }
		
        /* find hull convex */
        vector<int> hull;
        convexHull(Mat(points), hull, true);
		
        /* draw all the points */
        img = Scalar::all(0);
        for( i = 0; i < count; i++ )
            circle(img, points[i], 3, Scalar(0, 0, 255), CV_FILLED, CV_AA);

        /* draw the convex by points */
        int hullcount = (int)hull.size();
        Point pt0 = points[hull[hullcount-1]];
        for( i = 0; i < hullcount; i++ )
        {
            Point pt1 = points[hull[i]];
            line(img, pt0, pt1, Scalar(0, 255, 0), 1, CV_AA);
            pt0 = pt1;
        }

        imshow("hull", img);

        key = (char)waitKey();
        if( key == 27 || key == 'q' || key == 'Q' ) // 'ESC'
            break;
    }

    return 0;
}

