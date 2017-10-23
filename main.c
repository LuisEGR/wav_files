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

  // Abro los archivos de entrada y de salida,
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

  // Creo una cabecera para el archivo de salida y la escribo
  whNew = newWAVHeader(MONO, cantidadDeMuestras, wh.SampleRate);
  writeWAVHeader(salida, whNew);

  // Hago la lectura muestra por muestra, cada una se divide
  // entre 2 y se escribe en el archivo de salida
  for (int i = 0; i < cantidadDeMuestras; i++) {
    muestra = readSampleMono(entrada, i);
    muestra.muestra = muestra.muestra / 2;  // Media amplitud
    writeSampleMono(salida, muestra);
  }

  // Muestro las cabeceras para comparar
  printf("\nEntrada:\n");
  printHeaderWAV(wh);

  printf("\nSalida:\n");
  printHeaderWAV(whNew);

  // Cierro los archivos
  fclose(entrada);
  fclose(salida);
}
