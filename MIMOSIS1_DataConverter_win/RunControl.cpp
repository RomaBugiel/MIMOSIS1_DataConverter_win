#include "DataConverter.h"

int main()
{
	std::cout << "\n\n >>>>>>> Running data conversion for MIMOSIS1 <<<<<<<< \n\n" << std::endl;
	//std::unique_ptr<DataConverter> reader(DataConverter());
	DataConverter* reader = new DataConverter();
	reader->init();
	std::cout << *reader;
	reader->open_tree();
	reader->open_file();
	reader->fill_tree(3);
	reader->close_tree();
	return 0;
}
