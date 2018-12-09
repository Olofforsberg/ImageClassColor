

#include "igg_image/io_strategies/ppm_strategy.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace igg {

  bool PpmIoStrategy::Write(const std::string& file_name,
             				const ImageData& data) const {
  	//standard image start in ppm, p3=color img, explainging text, width and height, max_value in greyscale for each color
  	std::ofstream myfile;
  	myfile.open (file_name);
  	myfile << "P3 " << "\n";
  	myfile << "# A image " << "\n";
  	myfile << data.cols << " " << data.rows << " " << "\n";
  	myfile << data.max_val << " " << "\n";
    for (int r = 0; r < data.rows; ++r) {
    	for (int c = 0; c < data.cols; ++c) {
      		int idx = r * data.cols + c;
     		myfile << data.data[0][idx] << " " << data.data[1][idx] << " " << data.data[2][idx] << " ";

    	}
    	myfile << "\n";
	}
	myfile.close();
  }  

  ImageData PpmIoStrategy::Read(const std::string& file_name) const {
  	ImageData new_img;
  	std::ifstream image_file(file_name);
  	if (!image_file) {
        std::cout << "Unable to open file" << std::endl;
        exit(1); // terminate with error
    }
  	std::string line;
  	int rows, cols, max_value;
  	getline(image_file,line);
  	getline(image_file,line);
  	getline(image_file,line);
  	std::istringstream ss_row_col(line);
  	ss_row_col>>rows>>cols;
  	getline(image_file,line);
  	std::istringstream ss_max_value(line);
  	ss_max_value>>max_value;
  	//fill these vectors with pixel values
  	std::vector<int> red_v(rows * cols);
  	std::vector<int> green_v(rows * cols);
  	std::vector<int> blue_v(rows * cols);
    int red,green,blue;
    int idx = 0;
    while (image_file >> red >> green >> blue) {
		//std::cout << " red " << red << " gren " << green  << " blue " << blue  <<  std::endl;
		red_v[idx] = red;
		green_v[idx] = green;
		blue_v[idx] = blue;
		idx++;
    }
    image_file.close();

   		//put the color vectors in the data vector in right order
   		new_img.data = {red_v, green_v, blue_v};
 		new_img.rows = rows;
 		new_img.cols = cols;
 		new_img.max_val = max_value;
  	return new_img;
  }
};

 // namespace igg