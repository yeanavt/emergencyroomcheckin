# ER Check-In Using Singly Connected Linked Lists — README

## Overview

This single-file HTML dashboard is a teaching tool for a **18-minute demo** on singly-linked lists, sorted insertion (priority queues), and embedded ethics in computer science. It accompanies a C++ program (`ERmanager`) that simulates an Emergency Room patient check-in system where patients are prioritized by self-reported pain level.

The dashboard is designed to be opened in any modern browser — no installation, no dependencies, no server required. Just open `er_teaching_dashboard.html` and present.

---

## Layout

The dashboard is split into two independently scrollable panels with a **draggable divider** between them.

### Left Panel — Pointer Trace Visualizer (dark theme)

Steps through each `check_in()` call sub-step by sub-step. For every press of the Next button, you see:

- The **exact line of C++ code** being evaluated
- A plain-English description of what the code does and why
- The **linked list** rendered as node boxes with `data` and `next` fields
- **`compare`** (pink label above the node) and **`compare2`** (green label below the node) pointer positions
- A **floating badge** showing the new node waiting to be inserted
- **Console output** matching what the actual C++ program would print

Six main steps are available via tabs: Init, Jack(5), Jose(6), Chris(10), Mary(6), and Jay(2).

### Right Panel — Logic Flowchart (light theme)

A complete flowchart of the `check_in()` method's branching structure. Every decision diamond, action box, and loop body is labeled with its **source code line number**. Six highlight buttons let you isolate the path taken by each patient:

| Button    | Color  | Path                                         |
|-----------|--------|----------------------------------------------|
| All       | —      | Shows every branch                           |
| Reject    | Red    | Validation failure → return false (Line 86)  |
| Jack      | Green  | Empty list → Case 2: becomes head (Line 91)  |
| Jose(6)   | Blue   | Pain > head → Case 3a: new head (Line 107)   |
| Chris(10) | Orange | Pain > head → Case 3a: new head (Line 107)   |
| Mary      | Purple | While-loop traversal → Case 3b-i: mid-list (Line 126) |
| Jay       | Teal   | While-loop to tail → Case 3b-ii: append (Line 136)    |

---

## Controls

| Control             | Action                                                 |
|---------------------|--------------------------------------------------------|
| ← → Arrow Keys     | Step backward/forward through the pointer trace        |
| ◀ ▶ Buttons         | Same as arrow keys                                     |
| Patient Tabs (left) | Jump to a specific patient's check-in sequence         |
| Path Buttons (right)| Highlight a specific patient's path on the flowchart   |
| Center Divider      | Click and drag to resize panels                        |

**Auto-sync:** As you step through the left panel, the flowchart on the right automatically highlights the corresponding path.

---

## Files in This Package

| File | Description |
|------|-------------|
| `er_teaching_dashboard.html` | The combined side-by-side dashboard (this is the main file) |
| `ERmanager_commented.cpp` | The original C++ code with line-by-line comments on every line |
| `er_pointer_trace_visualization.html` | Standalone version of the left panel |
| `checkin_logic_flowchart.html` | Standalone version of the right panel |

---

## Suggested 20-Minute Demo Flow

**Minutes 1–3: Orient students.**
Open the dashboard. Briefly explain the ER scenario: patients check in with a name and a pain level (1–10), and the system maintains a sorted linked list where higher pain = higher priority.

**Minutes 3–8: Walk through the code structure.**
Use the left panel to step through Jack (empty list insertion) and Jose (insert at front). Ask foundational questions like "What is `struct PatientInfo` for?" and "Why does `check_in()` need two pointers?"

**Minutes 8–15: Trace the interesting insertions.**
Step through Mary (full while-loop traversal with `compare`/`compare2` leapfrogging through the list) and Jay (traverses to the tail and appends). Use the flowchart on the right to show which branch of the code fires at each decision point.

**Minutes 15–20: Pivot to ethics.**
With the final list visible (Chris 10 → Jose 6 → Mary 6 → Jack 5 → Jay 2), ask: "Is a single self-reported pain integer a fair way to prioritize patients?" This connects to the embedded ethics framework from Farghally, Seyam, and Ellis (ITiCSE 2025) — specifically the CS3 priority queue ethics assignment about discrimination in queuing systems.

---

## Ethics Discussion Prompts

These questions bridge the technical content to ethical reasoning:

1. **Subjectivity of pain:** Some patients overreport; others (elderly, non-English speakers, children) underreport. Who gets systematically disadvantaged?
2. **Single-factor sorting:** Real triage uses vitals, age, medical history, and nurse assessment. What happens when you reduce urgency to one integer?
3. **Privacy vs. safety:** The system stores only first names. Is minimal data a privacy win or an identification risk?
4. **FIFO among ties:** Jose(6) stays ahead of Mary(6) because he arrived first. Is arrival order always fair?
5. **Pay-for-priority:** If a hospital added +3 to paying patients' pain scores, would that be ethical?
6. **Developer responsibility:** Where does your ethical responsibility begin and end as the person who wrote the sorting algorithm?

---

## Technical Notes

- **Pure HTML/CSS/JS** — no frameworks, no build step, no external dependencies beyond two Google Fonts (JetBrains Mono, DM Sans, Instrument Serif). Works offline if fonts are cached.
- **Responsive divider** — drag to resize; on screens under 900px wide the panels stack vertically.
- **Keyboard accessible** — arrow keys navigate the pointer trace.
- Tested in Chrome, Firefox, Safari, and Edge.

---

## Source Context

This dashboard supports a teaching demo inspired by:

> Farghally, M., Seyam, M., & Ellis, M. (2025). *Embedded Ethics in CS: Experiences with Integrating Ethics Assignments in Sophomore, Junior, and Senior Level Courses.* Proceedings of the 30th ACM Conference on Innovation and Technology in Computer Science Education (ITiCSE 2025). https://doi.org/10.1145/3724363.3729054

The C++ code simulates a priority queue via singly connected (and sorted) linked-list insertion.
