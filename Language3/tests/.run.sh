touch tests//.timeout
CMD="valgrind --leak-check=full /home/roberlks222/Documents/Clase/MP/MP2223/Language3/dist/Debug/GNU-Linux/language3  ../Books/fortunata.bgr ../Books/quijote.bgr ../Books/fortunata.bgr 1> tests//.out7 2>&1"
eval $CMD
rm tests//.timeout
