# The-Optimal-Design
C++ implementations of classic models and approaches in optimal design theory for numerical calculation
## using Cyclic Coordinate Method to find min value of function:
<img src="https://latex.codecogs.com/svg.latex?\Large&space;f(x)=x_1^2+2x_2^2-2x_1x_2-4x_1" title="f(x) =x_1^2+2x_2^2-2x_1x_2-4x_1"/>
the start point is <img src="https://latex.codecogs.com/svg.latex?\Large&space;x^0=[1,1]^T" title="x^0 = [1,1]^T"/> and Convergence precision <img src="https://latex.codecogs.com/svg.latex?\Large&space;{\varepsilon}" title="{\varepsilon}"/>is 0.1

## Use following 4 different unconstrained optimization methods to find min value of function:
<img src="https://latex.codecogs.com/svg.latex?\Large&space;f(x,y)=x^4-2x^2y-2xy+x^2+2Y^2+4.5x-4y+4" title="f(x,y)=x^4-2x^2y-2xy+x^2+2y^2+4.5x-4y+4"/>
the start point is (-2.5, 4.25).  
Method 1: Gradient Descent Method  
Method 2: Damping Newton's Method  
Method 3: Conjugate Gradient Method  
Method 4: DFP Method

## Find the range where minimum value located for function:
<img src="https://latex.codecogs.com/svg.latex?\Large&space;f(x)=x^2-10x+20" title="f(x)=x^2-10x+20"/>
the start point is a and step is h. Input a = 10, h = 2.

## Use following 6 different methods to find min value of function in range [3,5], Convergence precision is 0.001:
<img src="https://latex.codecogs.com/svg.latex?\Large&space;f(x)=x^4-4x^3-6x^2-16x+4" title="f(x)=x^4-4x^3-6x^2-16x+4"/>
Method 1: Golden Section Method＜br/＞
Method 2: Newton's Method＜br/＞
Method 3: Quadratic Interpolation＜br/＞
Method 4: Cubic Interpolation＜br/＞
Method 5: Line Search Method＜br/＞
Method 6: Bisection Method

## Find min value of function with penalty function. 
Target Function:<img src="https://latex.codecogs.com/svg.latex?\Large&space;f(x,y)=x^2+y^2" title="f(x,y)=x^2+y^2"/>
Penalty function:<img src="https://latex.codecogs.com/svg.latex?\Large&space;x &ge; 1, y-x &ge; 6" title="x &ge; 1, y-x &ge; 6"/>