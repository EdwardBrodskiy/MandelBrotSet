# MandelBrotSet

MandelBrotSet is a C++ project that renders both the Mandelbrot and BuddhaBrot sets, and allows you to explore it. Utilizing multiple CPU cores, the project ensures fast rendering and employs a checkered rendering approach to prevent the overloading of a single core. The project leverages the sfml library for visual production.

The visual renderings are based on the fundamental equation f(z, c) = z^2 + c, which forms the core of these fascinating fractal sets.

![Set of 4 examples](https://github.com/EdwardBrodskiy/MandelBrotSet/blob/master/sample-images/set%20of%204.png)

## Functionality

\<LMB> = zoom in (half the width)

\<RMB> = room out (double the width)

<+> = increase number of times f(z, c) is applied by 500

<-> = decrease number of times f(z, c) is applied by 500

\<b> = show buddahbrot set (goes away after another action is called)

## Initial settings

resolution 1920 by 1080p

f(z, c) is applied 128 times per pixel

center is at 0 + 0i

## Comments

This was a learning project for me if you notice things that could be done better i would be happy to hear 
about it.

## Samples

Also avliable under the sample images folder

![Mandelbrot Set](https://github.com/EdwardBrodskiy/MandelBrotSet/blob/master/sample-images/mandelbrot%201080%20hue.png)

![Buddhabrot set](https://github.com/EdwardBrodskiy/MandelBrotSet/blob/master/sample-images/buddah%201080%20layered.png)

![Mandelbrot Set example 1](https://github.com/EdwardBrodskiy/MandelBrotSet/blob/master/sample-images/MandelBrotSet%201080%201.png)

