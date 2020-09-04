#include "DataConverter.h"

//-------------------------------------------------------------------------------------------------


std::ostream& operator<<(std::ostream& os, const DataConverter& dataconverter)
{
	os << std::setw(30) << " Data Converter is run with: " << std::endl;
	os << std::setw(30) << "_in_file_path: " << dataconverter._in_file_path << std::endl;
	os << std::setw(30) << "_in_file_name: " << dataconverter._in_file_name << std::endl;
	os << std::setw(30) << "_out_tree_file_path: " << dataconverter._out_tree_file_path << std::endl;
	os << std::setw(30) << "_out_tree_file_name: " << dataconverter._out_tree_file_name << std::endl;
	os << std::setw(30) << "_out_prefix: " << dataconverter._out_prefix << std::endl;
	os << std::setw(30) << "_out_tree_name: " << dataconverter._out_tree_name << std::endl;
	os << std::setw(30) << "_is_noise: " << dataconverter._is_noise << std::endl;
	os << std::setw(30) << "_param_1: " << dataconverter._param_1 << std::endl;
	os << std::setw(30) << "_param_2: " << dataconverter._param_2 << std::endl;
	os << std::setw(30) << "_param_3: " << dataconverter._param_3 << std::endl;
	os << std::setw(30) << "_param_1_value: " << dataconverter._param_1_value << std::endl;
	os << std::setw(30) << "_param_2_value: " << dataconverter._param_2_value << std::endl;
	os << std::setw(30) << "_param_3_value: " << dataconverter._param_3_value << std::endl;
	os << std::setw(30) << "_input_data_format: " << dataconverter._input_data_format << std::endl;
	os << std::setw(30) << "_output_data_format: " << dataconverter._output_data_format << std::endl;
	os << std::setw(30) << "_nb_of_rows: " << dataconverter._nb_of_rows << std::endl;
	os << std::setw(30) << "_nb_of_columns: " << dataconverter._nb_of_columns << std::endl;
	os << std::setw(30) << "_row_start : " << dataconverter._row_start << std::endl;
	os << std::setw(30) << "_row_end : " << dataconverter._row_end << std::endl;
	os << std::setw(30) << "_column_start : " << dataconverter._column_start << std::endl;
	os << std::setw(30) << "_column_end : " << dataconverter._column_end << std::endl;
	return os;
}

//-------------------------------------------------------------------------------------------------

void DataConverter::init()
{
	MSG(DEB, "init() --> starts");

	if(!SYSTEM_SEL.compare("win")) 
	{	
		MSG(CNTR, "\tSYSTEM: WINDOWS")
		slash = backslash;
		
		if(config.ReadFile("config_windows.txt", kEnvUser) < 0)
		{ 	
			MSG(ERR,  "Could not read configuration file in DataConverter - exit")
			exit(0);
		}
	}
	else if(!SYSTEM_SEL.compare("unix")) {
		
		MSG(CNTR, "\tSYSTEM: LINUX")
		slash = forwardslash;
		
		if(config.ReadFile("config_linux.txt", kEnvUser) < 0)
		{ 	
			MSG(ERR, "Could not read configuration file in DataConverter - exit")
			exit(0);
		}
	}
	else 
	{
		MSG(ERR, "Define WINDOWS or LINUX !!! ")
		exit(0);
	}
	
	MSG(CNTR, "\tslash: " << slash )


	_in_file_path = config.GetValue("_in_file_path", "");
	_in_file_name = config.GetValue("_in_file_name", "");
	_out_tree_file_path = config.GetValue("_out_tree_file_path", "");
	_out_tree_file_name = config.GetValue("_out_tree_file_name", "test_tree");
	_out_prefix = config.GetValue("_out_prefix", "");

	_out_tree_name = config.GetValue("_out_tree_name", "tree_fired_mimosis1");

	_is_noise = config.GetValue("_is_noise", 1);

	_param_1 = config.GetValue("_param_1", "");
	_param_2 = config.GetValue("_param_2", "");
	_param_3 = config.GetValue("_param_3", "");

	_param_1_value = config.GetValue("_param_1_value", 0);
	_param_2_value = config.GetValue("_param_2_value", 0);
	_param_3_value = config.GetValue("_param_3_value", 0);

	_input_data_format = config.GetValue("_input_data_format", 3);
	_output_data_format = config.GetValue("_output_data_format", 1);

	_nb_of_rows = config.GetValue("_nb_of_rows", 0);
	_nb_of_columns = config.GetValue("_nb_of_columns", 0);
	_nb_of_frames = config.GetValue("_nb_of_frames", -1);
	_row_start = config.GetValue("_row_start", 0);
	_row_end = config.GetValue("_row_end", 0);
	_column_start = config.GetValue("_column_start", 0);
	_column_end = config.GetValue("_column_end", 0);

	_param = _param_1 + "_" + std::to_string(_param_1_value) + "_" +
		_param_2 + "_" + std::to_string(_param_2_value) + "_" +
		_param_3 + "_" + std::to_string(_param_3_value);

	MSG(CNTR, "\tThe _params are: " + _param);

}

