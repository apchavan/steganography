/**
 * This file contains the definitions of 'MatImage' class
 * Declaration is in 'MatImage.h'
 */
 
#include <string>
#include <iostream>
#include <cassert>
#include "MatImage.h"
#include "util.h"
#include "Error.h"

using namespace cv;
using namespace std;
using Glib::RefPtr;
using Gdk::Pixbuf;

using byte = uint8_t;
using uint = unsigned int;

namespace Steganography
{
	// Open an image file
	MatImage::MatImage(const string& filename)
		{
			mMat = imread(filename, CV_LOAD_IMAGE_COLOR);  // Loads the image from given file name with its default color
			
			// Verify for the image data is right ?
			if(not mMat.data)
				throw IOError(" Error ! Can't open the image file .... ");
				
			/**
			 * If all is ok, then convert the image from BGR to RGB format using method 'cvtColor()'
			 * This is required since OpenCV loads the image as BGR and GTK also requires the image in RGB
			 * to display correctly
			 */
			 cvtColor(mMat, mMat, CV_BGR2RGB);
		}
		
	// Create from 'Gdk::Pixbuf'
	MatImage::MatImage(const Glib::RefPtr<Gdk::Pixbuf>& p)
		{
			// Copy the 'Gdk::Pixbuf'
			RefPtr<Pixbuf> pp = p->copy();
			
			// Then convert into 'cv::mMat'
			mMat = Mat(
						Size(pp->get_width(), pp->get_height()),		// Dimensions
						CV_8UC3,										// Type
						pp->get_pixels(),								// Pointer to the data
						pp->get_rowstride()								// Bytes per row
					  );
					
			/**
			 * Any primitive type from the list can be defined by an identifier in the form 
			 * 'CV_<bit-depth>{U|S|F}C(<number_of_channels>)'
			 * where U is unsigned integer type, S is signed integer type, and F is float type, C means channels.
			 * so CV_8UC3 is an 8-bit unsigned integer matrix/image with 3 channels. 
			 * Although it is most common that this means an RGB (or actually BGR) image, it does not mandate it. 
			 * It simply means that there are three channels, and how you use them is up to you and your application. 
			 */
		}
		
	// Create from 'cv::Mat'
	MatImage::MatImage(const Mat& mat)
		{
			mMat = mat.clone();
		}
		
	// Copy constructor
	MatImage::MatImage(const MatImage& image)
		{
			mMat = image.mMat.clone();
		}
		
	// Destructor
	MatImage::~MatImage()
		{
			// Nothing to do since all clean up will be done automatically
		}
		
	// Save image with given file name to disk
	void MatImage::save(const string& filename)const
		{
			// Again convert RGB to BGR format then proceed to save
			Mat bgr;
			cvtColor(mMat, bgr, CV_RGB2BGR);
			imwrite(filename, bgr);
		}
		
	/** Getters */
	
	long MatImage::cols() const
		{
			return mMat.cols;	// Returns the number of pixels in a row (i.e. width)
		}
	
	long MatImage::rows() const
		{
			return mMat.rows;	// Returns the number of pixels in a column (i.e. height)
		}
		
	long MatImage::step() const
		{
			return mMat.step;	// Returns the number of bytes in a row
		}
		
	short MatImage::channels() const
		{
			return mMat.channels();	// Returns the number of bytes in a pixel
		}
		
	short MatImage::bps() const
		{
			return sizeof(*mMat.data)*8;	// Returns the number of bits per sample
		}
		
	byte * MatImage::data() const
		{
			return mMat.data;	// Returns the pointer to pixel array
		}
		
	long MatImage::max() const
		{
			return (cols()*(rows()-1))/3;	// Returns the maximum size of text that this image can hide
		}
		
	bool MatImage::empty() const
		{
			return mMat.empty();	// Check whether the image is empty or not
		}
		
	// Converts the image to 'Gdk::Pixbuf' object
	RefPtr<Pixbuf> MatImage::pixbuf() const
		{
			return Gdk::Pixbuf::create_from_data(
													mMat.data,				// Pointer to the pixels array
													Gdk::COLORSPACE_RGB,	// Colorspace RGB only
													false,					// Transparancy ?
													8,						// Bits per sample always 8
													mMat.cols,				// Width
													mMat.rows,				// Height
													mMat.step				// Bytes per row ('get_rowstride()' or 'step')
												);
		}
		
