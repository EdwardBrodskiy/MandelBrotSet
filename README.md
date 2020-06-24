# MandelBrotSet

This program renders the mandelbrot set as well as the BuddhaBrot set and allows you to explore it.  It makes use of multiple cores on the cpu to make the rendering fast as well as using a checkered rendering approach to not overload one particular core.  The program uses sfml library to produce the visuals.

Based on this eq f(z, c) = z^2 + c.

![Set of 4 examples](https://github.com/EdwardBrodskiy/MandelBrotSet/blob/master/Sample%20images/set%20of%204.png)

<b> Functionality: </b>

\<LMB> = zoom in (half the width)

\<RMB> = room out (double the width)

<+> = increase number of times f(z, c) is applied by 500

<-> = decrease number of times f(z, c) is applied by 500

\<b> = show buddahbrot set (goes away after another action is called)

<b> Initial settings: </b>

resolution 1920 by 1080p

f(z, c) is applied 128 times per pixel

center is at 0 + 0i

<b> Comments: </b>

This was a learning project for me if you notice things that could be done better i would be happy to hear 
about it.

<b> Samples: </b>
Also avliable under the sample images folder

![Mandelbrot Set](https://github.com/EdwardBrodskiy/MandelBrotSet/blob/master/Sample%20images/mandelbrot%201080%20hue.png)

![Buddhabrot set](https://github.com/EdwardBrodskiy/MandelBrotSet/blob/master/Sample%20images/buddah%201080%20layered.png)

![Mandelbrot Set example 1](https://github.com/EdwardBrodskiy/MandelBrotSet/blob/master/Sample%20images/MandelBrotSet%201080%201.png)

