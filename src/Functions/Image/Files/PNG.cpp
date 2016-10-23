/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#include "../FileImage.h"


void Functions::FileImage::SaveToPNG(std::string filename, RGBA* imageRGBA, unsigned short width, unsigned short height){
	FILE *fp = NULL;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_bytep row = NULL;

	// Open file for writing (binary mode)
	fp = fopen(filename.c_str(), "wb");
	if (fp == NULL) {
		LOGSYSTEM->Error("Could not open file for writing");
		return;
	}

	// Initialize write structure
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		LOGSYSTEM->Error("Could not allocate write struct");
		fclose(fp);
		return;
	}

	// Initialize info structure
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		LOGSYSTEM->Error("Could not allocate info struct");
		fclose(fp);
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		return;
	}

	// Setup Exception handling
	if (setjmp(png_jmpbuf(png_ptr))) {
		LOGSYSTEM->Error("Error during png creation");
		fclose(fp);
		png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		return;
	}

	png_init_io(png_ptr, fp);

	// Write header (8 bit colour depth)
	png_set_IHDR(png_ptr, info_ptr, width, height,
			8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	png_write_info(png_ptr, info_ptr);

	// Allocate memory for one row (3 bytes per pixel - RGB)
	row = (png_bytep) malloc(4 * width * sizeof(png_byte));

	// Write image data
	int x, y;
	for (y=0 ; y<height ; y++) {
		for (x=0 ; x<width ; x++) {
			row[x*4] = imageRGBA[y*width + x].R;
			row[x*4+1] = imageRGBA[y*width + x].G;
			row[x*4+2] = imageRGBA[y*width + x].B;
			row[x*4+3] = imageRGBA[y*width + x].A;
		}
		png_write_row(png_ptr, row);
	}

	// End write
	png_write_end(png_ptr, NULL);

	fclose(fp);
	png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
	free(row);
}

RGBA* Functions::FileImage::LoadPNGToRGBA(std::string filename, unsigned short* width, unsigned short* height){

	    png_byte header[8];

	    FILE *fp = fopen(filename.c_str(), "rb");

	    // read the header
	    size_t result = fread(header, 1, 8, fp);
	    if (result != 8){
	    	LOGSYSTEM->Error("PNG HEADER FAILED TO READ");
	    	fclose(fp);
	    	return NULL;
	    }

	    if (png_sig_cmp(header, 0, 8))
	    {
	        LOGSYSTEM->Error("PNG HEADER IS NOT CORRECT");
	        fclose(fp);
	        return NULL;
	    }

	    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	    if (!png_ptr)
	    {
	    	LOGSYSTEM->Error("error: png_create_read_struct returned 0.");
	        fclose(fp);
	        return NULL;
	    }

	    // create png info struct
	    png_infop info_ptr = png_create_info_struct(png_ptr);
	    if (!info_ptr)
	    {
	    	LOGSYSTEM->Error("error: png_create_info_struct returned 0.");
	        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
	        fclose(fp);
	        return NULL;
	    }

	    // create png info struct
	    png_infop end_info = png_create_info_struct(png_ptr);
	    if (!end_info)
	    {
	    	LOGSYSTEM->Error("error: png_create_info_struct returned 0.");
	        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
	        fclose(fp);
	        return NULL;
	    }

	    // the code in this if statement gets called if libpng encounters an error
	    if (setjmp(png_jmpbuf(png_ptr))) {
	    	LOGSYSTEM->Error("error from libpng");
	        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	        fclose(fp);
	        return NULL;
	    }

	    // init png reading
	    png_init_io(png_ptr, fp);

	    // let libpng know you already read the first 8 bytes
	    png_set_sig_bytes(png_ptr, 8);

	    // read all the info up to the image data
	    png_read_info(png_ptr, info_ptr);

	    // variables to pass to get info
	    int bit_depth, color_type;
	    png_uint_32 temp_width, temp_height;

	    // get info about png
	    png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
	        NULL, NULL, NULL);

	    if (width){ *width = temp_width; }
	    if (height){ *height = temp_height; }

	    // Update the png info struct.
	    png_read_update_info(png_ptr, info_ptr);

	    // Row size in bytes.
	    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

	    // glTexImage2d requires rows to be 4-byte aligned
	    rowbytes += 3 - ((rowbytes-1) % 4);

	    // Allocate the image_data as a big block, to be given to opengl
	    png_byte * imageData = (png_byte *)malloc(rowbytes * temp_height * sizeof(png_byte)+15);
	    if (imageData == NULL)
	    {
	    	LOGSYSTEM->Error("error: could not allocate memory for PNG image data");
	        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	        fclose(fp);
	        return NULL;
	    }

	    // row_pointers is for pointing to image_data for reading the png with libpng
	    png_byte ** row_pointers = (png_byte **)malloc(temp_height * sizeof(png_byte *));
	    if (row_pointers == NULL)
	    {
	    	LOGSYSTEM->Error("error: could not allocate memory for PNG row pointers");
	        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	        free(imageData);
	        fclose(fp);
	        return NULL;
	    }

	    // set the individual row_pointers to point at the correct offsets of image_data
	    for (unsigned int i = 0; i < temp_height; i++)
	    {
	        row_pointers[temp_height - 1 - i] = imageData + i * rowbytes;
	    }

	    // read the png into image_data through row_pointers
	    png_read_image(png_ptr, row_pointers);

	    unsigned int size = (*width)*(*height);
	    RGBA* finalImageData = new RGBA[size];
	    for (unsigned int i = 0; i < size; i++){
	    	finalImageData[i] = {imageData[(i*4)], imageData[(i*4+1)], imageData[(i*4+2)], imageData[(i*4+3)]};
	    }

	    // clean up
	    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	    free(imageData);
	    free(row_pointers);
	    fclose(fp);
	    return finalImageData;
}
