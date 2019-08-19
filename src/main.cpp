#include "helpers/qrng.h"
#include "modules/random_image_renderer.h"

int main() {
  printQrngInfo();

  RandomImageRenderer::renderRandomScreens();

  exit(EXIT_SUCCESS);
}
