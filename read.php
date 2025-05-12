<?php
header('Content-Type: application/json');
header('Access-Control-Allow-Origin: *');

include "db.php";

$sql = mysqli_query($koneksi, "SELECT esp_suhu, esp_kelembapan, waktu FROM datasensor ORDER BY id DESC LIMIT 1");

$data = mysqli_fetch_assoc($sql);

if ($data) {
    echo json_encode([
        'temperature' => number_format((float)$data['esp_suhu'], 1) . '°C',
        'humidity' => number_format((float)$data['esp_kelembapan'], 0) . '%',
        'timestamp' => $data['waktu']
    ]);    
} else {
    echo json_encode(['error' => 'no data found']);
}
