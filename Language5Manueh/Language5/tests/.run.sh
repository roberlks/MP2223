touch tests//.timeout
CMD="valgrind --leak-check=full /home/roberlks222/Documents/Clase/MP/MP2223/Language5Manueh/Language5/./dist/JOIN/GNU-Linux/JOIN  -o tests/output/english.bgr ../Books/aliceWonder.bgr ../Books/changedMan.bgr 1> tests//.out9 2>&1"
eval $CMD
rm tests//.timeout
