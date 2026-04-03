# Configuration
ARDUINO_CLI = arduino-cli
BOARD_TYPE = arduino:avr:uno
SERIAL_PORT = /dev/ttyACM0

.PHONY: create upload

# make create s=<sketch name>
create:
	$(ARDUINO_CLI) sketch new $(s)

# make upload s=<sketch name>
upload:
	$(ARDUINO_CLI) compile -v -b $(BOARD_TYPE) -u -p $(SERIAL_PORT) $(s)

