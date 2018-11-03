#include "image.h"
using namespace igg;
#include <functional>
#include <algorithm>
#include <iostream>

//Image::Image(const IoStrategy& strategy) {};
Image::Image(int rows, int cols, const IoStrategy& strategy): io_strategy{strategy}
{
	data_.reserve(cols*rows);
	rows_ = rows;
	cols_ = cols;
}
int Image::rows() const {return this->rows_; }
int Image::cols() const {return this->cols_; }
int Image::at(int row, int col) const { return data_[row*cols_+col]; }
int& Image::at(int row, int col) { return data_[row*cols_+col]; }

Image::~Image() {};

bool Image::FillFromPgm(const std::string& file_name)
{
	// io_tools::ImageData img = io_tools::ReadFromPgm(file_name);
	// Image(img.rows,img.cols);
	// data_ = img.data;
	// rows_ = img.rows;
	// cols_ = img.cols;
	// max_val_ = img.max_val;
	// return (!img.data.empty());
}
void Image::WriteToPgm(const std::string& file_name)
{
	// io_tools::ImageData img;
	// img.rows = this->rows_;
	// img.cols = this->cols_;
	// img.max_val = this->max_val_;
	// img.data = this->data_;
	// io_tools::WriteToPgm(img, file_name);
}

std::vector<float> Image::ComputeHistogram(int bins) const
{
	//compute a normalised histogram of image
	std::vector<float> hist(bins,0);
	float bin_width = (float) this->max_val_/bins;
	float samples = this->cols_*this->rows_;
	//go though imgage and create histog.
	for(auto const& value: this->data_) 
	{
		int index = (int) value/bin_width;
		hist[index] += 1.0/samples; 
	}
	return hist;
}
void Image::DownScale(int scale)
{
	rows_ /= scale;
	cols_ /= scale;
	std::vector<int> new_img(rows_*cols_);
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
	std::vector<int> new_img(rows_*cols_);
	for (int i = 0; i < rows_; ++i)
	{
		for (int j = 0; j < cols_; ++j)
		{
			new_img[i*cols_+j] = data_[(int) i/scale*cols_/scale + (int) j/scale];
		}
	}
	data_ = new_img;
}