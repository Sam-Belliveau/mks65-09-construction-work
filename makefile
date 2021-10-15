
CC=gcc
BIN=./bin
OUT=$(BIN)/construction

all: $(OUT)

$(OUT): main.c $(BIN)
	$(CC) main.c -g -o $(OUT)

$(BIN): 
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)

run: $(OUT)
	$(OUT)

debug: $(OUT)
	lldb $(OUT)
