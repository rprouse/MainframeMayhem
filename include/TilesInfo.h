// From ZGB - https://github.com/Zal0/ZGB/blob/master/common/include/TilesInfo.h
#ifndef TILES_INFO_H
#define TILES_INFO_H

struct TilesInfo {
	unsigned char num_frames;
	unsigned char* data;
	unsigned char num_pals;
	unsigned int* pals;
	unsigned char* color_data;
};

#endif