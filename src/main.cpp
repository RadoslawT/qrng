#include "helpers/qrng.h"
#include "models/random_image_renderer.h"

int main() {
  printQrngInfo();

  RandomImageRenderer::renderRandomScreens();

  exit(EXIT_SUCCESS);
}
