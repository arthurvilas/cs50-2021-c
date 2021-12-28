#include "helpers.h"
#include <math.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg;
    for (RGBTRIPLE *p = &image[0][0]; p < &image[height][width]; p++) {
        avg = round((p->rgbtRed + p->rgbtGreen + p->rgbtBlue) / 3.0);
        p->rgbtRed = avg;
        p->rgbtGreen = avg;
        p->rgbtBlue = avg;
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++) {
        for (int j = 0, k = width - 1; j < k; j++, k--) {
            temp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Store original image
    RGBTRIPLE original_image[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            original_image[i][j] = image[i][j];
        }
    }
   
    // Calculate and apply averages
    int num_pixels, total_red, total_green, total_blue;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            num_pixels = 0;
            total_red = 0;
            total_green = 0;
            total_blue = 0;
            for (int k = i - 1; k <= i + 1; k++) {
                for (int l = j - 1; l <= j + 1; l++) {

                    // Ignore out of bounds pixels
                    if (k < 0 || k >= height || l < 0 || l >= width) {
                        continue;
                    }

                    num_pixels++;
                    total_red += original_image[k][l].rgbtRed;
                    total_green += original_image[k][l].rgbtGreen;
                    total_blue += original_image[k][l].rgbtBlue;
                }
            }
            image[i][j].rgbtRed = round(total_red / (float) num_pixels);
            image[i][j].rgbtGreen = round(total_green / (float) num_pixels);
            image[i][j].rgbtBlue = round(total_blue / (float) num_pixels);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Store original image
    RGBTRIPLE original_image[height][width];
    memcpy(original_image, image, sizeof(RGBTRIPLE) * height * width);

    // Kernels
    int gx_matrix[][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy_matrix[][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int final_r, final_g, final_b;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            // Compute kernels for each channel
            int *gx_matrix_aux = &gx_matrix[0][0];
            int *gy_matrix_aux = &gy_matrix[0][0];
            int gx_r = 0, gx_g = 0, gx_b = 0;
            int gy_r = 0, gy_g = 0, gy_b = 0;

            for (int k = i - 1; k <= i + 1; k++) {
                for (int l = j - 1; l <= j + 1; l++) {

                    // Ignore out of bounds pixels
                    if (k < 0 || k >= height || l < 0 || l >= width) {
                        gx_matrix_aux++;
                        gy_matrix_aux++;
                        continue;
                    }

                    gx_r += *gx_matrix_aux * original_image[k][l].rgbtRed;
                    gx_g += *gx_matrix_aux * original_image[k][l].rgbtGreen;
                    gx_b += *gx_matrix_aux * original_image[k][l].rgbtBlue;
                    
                    gy_r += *gy_matrix_aux * original_image[k][l].rgbtRed;
                    gy_g += *gy_matrix_aux * original_image[k][l].rgbtGreen;
                    gy_b += *gy_matrix_aux * original_image[k][l].rgbtBlue;

                    gx_matrix_aux++;
                    gy_matrix_aux++;
                }
            }
            
            final_r = round(sqrt(pow(gx_r, 2) + pow(gy_r, 2)));
            image[i][j].rgbtRed = final_r > 255 ? 255 : final_r;

            final_g = round(sqrt(pow(gx_g, 2) + pow(gy_g, 2)));
            image[i][j].rgbtGreen = final_g > 255 ? 255 : final_g;
            
            final_b = round(sqrt(pow(gx_b, 2) + pow(gy_b, 2)));
            image[i][j].rgbtBlue = final_b > 255 ? 255 : final_b;
        }
    }
    return;
}