#include "color.hpp"

#include <format>
#include <iostream>

constexpr int IMAGE_WIDTH = 256;
constexpr int IMAGE_HEIGHT = 256;

using namespace rtow;

int main() {
  std::cout << std::format("P3\n{} {}\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

  for (int y = 0; y < IMAGE_HEIGHT; y++) {
    std::clog << std::format("\rScanlines remaining: {} ", IMAGE_HEIGHT - 1) << std::flush;

    for (int x = 0; x < IMAGE_WIDTH; x++) {
      Color pixel_color(static_cast<double>(x) / (IMAGE_WIDTH - 1),
                        static_cast<double>(y) / (IMAGE_HEIGHT - 1), 0.0);

      write_color(std::cout, pixel_color);
    }
  }

  // Extra spaces are a hack to overwrite previous text
  std::clog << "\rDone.                       \n";

  return 0;
}
