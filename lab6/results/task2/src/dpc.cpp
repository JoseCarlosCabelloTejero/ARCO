#include <iostream>
#include <math.h>
#include <omp.h>
#include <CL/sycl.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

using namespace std;
using namespace sycl;

int main(int argc, char const *argv[])
{
    // TODO: Check that the input image is in the args
    if (argv[1] == NULL) {
	    std::cout << "Error no image provided " << std::endl;
        exit(1);
    }

    /* Define selector and queue */
    cpu_selector selector;
    queue q(selector);

    std::cout << "Device name: " << q.get_device().get_info<info::device::name>()<< std::endl;
    //Load image
    int img_width, img_height, channels;

    unsigned char *image = stbi_load(argv[1], &img_width, &img_height, &channels, 0);
    
    if (image == NULL) {
	    std::cout << "Error while loading image" << std::endl;
        exit(1);
    }

    //Debug information
    std::cout << "Loaded image with a width of " << img_width << " height of " << img_height << " and " << channels << " channels" << std::endl;

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

    /* Create buffers for each array */
    buffer<uint8_t, 1> b_gray_image( gray_scale_image, range<1>(num_pixels) );
    buffer<uint8_t, 1> b_output_image( output_image, range<1>(num_pixels) );
    buffer<int, 2> b_weights(*weights, range<2>(3,3) );
    buffer<int, 2> b_weights_y( *weights_y, range<2>(3,3));

    int ks = 1; // Kernel size
    
    int dimension = img_height*img_width*ks;
    double start = omp_get_wtime();
    
    range<2> num_items{static_cast<unsigned int>(img_width), static_cast<unsigned int>(img_height)};

    q.submit([&](handler &h){
	accessor a_gray_image(b_gray_image, h, read_only);
	accessor a_output_image(b_output_image, h, write_only);
	accessor a_weights(b_weights, h, read_only);
	accessor a_weights_y(b_weights_y, h, read_only);

	h.parallel_for(num_items, [=](id<2> item){
	//TIP: Think about the start and end of each index
    
	    double sum_x = 0.0;
	    double sum_y = 0.0;
	    int row = item[1];
	    int col = item[0];
        
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
                int weight = a_weights[i+1][j+1];
                int weight_y = a_weights_y[i+1][j+1];
                    
                int original_value = a_gray_image[(row+i) * img_width + col + j];
                sum_x += weight * original_value;
                sum_y += weight_y * original_value;
            }
        }
        
        int G = unsigned(std::sqrt(sum_x*sum_x+sum_y*sum_y));
        a_output_image[row * img_width + col] = std::min(G, 255);
        
	});

    }).wait();

    host_accessor h_accessor{b_output_image};
    
    double end = omp_get_wtime();
    std::cout << "Time " << end - start << std::endl;

    stbi_write_png("borders.png", img_width, img_height, 1, output_image, 0);

    //Free image
    
    stbi_image_free(image);
    
    delete [] output_image;
    delete [] gray_scale_image;

    return 0;
}
