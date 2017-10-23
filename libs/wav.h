#ifndef WAV_H
#define WAV_H

#define SUBCHUNK1SIZE (16)
#define AUDIO_FORMAT (1) /*formato PCM*/
#define BITS_PER_SAMPLE (16)
#define MONO (1)
#define ESTEREO (2)

#include <stdint.h>
#include <stdio.h>

typedef struct WAVHeader {
  char ChunkID[4];   /*  4 bytes   */
  int32_t ChunkSize; /*  4 bytes   */
  char Format[4];    /*  4 bytes  */

  char Subchunk1ID[4];   /*  4 bytes   */
  int32_t Subchunk1Size; /*  4 bytes  */
  int16_t AudioFormat;   /*  2 bytes   */
  int16_t NumChannels;   /*  2 bytes   */
  int32_t SampleRate;    /*  4 bytes   */
  int32_t ByteRate;      /*  4 bytes   */
  int16_t BlockAlign;    /*  2 bytes   */
  int16_t BitsPerSample; /*  2 bytes   */

  char Subchunk2ID[4];   /*  4 bytes   */
  int32_t Subchunk2Size; /*  4 bytes   */

} WAVHeader;

typedef struct MuestraMono { double muestra; } MuestraMono;

typedef struct MuestraEstereo {
  double left;
  double right;
} MuestraEstereo;

// Creación
WAVHeader newWAVHeader(int numChannels, int32_t numMuestras,
                       int32_t sampleRate);
MuestraMono newMuestraMono(double valor);
MuestraEstereo newMuestraEstereo(double left, double right);

// Escritura
int writeWAVHeader(FILE *file_p, WAVHeader wav_header);
void writeSampleMono(FILE *file_p, MuestraMono muestra);
void writeSampleEstereo(FILE *file_p, MuestraEstereo muestra);

// Lectura
WAVHeader readHeaderWAV(FILE *file_p);
MuestraMono readSampleMono(FILE *file_p, int index);
MuestraEstereo readSampleEstereo(FILE *file_p, int index);

// Mostrar en terminal
void printHeaderWAV(WAVHeader header);
void printSamplesWAV(FILE *file_p, WAVHeader header);

#endif
