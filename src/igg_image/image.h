#pragma once

#include <vector>
//#include "io_tools.h"
#include "io_strategies/strategy.h"


namespace igg {

	class Image {
		public:
			Image(const IoStrategy& strategy): io_strategy{strategy}{};
			Image(int rows, int cols, const IoStrategy& strategy);

			int rows() const;
			int cols() const;
			int at(int row, int col) const;
			int& at(int row, int col);
			bool FillFromPgm(const std::string& file_name);
			void WriteToPgm(const std::string& file_name);
			std::vector<float> ComputeHistogram(int bins) const;
			void DownScale(int scale);
			void UpScale(int scale);

			~Image();
		private:
			int rows_ = 0;
			int cols_ = 0;
			int max_val_ = 255;
			std::vector<int> data_;
			const igg::IoStrategy& io_strategy;
	};
}  // namespace igg