
void moveBeak(int destination, int stepDelay, int doneDelay) {
	
	mouth.attach(8);
	
	int current = mouth.read();
	
	if(current > destination) {
		
		for(int i=current; i>destination; i--) {
			mouth.write(i);
			delay(stepDelay);
		}
		
	} else if(current < destination) {
		
		for(int i=current; i<destination; i++) {
			mouth.write(i);
			delay(stepDelay);
		}
		
	}
	
	mouth.detach();
	delay(doneDelay);
	
}

void openBeak() {
	int stepDelay = 10;
	int doneDelay = 50;
	moveBeak(90, stepDelay, doneDelay);
}

void underbiteCloseBeak() {	
	int stepDelay = 10;
	int doneDelay = 50;
	moveBeak(0, stepDelay, doneDelay);
}

void overbiteCloseBeak() {
	int stepDelay = 10;
	int doneDelay = 50;
	moveBeak(180, stepDelay, doneDelay);
}


void peck() {
	moveBeak(10, 5, 50);
	moveBeak(30, 5, 50);
}

void randomBeak() {
	moveBeak((int)random(0, 180), 5, 50);
}

