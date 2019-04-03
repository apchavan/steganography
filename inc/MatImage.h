/**
  * This file contains declaration of 'MatImage' class i.e. used to represent an image.
  * 'MatImage' class provides the basic methods to manipulate image for hiding the text inside them.
  */
 
 #ifndef MATIMAGE_H
 #define MATIMAGE_H
 
 #include <string>
 #include <gtkmm.h>
 #include <opencv2/core/core.hpp>
 #include <opencv2/highgui/highgui.hpp>
 #include <opencv2/imgproc/imgproc.hpp>
 
 namespace Steganography
 {
 	/**
 	 * Class to represent an image & hide the text within it.
 	 */
 	  
 	class MatImage
 		{
 			private : 
 				/** The OpenCV's image class to hold our data */
 				cv::Mat mMat;
 				
 				/** Helpers */
 				
 				/** Set the key view, the text hidden in the image */
 				void set_key(const std::string& key);
 				
 				/** Conceals the given 'text' in the image */
 				void conceal(const std::string& text,const std::string& key);
 				
 				/** Return  the SHA-1 hashed string of key set for image */
 				std::string hash(const std::string& key) const;
 				
 				/** Returns the text hidden in the image */
 				std::string reveal(const std::string& key) const;
 				
 			public : 
 				/** Create an empty image with nothing */
 				MatImage() = default;
 				
 				/** Create an object of 'MatImage' class from image file name */
 				MatImage(const std::string& filename);
 				
 				/** Create an object of 'MatImage' class from 'Pixbuf' object */
 				MatImage(const Glib::RefPtr<Gdk::Pixbuf>& p);
 				
 				/** Create an object of 'MatImage' class from 'Mat' object */
 				MatImage(const cv::Mat& mat);
 				
 				/** Copies an object of 'MatImage' class to another object */
 				MatImage(const MatImage& image);
 				
 				/** Destructor for class 'MatImage' */
 				virtual ~MatImage();
 				/**
 				 * Desciption for 'virtual ~TextFile();' :=>
 				 * Virtual destructors are useful when you have a parent and child class, and you want to delete an 
 				 * instance of the base class by first deleting the instance of the child class. This prevents a memory 
 				 * leak, which would have otherwise happenened if your destructor was not virtual; the base class instance 
 				 * would only have been deleted, leaving the derived instance to cause a memory leak. 
 				 */
 				 
 				 /** To save the image with the given filename */
 				 void save(const std::string& filename) const;
 				 
 				 /** Getters */
 				 
 				 long cols() const;  // Returns the number of pixels in a row (i.e. width)
 				 long rows() const;  // Returns the number of pixels in a column (i.e. height)
 				 long step() const;  // Returns the number of bytes in a row
 				 short channels() const;  // Returns the number of bytes in a pixel
 				 short bps() const;  // Returns the number of bits per sample
 				 uint8_t * data() const;  // Returns the pointer to pixel array
 				 long max() const;  // Returns the maximum size of text that this image can hide
 				 bool empty() const;  // Check whether the image is empty or not
 				 
 				 /**
 				  * Converts the image to 'Gdk::Pixbuf' object
 				  * This can also be used to display image in Gtk window
 				  * @return 'Gdk::Pixbuf' object of image
 				  **/
 				 Glib::RefPtr<Gdk::Pixbuf> pixbuf() const;
 				 
 				 /**
 				  * Scales the image to the desired size
 				  * One parameter is set to 0, it is adjusted to keep aspect ratio
 				  * @param width			The width of desired size
 				  * @param height			The height of desired size
 				  * 
 				  * @return A scaled 'Gdk::Pixbuf' object
 				  */
 				 Glib::RefPtr<Gdk::Pixbuf> scale(int width, int height) const;
 				 
 				 /**
 				  * Scales the image to fit in the desired size
 				  * @param width			The width of desired size
 				  * @param height			The height of desired size
 				  * 
 				  * @return A scaled 'Gdk::Pixbuf' object that fits in the given size 
 				  */
 				 Glib::RefPtr<Gdk::Pixbuf> fit(int width, int height) const;
 				 
 				 /**
 				  * Displays the image for certain amount of time
 				  * @param msecs	Number of milliseconds to display
 				  */
 				 void show(int msecs = 0) const;
 				 
 				 /**
 				  * Hide the text inside the image
 				  * This will hide the text in the object itself without creating the new object
 				  * @param		The text to be hidden
 				  * @param		The password reqired to get hidden text after
 				  *
 				  * @return		The object of class 'MatImage' itself
 				  */
 				  MatImage& steg(const std::string& text, const std::string& key);
 				  
 				  /**
 				   * Get the hidden text from the image
 				   * @param		The password required to get the hidden text
 				   * @return	The hidden text
 				   */
 				  std::string unsteg(const std::string& key) const;
 		};	// class 'MatImage' closed.
 		
 }	// namespace 'Steganography' closed.
 
 #endif	// 'MATIMAGE_H' closed.