	// Scales the image to the desired size
	RefPtr<Pixbuf> MatImage::scale(int width, int height) const
		{
			// Both width and height can't be zero
			if(width<=0 and height<=0)
				throw invalid_argument("Both width and height can not be zero at same time");
				
			// Get aspect ratio of original image
			double ratio = static_cast<double>(cols())/rows();
			/**
			 * 'static_cast' is used for cases where you basically want to reverse an implicit conversion, 
			 * with a few restrictions and additions. static_cast performs no runtime checks. 
			 * This should be used if you know that you refer to an object of a specific type, 
			 * and thus a check would be unnecessary.
			 * 
			 * 'dynamic_cast' is useful when you don't know what the dynamic type of the object is. 
			 * It returns a null pointer
			 * if the object referred to doesn't contain the type casted to as a base class 
			 * (when you cast to a reference, a bad_cast exception is thrown in that case).
			 */
			 
			 // Now either width or height is zero then adjust it to maintain the ratio
			 if(width<=0)
			 	width = height*ratio;
			 else if(height<=0)
			 	height=width/ratio;
			 	
			 // Now scale the image & return
			 return this->pixbuf()->scale_simple(width, height, Gdk::INTERP_BILINEAR);
		}
	
	// Returns the scaled image that fit into the given dimenstion
	RefPtr<Pixbuf> MatImage::fit(int width, int height) const
		{
			// Width or height must not be zero
			if(width<1 or height<1)
				throw invalid_argument("Width and height should be greater than zero ! ");
				
			// Get ratio of window
			double win_ratio = static_cast<double>(width)/height;
			// Now, get ratio of image
			double img_ratio = static_cast<double>(cols())/rows();
			
			// Fit the image 
			if( win_ratio > img_ratio )
				return this->scale(0, height);
			else
				return this->scale(width, 0);
		}
		
	// Display the image using OpenCV 
	void MatImage::show(int msecs) const
		{
			// Create a window
			namedWindow("MatImage", CV_WINDOW_NORMAL);
			// Display image in the window
			imshow("MatImage", mMat);
			// Wait for 'msecs'
			waitKey(msecs);			
		}
		
	// Steg definition
	MatImage& MatImage::steg(const string& text, const string& key)
		{
			// Check for exceptions
			if(empty())
				throw ImageEmptyError();
				
			if(text.empty())
				throw TextEmptyError();
				
			if(key.empty())
				throw KeyEmptyError();
				
			if(cols() < 80)
				throw InsufficientImageError(" Size error :Image is of too small size ! ");
			
			if(text.size() >= max())
				throw InsufficientImageError(" Insufficient image capacity error : The text to be hidden is large than the image ! ");
			
			// If everything is valid, then proceed to 'steg'
			
			// First steg the key using 'set_key()'
			set_key(key);
			
			// After that, steg the text using 'conceal()'
			conceal(text, key);
			
			return (*this);
		}
		
	// Unsteg definitions
	string MatImage::unsteg(const string& key)const
		{
			// Check for the necessary conditions first
			assert(sha(key).size()==20);
			
			if(empty())
				throw ImageEmptyError();
				
			if(cols() < 80)
				throw InsufficientImageError(" The image is not stego ");
				
			if(sha(key) != hash(key))
				throw KeyMismatchError();
				
			// Decrypt and return the key
			return reveal(key);
		}
		
	/** Respective definitions for 'private' helper methods. */
	
	// set_key() definition
	void MatImage :: set_key(const string& key)
		{
			// Password should not be the empty
			if(key.empty())
				throw KeyEmptyError();
			
			// Now we store SHA-1 digest of key in the image and NOT the key in original form
			string hash = sha(key);
			assert(hash.size()==20);
			
			// Key will be used to choose the store bits and ignore color
			auto kit = key.begin();
			
			// The will be written to the first row of the image in the form of hash
			auto mit = mMat.begin<Vec3b>();
			
			// For every character or byte of image
			for( auto hit = hash.begin(); hit != hash.end(); ++hit)
				{
					// Get the color to ignore
					int ignore = static_cast<uint>(*(kit++))%8;
					if(kit == key.end()) kit=key.begin();
					
					// Set bits
					uchar c = static_cast<uchar>(*hit);
					int i=0, b=0;
					
					// 3 pixels for each byte
					for( int px = 0 ; px < 3 ; ++px, ++mit)
						{
							// 3 colors for each pixel
							for( int color = 0; color < 3; ++color, ++i)
								{
									// Don't use the ignore color
									if(i != ignore)
										{
											// Get the store bit
											int s = static_cast<int>(*(kit++))%2;
											if(kit == key.end()) kit = key.begin();
											
											// Now store the bit 
											setbit( (*mit)[color], getbit(c, b++), s);
										}
								} // 'for( int color = 0; color < 3; ++color, ++i)' closed.
								
						} // 'for( int px = 0 ; px < 3 ; ++px, ++mit)' closed.
						
				} // 'for( auto hit = hash.begin(); hit != hash.end(); ++hit)' closed.
				
		} // 'set_key()' closed.
		
