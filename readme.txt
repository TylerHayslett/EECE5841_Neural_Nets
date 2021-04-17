--------------------------------------------------------------------------------
-- Purpose
--------------------------------------------------------------------------------
Test and qualify the Sobel filter against noise


--------------------------------------------------------------------------------
-- Tyler created source code files
--------------------------------------------------------------------------------
sobel_edging.c
sobel_noise_test.c
sobel_filtered_noise_test.c
image_functions.h
image_functions.c

--------------------------------------------------------------------------------
-- Build/Run
--------------------------------------------------------------------------------
Please run make to build the executeables, if you get an error run "make clean"
first.

Then run the following:
-- This executeable just sobel filters an image
./sobel_edging <image> <threshold>

<image> - file name for the image you would like to process
<threshold> optional - the intensity value at which to binarize the Sobel filtered image


-- This executable preforms a set of trials/sweep over noise levels to quantify sobel preformance
./sobel_noise_test <image> <number of trials> <noise level>

<image> - file name for the image you would like to process
<number of trials> optional - the number of iterations you would like to average to estimate error and threshold, default 100
<noise level> optional - the noise level at which you wish to run your trials. If this argument is left off, you will run a sweep through 0-99. 
                         NOTE: if you wish to specify noise level, you must also specify number of trials



-- This executable preforms a set of trials/sweep over noise levels to quantify sobel preformance but also filters before applying sobel to noisy picture
./sobel_filtered_noise_test <image> <number of trials> <noise level>

<image> - file name for the image you would like to process
<number of trials> optional - the number of iterations you would like to average to estimate error and threshold, default 100
<noise level> optional - the noise level at which you wish to run your trials. If this argument is left off, you will run a sweep through 0-99. 
                         NOTE: if you wish to specify noise level, you must also specify number of trials

