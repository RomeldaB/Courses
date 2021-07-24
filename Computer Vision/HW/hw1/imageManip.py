import math

import numpy as np
from PIL import Image
from skimage import color, io


def load(image_path):
    """Loads an image from a file path.

    HINT: Look up `skimage.io.imread()` function.

    Args:
        image_path: file path to the image.

    Returns:
        out: numpy array of shape(image_height, image_width, 3).
    """
    out = None

    ### YOUR CODE HERE
    # Use skimage io.imread
    out = io.imread(image_path)
    ### END YOUR CODE

    # Let's convert the image to be between the correct range.
    out = out.astype(np.float64) / 255
    return out


def dim_image(image):
    """Change the value of every pixel by following

                        x_n = 0.5*x_p^2

    where x_n is the new value and x_p is the original value.

    Args:
        image: numpy array of shape(image_height, image_width, 3).

    Returns:
        out: numpy array of shape(image_height, image_width, 3).
    """

    out = None
    ### YOUR CODE HERE
    #initialize out
    out = np.zeros((image.shape[0], image.shape[1], 3))
    #dim image
    for x in range(image.shape[0]):
        for y in range(image.shape[1]):
            out[x][y] = 0.5*image[x][y]*image[x][y]
    ### END YOUR CODE

    return out


def convert_to_grey_scale(image):
    """Change image to gray scale.

    HINT: Look at `skimage.color` library to see if there is a function
    there you can use.

    Args:
        image: numpy array of shape(image_height, image_width, 3).

    Returns:
        out: numpy array of shape(image_height, image_width).
    """
    out = None
    ### YOUR CODE HERE

    #the function we are searching for is rgb2gray()
    out = color.rgb2gray(image)

    ### END YOUR CODE

    return out


def rgb_exclusion(image, channel):
    """Return image **excluding** the rgb channel specified

    Args:
        image: numpy array of shape(image_height, image_width, 3).
        channel: str specifying the channel. Can be either "R", "G" or "B".

    Returns:
        out: numpy array of shape(image_height, image_width, 3).
    """

    out = None

    ### YOUR CODE HERE

    # Initialize out
    a, b, c = image.shape
    # make out = image
    out = np.zeros((a, b, c))
    for x in range(a):
        for y in range(b):
            for z in range(c):
                out[x][y][z] = image[x][y][z]
    # Exclude color according to channel
    if channel == 'R':
        for x in range(a):
            for y in range(b):   
                out[x][y][0] = 0 #Make Red 0 on each pixel
    elif channel == 'G':
        for x in range(a):
            for y in range(b):   
                out[x][y][1] = 0 #Make Green 0 on each pixel
    else:
        for x in range(a):
            for y in range(b):   
                out[x][y][2] = 0 #Make Blue 0 on each pixel

    ### END YOUR CODE

    return out


def lab_decomposition(image, channel):
    """Decomposes the image into LAB and only returns the channel specified.

    Args:
        image: numpy array of shape(image_height, image_width, 3).
        channel: str specifying the channel. Can be either "L", "A" or "B".

    Returns:
        out: numpy array of shape(image_height, image_width).
    """

    lab = color.rgb2lab(image)
    out = None

    ### YOUR CODE HERE
    a, b, c = image.shape
    out = np.zeros((a, b)) # 2d image so grayscale one
    #handle L channel
    if channel == 'L':
        for x in range(a):
            for y in range(b):
                out[x][y] = image[x][y][0]
    #handle A channel
    elif channel == 'A':
        for x in range(a):
            for y in range(b):
                out[x][y] = image[x][y][1]
    #handle B channel
    else:
        for x in range(a):
            for y in range(b):
                out[x][y] = image[x][y][2]
    ### END YOUR CODE

    return out


