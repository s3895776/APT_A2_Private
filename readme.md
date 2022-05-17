[![Unit-Tests](https://github.com/themarcusmin/APT_A2/actions/workflows/unit-tests.yaml/badge.svg)](https://github.com/themarcusmin/APT_A2/actions?query=workflow%3AUnit-Tests)
[![Integration-Tests](https://github.com/themarcusmin/APT_A2/actions/workflows/integration-tests.yaml/badge.svg)](https://github.com/themarcusmin/APT_A2/actions?query=workflow%3AIntegration-Tests)

# Scrabble

A c++ implementation of the board-game scrabble.

## Building/Running
The program can be made with `make scrabble` and will be built to ./scrabble

## Testing

### Integration Tests
Per the assignment specifications a number of integration tests can be found in the ./tests/ directory.
The testname.input files are passed as cin input to the program, and the game output is writen to testname.gameout, which is to be compared with testname.output.

They can be run individually, or for convenience there is a runTests.bash file to run them all and report the results.


### Unit Tests
In addition to the integration tests, unit-test cpp files can also be found in the ./tests/ directory.\
These test methods exist to test methods in isolation and without needing to diff output.

The unit-tests can be made with `make all` or `make Testing`.
And the binary to run the unit test will be built to ./Testing.

## Team
- Dan Podbury (s3881206)
- Guo An Liew (s3895776)
- Kerubo Ndubi (s3844734)
- Min Min Oo (s3860838)
