/*
 * histogram.h
 *
 *  Created on: 12.05.2011
 *      Author: jia3ep
 */

#pragma once

#include <vector>

class histogram
{
public:
  histogram();
  ~histogram();

  void init_from_YUV420SP( unsigned char* yuv420sp, int width, int height );
  void get_histograms( int* r, int* g, int* b ) const;
  int get_max_height() const { return max_height_; }
  int get_height() const { return height_; }
  int get_width() const { return width_; }

protected:
  int			width_;
  int			height_;
  mutable int	max_height_;

  std::vector<int>	rgbdata_;
};
