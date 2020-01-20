#include <stdlib.h>

#include "init.h"
#include "dft.h"
#include "handlers.h"

int main() {
	buf = calloc(sizeof(complex), NR_SAMPLES);
	scratch = calloc(sizeof(complex), NR_SAMPLES);
	
	init();
	
	while(true) {
		if(curr_nr_samples >= NR_SAMPLES) {
			disable_timer();
			
			fft(buf, NR_SAMPLES, scratch);
			draw_chart(buf, NR_SAMPLES);
			
			curr_nr_samples = 0;
			
			enable_timer();
		}
	}
}
