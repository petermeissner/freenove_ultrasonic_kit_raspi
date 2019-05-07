
# loading package 
library(RpiR)


# initialization overhead
RpiR::init()
RpiR::pin_mode(0, "out")


# assing pin numbers
ledPin    <- 0 
buttonPin <- 1

# set up mode of pins
pin_mode(ledPin, OUTPUT)
pin_mode(buttonPin, INPUT)

# set pin to high level aka pull it 'up'
pin_control(buttonPin, mode = "up")

# endless loop
repeat {
	if ( read_digital(buttonPin) == LOW ) {
		
		write_digital(ledPin, HIGH)
		cat("\rled on... ")
		
	} else {
	
		write_digital(ledPin, LOW)
		cat("\r...led off")
	
	}
}


