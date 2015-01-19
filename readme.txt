Made By: Devender Verma(ph0enix)

To run paint you have to do following things:
1) install microsoft visual studio in your pc.
2) now what you need is to install GLUT for Visual Studio:
 a) download  GLUT package from "http://www.xmission.com/~nate/glut/glut-3.7.6-bin.zip".
 It should contain following three files:
	*glut.h
	*glut32.lib
	*glut32.dll
 -- If you have a 32 bits operating system, place "glut32.dll" to C:\Windows\System32\, if your operating system is 64 bits, place it to 'C:\Windows\SysWOW64\' (to your system directory)

-- Place "glut.h" in  C:\Program Files\Microsoft Visual Studio 12\VC\include\GL\ (NOTE: 12 here refers to your VS version it may be 8 or 10)

If you do not find VC and following directories.. go on create it.

-- Place "glut32.lib" to C:\Program Files\Microsoft Visual Studio 12\VC\lib\

3) Now, open visual Studio and
Under Visual C++, select Win32 Console Application.
Go to Project -> Properties. Select 'All Configuration' from Configuration dropdown menu on top left corner
Select Linker -> Input
Now right click on "Additional Dependence" found on Right panel and click Edit
now type

opengl32.lib
glu32.lib
glut32.lib
(NOTE: Each .lib in new line)

4) Now copy code from paint.cpp from downloaded project to your project.

5) run the code.
Functions implemented in paint are:
New – it creates the new canvas by calling makePallete() method that I created.
Line – this creates a line by double clicking on the canvas and then extending the line as much as you want.
Curve- In this I have created Bezier curve by passing four point vertices
Ellipse- for this we need two points.
Triangle- needs three points as corner vertices
Hexagon – needs 6 points.
Rounded rectangle- needs two opposite diagonal points.
Crop- needs two opposite diagonal points.
Save- it asks for file name in command line. For save I have just fetched the pixel values and stored it to the file by glReadPixels().
Open – opens the file created by this paint.

