

#include  <cstdint>
#include  <array>

#define ROWS     504
#define COLS     1024


// -----------------   Integrated Frame --------------------------

struct Integrated_Frame
{
	//uint32_t int_frame[1024][504];
	std::array<  std::array<uint32_t, ROWS>, COLS> integrated_frame;

};

