#include <iostream>
#include <math.h>
#include <omp.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

using namespace std;

int main(int argc, char const *argv[])
{
    // TODO: Check that the input image is in the args
    if (argv[1] == NULL) {
        cout << "Error no image provided " << endl;
        exit(1);
    }

    //Load image
    int img_width, img_height, channels;

    unsigned char *image = stbi_load(argv[1], &img_width, &img_height, &channels, 0);
    
    if (image == NULL) {
        cout << "Error while loading image" << endl;
        exit(1);
    }

    //Debug information
    cout << "Loaded image with a width of " << img_width << " height of " << img_height << " and " << channels << " channels" << endl;

    size_t num_pixels = img_width * img_height;
    size_t img_size = num_pixels * channels;

    int gray_channels = 1;
    
    //TODO: Create two uint8_t arrays with the size of the final image
    //TIPS: The first one will be used to store the gray image
    //TIPS: THe second one will be used to store the final image
    uint8_t *gray_scale_image = new uint8_t[num_pixels];//TODO: YOUR CODE
    uint8_t *output_image = new uint8_t[img_size];//TODO: YOUR CODE
    
    //TIPS: Weights represents horizontal sobel
    int weights[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    //TIPS: Weights_y represents vertical sobel
    int weights_y[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

    //TIP: Convert the image to gray
    for(unsigned char *p = image, *pg = gray_scale_image; p != image + img_size; p += channels, pg += gray_channels) {
         *pg = (uint8_t)((*p + *(p + 1) + *(p + 2))/3.0);
    }
    /*
    for (int row = 0; row < img_height; row++) {
        for (int col = 0; col < img_width; col++) {
            std::cout << static_cast<unsigned int> (gray_scale_image[(row) * img_width + col]) << " ";
        }
        
        std::cout << "heyy" << std::endl;
    }
    */
    int ks = 3; // Kernel size
    
    double start = omp_get_wtime();

    //TODO: Loop over each pixel
    for(int row = 0; row < img_height; row++) {
        for (int col = 0; col < img_width; col++) {
            double sum_x = 0.0;
            double sum_y = 0.0;

            //TIP: Think about the start and end of each index
            for(int i = -1; i <= 1; i++) {
                for(int j = -1; j <= 1; j++) {

                    // TODO: Check the boundaries UP, DOWN, LEFT, RIGHT
                    // TIP: Remember that in the top left pixel, for example
                    // we are applying the upper and left part of the kernel
                    // to missing pixels, one approach is ignore it.
                    if(row==0) {
                        continue; // Up
                    }

                    if(row==img_height-1) {
                        continue; // Down
                    }

                    if(col==0) {
                        continue; // left
                    }

                    if(col==img_width-1) {
                        continue; // right
                    }

                    //TODO: Check the start and end of i and j, 
                    //TODO: get the filter value of each filter
                    int weight = weights[i+1][j+1];
                    int weight_y = weights_y[i+1][j+1];
                    
                    int original_value = gray_scale_image[(row+i) * img_width + col + j];
                    sum_x += weight * original_value;
                    sum_y += weight_y * original_value;
                }
            }
            int G = unsigned(std::sqrt(sum_x*sum_x+sum_y*sum_y));
            output_image[row * img_width + col] = std::min(G, 255);
        }
    }
            
    double end = omp_get_wtime();
    cout << "Time " << end - start << endl;

    stbi_write_png("borders.png", img_width, img_height, 1, output_image, 0);

    

    //Free image
    stbi_image_free(image);
    delete [] output_image;
    delete [] gray_scale_image;
    
    return 0;
}
