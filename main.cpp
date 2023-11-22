#define DR_WAV_IMPLEMENTATION
#include <mlpack.hpp>

#include "dr_wav.h"

int main(int argc, char* argv[]) {
  ///////////////////////////////////////////////////////////////////////////
  /// Doing a linear solve //////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  using namespace arma;

  mat A(5, 5, fill::randu);
  vec b(5, fill::randu);
  mat B(5, 5, fill::randu);

  vec x1 = solve(A, b);

  vec x2;
  bool status = solve(x2, A, b);

  mat X1 = solve(A, B);

  mat X2 = solve(A, B, solve_opts::fast);  // enable fast mode

  mat X3 = solve(trimatu(A), B);  // indicate that A is triangular

  ///////////////////////////////////////////////////////////////////////////
  /// Writing out a .WAV file ///////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////

  drwav_data_format format;
  format.container = drwav_container_riff;
  format.format = DR_WAVE_FORMAT_IEEE_FLOAT;
  format.channels = 1;
  format.sampleRate = 44100;
  format.bitsPerSample = 32;

  drwav* pWav = drwav_open_file_write("out.wav", &format);
  for (double d = 0; d < 10000; d += 1) {
    float f = std::sin(d);
    drwav_write(pWav, 1, &f);
  }
  drwav_close(pWav);
}
