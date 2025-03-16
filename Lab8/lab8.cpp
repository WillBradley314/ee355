#include "lodepng.h"
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// A simple class to handle PNG images
class PNGImage {
public:
    std::vector<unsigned char> image; // stores image data in RGBA format
    unsigned width, height;

    PNGImage() : width(0), height(0) {}

    // Load a PNG file into the image vector.
    bool load(const std::string &filename) {
	//...
        return !lodepng::decode(image, width, height, filename);
    }

    // Save the image vector into a PNG file.
    bool save(const std::string &filename) {
        bool error = lodepng::encode(filename, image, width, height);
        if (error) {
            cerr << "Error: Could not save the image file to " << filename << "." << endl;
        }
        else {
            cout << "Image saved as " << filename << "." << endl;
        }
        return !error;
    }
};

// Function to apply a tint by scaling the red, green, and blue channels.
void tintImage(std::vector<unsigned char>& image, unsigned width, unsigned height, double rFactor, double gFactor, double bFactor) {
    int i;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            i = 4 * (width * y + x); // index of red
            image[i] = min(255, max(0, int(image[i]*rFactor)));  // min & max prevent overflow
            image[i+1] = min(255, max(0, int(image[i+1]*gFactor))); 
            image[i+2] = min(255, max(0, int(image[i+2]*bFactor))); 
        }
    }
}

// Function to invert the image colors.
void invertImage(std::vector<unsigned char>& image, unsigned width, unsigned height) {
int i;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            i = 4 * (width * y + x); // index of red
            image[i] = 255 - image[i];
            image[i+1] = 255 - image[i+1];
            image[i+2] = 255 - image[i+2];
        }
    }


}

// Function to add Gaussian noise to the image.
void addGaussianNoise(std::vector<unsigned char>& image, double mean, double stddev) {
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> d(mean, stddev);
    int noise;
    
    for (int i = 0; i < image.size(); i+=4) {
        for (int j = 0; j < 3; j++) {
            noise = image[i+j] + int(d(gen));
            image[i+j] = min(255, max(0, noise));
        }
    }

}

// Function to add salt-and-pepper noise to the image.
void addSaltPepperNoise(std::vector<unsigned char>& image, double noiseRatio) {
    size_t totalPixels = image.size() / 4;
    size_t numNoisy = static_cast<size_t>(totalPixels * noiseRatio);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, totalPixels - 1);
    int j, sp;
    
    for (int i = 0; i < numNoisy; i++) {
        j = 4 * dis(gen);
        sp = 2 * dis(gen);
        if (sp > totalPixels) {
            image[j] = 255;
            image[j+1] = 255;
            image[j+2] = 255;
        }
        else {
            image[j] = 0;
            image[j+1] = 0;
            image[j+2] = 0;
        }
    }


}

// Function to zoom the image using nearest-neighbor interpolation.
std::vector<unsigned char> zoomImage(const std::vector<unsigned char>& image, unsigned width, unsigned height, double scale, unsigned &newWidth, unsigned &newHeight) {
    int i, j, nearX, nearY;
    newWidth = unsigned(width * scale);
    newHeight = unsigned(height * scale); 
    vector<unsigned char> zoomed(newWidth * newHeight * 4);

    for (int y = 0; y < newHeight; y++) {
        for (int x = 0; x < newWidth; x++) {
            i = 4 * (newWidth * y + x); // index of red
            nearX = min(int(x/scale), int(width-1));
            nearY = min(int(y/scale), int(height-1));
            j = 4 * (width * nearY + nearX);
            zoomed[i] = image[j];
            zoomed[i+1] = image[j+1];
            zoomed[i+2] = image[j+2];
            zoomed[i+3] = 255;
        }
    }
    return zoomed;
}

// Function to apply a glass effect.
// For each pixel, a nearby random pixel (within a specified radius) is used.
std::vector<unsigned char> glassEffect(const std::vector<unsigned char>& src, unsigned width, unsigned height, int radius) {
    std::vector<unsigned char> dst(src.size());
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(-radius, radius);

    int x, y, xRand, yRand, i, j;
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            xRand = min(width-1, unsigned(max(0,x+dis(gen))));
            yRand = min(height-1, unsigned(max(0,y+dis(gen))));
            i = 4 * (width * y + x);
            j = 4 * (width * yRand + xRand);  
            dst[i] = src[j];
            dst[i+1] = src[j+1];
            dst[i+2] = src[j+2];
            dst[i+3] = 255;

        }
    }
    return dst;
}

