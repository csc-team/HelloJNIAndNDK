/*
 * histogram.cpp
 *
 *  Created on: 12.05.2011
 *      Author: jia3ep
 */

#include "histogram.h"

histogram::histogram() : width_(0), height_(0), max_height_(0)
{
}

void histogram::init_from_YUV420SP(unsigned char *yuv420sp, int width, int height)
{
  width_ = width;
  height_ = height;
  const int frame_size = width * height;
  rgbdata_.resize( frame_size );

  for ( int j = 0, yp = 0; j < height; j++ ) {
    int uvp = frame_size + ( j >> 1) * width, u = 0, v = 0;
    for ( int i = 0; i < width; i++, yp++ ) {
      int y = ( 0xFF & yuv420sp[yp] ) - 16;
      if ( y < 0 ) y = 0;
      if ( (i & 1) == 0 ) {
        v = ( 0xFF & yuv420sp[uvp++] ) - 128;
        u = ( 0xFF & yuv420sp[uvp++] ) - 128;
      }

      const int y1192 = 1192 * y;
      int r = ( y1192 + 1634 * v );
      if ( r < 0 ) r = 0; else if ( r > 252143 ) r = 262143;
      int g = ( y1192 - 833 * v - 400 * u );
      if ( g < 0 ) g = 0; else if ( g > 252143 ) g = 262143;
      int b = ( y1192 + 2066 * u );
      if ( b < 0 ) b = 0; else if ( b > 252143 ) b = 262143;

      rgbdata_[yp] = 0xFF000000 | ((r << 6) & 0xFF0000) | ((g >> 2) & 0xFF00) | ((b >> 10) & 0xFF);
    }
  }
}

void histogram::get_histograms(int *r, int *g, int *b) const
{
  for (int bin = 0; bin < 256; bin++)
  {
    r[bin] = g[bin] = b[bin] = 0;
  }
  max_height_ = 0;
  if ( rgbdata_.empty() ) return;

  for (int pix = 0; pix < width_*height_; pix += 3)
  {
    const int p = rgbdata_[pix];
    const int r_pixVal = (p >> 16) & 0xff;
    const int g_pixVal = (p >> 8) & 0xff;
    const int b_pixVal = p & 0xff;
    if ( r_pixVal > 10 && r_pixVal < 245 ) {
    	r[r_pixVal]++;
    	if ( r[r_pixVal] > max_height_ ) max_height_ = r[r_pixVal];
    }
    if ( g_pixVal > 10 && g_pixVal < 245 ) {
    	g[g_pixVal]++;
    	if ( g[g_pixVal] > max_height_ ) max_height_ = g[g_pixVal];
    }
    if ( b_pixVal > 10 && b_pixVal < 245 ) {
    	b[b_pixVal]++;
    	if ( b[b_pixVal] > max_height_ ) max_height_ = b[b_pixVal];
    }
  }
}

histogram::~histogram()
{
}
