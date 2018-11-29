#include <gtest/gtest.h>
#include "image.h"
#include "io_strategies/strategy.h"
#include "io_strategies/dummy_strategy.h"
#include "io_strategies/png_strategy.h"
#include "io_strategies/ppm_strategy.h"

#include <iostream>

using namespace igg;

TEST(test_initiate_class,output_test)
{
	//const DummyIoStrategy strategy();
	//DummyIoStrategy& io_strad = strategy;
	Image test_img(15,15, PngIoStrategy());
	EXPECT_EQ(15,test_img.rows());
	EXPECT_EQ(15,test_img.cols());
}

TEST(test_at,output_at)
{
	//const DummyIoStrategy strategy();
	//DummyIoStrategy& io_strad = strategy;
	Image test_img(15,15, DummyIoStrategy());
	igg::pixel pixel;
	pixel.data[0] = 10, pixel.data[1] = 5, pixel.data[2] = 15;
	test_img.at(5,5) = pixel;
	EXPECT_EQ(pixel.data[0],test_img.at(5,5).data[0]);
	EXPECT_EQ(pixel.data[1],test_img.at(5,5).data[1]);
	EXPECT_EQ(pixel.data[2],test_img.at(5,5).data[2]);
}

TEST(Test_image_read,Output_test) {
	PngIoStrategy strat = PngIoStrategy();
	Image test_img(2,2,strat);
	test_img.ReadFromDisk("../data/lena.png");
	test_img.WriteToDisk("../data/lena2.png");
}

TEST(Test_image_write,Output_test) {
	PpmIoStrategy strat = PpmIoStrategy();
	Image test_img(strat);
	test_img.ReadFromDisk("../data/pbmlib.ascii.ppm");
	//test_img.WriteToDisk("../data/lena_saved.png");
}

// TEST(Scale_down,Output_test) {
// 	Image test_img;
// 	test_img.ReadFromDisk("../data/lena.png");
// 	int cols = test_img.cols();
// 	int rows = test_img.rows();
// 	test_img.DownScale(2);
// 	test_img.WriteToDisk("../data/lena_down.png");


// 	EXPECT_EQ(test_img.rows(),rows/2);
// 	EXPECT_EQ(test_img.cols(),cols/2);
// }

// TEST(Scale_Up,Output_test) {
// 	Image test_img;
// 	test_img.ReadFromDisk("../data/lena.png");
// 	int cols = test_img.cols();
// 	int rows = test_img.rows();
// 	test_img.UpScale(2);
// 	std::cout << "write" << std::endl;
// 	test_img.WriteToDisk("../data/lena_up.png");

// 	EXPECT_EQ(test_img.rows(),rows*2);
// 	EXPECT_EQ(test_img.cols(),cols*2);
// }