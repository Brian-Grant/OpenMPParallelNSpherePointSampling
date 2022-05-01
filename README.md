# 547_03


run make 
    to compile ndsphere

run make test
    to run ndsphere with 4 threads

run make t1 
    to run ndsphere with 1 thread ----sequential

run make tn t=<num_threads>
    to run ndsphere with <num_threads> threads




run make seg
    to compile the SIMD line segment program

run make s
    to run the simd line segment program

run make clean to clean



NOTE:
The only commit after 12pm was one to include the extra credit visualization

The main program including the method of generating points that was
approved on Piazza for the extra credit was not modified.
The Piazza post was --Looking at methods 20 and 21. Either of these are valid for the extra 10 points, right?
I used method 20

Modifications:

Modified ndsphere.cpp to output histogram data to out.csv

a sample csv is now available

plot.py will plot data based on the csv

vis.png is a sample plot

makefile 
    make plot -----to make plot from generated data
