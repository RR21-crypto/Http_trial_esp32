# ESP32 IoT Dashboard with PHP & MySQL

## Simple IoT Dashboard Trial Project

This project serves as a starting point for my exploration into building an IoT monitoring system using an ESP32 microcontroller, a PHP web server, and a MySQL/MariaDB database. The primary goal is to learn how to wirelessly send data from a microcontroller to a local server, store it in a database, and display it on a dynamically updating web page.

While this is an initial learning project, its architecture has the potential to be extended and scaled for more complex IoT applications.

## Features

*   Collects data (simulated temperature and humidity in this example) from an ESP32.
*   Sends sensor data wirelessly via WiFi using HTTP POST requests.
*   Stores the received data into a MySQL/MariaDB database.
*   Provides a simple web dashboard interface to display the latest sensor readings.
*   The dashboard automatically fetches and updates with the latest data from the database periodically using JavaScript (AJAX/Fetch API).
*   Basic user interface styling using Tailwind CSS.

## Technologies Used

*   **Hardware:** ESP32
*   **Framework:** Arduino Framework
*   **Connectivity:** WiFi
*   **Protocol:** HTTP
*   **Server-side:** PHP
*   **Database:** MySQL / MariaDB (Compatible)
*   **Frontend:** HTML, CSS, JavaScript
*   **Styling:** Tailwind CSS (via CDN)
*   **Arduino Libraries:**
    *   `WiFi.h`
    *   `HTTPClient.h`
    *   `ArduinoJson.h`

## Project Structure

your-project-folder/
├── esp32_sketch/
│   └── esp32_iot_sender.ino  # ESP32 code
└── webserver/
└── iot-dashboard/        # Place this folder in your web server's root directory (e.g., xampp/htdocs)
├── index.html        # Main dashboard web page
├── insert.php        # PHP script to receive & store data from ESP32
├── read.php          # PHP script to read the latest data from the database
└── db.php            # PHP script for database connection



## Database Setup

You need to set up a database and a table on your MySQL/MariaDB server (e.g., using phpMyAdmin).

1.  Create a new database named `iot_data`.
2.  Inside the `iot_data` database, create a table named `datasensor` with the following structure:

    ```sql
    CREATE TABLE `datasensor` (
      `id` INT(11) NOT NULL AUTO_INCREMENT,
      `esp_suhu` TINYTEXT DEFAULT NULL,
      `esp_kelembapan` TINYTEXT DEFAULT NULL,
      `waktu` TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
      PRIMARY KEY (`id`)
    ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
    ```

    *   Ensure the `id` column is set as `AUTO_INCREMENT` and is the `PRIMARY KEY`.
    *   The `waktu` column is set to automatically record the timestamp.

## Code Setup

1.  **ESP32 Sketch (`esp32_iot_sender.ino`):**
    *   Open the sketch in your Arduino IDE (or preferred IDE like VS Code + PlatformIO).
    *   Update the WiFi credentials:
        ```cpp
        const char* ssid = "YOUR_WIFI_SSID";
        const char* password = "YOUR_WIFI_PASSWORD";
        ```
    *   Update the `server` variable with the correct IP address of your computer running the web server (XAMPP). Ensure it's the IPv4 address obtained from `ipconfig` when connected to the *same* network as the ESP32.
        ```cpp
        String server = "http://YOUR_COMPUTERS_IP_ADDRESS/iot-dashboard/insert.php";
        ```
    *   Compile and upload the sketch to your ESP32.

2.  **Webserver Files (`iot-dashboard/`):**
    *   Place the `iot-dashboard` folder inside your web server's root directory (e.g., `C:\xampp\htdocs\`).
    *   Edit `db.php` to ensure the database connection details are correct (database name, username, password - default XAMPP is `root` with no password).
    *   Ensure your web server (Apache in XAMPP) is running.

## Usage

1.  Ensure your ESP32 is powered on and connected to WiFi.
2.  Ensure your web server (XAMPP) is running Apache and MySQL.
3.  Open a web browser and navigate to `http://localhost/iot-dashboard/` or `http://YOUR_COMPUTERS_IP_ADDRESS/iot-dashboard/`.
4.  The dashboard should load and start displaying the latest data fetched from the database every second.

## Potential Enhancements

*   Implement reading from actual sensors (DHT11/DHT22 for Temp/Humidity).
*   Add support for different sensor types and data points.
*   Add user authentication for the dashboard.
*   Set up remote access (e.g., using MQTT or hosting the web server publicly with proper security).
*   Add data visualization features (charts, graphs) using libraries like Chart.js.
*   Improve error handling and add logging.
*   Develop a more sophisticated and responsive user interface.
*   Add controls to send commands back to the ESP32.

This project provides a solid foundation for further learning and building more complex IoT applications. Feel free to fork, modify, and expand upon it!
