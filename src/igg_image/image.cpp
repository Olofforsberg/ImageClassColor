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
	data_.reserve((int) img_read.data[0].size());
	for (int i = 0; i < (int) img_read.data[0].size(); ++i)
	{
		pixel new_pixel;
		new_pixel.data[0] = img_read.data[0][i];
		new_pixel.data[1] = img_read.data[1][i];
		new_pixel.data[2] = img_read.data[2][i];
		data_.push_back(new_pixel);
	}
	return (!img_read.data.empty());
	img_read.data.clear();
}
void Image::WriteToDisk(const std::string& file_name)
{
	igg::ImageData img_saved;
	img_saved.max_val = max_val_;
	img_saved.cols = cols_;
	img_saved.rows = rows_;
	img_saved.data.reserve((int) data_.size());
	for (int i = 0; i < (int) data_.size(); ++i)
	{		
		img_saved.data[0].push_back(data_[i].data[0]);
		img_saved.data[1].push_back(data_[i].data[1]);
		img_saved.data[2].push_back(data_[i].data[2]);
	}
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
	for (int c = 0; c < 3; ++c)
	{
		for (int j = 0; j < cols_; ++j)
		{
			for (int i = 0; i < rows_; ++i)
			{
				//std::cout << "i " << i << " j " << j << " i*cols_*scale+j*scale " << i*cols_*scale+j*scale << " data size "<< data_.size() << std::endl;
				new_img[(int) i*cols_+j].data[c] = data_[(int) i*cols_*(scale*scale) + (int) j*scale].data[c];
			}
		}
		data_ = new_img;
	}
}

void Image::UpScale(int scale)
{
	rows_ *= scale;
	cols_ *= scale;
	std::vector<igg::pixel> new_img(rows_*cols_);
		//this for goes through the colors red green and blue
	for (int c = 0; c < 3; ++c)
	{
		for (int i = 0; i < rows_; ++i)
		{
			for (int j = 0; j < cols_; ++j)
			{
				new_img[i*cols_+j].data[c] = data_[(int) i/scale*cols_/scale + (int) j/scale].data[c];
			}
		}
		data_ = new_img;
	}
}