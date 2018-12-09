#include "image.h"
#include <functional>
#include <algorithm>
#include <iostream>

using namespace igg;


Image::Image(int rows, int cols, const IoStrategy& strategy): io_strategy{strategy}
{
	data_.reserve(cols*rows);
	rows_ = rows;
	cols_ = cols;
}
int Image::rows() const {return this->rows_; }
int Image::cols() const {return this->cols_; }
pixel Image::at(int row, int col) const { return data_[row*cols_+col]; }
pixel& Image::at(int row, int col) { return data_[row*cols_+col]; }

Image::~Image() {};

bool Image::ReadFromDisk(const std::string& file_name)
{
	igg::ImageData img_read;
	img_read = io_strategy.Read(file_name);
	rows_ = img_read.rows;
	cols_ = img_read.cols;
	max_val_ = img_read.max_val;
	data_.clear();
	data_.reserve((int) rows_ * cols_);
	for (int i = 0; i < (int) img_read.data[0].size(); ++i)
	{
		pixel new_pixel;
		new_pixel.data[0] = img_read.data[0][i];
		new_pixel.data[1] = img_read.data[1][i];
		new_pixel.data[2] = img_read.data[2][i];
		data_.push_back(new_pixel);
	}
	return (!img_read.data.empty());
}
void Image::WriteToDisk(const std::string& file_name)
{
	igg::ImageData img_saved;
	img_saved.max_val = max_val_;
	img_saved.cols = cols_;
	img_saved.rows = rows_;
	img_saved.data.reserve(3);
	std::vector<int> red(rows_ * cols_, 0);
  	std::vector<int> green(rows_ * cols_, 0);
  	std::vector<int> blue(rows_ * cols_, 0);
  	for (int i = 0; i < rows_*cols_; ++i)
  	{
  		red[i] = data_[i].data[0];
  		green[i] = data_[i].data[1];
  		blue[i] = data_[i].data[2];
  	}
	img_saved.data = {red, green, blue};
	io_strategy.Write(file_name, img_saved);
}

std::vector<float> Image::ComputeHistogram(int bins) const
{
	//compute a normalised histogram of image
	// std::vector<float> hist(bins,0);
	// float bin_width = (float) this->max_val_/bins;
	// float samples = this->cols_*this->rows_;
	// //go though imgage and create histog.
	// for (int i = 0; i < 3; ++i)
	// {
	// 	for(auto const& value: this->data_) 
	// 	{
	// 		int index = (int) value[i]/bin_width;
	// 		hist[index] += 1.0/samples; 
	// 	}
	// }
	// return hist;
}
void Image::DownScale(int scale)
{
	rows_ /= scale;
	cols_ /= scale;
	std::vector<igg::pixel> new_img(rows_*cols_);

	//this for goes through the colors red green and blue
	for (int j = 0; j < cols_; ++j)
	{
		for (int i = 0; i < rows_; ++i)
		{
			//std::cout << "i " << i << " j " << j << " i*cols_*scale+j*scale " << i*cols_*scale+j*scale << " data size "<< data_.size() << std::endl;
			new_img[(int) i*cols_+j] = data_[(int) i*cols_*(scale*scale) + (int) j*scale];
		}
	}
	data_ = new_img;
}

void Image::UpScale(int scale)
{
	rows_ *= scale;
	cols_ *= scale;
	std::vector<igg::pixel> new_img(rows_*cols_);
		//this for goes through the colors red green and blue
	for (int i = 0; i < rows_; ++i)
	{
		for (int j = 0; j < cols_; ++j)
		{
			new_img[i*cols_+j] = data_[(int) i/scale*cols_/scale + (int) j/scale];
		}
	}
	data_ = new_img;
}

void Image::Print()
{
	std::cout << " Print, data size "  << data_.size() << std::endl;
	for (int i = 0; i < data_.size(); ++i)
	{
		std::cout << " data red " << data_[i].data[0] << std::endl;
	}
/*	for (int r = 0; r < rows_; ++r) {
    	for (int c = 0; c < cols_; ++c) {
      		//int idx = r * cols_ + c;
			//data_[idx] = new_pixel;
			pixel pix = this->at(r,c);
			std::cout << " red pixel " << pix.data[0] << std::endl;

			//this->at(r,c) = new_pixel;
    	}
  	}*/
}