// Function to perform edge detection using a Sobel-like operator.
// The image is converted to grayscale and the edge magnitude is computed.
std::vector<unsigned char> edgeDetection(const std::vector<unsigned char>& src, unsigned width, unsigned height) {
    std::vector<unsigned char> dst(src.size(), 255); // Initialize with white pixels.
    std::vector<unsigned char> gray(width * height, 0);
    // Convert to grayscale.
    //...

    for (int i = 0; i < src.size(); i+=4) {
        gray[i/4] = 0.299*src[i] + 0.587*src[i+1] + 0.114*src[i+2];
    }

    // Apply a simple Sobel operator.
    for (unsigned y = 1; y < height - 1; y++) {
        for (unsigned x = 1; x < width - 1; x++) {
            int gx = -gray[(y-1)*width + (x-1)] + gray[(y-1)*width + (x+1)]
                     -2 * gray[y*width + (x-1)] + 2 * gray[y*width + (x+1)]
                     -gray[(y+1)*width + (x-1)] + gray[(y+1)*width + (x+1)];
            int gy = -gray[(y-1)*width + (x-1)] - 2 * gray[(y-1)*width + x] - gray[(y-1)*width + (x+1)]
                     + gray[(y+1)*width + (x-1)] + 2 * gray[(y+1)*width + x] + gray[(y+1)*width + (x+1)];
            int edgeVal = std::min(255, abs(gx) + abs(gy));
            size_t dstIndex = (y * width + x) * 4;
            dst[dstIndex]   = edgeVal;
            dst[dstIndex+1] = edgeVal;
            dst[dstIndex+2] = edgeVal;
            dst[dstIndex+3] = 255;
        }
    }
    return dst;
}

// Function to smooth the image using a simple 3x3 average filter.
std::vector<unsigned char> smoothImage(const std::vector<unsigned char>& src, unsigned width, unsigned height) {
    std::vector<unsigned char> dst(src.size());
    int x, y, i, j;
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int rAvg(0), gAvg(0), bAvg(0); 
            for (int yMat = max(0,y-1); yMat < min(int(width-1),y+2); yMat++) {
                for (int xMat = max(0,x-1); xMat < min(int(width-1),x+2); xMat++) {
                    rAvg += src[4 * (width * yMat + xMat)];
                    gAvg += src[4 * (width * yMat + xMat) + 1];
                    bAvg += src[4 * (width * yMat + xMat) + 2];
                }
            }
            rAvg/=9;
            gAvg/=9;
            bAvg/=9;

            i = 4 * (width * y + x);
            dst[i] = rAvg;
            dst[i+1] = gAvg;
            dst[i+2] = bAvg;
            dst[i+3] = 255;
        }
    }
    return dst;
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: png_lab <input_png_file>" << endl;
        return 1;
    }

    string inputFile = argv[1];
    PNGImage img;
    if (!img.load(inputFile)) {
        cerr << "Error: Could not load the image file." << endl;
        return 1;
    }
    else {
        cout << "Image loaded successfully: " << img.width << " x " << img.height << endl;
    }
    img.save("output.png");
    

    // Create copies of the image data for each operation.
    vector<unsigned char> tinted       = img.image;
    vector<unsigned char> inverted     = img.image;
    vector<unsigned char> gaussianNoisy = img.image;
    vector<unsigned char> spNoisy       = img.image;

    // Apply tint: Increase the red channel.
    tintImage(tinted, img.width, img.height, 1.2, 1.0, 1.0);

    // Invert colors.
    invertImage(inverted, img.width, img.height);

    // Add Gaussian noise (mean=0, stddev=30).
    addGaussianNoise(gaussianNoisy, 0.0, 30.0);

    // Add salt-and-pepper noise (affect 5% of pixels).
    addSaltPepperNoise(spNoisy, 0.05);

    // Zoom the image by a factor of 1.5.
    unsigned newWidth, newHeight;
    vector<unsigned char> zoomed = zoomImage(img.image, img.width, img.height, 1.5, newWidth, newHeight);

    // Apply glass effect with a displacement radius of 3.
    vector<unsigned char> glass = glassEffect(img.image, img.width, img.height, 3);

    // Perform edge detection.
    vector<unsigned char> edges = edgeDetection(img.image, img.width, img.height);

    // Smooth the image using a 3x3 average.
    vector<unsigned char> smooth = smoothImage(img.image, img.width, img.height);

    // Save all output images.
    PNGImage outImg;
    outImg.width = img.width;
    outImg.height = img.height;

    outImg.image = tinted;
    outImg.save("tinted.png");

    outImg.image = inverted;
    outImg.save("inverted.png");

    outImg.image = gaussianNoisy;
    outImg.save("gaussian_noisy.png");

    outImg.image = spNoisy;
    outImg.save("saltpepper_noisy.png");

    outImg.image = zoomed;
    outImg.width = newWidth;
    outImg.height = newHeight;
    outImg.save("zoomed.png");

    outImg.image = glass;
    outImg.width = img.width;
    outImg.height = img.height;
    outImg.save("glass.png");

    outImg.image = edges;
    outImg.width = img.width;
    outImg.height = img.height;
    outImg.save("edge.png");

    outImg.image = smooth;
    outImg.width = img.width;
    outImg.height = img.height;
    outImg.save("smooth.png");

    cout << "Processing completed. Check the output PNG files." << endl;
    return 0;
}
