# CPS Term Project: Global Temperature Analysis

Miikka11212's C course project for analyzing monthly records in `GlobalTemperatures.csv`. The original `final.c` functions and `main()` structure are preserved.

## Files

| File | Purpose |
| --- | --- |
| `final.c` | Original analysis functions for questions 1–11 |
| `GlobalTemperatures.csv` | Monthly input data, 1750–2015 |
| `question6.gnu`, `question7.gnu`, `question8.gnu` | Annual-temperature plotting scripts |
| `q11.gnu`, `q11.txt` | Land / combined land-and-ocean plot and saved data |
| `gnu/q9.gnu`, `gnu/2q9.txt` | Century comparison plot and saved data |

## Build and run

Use GCC on Linux/macOS or a compatible MinGW environment on Windows. The original source uses `unistd.h` and `chdir`.

```sh
gcc final.c -o final
./final
```

On Windows, compile with `gcc final.c -o final.exe` and run `.\final.exe`.

The original `main()` currently has all analysis calls commented out, so the program produces no analysis as committed. To run a question, enable the relevant function call and update or remove `chdir("/Users/miikka/Desktop/CPS/")` to match the dataset location.

- `question1256()` handles annual averages, hottest/coldest years, and question 6 data.
- `question2()` computes century averages.
- `question3()` computes monthly averages for 1900–2015.
- `question4()` finds the hottest and coldest months.
- `question7()` through `question11()` write data for the corresponding plots.

## Plotting

Gnuplot is optional. After generating matching data, run a script from the repository root:

```sh
gnuplot -persist question7.gnu
gnuplot -persist q11.gnu
```

Some original output filenames differ from the script inputs:

- Question 6 writes `Question6.dat`; its plot reads `Question6.txt`.
- Question 9 writes `q9.dat`; its plot reads `q9.txt`. Saved reference data is `gnu/2q9.txt`.
- Question 11 writes `gnu/q11.txt`; its plot reads root `q11.txt`.

Align those filenames when running the relevant plot. Saved data is historical output, not a newly verified result. The question 11 series labeled ocean is actually the combined land-and-ocean temperature.

## Project status

This repository preserves the original coursework implementation. Calculations remain unverified, including missing CSV-value handling and question 9 accumulation/iteration issues. The assignment specification and the dataset's original source/license were not recorded in the repository.

## Cleanup

Superseded source experiments, compiled binaries, debugger bundles, machine-specific editor settings, scratch files, and unused generated data were removed. Previous files remain recoverable from Git history. `.gitignore` excludes build artifacts and generated `.dat` files. The trailing space in the question 6 script filename was removed to support Windows checkout; script contents are unchanged.

Author: Miikka11212. Educational CPS course term project.
