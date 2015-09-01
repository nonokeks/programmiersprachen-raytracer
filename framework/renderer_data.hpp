#ifndef BUW_RENDERER_DATA_HPP
#define BUW_RENDERER_DATA_HPP 

struct Renderer_data {

	Renderer_data():
	width{0},
	height{0},
	camera_name{""},
	filename{""}{}
	
	Renderer_data(unsigned x, unsigned y, std::string const& camera, std::string const& file):
		width{x},
		height{y},
		camera_name{camera},
		filename{file} {}
	
	unsigned width;
	unsigned height;
	std::string camera_name;
	std::string filename;
};

#endif