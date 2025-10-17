Description:
As a student with a background in biomedicine, I wanted my CS50 final project to connect computer science with human physiology — something that can demonstrate how programming can help understand and visualize biomedical data.
For this reason, I decided to build a Blood Pressure Analyzer, a simple C and Python–based program that simulates how biomedical data can be collected, classified, and analyzed.
The program allows the user to enter multiple blood pressure measurements — including systolic, diastolic, and optionally heart rate. It then classifies each measurement according to the international hypertension stages (based on European Society of Hypertension guidelines), calculates additional derived parameters like pulse pressure (PP) and mean arterial pressure (MAP), summarizes the results, and finally exports the data to a CSV file.
A separate Python visualization script then reads this CSV file and produces a clear time-series plot of the measured values, saving it as a PNG image.
This combination of C for data processing and Python for data visualization was chosen intentionally, as it reflects how many biomedical systems are built in practice — a lower-level component for fast data collection and computation, and a higher-level component for visualization and reporting.
Background: Understanding Blood Pressure
Blood pressure is one of the most fundamental indicators of cardiovascular health. It represents the force that circulating blood exerts on the walls of arteries. It is typically expressed using two values:
•	Systolic pressure (SYS) – the higher number, representing the pressure in the arteries when the heart contracts and pumps blood.
•	Diastolic pressure (DIAS) – the lower number, representing the pressure in the arteries when the heart relaxes between beats.
A typical healthy value might be written as 120/80 mmHg. Both numbers are important, and their relationship provides valuable insight into the function of the cardiovascular system.
When blood pressure is consistently above the normal range, it indicates hypertension, which is a major risk factor for heart attack, stroke, and kidney disease. On the other hand, values that are too low can signal hypotension, which might cause dizziness or fainting.
Monitoring, classifying, and interpreting these numbers is therefore crucial — and this project demonstrates how code can help automate that process.

How the Program Works
The project consists of two main parts:
1. Data Collection and Analysis (C language)
The C program runs in the terminal. It asks the user:
“How many measurements do you want to enter?”
For each measurement, the user inputs:
SYS/DIA HR
For example: 128/82 72
Heart rate (HR) is optional — if omitted, it is stored as zero.
Each value is validated (no negative or unrealistically low numbers are allowed), and then the program determines the blood pressure category based on these thresholds:
Category	Systolic (mmHg)	Diastolic (mmHg)
Normal	< 130	< 85
High Normal	130–139	85–89
Stage I Hypertension	140–159	90–99
Stage II Hypertension	160–179	100–109
Stage III Hypertension	≥ 180	≥ 110


For each day, the program also computes two derived biomedical values:
•	Pulse Pressure (PP) = SYS − DIAS
→ This represents the difference between systolic and diastolic pressure.
A normal PP is around 40 mmHg. Very high pulse pressure can indicate stiff arteries or other cardiovascular issues.
•	Mean Arterial Pressure (MAP) = (SYS + 2 × DIAS) / 3
→ This is an estimate of the average arterial pressure throughout one heartbeat cycle.
MAP provides a good indicator of how well blood is flowing to organs. Typical values are around 90–100 mmHg in healthy adults.
After processing all measurements, the program displays the category for each day (for example, Stage I Hypertension | PP=45 | MAP=107.5), and prints a summary counting how many results fall into each group.
All data — including SYS, DIAS, HR, PP, MAP, and category — are then exported to a file called readings.csv. The CSV file is easy to read in other programs like Excel or MATLAB, but here it serves as an input for the Python visualization script.
2. Data Visualization (Python script)
The Python part of the project is a simple but elegant way to turn numbers into meaningful graphics. It reads the CSV file and extracts the columns for day, systolic, and diastolic pressures. Using the matplotlib library, it plots both curves on a single graph, with markers at each measurement point.
The script runs in non-interactive mode (using matplotlib.use("Agg")), so it doesn’t open a window — instead, it automatically saves the resulting image into an out/ folder as a file called bp_timeseries.png.
If the folder doesn’t exist, it is created automatically.
The final graph clearly shows the trend of blood pressure over time, making it easy to visualize whether the values are stable, rising, or fluctuating.
This part of the project demonstrates how Python is often used in biomedical engineering — not for the data collection itself, but for data analysis and visualization, which is key for interpreting medical results.
