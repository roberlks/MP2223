touch tests//.timeout
CMD="valgrind --leak-check=full /home/roberlks222/Documents/Clase/MP/MP2223/Language5/./dist/LEARN/GNU-Linux/LEARN  -l spanish -o tests/output/test_ES.bgr ../Books/test_ES.txt 1> tests//.out25 2>&1"
eval $CMD
rm tests//.timeout
