.PHONY: clean build

clean:
	@echo "Cleaning..."
	@rm -rf build

build: clean
	@echo "Building..."
	@mkdir -p build
	@cd build && cmake .. && cmake --build .

all: build

.DEFAULT_GOAL := all
