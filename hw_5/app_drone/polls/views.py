from django.shortcuts import render
from django.http import HttpResponse
import requests
import numpy as np
import skfmm
import matplotlib
matplotlib.use('agg')
import matplotlib.pyplot as plt
import cv2
from PIL import Image, ImageDraw


def index(request):

    date = request.GET['date']
    n = int(request.GET['n'])

    json_data = requests.get("https://ce290-hw5-weather-report.appspot.com/?date="+str(date)).json()
    centroid_y = json_data['centroid_y']
    centroid_x = json_data['centroid_x']
    radius = json_data['radius']

    fig = compute_shortest_path(centroid_y, centroid_x, radius, n)

    im = fig2img(fig)
    draw = ImageDraw.Draw(im)  # create a drawing object that is
    # used to draw on the new image
    red = (0, 0, 0)  # color of our text
    text_pos = (10, 10)  # top-left position of our text
    text = "date : "+str(date)+" n : "+str(n)  # text to draw
    # Now, we'll do the drawing:
    draw.text(text_pos, text, fill=red)

    del draw  # I'm done drawing so I don't need this anymore

    # We need an HttpResponse object with the correct mimetype
    response = HttpResponse(content_type="image/png")
    # now, we tell the image to save as a PNG to the
    # provided file-like object
    im.save(response, 'PNG')

    return response  # and we're done!

def fig2img ( fig ):
    """
    @brief Convert a Matplotlib figure to a PIL Image in RGBA format and return it
    @param fig a matplotlib figure
    @return a Python Imaging Library ( PIL ) image
    """
    # put the figure pixmap into a numpy array
    buf = fig2data ( fig )
    w, h, d = buf.shape
    return Image.frombytes( "RGBA", ( w ,h ), buf.tostring( ) )

def fig2data(fig):
    """
    @brief Convert a Matplotlib figure to a 4D numpy array with RGBA channels and return it
    @param fig a matplotlib figure
    @return a numpy 3D array of RGBA values
    """
    # draw the renderer
    fig.canvas.draw()

    # Get the RGBA buffer from the figure
    w, h = fig.canvas.get_width_height()
    buf = np.fromstring(fig.canvas.tostring_argb(), dtype=np.uint8)
    buf.shape = (w, h, 4)

    # canvas.tostring_argb give pixmap in ARGB mode. Roll the ALPHA channel to have it in RGBA mode
    buf = np.roll(buf, 3, axis=2)
    return buf

def compute_shortest_path(centroid_y, centroid_x, radius, n):
    l = 20
    X, Y = np.meshgrid(np.linspace(-l/2, l/2, n), np.linspace(-l/2, l/2, n))

    phi = np.ones((n, n))
    phi[np.logical_and(X==-10, Y==-10)] = 0
    mask = np.less_equal(np.sqrt((X - (centroid_y - 10))**2 + (Y - (centroid_y - 10))**2), radius)
    phi = np.ma.MaskedArray(phi, mask)
    distance = skfmm.distance(phi)
    distance = distance.T


    #compute gradient with Sobel method
    dx = cv2.Sobel(distance, cv2.CV_64F,0,1,ksize=1)
    dy = cv2.Sobel(distance, cv2.CV_64F,1,0,ksize=1)

    path = gradient_descent(0.001, 1000000, distance, dx, dy, X, Y, [9.9, 9.8])


    #plot
    fig = plt.figure(figsize=(10, 8))
    plt.contour(X, Y, phi, [0], linewidths=(3), colors='black')
    plt.contour(X, Y, phi.mask, [0], linewidths=(3), colors='red')
    plt.contour(X, Y, distance.T, 100)
    plt.colorbar()
    plt.plot(*zip(*path))

    return fig

def gradient_descent(alpha, iterations, distance, dx, dy, X, Y, start_point):
    path = [start_point]
    next_point_coordinate_approx = map_function(start_point, dx, dy)
    for i in range(iterations):
        gradx = dx[next_point_coordinate_approx[0], next_point_coordinate_approx[1]]
        grady = dy[next_point_coordinate_approx[0], next_point_coordinate_approx[1]]
        mod = np.sqrt(gradx**2 + grady**2)
        beta = np.arctan(grady/gradx)
        next_point = path[-1] - alpha * mod * np.array([np.cos(beta), np.sin(beta)])
        next_point_coordinate_approx = map_function(next_point, dx, dy)
        path.append(next_point)
        if next_point[0] <= -9.9 or next_point[1] <= -9.9:
            return path
    return path

def map_function(point, dx, dy):
    new_point = (int((point[0]+10)*10)-1, int((point[1]+10)*10)-1)
    gradx = dx[new_point]
    grady = dy[new_point]
    i = 0
    if gradx == 0 or grady == 0 :
        for i in range(-100, 100):
            for j in range(-100, 100):
                new_point = (int((point[0]+10)*10)+i, int((point[1]+10)*10)+j)
                gradx = dx[new_point]
                grady = dy[new_point]
                if (gradx != 0 and grady != 0):
                    return new_point
    return new_point