// -------------------------------------------------------------------------------------------------

void DataConverter::open_tree()
{

	MSG(DEB, "open_tree() --> starts ");
	TString out_name{ "" };
	const int nb_of_bins_x{ (_column_end - _column_start) + 1 };
	const int nb_of_bins_y{ (_row_end - _row_start) + 1 };

	if (_is_noise)
	{
		out_name = _out_tree_file_path + "\\" +
			_out_tree_file_name + "_" +
			"NOISE" +
			_out_prefix +
			".root";
	}
	else
	{
		out_name = _out_tree_file_path + "\\" +
			_out_tree_file_name + "_" +
			_param + "_" +
			_out_prefix +
			".root";
	}


	//Create output file
	_output_data_file = nullptr;
	_output_data_file = TFile::Open(out_name, "RECREATE");

	if (!_output_data_file)
	{
		MSG(ERR, "Could not open output ROOT tree - exit")
			exit(0);
	}
	else
	{
		MSG(INFO, "ROOT tree location: " << out_name);
		MSG(INFO, "Tree name: " << _out_tree_name)

		// Create a TTree
		_output_data_file->cd();
		_mimosis_tree = new TTree(_out_tree_name, _out_tree_name);

		TString histo_name;
		if (_is_noise) 	histo_name = "noise";
		else 			histo_name = _param;

		MSG(CNTR, "\tThe core to histo name is: " + histo_name);


		//Add TTree members  

		h2_integrated_frame_matrix = new TH2D("h2_integrated_frame_matrix", "Integrated frame (N=" + TString::Itoa(_nb_of_frames,10) +") for: " + histo_name + " - entire matrix; row; colum", _nb_of_columns, 0, _nb_of_columns, _nb_of_rows, 0, _nb_of_rows);
		h2_integrated_frame_part = new TH2D("h2_integrated_frame_part", "Integrated frame (N=" + TString::Itoa(_nb_of_frames, 10) + ") for: " + histo_name + "; row; colum", nb_of_bins_x, _column_start, _column_end + 1, nb_of_bins_y, _row_start, _row_end + 1);

		h_fired_pixels_int_frame = new TH1D("h_fired_pixels_integrated_frame", "Multiplicity of hits per pixel integrated from " + TString::Itoa(_nb_of_frames, 10), _nb_of_frames, 0, _nb_of_frames);
		
	}

}

// -------------------------------------------------------------------------------------------------

void DataConverter::close_tree()
{
	MSG(DEB, "close_tree() --> starts");

	_output_data_file->Write();
	_output_data_file->Close();

}

// -------------------------------------------------------------------------------------------------

int DataConverter::get_file_size()
{
	MSG(DEB, "get_file_size() --> starts");

	in_file.seekg(0, in_file.end);
	int length = in_file.tellg();
	in_file.seekg(0, in_file.beg);

	return length;
}

