

#include "igg_image/io_strategies/ppm_strategy.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace igg {

  bool PpmIoStrategy::Write(const std::string& file_name,
             const ImageData& data) const {
  	//somethiug
  }
  ImageData PpmIoStrategy::Read(const std::string& file_name) const {
  	ImageData new_img;
  	std::ifstream image_file(file_name);
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

  	if (image_file.is_open())
  	{
  		while(getline(image_file,line))
  		{
  			std::istringstream ss(line);
  			//take out colours from each pixel
  			int red, green, blue;
  			while(ss>>red>>green>>blue)
  			{
  				red_v.push_back(red);
  				green_v.push_back(green);
  				blue_v.push_back(blue);
  			}
   		}
   		//put the color vectors in the data vector in right order
   		new_img.data = {red_v, green_v, blue_v};
 		new_img.rows = rows;
 		new_img.cols = cols;
 		new_img.max_val = max_value;
  	}
  	return new_img;
  }
};

 // namespace igg