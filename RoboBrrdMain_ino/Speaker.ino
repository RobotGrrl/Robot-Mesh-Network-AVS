
void randomChirp() {
    for(int i=0; i<10; i++) {
        playTone((int)random(100,800), (int)random(50, 200));
    }
}


void playTone(int tone, int duration) {
	
	for (long i = 0; i < duration * 1000L; i += tone * 2) {
		digitalWrite(spkr, HIGH);
		delayMicroseconds(tone);
		digitalWrite(spkr, LOW);
		delayMicroseconds(tone);
	}
	
}

