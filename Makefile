# Configuration
ARDUINO_CLI = arduino-cli
BOARD_TYPE = arduino:avr:uno
SERIAL_PORT = /dev/ttyACM0

.PHONY: upload

upload:
	$(ARDUINO_CLI) compile -v -b $(BOARD_TYPE) -u -p $(SERIAL_PORT) $(shell pwd)/$(p)

