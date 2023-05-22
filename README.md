# Application of computer vision to verify position of objects placed on machining center. 


The aim of this project is to create vision systems, that check the correctness of position of 
the palette placed on machining center and verify accuracy of elements situated on it. 
<br><br>
The goal of this code is to monitor if palette is correctly placed and if it doesn’t rotated or moved. 
Moreover, code needs to verify the number of elements located on palette and its location. Additionally, QR code 
with information about name of the palette and number and position of elements situated on it, is 
sticked at the center of the palette. 
<br><br>
At the very beginning of using this system, it is needed to take a model image by attached 
camera. Then, the code processes this image by changing it from RGB model to HSV and then 
changing it into binary image. Based on that, program finds the contour of considered element. 
Initially many contours are found, but by using proper filtration, which relay on the rejection of 
every contour with too small area, at the end only one contour is returned. After creating model 
image, it is forbidden to move camera or machining center, because every move will lead to 
inadequate results. <br> 
In the next step, right process starts. When palette is placed on machining center, camera take 
the picture and code starts to process image again. It is done exactly like in case of model image. 
Program finds the right contour of palette and returns it. Slight difference is noticeable in case of 
small elements. Because of the fact that it can be fifteen combinations of elements’ arrangement, 
every single small element placed on palette is verify separately. 
Created program reads QR code, located on palette, and processes the encoded information. 
Subsequently, it compares if date transferred by QR is compatible with details returned by image 
processing. <br>
To control correspondence between information contained in QR code and captured image, 
two things are checked. Firstly, similarity of the objects is controlled. However, the second step 
of this verification is the comparison of extreme values read from contour matrix. Of course, each 
captured image is slightly different, so this analogy requires taking in account the tolerance. 
Program returns “true” value if every single element is placed correctly and “false” if any of 
examined item is in the wrong position. 
<br><br>
For the puprose of my diploma thesis the core of this vision system was microcomputer 
Raspberry Pi 4 model B with operating system, Raspberry Pi OS (32-bit) – Debian Bullseye, 
installed on it. Additionally, the camera called Spy Camera HD 5MPx Flex was attached. 