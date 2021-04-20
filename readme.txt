--------------------------------------------------------------------------------
-- Purpose
--------------------------------------------------------------------------------
Demonstrate a Neural Network classifying handwritten MNIST digits using softmax


--------------------------------------------------------------------------------
-- Build/Run
--------------------------------------------------------------------------------
Please run make to build the executeables, if you get an error run "make clean"
first.

Then run the following:
-- This executeable just sobel filters an image
./test_nets <number of layers> <nodes per layer> <training/learning rate>

<number of layers>       - Number of layers including output, 4 seems to be to large
<nodes per layer>        - Nodes per hidden layer, 90 seems to be a sweet spot
<training/learning rate> - Scalar for gradient application to W/B, 3 works ok


