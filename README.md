# Drone Mission

For this project, we created a control system for a drone. This system will allow a user
to effectively operate a remote-controlled drone from a computer. Every aspect required to
develop a full control system will be made during this project. Those crucial elements are the
following: 1) Firmware, 2) Backend Software, 3) Frontend, and 4) Simulation Software.

## Firmware
The Firmware will be the code running on the drone's microcontroller. It will have the ability to
listen to, parse, and handle incoming packets from the Backend Software (2). If deemed
appropriate, the Firmware code will also have the ability to transmit packets back to the
operator's machine.

## Backend Software
The Backend code will contain several modules required for this control system to work
properly. Firstly, a drone module will be created which will contain all required attributes (such as
latitude, longitude, and altitude) and peripherals (such as motors and LEDs) that the drone will
require. Furthermore, all of the drone functionality (such as movement commands) will be
programmed here.

In addition, a Controls module will be made. This module will contain classes that will be
responsible for handling user input from various devices (such as a keyboard and a video game
controller). The ability to remap different buttons on the user's controller will be built in and
utilized by the Frontend (3). Also within this module will be code to translate user data into
recognizable packets and code to send those packets to the drone.

## Frontend
The Frontend will contain a nice graphical user interface for the operator of the drone to use.
The GUI will display relevant data to the operator and will aid the operator in performing different
tasks (such as remapping controls). This application will be running the Backend (2).

## Simulation Software
The Simulation will contain a digital render of a drone and a basic environment. The drone
model will respond to user input in real-time, providing the operator with visual feedback.
Depending on development, the simulation will either be a standalone application or will be tied
in with the Frontend (3) application.

Key role:
- Collaborated on a 12-member Scrum team specializing in frontend, backend, simulation, and firmware development.
- Led implementation of drone controls and a custom JavaFX Web engine, showcasing expertise in backend drone development.
- Key contributor in merging code across teams, serving as the main point of contact for seamless project cohesion


https://github.com/AT1XX/Drone-mission/assets/119278828/d648dcd2-016a-4bd8-9ea0-500aa4ee06a6

