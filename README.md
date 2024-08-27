# djvu2mask
Extracting binary mask from DjVu documents on Debian Linux

Brute force approach:

For every *.djvu file in the specified directory do the following

1. Extract the mask with

`ddjvu -format=pbm -mode=mask <file name>.djvu <file name>_mask.pbm`

2. Convert *.pbm to *.png with with ImageMagick's convert

3. Remove the original *.pbm files.

https://sourceforge.net/p/djvu/bugs/357/

ddjvu -1 should always return a binary mask as a PBM files.
PBM files can only represent binary images anyway.
https://linux.die.net/man/5/pbm

A pbm image's magic number is the two characters 'P4'.




