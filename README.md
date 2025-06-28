# 🌍 CPS Term Project: Global Temperature Data Analysis

This project analyzes historical global temperature data using a C program. It reads a CSV file containing temperature records from various regions of the Earth and answers a series of structured climate-related questions based on a course lab manual.

## 📁 Features

- Parses and processes global temperature data from CSV files
- Answers climate-related questions using basic data analysis
- Generates result outputs as text files and gnuplot-compatible scripts
- Modular C code structure for different parts of the analysis

## 🧰 Tech Stack

- C Programming Language
- Gnuplot (for data visualization)
- Standard C Libraries (`stdio.h`, `stdlib.h`, etc.)

## 📂 Project Structure

```
CPS_Term_Project/
├── GlobalTemperatures.csv      # Input dataset
├── final.c                     # Main logic for solving questions
├── print_csv.c                 # CSV parsing and output formatting
├── questionX.gnu / qX.txt      # Gnuplot scripts and result files for each question
├── MAYBE_WORK.c / assignment.c # Alternate versions of analysis code
├── output/                     # Directory for output results
├── stuff/, temp/               # Additional utility folders
└── README.md                   # This file
```

## 🚀 How to Run

1. **Compile the code** (example for `final.c`):
   ```bash
   gcc final.c -o final
   ```

2. **Run the executable**:
   ```bash
   ./final
   ```

3. **View the output**:
   - Check the generated `.txt` or `.gnu` files
   - Use `gnuplot` to visualize results:
     ```bash
     gnuplot q11.gnu
     ```

## 📊 Sample Output

Outputs include statistical data and trends extracted from the global temperature dataset, formatted as text and plotted graphs.

## 📌 Notes

- Ensure you have `gnuplot` installed for visualizations.
- The input CSV file must be named `GlobalTemperatures.csv` and be in the root directory.

## 🧑‍💻 Author

Miikka11212

---

For educational use as part of the CPS course term project.