	// conceal() definition
	void MatImage :: conceal(const string& text, const string& key)
		{
			// Check for pre-conditions
			if(text.empty())
				throw TextEmptyError();
			if(key.empty())
				throw KeyEmptyError();
				
			// If all ok, then start writing the text from the second row of the image
			auto mit = mMat.begin<Vec3b>() + cols();
			
			// Add '\0' to the end of the text for indication while decrypting later
			auto txt = text;
			txt.push_back(0);
			
			// The key will be used to choose store the bits and ignore color
			auto kit = key.begin();
			
			// For each character or byte of the text
			for( auto tit = txt.begin() ; tit != txt.end() ; ++tit)
				{
					// Get the ignore bit
					int ignore = static_cast<uint>(*(kit++))%9;
					if(kit == key.end()) kit=key.begin();
					
					// Set the bits
					uchar c = static_cast<uchar>(*tit);
					int i=0, b=0;
					
					// 3 pixels for each byte
					for(int px=0; px<3; ++px, ++mit)
						{
							// 3 colors for each pixel
							for(int color=0; color<3 ; ++color, ++i)
								{
									// Don't use the ignore color
									if(i!=ignore)
										{
											// Get the store bit
											int s = static_cast<uint>(*(kit++))%2;
											if(kit==key.end()) kit=key.begin();
											
											// Store the bit
											setbit( (*mit)[color], getbit(c, b++), s);
										}
								}
						}
				}
		} // 'conceal()' closed.
		
	// Reveal the text hidden
	string MatImage::reveal(const string& key)const
		{
			string text;
			
			// Key will be used to store the bits and the ignore color
			auto kit = key.begin();
			
			// Start iterating the pixels from the second row
			for( auto mit = mMat.begin<Vec3b>()+cols() ; ; )
				{
					// Get the ignore color 
					int ignore = static_cast<uint>(*(kit++))%9;
					if(kit == key.end()) kit = key.begin();
					
					// Set the bits
					uchar c;
					int b=0, i=0;
					
					// 3 pixels for each byte
					for(int px=0; px<3; ++px, ++mit)
						{
							// 3 colors for each pixels
							for(int color=0; color<3; ++color, ++i)
								{
									// Don't use the ignore color
									if(i != ignore)
										{
											// Get the store bit
											int s = static_cast<uint>(*(kit++))%2;
											if(kit == key.end()) kit=key.begin();
											
											// Get the bit from the color
											setbit( c, getbit((*mit)[color], s), b++);
										}
								}
						}
					// After getting each byte, check first whether it is the end of the text
					if( c == 0 ) break;
					text.push_back(c);
				}
			return (text);
		} // 'reveal()' closed.
		
	// Get the hash string of the key
	string MatImage::hash(const string& key) const
		{
    		string hash;

    		// Key will be used to choose store bits and ignore color
		    auto kit = key.begin();

		    // Start iterating the pixels from 1st row
		    auto mit = mMat.begin<Vec3b>();
		    
	        // The hash is 20 bytes long
	        for (int size = 0; size < 20; ++size)
	        	{
			        // Get the ignore color
			        int ignore = static_cast<uint>(*(kit++)) % 8;
			        if (kit == key.end()) kit = key.begin();

			        // Set bits
        			uchar c;
			        int b = 0, i = 0;

			        // 3 pixels for each byte
			        for (int px = 0; px < 3; ++px, ++mit)
			        	{
				            // 3 colors for each pixel
				            for (int color = 0; color < 3; ++color, ++i)
				            	{
					                // Don't use the ignore color
					                if (i != ignore) 
					                	{
						                    // Get the store bit
						                    int s = static_cast<uint>(*(kit++)) % 2;
						                    if (kit == key.end()) kit = key.begin();

						                    // Get the bit from the color
						                    setbit(c, getbit((*mit)[color], s), b++);
						                }	// 'if (i != ignore)' closed.

					            }	// 'for (int color = 0; color < 3; ++color, ++i)' closed.

				        }	// 'for (int px = 0; px < 3; ++px, ++mit)' closed.

			        hash.push_back(c);
    			}	// 'for (int size = 0; size < 20; ++size)' closed.

 		   return (hash);    
		} // 'hash()' closed.

} // namespace 'Steganography' closed.
