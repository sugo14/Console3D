#include "screendata.hpp"

ScreenData::ScreenData() {
    refresh();
    clearImages();
}

void ScreenData::refresh() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            pixels[i][j] = 0;
            depthBuffer[i][j] = -100000;
        }
    }
}

int ScreenData::getPixel(int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return 0; }
    if (imagePixels[y][x] != 0) { return imagePixels[y][x]; }
    return pixels[y][x];
}

bool ScreenData::setPixel(int x, int y, float z, int color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return false; }
    if (z < depthBuffer[y][x]) { return false; }

    pixels[y][x] = color;
    depthBuffer[y][x] = z;
    return true;
}

void ScreenData::setImagePixel(int x, int y, int color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return; }
    imagePixels[y][x] = color;
}

void ScreenData::clearImages() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            imagePixels[i][j] = 0;
        }
    }
}

void ScreenData::drawLine(int x1, int y1, int x2, int y2, int color, float z) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        setPixel(x1, y1, z, color);
        if (x1 == x2 && y1 == y2) { break; }
        int err2 = err * 2;
        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void ScreenData::drawImage(Image& image, int x, int y) {
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            int pixelColor = image.getPixel(j, i);
            if (pixelColor == 0) { continue; }
            setImagePixel(x + j, y + i, pixelColor);
        }
    }
}
