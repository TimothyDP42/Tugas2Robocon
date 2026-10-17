# Tugas Magang Robocon 2 : Turtle Saw
Projek ROS2 kecil yang menjalankan TurtleSim untuk menggambar sebuah bilah gergaji berbentuk melingkar

# Cara Kerja
Pertama, program akan _teleport_ ke titik terendah x,y lingkaran, dan mulai menggambarnya berarahan jarum jam. Pusat dari semua lingkaran ini ada di daerah (5.5, 5.5).
Untuk lingkaran pertama, program akan menghasilkan lingkaran berdiameter 1 meter dalam durasi 2 sekon. Selanjutnya, program akan membuat lingkaran yang berdiameter 4 meter selama 2 sekon.
Terakhir, program akan mengikuti outline sebuah lingkaran berdiameter 6 meter, bergerak sejauh 0.5 meter ke arah pusat, dan diteleportasi pada posisi selanjutnya pada setiap 1/18 bagian lingkaran, alhasil jeruji tajam.
