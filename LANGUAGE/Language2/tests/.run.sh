touch tests//.timeout
CMD="valgrind --leak-check=full /home/roberlks222/Documents/Clase/MP/MP2223/Language2/dist/Debug/GNU-Linux/language2  ../Books/BodasdeSangre_FedericoGarciaLorca.bgr ../Books/quijote.bgr tests/output/spanish.bgr 1> tests//.out13 2>&1"
eval $CMD
rm tests//.timeout
