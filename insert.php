<?php
require "db.php";
$data = json_decode(file_get_contents("php://input"), true);

$suhu = $data['esp_suhu'] ?? null ;
$kelembapan = $data['esp_kelembapan'] ?? null ;
$query = "INSERT INTO datasensor (esp_suhu, esp_kelembapan) VALUES ('$suhu', '$kelembapan')";

if ($koneksi -> query($query)){
    echo json_encode("data sudah masuk - suhu : $suhu, kelembapan : $kelembapan");
}else {
    echo json_encode("error DB : ".$koneksi -> error);
}