// -------------------------------------------------------------------------------------------------

std::string DataConverter::print_hex(std::string s, bool upper_case)
{
	MSG(DEB, "print_hex() --> starts");

	std::ostringstream ret;
	int z{ 0 };

	//String::size_type i -- 8 bits
	for (std::string::size_type i = 0; i < s.length(); ++i)
	{
		z = s[i] & 0xff;
		ret << std::hex << std::setfill('0') << std::setw(2) << (upper_case ? std::uppercase : std::nouppercase) << z << " ";
	}

	return ret.str();
}

// -------------------------------------------------------------------------------------------------


void DataConverter::open_file()
{
	//Open file
	in_file.open(_in_file_path + slash + _in_file_name, std::ios::out | std::ios::in | std::ios::binary);

	in_file.seekg(0, std::ios::beg);
	_input_file_size = get_file_size();

	if (!in_file.is_open())
	{
		MSG(ERR, "There is no input file:" << _in_file_path + slash + _in_file_name << " -- exit");
		exit(0);
	}
	else {
		MSG(INFO, "Input file loaded: " << _in_file_path << slash << _in_file_name);
		MSG(INFO, "Input file length: " << _input_file_size);
	}
	std::cout << "Control 0" << std::endl;

}

// -------------------------------------------------------------------------------------------------
void DataConverter::fill_tree(int input_data_format) {
	
	std::cout << "input_data_format" << input_data_format << std::endl;

	switch (input_data_format)
	{
	case 1: { fill_tree_raw(); 		break; }
	case 2: { fill_tree_dec(); 		break; }
	case 3: { fill_tree_fired(); 	break; }
	default: {
		MSG(WARN, "Input data format not provided. Fired-DAQ format will be launched.");
		fill_tree_fired(); break;
	}
	}
}
// -------------------------------------------------------------------------------------------------

void DataConverter::fill_tree_raw()
{
	MSG(INFO, "Input data format: RAW-DAQ.");
}

// -------------------------------------------------------------------------------------------------

void DataConverter::fill_tree_dec()
{
	MSG(INFO, "Input data format: DEC-DAQ.");
}

// -------------------------------------------------------------------------------------------------

void DataConverter::fill_tree_fired()
{
	MSG(INFO, "Input data format: fired-DAQ format.");

	Integrated_Frame* input = new Integrated_Frame;
	//Integrated_Frame 	input; // doesn't work on Windows because of large array?

	long int			current_position{ static_cast<long>(in_file.tellg()) };
	unsigned int		how_many_hits{ 0 };

	while (!in_file.eof())
	{
		//Avoids additional entry when the file over but not -1 yet
		if (current_position == _input_file_size) break;


		// Read array of integrated frame 
		//in_file.read((char*)&input, sizeof(input));
		in_file.read((char*)input, sizeof((*input)));

	}

	long int row_nb = ( &(input->integrated_frame[0]) )->size();
	long int col_nb = (input->integrated_frame).size();

	//std::cout << print_hex( std::string( (char*) &input, sizeof(input)), true) << std::endl;;
	
	MSG(CNTR, "\tInput array is: " + std::to_string(col_nb) + " per " + std::to_string(row_nb) );

	for (long unsigned int col_it = 0; col_it < col_nb; col_it++)
	{
		for (long unsigned int row_it = 0; row_it < row_nb; row_it++)
		{
			how_many_hits = input->integrated_frame[col_it][row_it];
			if (how_many_hits == 0) continue;

			MSG(DEB, "\t\tFired pixel: " + std::to_string(col_it) + " " + std::to_string(row_it) + " --> " + std::to_string(how_many_hits));

			h2_integrated_frame_matrix->Fill(col_it, row_it, how_many_hits);
			h2_integrated_frame_part->Fill(col_it, row_it, how_many_hits);
			h_fired_pixels_int_frame->Fill(how_many_hits);

		}
	}
}

