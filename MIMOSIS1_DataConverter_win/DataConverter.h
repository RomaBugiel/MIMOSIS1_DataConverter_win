#ifndef _DATACONVERTER_H_        // include guard 
#define _DATACONVERTER_H_        

#include "input_data_formats.h"
#include "cout_msg.h"

#include "globals.h"

#include  <cstdint>
#include  <array>

#define ROWS     504
#define COLS     1024


class DataConverter {

public:

	DataConverter() {};

	// ------- Methods 	------- 

	//Generals
	void 		init();
	int 		get_file_size();
	std::string print_hex(std::string, bool);
	friend std::ostream& operator<<(std::ostream& os, const DataConverter& treereader);


	//Maintain ROOT tree
	void	open_file();
	void 	fill_tree(int input_data_format = 3);

	void 	fill_tree_raw();
	void 	fill_tree_dec();
	void 	fill_tree_fired();

	void 	open_tree();
	void 	close_tree();

	//Input files
	std::ifstream in_file;
	long int _input_file_size{ 0 };


private:

	//System diff -- to be changed and moved to globals.h
	std::string slash;

	//Input file
	std::string _in_file_path;
	std::string _in_file_name;
	int _is_noise;

	//Output tree
	TString _out_prefix{ "" };
	TString _out_tree_file_path{ "" };
	TString _out_tree_file_name{ "" };
	TString _out_tree_name{ "" };

	//Detector parameters
	int _nb_of_rows;
	int _nb_of_columns;
	int	_nb_of_frames;
	int _row_start;
	int _row_end;
	int _column_start;
	int _column_end;

	//Data formats flags
	int _input_data_format;
	int _output_data_format;

	//TTree definition
	TFile* _output_data_file;
	TTree* _mimosis_tree;

	std::string _param_1;
	std::string _param_2;
	std::string _param_3;
	std::string _param{ "" };

	int _param_1_value;
	int _param_2_value;
	int _param_3_value;

	//Branch definition
	TH2D* h2_integrated_frame_matrix;
	TH2D* h2_integrated_frame_part;
	TH1D* h_fired_pixels_int_frame;
	TEnv config;

	~DataConverter();
};

#endif

