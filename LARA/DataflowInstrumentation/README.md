# Dataflow Instrumentation

LARA aspect to instrument code in order to produce a dataflow execution trace

## How to use

The name of the function to instrument must be configured as a parameter, e.g. {"fun": "name"}, on the configuration file

## Known bugs

- Constants on the right hand side of operations whose left hand side is another operation do not get assigned the right counter
- Closing bracket for the graph is not generated when the function has a return statement
- Most unary operators are not yet supported, with the exception of pre/post increment/decrement
- Function calls are not yet supported

The .dot file can be easily modified to accomodate these bugs after generation