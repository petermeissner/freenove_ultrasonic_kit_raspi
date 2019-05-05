
# loading package 
library(RpiR)


# initialization overhead
RpiR::init()


# blink once function
blink_once <- function (on_s = 1, off_s = 1) {
	# make sure LED is turned off on exit
	on.exit( write_digital(0, 0) )
	
	# turn LED on and wait 1s
	write_digital(0, 1)
	Sys.sleep(on_s)
	
	# turn LED off and wait 1s
	write_digital(0, 0)
	Sys.sleep(off_s)
}


# endless loop 
repeat {
	blink_once(on_s = 1, off_s = 1)
}
