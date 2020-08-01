// August 18-21 2017 | Jervone Hall

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>

const int _width = 200;
const int _height = 200;

struct pixel {
    int r = 0;
    int g = 0;
    int b = 0;
	int x = 0;
	int y = 0;
};

int main() {    
    pixel grid[_width][_height];
    
    sf::Image image;
    image.create(_width, _height, sf::Color::Black);

	// Start at top center
	grid[0][149].r = 255;

	// Generate other rows using simple rules
	for(int y=0; y<_height;y++) {
		for(int i=0;i<_width-2;i++) {
			pixel a = grid[y][i];
			pixel b = grid[y][i+1];
			pixel c = grid[y][i+2];
			
			// Work of the rules
			if(y < _height - 1) {
				// 000 -> 0
				if(a.r == 0 && b.r == 0 && c.r == 0)
					grid[y+1][i+1].r = 0;
				// 100 -> 1
				if(a.r == 255 && b.r == 0 && c.r == 0) 
					grid[y+1][i+1].r = 255;
				// 010 -> 0
				if(a.r == 0 && b.r == 255 && c.r == 0)
					grid[y+1][i+1].r = 0;
				// 001 -> 1
				if(a.r == 0 && b.r == 0 && c.r == 255)
					grid[y+1][i+1].r = 255;
				// 110 -> 1
				if(a.r == 255 && b.r == 255 && c.r == 0)
					grid[y+1][i+1].r = 255;
				// 111 -> 0
				if(a.r == 255 && b.r == 255 && c.r == 255)
					grid[y+1][i+1].r = 0;
				// 011 -> 1
				if(a.r == 0 && b.r == 255 && c.r == 255)
					grid[y+1][i+1].r = 255;
				// 101 -> 0
				if(a.r == 255 && b.r == 0 && c.r == 255)
					grid[y+1][i+1].r = 0;
			}
		}		
	}
	
	// Pixels as a vector
    std::vector<pixel> pixels;

	// Push pixels from grid in to vector
    for(int i = 0; i < _width; i++) {
        for(int j = 0; j < _height; j++) {
			grid[i][j].x = j;
			grid[i][j].y = i;
			pixels.push_back(grid[i][j]);
        }
    }
	
    // Color image pixels
	for(int i=0;i<pixels.size();i++) {
        sf::Color color = image.getPixel(i, 0);
        color.r = pixels[i].r;
        image.setPixel(i, 0, color);
    }
    
    if(!image.saveToFile("output.png"))
		return -1;

	return 0;
}
