#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"
#include <string>

using std::cout, std::endl, std::string, std::runtime_error;

void initializeImage(Pixel image[][MAX_HEIGHT]) {
  // iterate through columns
  for (unsigned int col = 0; col < MAX_WIDTH; col++) {
    // iterate through rows
    for (unsigned int row = 0; row < MAX_HEIGHT; row++) {
      // initialize pixel
      image[col][row] = {0, 0, 0};
    }
  }
}

void loadImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int& height) {
    // TODO: implement (part 1)
    std::ifstream file(filename);
    // check if <filename> in file
    if (!(file.is_open())) {
        throw std::runtime_error("Failed to open " + filename);
    }
    string type;
    file >> type;
    // check if P3
    if (type != "P3" && type != "p3") {
        throw std::runtime_error("Invalid type " + type);
    }
    // check dimensions
    string widthStr; string heightStr;
    file >> widthStr >> heightStr;
    width = stoi(widthStr);
    height = stoi(heightStr);
    if (file.fail() || width < 1 || width > MAX_WIDTH || height < 1 || height > MAX_HEIGHT) {
        throw std::runtime_error("Invalid dimensions");
    }
  
    // check color value
    unsigned int maxColor;
    file >> maxColor;
    if (maxColor != 255 || file.fail()) {
        throw std::runtime_error("Invalid max color value");
    }

    unsigned int totPixel = width*height;
    unsigned int pixelCount = 0;
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            Pixel pixel;
            file >> pixel.r >> pixel.g >> pixel.b;
            if (file.fail()) {
                throw std::runtime_error("Not enough values");
            }
            if (pixel.r > 255 || pixel.g > 255 || pixel.b > 255 || pixel.r < 0 || pixel.g < 0 || pixel.b < 0) {
                throw std::runtime_error("Invalid color value");
            }
            image[j][i] = pixel;  // image[column][row]
            ++pixelCount;
        }
    }
    int trash;
    if (file >> trash) {
        throw std::runtime_error("Too many values");
    }
    if (pixelCount != totPixel) {
        throw std::runtime_error("Not enough values");
    }
    file.close();
}


void outputImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height) {
  // TODO: implement (part 1)
  std::ofstream file(filename);
  file << "P3" << endl;
  file << width << " " << height << endl;  
  file << "255" << endl;

  for (unsigned int i = 0; i < height; ++i) {
      for (unsigned int j = 0; j < width; ++j) {
          file << image[j][i].r << " " << image[j][i].g << " " << image[j][i].b << " ";
      }
      file << endl;
  }

  // close file
  file.close();
}

unsigned int energy(Pixel image[][MAX_HEIGHT], unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
  // TODO: implement (part 1)
  // to find energy of a pixel, we find the horizontal and vertical energies, 
  // and then sum them to find the total energy
  int left; int right; int upper; int lower;

  if (x == width-1) {
      right = 0;
  } 
  else {
      right = x+1;
  }
  if (x == 0) {
    left = width-1; 
  } 
  else {
      left = x-1;
  }
  if (y == height-1) {
      lower = 0;
  } 
  else {
      lower = y+1;
  }
  if (y == 0) {
      upper = height-1;
  } 
  else {
      upper = y-1;
  }


  Pixel rightP = image[right][y];
  Pixel leftP = image[left][y];
  Pixel lowerP = image[x][lower];
  Pixel upperP = image[x][upper];

  // horizontal energy right-left
  int x_r = rightP.r-leftP.r;
  int x_g = rightP.g-leftP.g;
  int x_b = rightP.b-leftP.b;
  unsigned int x_2 = pow(x_r, 2)+pow(x_g, 2)+pow(x_b, 2);

  // vertical energy lower-upper
  int y_r = lowerP.r-upperP.r;
  int y_g = lowerP.g-upperP.g;
  int y_b = lowerP.b-upperP.b;
  unsigned int y_2 = pow(y_r, 2)+pow(y_g, 2)+pow(y_b, 2);

  // Total energy is the sum of the horizontal and vertical energies
  unsigned int totalEnergy = x_2+y_2;
  if (totalEnergy != 0) {
    return totalEnergy;
  }
  return 0;
}

