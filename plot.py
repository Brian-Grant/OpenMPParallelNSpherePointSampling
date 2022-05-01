import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from scipy.interpolate import make_interp_spline
from matplotlib.ticker import MaxNLocator
"""
def main():
    print("plotting")
    fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
    DataAll1D = np.loadtxt("out.csv", delimiter=",")

    # create 2d x,y grid (both X and Y will be 2d)
    X, Y = np.meshgrid(DataAll1D[:,0], DataAll1D[:,1])

    # repeat Z to make it a 2d grid
    Z = np.tile(DataAll1D[:,2], (len(DataAll1D[:,2]), 1))

    #fig = plt.figure()
    #ax = fig.add_subplot(111, projection='3d')

    ax.plot_surface(X, Y, Z, cmap='viridis', edgecolor='none', linewidth=0, antialiased=False)
    #ax.plot_surface(X, Y, Z, cmap=cm.coolwarm,
                       #linewidth=0, antialiased=False)
    


    plt.show()
 


main()

"""



def main():
    print("plotting")

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    DATA = np.loadtxt("out.csv", delimiter=",")

    X = DATA[:,0]
    Y = DATA[:,1]
    Z = DATA[:,2]

    surf = ax.plot_trisurf(X, Y, Z, cmap=cm.jet)
    fig.colorbar(surf)
    fig.tight_layout()
    plt.show()

 


main()
