# Azirka: A* Pathfinding Visualizer

A lightweight, real-time interactive console visualizer for the **A* Search Algorithm** written in C++. The pathfinder recalculates dynamically based on event-driven inputs, providing instant feedback as you modify the grid map.

## Features

* **Real-time Dynamic Recalculation:** The path updates instantly when moving the cursor or drawing barriers without cold-looping the CPU.
* **8-Way Movement Support:** The algorithm correctly calculates straight steps (cost = 10) and diagonal steps (cost = 14).
* **Optimized Priority Queue:** Built utilizing C++ standard structures (`std::priority_queue`) to guarantee efficient node selections (log n).
* **Edge-case Protection:** Full safety validation ensuring the engine never enters infinite loops if the path is completely blocked.

## Controls

Navigate across the simulation field using your keyboard. The system updates event-by-event:

| Key | Action |
| :--- | :--- |
| W / A / S / D or Arrow Keys | Move selection cursor around the map |
| Space / Enter | Toggle Wall (#) / Empty cell (.) |
| Esc | Quit the application |

## Installation & Compilation

Since this program relies on standard Windows terminal headers, it is designed to run natively on **Windows OS**.

1. Open your terminal in the project folder and compile the code:
   bash
   g++ -O3 Azirka.cpp -o Azirka.exe


2. Run the application:

  ./Azirka.exe
