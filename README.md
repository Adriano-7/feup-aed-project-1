# Schedule Management System (Gestão de Horários)

> **Project**
> <br />
> Course Unit: [Algorithms and Data Structures (AED)](https://sigarra.up.pt/feup/pt/UCURR_GERAL.FICHA_UC_VIEW?pv_ocorrencia_id=501673), 2nd year
> <br />
> Course: Degree in Informatics and Computing Engineering (LEIC)
> <br />
> Faculty: **FEUP** (Faculty of Engineering of the University of Porto)
> <br />
> Project Guidelines: ([PDF](https://github.com/Adriano-7/trabalho_AED/files/9933280/aed2223_trabalho1.pdf))
> <br />
> Project evaluation: **19**/20

---

## Project Goals

This project aims to develop a schedule management system in **C++** capable of showing and modifying the schedules of university students. The core challenge was to choose the most appropriate and efficient data structures to handle thousands of records.

## Features

The application provides an interactive terminal menu allowing users to:
1. **View Data:**
   * Check the schedule of a specific student, class, or Curricular Unit (UC).
   * Check the students enrolled in a specific class or UC (with multiple sorting options).
2. **Submit Requests:**
   * Submit a request to change a class (`Changing`).
   * Submit a request to enroll in a new UC (`Enrollment`).
   * Submit a request to cancel a UC registration (`Removal`).
3. **Process Requests:**
   * View all pending requests.
   * Process the queue of requests based on strict validation rules.
   * Save the updated state back into the system files (`students_classes.csv`).

## Running the code

**Prerequisites:** You need `CMake` and a C++ compiler (supports C++14).

**Setup & Compilation:**
```bash
git clone https://github.com/Adriano-7/trabalho_AED.git
cd trabalho_AED
mkdir build && cd build
cmake ..
make
```

**Run the application:**
```bash
./trabalho
```
*(Note: The application uses `system("clear")` to clean the terminal, which works best in native Unix/Linux terminals rather than integrated IDE terminals like CLion).*

## Tech stack
- **C++14**: Core application logic.
- **STL**: `set`, `vector`, `map`, `queue`.
- **CMake**: Build system.
- **Doxygen**: API documentation generation.

## Team

- Adriano Machado
- Francisco Pires da Ana
- José Pedro Evans
