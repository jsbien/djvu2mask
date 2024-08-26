# djvu2mask
Extracting binary mask from DjVu documents on Debian Linux

Brute force approach:

For every *.djvu file in the specified directory do the following

1. Extract the mask with

ddjvu -format=pbm -mode=mask <file name>.djvu <file name>_mask.pbm

2. Convert *.pbm to *.png with with ImageMagick's convert

3. Remove the original *.ppm files.



