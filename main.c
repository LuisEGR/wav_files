/****************************************************************************
Copyright (c) 2017, Luis E. González R., ESCOM, Instituto Politécnico Nacional.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
****************************************************************************/

// El objetivo de está práctica es familiarizarse con el formato de los archivos
// wav para usos futuros.

#include <stdio.h>
#include "libs/wav.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Uso: %s <entrada.wav> <salida.wav>\n", argv[0]);
    return 0;
  }
  WAVHeader wh, whNew;
  FILE *entrada, *salida;
  MuestraMono muestra;

  // Se abren los archivos de entrada y de salida,
  // si el archivo de salida no existe se crea
  entrada = fopen(argv[1], "rb");
  salida = fopen(argv[2], "wb+");
  if (entrada == NULL || salida == NULL) {
    printf("\nError al abrir el archivo!");
    exit(0);
  }
  // Se lee la cabecera del archivo de entrada
  wh = readHeaderWAV(entrada);
  int cantidadDeMuestras = wh.Subchunk2Size / 2;

  // Se crea una cabecera para el archivo de salida y la escribo
  whNew = newWAVHeader(MONO, cantidadDeMuestras, wh.SampleRate);
  writeWAVHeader(salida, whNew);

  // Se hace la lectura muestra por muestra, cada una se divide
  // entre 2 y se escribe en el archivo de salida
  for (int i = 0; i < cantidadDeMuestras; i++) {
    muestra = readSampleMono(entrada, i);
    muestra.muestra = muestra.muestra / 2;  // Media amplitud
    writeSampleMono(salida, muestra);
  }

  // Se muestra las cabeceras para comparar
  printf("\nEntrada:\n");
  printHeaderWAV(wh);

  printf("\nSalida:\n");
  printHeaderWAV(whNew);

  // Se cierran los archivos
  fclose(entrada);
  fclose(salida);
}
