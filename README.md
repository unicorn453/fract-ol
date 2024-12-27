# Fractol: Explore Fractals with MinilibX

## About the Project

This project is a graphical application built using **MinilibX** from the 42 School. It allows you to explore three types of fractals on your local machine:

1. Mandelbrot Set
2. Julia Set
3. Burning Ship

Each fractal offers unique patterns and intricacies that can be explored interactively, giving you a deep dive into the beauty of fractal geometry.

---

## Getting Started

### Prerequisites

To run this project, you need:

- A Unix-based system (e.g., macOS or Linux)
- A terminal
- `make` utility installed

### Installation

1. Clone this repository:
   ```bash
   git clone <repository_url>
   ```
2. Navigate into the project folder:
   ```bash
   cd <project_folder>
   ```
3. Build the project:
   ```bash
   make
   ```

---

## Usage

To run the program, execute the following command in the terminal:

```bash
./fractol <type_of_fractal> [julia_parameter]
```

### Arguments

- `<type_of_fractal>`: Specify the fractal type (`mandelbrot`, `julia`, or `burning_ship`).
- `[julia_parameter]`: If you choose `julia`, you must provide a complex number parameter (e.g., `0.355+0.355i`) to generate the fractal.

### Example:

```bash
./fractol julia 0.355 0.355
```

---

## Controls

| **Key**        | **Action**                 |
| -------------- | -------------------------- |
| Scroll (Mouse) | Zoom in and out            |
| Arrow Keys     | Move the view              |
| Numbers (1-7)  | Change colors              |
| `R`            | Reset to the initial state |
| `ESC`          | Exit the window            |

---

## Features

- **Zoom and Pan**: Explore fractals in greater detail by zooming in with the mouse scroll and panning with arrow keys.
- **Dynamic Coloring**: Change the fractal's colors using numeric keys (1-7).
- **Reset View**: Revert the fractal to its initial state by pressing `R`.
- **Enhanced Details**: As you zoom in, the fractal's details become more prominent due to increased iterations.

---

## Screenshots

Below are some screenshots showcasing the fractals:

### Mandelbrot Set
![Mandelbrot Set](images/mandelbrot.png)

### Julia Set
![Julia Set](images/julia.png)

### Burning Ship
![Burning Ship](images/burning_ship.png)

---


## Acknowledgments

- **MinilibX**: Graphics library provided by the 42 School.
- **42 School**: For introducing and supporting this project.

---

## License

This project is open-source and available under the [MIT License](LICENSE).

