#pragma once

#include <vector>
//#include "io_tools.h"
#include "io_strategies/strategy.h"

namespace igg {

	struct pixel
	{//pixel with [0]-red [1]-green [2]-blue
	int data[3];
	};

	class Image {
		public:
			Image(const IoStrategy& strategy): io_strategy{strategy}{};
			Image(int rows, int cols, const IoStrategy& strategy);
			int rows() const;
			int cols() const;
			pixel at(int row, int col) const;
			pixel& at(int row, int col);
			bool ReadFromDisk(const std::string& file_name);
			void WriteToDisk(const std::string& file_name);
			std::vector<float> ComputeHistogram(int bins) const;
			void DownScale(int scale);
			void UpScale(int scale);
			igg::pixel Pixel;
			void Print();

			~Image();
		private:
			int rows_ = 0;
			int cols_ = 0;
			int max_val_ = 255;
			std::vector<igg::pixel> data_;
			const IoStrategy& io_strategy;
	};
}  // namespace igg