// uncomment functions as you implement them (part 2)

unsigned int loadVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_col, unsigned int width, unsigned int height, unsigned int seam[]) {
   // TODO: implement (part 2)
   unsigned int totalEnergy = 0;
   unsigned int col = start_col;

   for (unsigned int row = 0; row < height; row++) {
    seam[row] = col;
    totalEnergy += energy(image, col, row, width, height);  // total pixel energy; columns as x and rows as y
    unsigned int minEnergy = energy(image, col, row + 1, width, height); // might need to go back and bound this section
    unsigned int next_col = col;
    if (col < width - 1) { // right neighbor
        unsigned int rightEnergy = energy(image, col + 1, row + 1, width, height);
        if (rightEnergy < minEnergy) {
            minEnergy = rightEnergy;
            next_col = col + 1;
        }
    }
    if (col > 0) { // left neighbor
        unsigned int leftEnergy = energy(image, col - 1, row + 1, width, height);
        if (leftEnergy < minEnergy) {
            minEnergy = leftEnergy;
            next_col = col - 1;
        }
    }
    col = next_col;
    }

    if (totalEnergy > 0) {
        return totalEnergy;
    }
    else{
        return 0;
    }
}

unsigned int loadHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_row, unsigned int width, unsigned int height, unsigned int seam[]) {
    // TODO: implement (part 2)
   unsigned int totalEnergy = 0;
   unsigned int row = start_row;

   for (unsigned int col = 0; col < width; col++) {
    seam[col] = row;
    totalEnergy += energy(image, col, row, width, height);  // total pixel energy; columns as x and rows as y
    unsigned int minEnergy = energy(image, col + 1, row, width, height); // might need to go back and bound this section
    unsigned int next_row = row;
    if (row < height - 1) { // lower neighbor
        unsigned int rightEnergy = energy(image, col + 1, row + 1, width, height);
        if (rightEnergy < minEnergy) {
            minEnergy = rightEnergy;
            next_row = row + 1;
        }
    }
    if (row > 0) { // upper neighbor
        unsigned int leftEnergy = energy(image, col + 1, row - 1, width, height);
        if (leftEnergy < minEnergy) {
            minEnergy = leftEnergy;
            next_row = row - 1;
        }
    }
    row = next_row;
    }

    if (totalEnergy > 0) {
        return totalEnergy;
    }
    else{
        return 0;
    }
}

void findMinVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
   // TODO: implement (part 2)
   unsigned int min = loadVerticalSeam(image, 0, width, height, seam);
   int ind = 0;
   for(unsigned int col = 0; col< width; ++col) {
       int smtg = loadVerticalSeam(image, col, width, height, seam);
       if (min > smtg) {
        min = smtg;
        ind = col;
       }
   }
   min = loadVerticalSeam(image, ind, width, height, seam);
}

void findMinHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
   // TODO: implement (part 2)
   unsigned int min = loadHorizontalSeam(image, 0, width, height, seam);
   int ind = 0;
   for(unsigned int row = 0; row < height; ++row) {
       int smtg = loadHorizontalSeam(image, row, width, height, seam);
       if (min > smtg) {
        min = smtg;
        ind = row;
       }
   }
   min = loadHorizontalSeam(image, ind, width, height, seam);
   
}

void removeVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int height, unsigned int verticalSeam[]) {
   // TODO: implement (part 2)
   for (unsigned int row = 0; row < height; ++row) {
        unsigned int start_col = verticalSeam[row];
        for (unsigned int col = start_col; col < width - 1; ++col) {
            image[col][row] = image[col + 1][row]; 
        }
    }
    width--;
}

// void removeHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int& height, unsigned int horizontalSeam[]) {
//   // TODO: implement (part 2)
// }
