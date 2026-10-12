# Linear Regression

Fits a straight line `y = m·x + b` to 2D data in two ways and compares them:

- **Closed form**: the exact least-squares solution, worked out with algebra in one pass. It serves as the answer key.
- **Gradient descent**: starts at `m = 0, b = 0` and keeps stepping downhill on the mean squared error until it reaches the same line.

Before descending, the x values are standardized to z-scores (`(x − mean) / std`). This keeps the steps well-conditioned, and the fitted `m` and `b` are converted back to the original scale afterwards.

## Build

Needs a C++17 compiler and `make`.

```sh
make          # builds ./regression
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # full rebuild
```

## Usage

```sh
./regression [file.csv]
```

With no argument it reads `./data.csv`.

### Input format

One point per line, as `x,y`, with no header row:

```
1.0,7.0
2.0,9.0
3.5,12.0
```

At most 25 points are read (`MAX_POINTS` in `data.hpp`).

### Example

`test_line.csv` contains points that lie exactly on `y = 2x + 5`:

```
$ ./regression test_line.csv
file: test_line.csv    points: 10

closed form
  m = 2.0000    b = 5.0000

gradient descent  (alpha 0.0100, 500 iterations)
  iter 0  loss 303.0000  m 0.0000  b 0.0000
  ...
  iter 475  loss 0.0000  m 5.8340  b 16.3989
  m = 1.9999    b = 4.9998

gap
  m off by 0.0001
  b off by 0.0002

prediction at x = 1.0000
  closed form      7.0000
  gradient descent 6.9997
  actual           7.0000
```

The `m` and `b` values in the iteration log are in z-score space. They're converted back to the original scale when descent finishes.

## Tuning

The learning rate and iteration count are set in `gradient_descend.hpp`:

```cpp
const int    DEFAULT_ITER  = 500;
const double DEFAULT_ALPHA = 0.01;
```

You can also pass them directly with the `gradient_descend(data, alpha, iterations, verbose)` constructor.

## Files

| File | Purpose |
| --- | --- |
| `main.cpp` | Loads the CSV, runs both fits, prints the comparison |
| `data.hpp/.cpp` | CSV parser (`parseCSV`) |
| `linear_regression.hpp/.cpp` | Closed-form least-squares fit |
| `gradient_descend.hpp/.cpp` | Gradient-descent fit with z-score scaling |
| `data.csv` | Default sample dataset (25 points) |
| `test_line.csv` | Points on `y = 2x + 5`, useful for sanity checks |
