#include <iostream>
#include <opencv2/highgui/highgui.hpp> 
#include <chilitags.hpp>

using namespace std;

// Reads a set of images and prints one line per tag to stdout. 
//
// The form of the output lines is:
//    file-name tag-no top-left.x top-left.y top-right.x top-right.y bottom-right.x bottom-right.y bottom-left.x bottom-left.y 
//
// Notes:
//    - if an image contains multiple tags, multiple lines will be printed
//    - no line will be printed for images in which no tag was detected
//

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Usage: detect-corners image1 [image2 ...]\n\n";
        return 1;
    }

    cout.precision(8);

    for (int i = 1; i < argc; i++) {
        cv::Mat image = cv::imread(argv[i]);
        if(image.data) {
            for (const auto &tag : chilitags::Chilitags().find(image)) {
                cout << argv[i] << " " << tag.first << " "; 
                for(int j = 0; j < 4; j++) {
                    for(int k = 0; k < 2; k++) {
                        cout << tag.second(j, k);
                        if ( j < 3 || k < 1 ) { 
                            cout << " ";
                        }
                    }
                }
                cout << endl;
            }
        }
    }
    return 1;
}
