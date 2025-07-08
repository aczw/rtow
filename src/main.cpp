#include <cmath>
#include <format>
#include <iostream>

constexpr int IMAGE_WIDTH = 256;
constexpr int IMAGE_HEIGHT = 256;
constexpr double MAX_RGB_COLOR = 255.0;

int main() {
  std::cout << std::format("P3\n{} {}\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

  for (int y = 0; y < IMAGE_HEIGHT; y++) {
    std::clog << std::format("\rScanlines remaining: {} ", IMAGE_HEIGHT - 1) << std::flush;

    for (int x = 0; x < IMAGE_WIDTH; x++) {
      double r = static_cast<double>(x) / (IMAGE_WIDTH - 1);
      double g = static_cast<double>(y) / (IMAGE_HEIGHT - 1);
      double b = 0.0;

      long scaled_r = std::lround(MAX_RGB_COLOR * r);
      long scaled_g = std::lround(MAX_RGB_COLOR * g);
      long scaled_b = std::lround(MAX_RGB_COLOR * b);

      std::cout << std::format("{} {} {}\n", scaled_r, scaled_g, scaled_b);
    }
  }

  // Extra spaces are a hack to overwrite previous text
  std::clog << "\rDone.                       \n";

  return 0;
}