def hsv_decomposition(image, channel='H'):
    """Decomposes the image into HSV and only returns the channel specified.

    Args:
        image: numpy array of shape(image_height, image_width, 3).
        channel: str specifying the channel. Can be either "H", "S" or "V".

    Returns:
        out: numpy array of shape(image_height, image_width).
    """

    hsv = color.rgb2hsv(image)
    out = None

    ### YOUR CODE HERE
    # The code is almost same as in the method above
    a, b, c = image.shape
    out = np.zeros((a, b)) # 2d image so grayscale one
    #handle H channel
    if channel == 'H':
        for x in range(a):
            for y in range(b):
                out[x][y] = image[x][y][0]
    #handle S channel
    elif channel == 'S':
        for x in range(a):
            for y in range(b):
                out[x][y] = image[x][y][1]
    #handle V channel
    else:
        for x in range(a):
            for y in range(b):
                out[x][y] = image[x][y][2]
    ### END YOUR CODE

    return out


def mix_images(image1, image2, channel1, channel2):
    """Combines image1 and image2 by taking the left half of image1
    and the right half of image2. The final combination also excludes
    channel1 from image1 and channel2 from image2 for each image.

    HINTS: Use `rgb_exclusion()` you implemented earlier as a helper
    function. Also look up `np.concatenate()` to help you combine images.

    Args:
        image1: numpy array of shape(image_height, image_width, 3).
        image2: numpy array of shape(image_height, image_width, 3).
        channel1: str specifying channel used for image1.
        channel2: str specifying channel used for image2.

    Returns:
        out: numpy array of shape(image_height, image_width, 3).
    """

    out = None
    ### YOUR CODE HERE
    # We first get the 2 halves and then join them
    a,b,c = image1.shape
    d,e,f = image2.shape
    #Initialize halves
    h1 = np.zeros((a, b//2, c))
    h2 = np.zeros((d, e//2, f))
    #Exclude channels
    im1 = rgb_exclusion(image1, channel1)
    im2 = rgb_exclusion(image2, channel2)
    #Copy halves
    for x in range(a):
        for y in range(b//2):
            h1[x][y] = im1[x][y]
    for x in range(d):
        for y in range(e//2):
            h2[x][y] = im2[x][y + e//2]
    #Join halves
    out = np.concatenate((h1, h2), axis=1)
    ### END YOUR CODE

    return out


def mix_quadrants(image):
    """THIS IS AN EXTRA CREDIT FUNCTION.

    This function takes an image, and performs a different operation
    to each of the 4 quadrants of the image. Then it combines the 4
    quadrants back together.

    Here are the 4 operations you should perform on the 4 quadrants:
        Top left quadrant: Remove the 'R' channel using `rgb_exclusion()`.
        Top right quadrant: Dim the quadrant using `dim_image()`.
        Bottom left quadrant: Brighthen the quadrant using the function:
            x_n = x_p^0.5
        Bottom right quadrant: Remove the 'R' channel using `rgb_exclusion()`.

    Args:
        image1: numpy array of shape(image_height, image_width, 3).

    Returns:
        out: numpy array of shape(image_height, image_width, 3).
    """
    out = None

    ### YOUR CODE HERE
    a, b, c = image.shape
    #Initialize quadrants
    q1 = np.zeros((a//2 +1, b//2 +1, c))
    q2 = np.zeros((a//2 +1, b//2 +1, c))
    q3 = np.zeros((a//2 +1, b//2 +1, c))
    q4 = np.zeros((a//2 +1, b//2 +1, c))
    for x in range(a//2):
        for y in range(b//2):
            q1[x][y] = image[x][y]
    for x in range(a//2):
        for y in range(b//2, b):
            q2[x][y-b//2] = image[x][y]
    for x in range(a//2, a):
        for y in range(b//2):
            q3[x-a//2][y] = image[x][y]
    for x in range(a//2, a):
        for y in range(b//2, b):
            q4[x-a//2][y-b//2] = image[x][y]
    #Perform the four actions
    q1 = rgb_exclusion(q1, 'R')
    q2 = dim_image(q2)
    for x in range(a//2, a):
        for y in range(b//2):
            q3[x-a//2][y] = image[x][y]*0.5
    q4 = rgb_exclusion(q4, 'R')
    q1q3 = np.concatenate((q1, q3), axis=0)
    q2q4 = np.concatenate((q2, q4), axis=0)
    out = np.concatenate((q1q3, q2q4), axis=1)
    ### END YOUR CODE

    return out
