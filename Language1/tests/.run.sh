touch tests//.timeout
CMD="valgrind --leak-check=full /home/roberlks222/Documentos/Clase/MP/MP2223/Language1/dist/Debug/GNU-Linux/language1  < data/SimpleTextbigrams.txt 1> tests//.out7 2>&1"
eval $CMD
rm tests//.timeout
