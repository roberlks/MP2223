touch tests//.timeout
CMD="valgrind --leak-check=full /home/roberlks222/Documents/Clase/MP/MP2223/Language5/./dist/JOIN/GNU-Linux/JOIN  -o tests/output/spanish.bgr ../Books/BodasdeSangre_FedericoGarciaLorca.bgr ../Books/quijote.bgr 1> tests//.out1 2>&1"
eval $CMD
rm tests//.timeout
